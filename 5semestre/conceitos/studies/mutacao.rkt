#lang plai-typed


(define-type-alias Location number)


(define-type Binding
  [bind (name : symbol)  (val : Location)])
(define-type-alias Env (listof Binding))
(define mt-env empty)
(define extend-env cons)


(define-type Storage
             [cell (location : Location) (val : Value)])
(define-type-alias Store (listof Storage))
(define mt-store empty)
(define override-store cons)



(define-type ExprC
  [numC (n : number)]
  [idC (s : symbol)]
  [plusC (l : ExprC) (r : ExprC)]
  [multC (l : ExprC) (r : ExprC)]
  [ifC (c : ExprC) (s : ExprC) (n : ExprC)]
  [lamC (arg : symbol) (body : ExprC)]
  [appC (fun : ExprC) (arg : ExprC)]

  [boxC (arg : ExprC)]
  [unboxC (arg : ExprC)]
  [setboxC (b : ExprC) (v : ExprC)]
  [seqC (b1 : ExprC) (b2 : ExprC)])


(define-type ExprS
  [numS (n : number)]
  [idS (s : symbol)]
  [lamS (arg : symbol) (body : ExprS)]
  [appS (fun : ExprS) (arg : ExprS)]
  [plusS (l : ExprS) (r : ExprS)]
  [multS (l : ExprS) (r : ExprS)]
  [bminusS (l : ExprS) (r : ExprS)]
  [uminusS (e : ExprS)]
  [ifS (c : ExprS) (s : ExprS) (n : ExprS)]
  [boxS    (a : ExprS)]
  [unboxS  (a : ExprS)]
  [setboxS (b : ExprS) (v : ExprS)]
  [seqS    (b1 : ExprS) (b2 : ExprS)])


(define-type Value
  [numV (n : number)]
  [closV (arg : symbol) (body : ExprC) (env : Env)]
  
  [boxV (l : Location)])
    

