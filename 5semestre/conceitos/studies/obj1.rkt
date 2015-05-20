#lang plai-typed

(define-type Binding
  [bind (name : symbol)  (val : Value)])

(define-type-alias Env (listof Binding))
(define mt-env empty)
(define extend-env cons)

(define-type ExprC
  [numC (n : number)]
  [idC (s : symbol)]
  [plusC (l : ExprC) (r : ExprC)]
  [multC (l : ExprC) (r : ExprC)]
  [ifC (c : ExprC) (s : ExprC) (n : ExprC)]
  [lamC (arg : symbol) (body : ExprC)]
  [appC (fun : ExprC) (arg : ExprC)]
  [objC (ns : (listof symbol)) (es : (listof ExprC))]
  [msgC (o : ExprC) (n : symbol)])

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
  [objS (ns : (listof symbol)) (es : (listof ExprS))]
  [msgS (o : ExprS) (n : symbol) (a : ExprS)])

(define-type Value
  [numV (n : number)]
  [closV (arg : symbol) (body : ExprC) (env : Env)]
  [objV (ns : (listof symbol)) (vs : (listof Value))])

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
    [objS (ns es) (objC ns (map (lambda (e) (parse e)) es))]
    [msgS (o n a) (appC (msgC (desugar o) n) (desugar a))]))

(define (lookup-msg [n : symbol] [o : Value]) : Value
  (type-case Value o
             [objV (nomes valores)
                   (cond
                     [(empty? nomes)
                      (error 'lookup-msg "lista de metodos vazio")]
                     [(symbol=? n (first nomes)) (first valores)]
                     [else (lookup-msg n (objV (rest nomes) 
                                               (rest valores)))])]
             [else (error 'lookup-msg "o que foi passado nao e um objeto")]))

(define (interp [a : ExprC] [env : Env]) : Value
  (type-case ExprC a
    [numC (n) (numV n)]
    [idC (n) (lookup n env)]
    [plusC (l r) (num+ (interp l env) (interp r env))]
    [multC (l r) (num* (interp l env) (interp r env))]
    [ifC (c s n) (cond [(zero? (numV-n (interp c env))) (interp n env)] [else (interp s env)])]
    [lamC (a b) (closV a b env)]
    [appC (f a) (local ([define fd (interp f env)])
                       (interp (closV-body fd) (extend-env (bind (closV-arg fd) (interp a env)) (closV-env fd))))]
    [objC (ns es) (objV ns (map (lambda (e) 
                                  (interp e env)) es))]
    [msgC (o n) (lookup-msg n (interpo env))]))

(define (lookup [s : symbol] [env : Env]) : Value
  (cond 
    [(empty? env) (error 'lookup "Env vazio!")]
    [else (cond
            [(equal? (bind-name (first env)) s) (bind-val (first env))]
            [else (lookup s (rest env))])]))

(define (parse [s : s-expression]) : ExprS
  (cond
    [(s-exp-number? s)
     (numS (s-exp->number s))]
    [(s-exp-symbol? s)
     (idS (s-exp->symbol s))]
    [(s-exp-list? s)
     (let ([s1 (s-exp->list s)])
       (case (s-exp->symbol (first s1))
         [(+) (plusS (parse (second s1)) (parse (third s1)))]
         [(*) (multS (parse (second s1)) (parse (third s1)))]
         [(-) (cond 
                [(equal? (length s1) 3) (bminusS (parse (second s1)) (parse (third s1)))]
                [(equal? (length s1) 2) (uminusS (parse (second s1)))]
                [else (error 'parse "invalid minus")])]
         [(lam) (lamS (s-exp->symbol (second s1)) (parse (third s1)))]
         [(call) (appS (parse (second s1)) (parse (third s1)))]
         [(if) (ifS (parse (second s1)) (parse (third s1)) (parse (fourth s1)))]
         [else (error 'parse "invalid list input")]))]
    [else (error 'parse "invalid input")]))

(define (interpS [s : s-expression]) : Value
  (interp (desugar (parse s)) mt-env))

(test (interpS '(+ 10 (call (lam x (+ x x)) 16))) (numV 42))
