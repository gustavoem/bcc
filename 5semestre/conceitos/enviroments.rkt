#lang plai-typed
(define-type FunDefC
  [fdC (name : symbol) (arg : symbol) (body : ExprC)])

(define-type Binding
  [bind (name : symbol)  (val : number)])

(define-type-alias Env (listof Binding))
(define mt-env empty)
(define extend-env cons)

(define-type ExprC
  [numC (n : number)]
  [idC (s : symbol)]
  [appC (fun : symbol) (arg : ExprC)]
  [plusC (l : ExprC) (r : ExprC)]
  [multC (l : ExprC) (r : ExprC)]
  [ifC (c : ExprC) (s : ExprC) (n : ExprC)])

(define-type ExprS
  [numS (n : number)]
  [idS (s : symbol)]
  [appS (fun : symbol) (arg : ExprS)]
  [plusS (l : ExprS) (r : ExprS)]
  [multS (l : ExprS) (r : ExprS)]
  [bminusS (l : ExprS) (r : ExprS)]
  [uminusS (e : ExprS)]
  [ifS (c : ExprS) (s : ExprS) (n : ExprS)])

(define (desugar [as : ExprS]) : ExprC
  (type-case ExprS as
    [numS (n) (numC n)]
    [idS (s) (idC s)]
    [appS (fun arg) (appC fun (desugar arg))]
    [plusS (l r) (plusC (desugar l) (desugar r))]
    [multS (l r) (multC (desugar l) (desugar r))]
    [bminusS (l r) (plusC (desugar l) (multC (numC -1) (desugar r)))]
    [uminusS (e) (multC (numC -1) (desugar e))]
    [ifS (c s n) (ifC (desugar c) (desugar s) (desugar n))]))

(define (interpC [a : ExprC] [env : Env] [fds : (listof FunDefC)]) : number
  (type-case ExprC a
    [numC (n) n]
    [plusC (l r) (+ (interpC l env fds) (interpC r env fds))]
    [multC (l r) (* (interpC l env fds) (interpC r env fds))]
    [ifC (c s n) (cond [(zero? (interpC c env fds)) (interpC n env fds)] [else (interpC s env fds)])]
    [appC (f a) (local ([define fd (get-fun-def f fds)])
                       (interpC (fdC-body fd) (extend-env (bind (fdC-arg fd) (interpC a env fds)) env) fds))]
    [idC (n) (lookup n env)]))

(define (get-fun-def [f : symbol] [fds : (listof FunDefC)]) : FunDefC
  (cond 
    [(empty? fds) (error 'get-fun-def "Lista de funções vazia!")]
    [(cons? fds) (cond
                   [(equal? (fdC-name (first fds)) f) (first fds)]
                   [else (get-fun-def f (rest fds))])]))

(define (lookup [s : symbol] [env : Env]) : number
  (cond 
    [(empty? env) (error 'lookup "Env vazio!")]
    [else (cond
            [(equal? (bind-name (first env)) s) (bind-val (first env))]
            [else (lookup s (rest env))])])) 
    
(define (parseS [s : s-expression]) : ExprS
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
         [(call) (appS (s-exp->symbol (second s1)) (parseS (third s1)))]
         [(if) (ifS (parseS (second s1)) (parseS (third s1)) (parseS (fourth s1)))]
         [else (error 'parseS "invalid list input")]))]
    [else (error 'parseS "invalid input")]))


(define (interpS [s : ExprS] [fds : (listof FunDefC)]) : number
  (interpC (desugar s) mt-env fds))

;;;;;;testesssss
(define biblioteca (list 
                    [fdC 'dobro 'x (plusC (idC 'x) (idC 'x))]
                    [fdC 'quadrado 'y (multC (idC 'y) (idC 'y))]
                    [fdC 'narciso  'narciso (multC (idC 'narciso) (numC 1000))]
                    ))

(test (interpS (parseS '(+ -1400 (call dobro 7))) biblioteca) -1386)
(test (interpS (parseS '(call narciso (call dobro 7))) biblioteca) 14000)