(define (num+ [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r)) (numV (+ (numV-n l) (numV-n r)))]
    [else (error 'num+ "Adicao invalida")]))


(define (num* [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r)) (numV (* (numV-n l) (numV-n r)))]
    [else (error 'num* "Multiplicacao invalida")]))


(define (desugar [as : ExprS]) : ExprC
  (type-case ExprS as
    [numS (n) (numC n)]
    [idS (s) (idC s)]
    [lamS (a b) (lamC a (desugar b))]
    [appS (fun arg) (appC (desugar fun) (desugar arg))]
    [plusS (l r) (plusC (desugar l) (desugar r))]
    [multS (l r) (multC (desugar l) (desugar r))]
    [bminusS (l r) (plusC (desugar l) (multC (numC -1) (desugar r)))]
    [uminusS (e) (multC (numC -1) (desugar e))]
    [ifS (c s n) (ifC (desugar c) (desugar s) (desugar n))]
    [boxS    (a)  (boxC   (desugar a))]
    [unboxS  (a)  (unboxC (desugar a))]
    [setboxS (b v)   (setboxC (desugar b) (desugar v))]
    [seqS    (b1 b2) (seqC (desugar b1) (desugar b2))]))


(define-type Result
    [v*s (v : Value) (s : Store)])


(define new-loc
  (let ([n (box 0)])
    (lambda ()
      (begin
        (set-box! n (+ 1 (unbox n)))
        (unbox n)))))


(define (interp [a : ExprC] [env : Env] [sto : Store]) : Result
  (type-case ExprC a
    [numC (n) (v*s (numV n) sto)]
    [idC (n) (v*s (fetch (lookup n env) sto) sto)]
    [plusC (l r) 
           (type-case Result (interp l env sto)
               [v*s (v-l s-l)
                    (type-case Result (interp r env s-l)
                      [v*s (v-r s-r)
                           (v*s (num+ v-l v-r) s-r)])])]
    [multC (l r) 
           (type-case Result (interp l env sto)
               [v*s (v-l s-l)
                    (type-case Result (interp r env s-l)
                      [v*s (v-r s-r)
                           (v*s (num* v-l v-r) s-r)])])]
    [ifC (c s n) (cond [(zero? (numV-n (v*s-v (interp c env sto)))) (interp n env sto)] [else (interp s env sto)])]
    [lamC (a b) (v*s (closV a b env) sto)]
    [appC (f a) 
          (type-case Result (interp f env sto)
            [v*s (v-f s-f)
                 (type-case Result (interp a env s-f)
                    [v*s (v-a s-a) 
                        (let ([onde (new-loc)])
                            (interp (closV-body v-f)
                                (extend-env (bind (closV-arg v-f) onde) (closV-env v-f))
                                (override-store (cell onde v-a) s-a)))])])]
    
    [boxC (a)  
          (type-case Result (interp a env sto)
                     [v*s (v-a s-a)
                          (let ([onde (new-loc)])
                            (v*s (boxV onde) 
                                 (override-store (cell onde v-a) s-a)))])]

    [unboxC (a) (type-case Result (interp a env sto)
                  [v*s (v-a s-a)
                       (v*s 
                        (fetch (boxV-l v-a) s-a) ; valor
                        s-a                      ; store
                        )])]
    [seqC (b1 b2)
          (type-case Result (interp b1 env sto)
                     [v*s (v-b1 s-b1)
                          (interp b2 env s-b1)])]
    [setboxC (b v) (type-case Result (interp b env sto)
                     [v*s (v-b s-b)
                          (type-case Result (interp v env s-b)
                            [v*s (v-v s-v)
                                 (v*s v-v
                                      (override-store 
                                       (cell (boxV-l v-b)
                                             v-v)
                                       s-v))])])]

    ))


(define (lookup [s : symbol] [env : Env]) : Location
  (cond 
    [(empty? env) (error 'lookup "Env vazio!")]
    [else (cond
            [(equal? (bind-name (first env)) s) (bind-val (first env))]
            [else (lookup s (rest env))])]))


(define (fetch [l : Location] [sto : Store]) : Value
  (cond 
    [(empty? sto) (error 'fetch "Store vazio!")]
    [else (cond
            [(equal? (cell-location (first sto)) l) (cell-val (first sto))]
            [else (fetch l (rest sto))])]))


(define (parse [s : s-expression]) : ExprS
  (cond
    [(s-exp-number? s)
     (numS (s-exp->number s))]
    [(s-exp-symbol? s)
     (idS (s-exp->symbol s))]
    [(s-exp-list? s)
     (let ([sl (s-exp->list s)])
       (case (s-exp->symbol (first sl))
         [(+) (plusS (parse (second sl)) (parse (third sl)))]
         [(*) (multS (parse (second sl)) (parse (third sl)))]
         [(-) (cond 
                [(equal? (length sl) 3) (bminusS (parse (second sl)) (parse (third sl)))]
                [(equal? (length sl) 2) (uminusS (parse (second sl)))]
                [else (error 'parse "invalid minus")])]
         [(func) (lamS (s-exp->symbol (second sl)) (parse (third sl)))]
         [(call) (appS (parse (second sl)) (parse (third sl)))]
         [(if) (ifS (parse (second sl)) (parse (third sl)) (parse (fourth sl)))]
         [(-#) (boxS (parse (second sl)))]
         [(>#) (unboxS (parse (second sl)))]
         [(!#) (setboxS (parse (second sl)) (parse (third sl)))]
         [(seq) (seqS (parse (second sl)) (parse (third sl)))]
         [(def) (appS (lamS (s-exp->symbol (second sl)) (parse (fourth sl))) (parse (third sl))) ]
         [else (error 'parse "invalid list input")]))]
    [else (error 'parse "invalid input")]))


; Facilitador
(define (interpS [s : s-expression]) (interp (desugar (parse s)) mt-env mt-store))


; Testes
(test (v*s-v (interp (plusC (numC 10) (appC (lamC '_ (numC 5)) (numC 10)))
              mt-env mt-store))
      (numV 15))


(interpS '(+ 10 (call (func x (+ x x)) 16)))

(interpS '(seq (!# (-# 2) 32) (># (-# 2) (+ (># (-# 2)) 10))))

(interpS '(call (func f (call f (-# 32))) (func x (seq (!# x (+ (># x) 10)) (># x)))))
