#lang plai-typed

(define-type Binding
  [bind (name : symbol)  (val : Value)])

(define-type-alias Env (symbol -> Value))
(define (mt-env [name : symbol])
  (error 'lookup "name not found"))
(define (extend-env [b : Binding] [e : Env])
  (lambda ([name : symbol]) : Value
    (if (symbol=? name (bind-name b)) 
        (bind-val b)
        (lookup name e))))

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
  [msgS (o : ExprS) (n : symbol) (a : ExprS)]
  [letS (id : symbol) (val : ExprS) (expr : ExprS)])

(define-type Value
  [numV (n : number)]
  [closV (f : (Value -> Value))]
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
    [objS (ns es) (objC ns (map (lambda (e) (desugar e)) es))]
    [msgS (o n a) (appC (msgC (desugar o) n) (desugar a))]
    [letS (id val expr) (appC (lamC id (desugar expr)) (desugar val))]
    ))

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
    [lamC (a b) (closV (lambda (arg-v) (interp b (extend-env (bind a arg-v) env))))]
    [appC (f a) (local ([define fv (interp f env)]
                        [define av (interp a env)])
                       ((closV-f fv) av))]
    [objC (ns es) (objV ns (map (lambda (e) 
                                  (interp e env)) es))]
    [msgC (o n) (lookup-msg n (interp o env))]))

(define (lookup [s : symbol] [env : Env]) : Value
  (env s))

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
         [(lam) (lamS (s-exp->symbol (second sl)) (parse (third sl)))]
         [(call) (appS (parse (second sl)) (parse (third sl)))]
         [(if) (ifS (parse (second sl)) (parse (third sl)) (parse (fourth sl)))]
         [(obj) (cond
                  [(and (s-exp-list? (second sl)) (s-exp-list? (third sl)))
                        (objS (map (lambda (s) (s-exp->symbol s)) (s-exp->list (second sl)))
                              (map (lambda (e) (parse e)) (s-exp->list (third sl))))]
                  [else (error 'parse "Objeto mal definido")])]
         [(:=) (letS (s-exp->symbol (second sl)) (parse (third sl)) (parse (fourth sl)))] 
         [(->) (msgS (parse (second sl)) (s-exp->symbol (third sl)) (parse (fourth sl)))]
         [else (error 'parse "invalid list input")]))]
    [else (error 'parse "invalid input")]))

(define (interpS [s : s-expression]) : Value
  (interp (desugar (parse s)) mt-env))

(test (interpS '(:= leke (obj (soma1 subtrai1) 
                         ((lam x (+ x 1)) (lam x (- x 1)))) 
                    (-> leke subtrai1 (+ 1 2))
                )
      )(numV 2))

(test (interp (desugar (letS 'o (objS (list 'add1 'sub1)
                             (list (lamS 'x (plusS (idS 'x) (numS 1)))
                                   (lamS 'x (plusS (idS 'x) (numS -1)))))
(msgS (idS 'o) 'add1 (numS 3)))) mt-env) (numV 4))
