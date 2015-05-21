#lang plai-typed
(define-type ArithC
   [numC  (n : number)]
   [plusC (l : ArithC) (r : ArithC)]
   [multC (l : ArithC) (r : ArithC)])

(define-type ArithS
  [numS    (n : number)]
  [multS   (l : ArithS) (r : ArithS)]
  [plusS   (l : ArithS) (r : ArithS)]
  [bminusS (l : ArithS) (r : ArithS)]
  [uminusS  (e : ArithS)])

(define (parseS [s : s-expression]) : ArithS
  (cond
    [(s-exp-number? s)
     (numS (s-exp->number s))]
    [(s-exp-list? s)
     (let ([s1 (s-exp->list s)])
       (case (s-exp->symbol (first s1))
         [(+) (plusS (parseS (second s1)) (parseS (third s1)))]
         [(*) (multS (parseS (second s1)) (parseS (third s1)))]
         [(-) (cond 
                [(equal? (length s1) 3) (bminusS (parseS (second s1)) (parseS (third s1)))]
                [(equal? (length s1) 2) (uminusS (parseS (second s1)))]
                [else (error 'parseS "invalid minus")])
         ]
         [else (error 'parseS "invalid list input")]))]
    [else (error 'parseS "invalid input")]))

(define (interp [a : ArithC]) : number
  (type-case ArithC a
    [numC (n)  n]
    [plusC (l r) (+ (interp l) (interp r))]
    [multC (l r) (* (interp l) (interp r))]))

(define (desugar [s : ArithS]) : ArithC
  (type-case ArithS s
    [numS (n) (numC n)]
    [plusS (l r) (plusC (desugar l) (desugar r))]
    [multS (l r) (multC (desugar l) (desugar r))]
    [bminusS (l r) (plusC (desugar l) (multC (numC -1) (desugar r)))]
    [uminusS (e) (multC (numC -1) (desugar e))]))

(define (interpS [s : ArithS]) : number
  (interp (desugar s)))



(test (interpS (parseS '(- 1))) -1)
