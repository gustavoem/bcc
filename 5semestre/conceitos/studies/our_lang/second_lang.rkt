#lang plai-typed
(define-type FunDefC
  [fdC (name : symbol) (arg : symbol) (body : ExprC)])

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

(define (subst [valor : ExprC] [isso : symbol] [em : ExprC]) : ExprC
   (type-case ExprC em
     [numC (n) em]
     [plusC (l r) (plusC (subst valor isso l) (subst valor isso r))]
     [multC (l r) (multC (subst valor isso l) (subst valor isso r))]
     [ifC (c s n) (ifC (subst valor isso c) (subst valor isso s) (subst valor isso n))]
     [appC (f a) (appC f (subst valor isso a))]
     [idC (s) (cond [(symbol=? s isso) valor]
                    [else em])]))

(define (interpC [a : ExprC] [fds : (listof FunDefC)]) : number
  (type-case ExprC a
    [numC (n) n]
    [plusC (l r) (+ (interpC l fds) (interpC r fds))]
    [multC (l r) (* (interpC l fds) (interpC r fds))]
    [ifC (c s n) (cond [(zero? (interpC c fds)) (interpC n fds)] [else (interpC s fds)])]
    [appC (f a) (local ([define fd (get-fundef f fds)])
                        (interpC (subst a (fdC-arg fd) (fdC-body fd)) fds))]
    [idC (s) (error 'interpC "Nao devia ocorrer isso")]))

(define (get-fundef [f : symbol] [fds : (listof FunDefC)]) : FunDefC
  (cond
    [(empty? fds) (error 'get-fundef "Biblioteca de funcoes vazia")]
    [(cons? fds) (cond
                   [(equal? f (fdC-name (first fds))) (first fds)]
                   [else (get-fundef f (rest fds))])]))

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
  (interpC (desugar s) fds))

;copiei do livro
(fdC 'double 'x (plusC(idC 'x) (idC 'x)))
(fdC 'quadruple 'x ( appC ' double ( appC ' double ( idC 'x ) ) ) )
(fdC 'const5 '_ ( numC 5) )
;;


;;;;;;testesssss
(define biblioteca (list 
                    [fdC 'dobro 'x (plusC (idC 'x) (idC 'x))]
                    [fdC 'quadrado 'y (multC (idC 'y) (idC 'y))]
                    [fdC 'narciso  'narciso (multC (idC 'narciso) (numC 1000))]
                    ))

(interpS (parseS '(+ -1400 (call dobro 7))) biblioteca)
(test (interpS (parseS '(call narciso (call dobro 7))) biblioteca) 14000)