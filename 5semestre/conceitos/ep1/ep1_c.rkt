#lang plai-typed

#|
 | Funções não tem mais nome, serão chamadas de lamC (em homenagem ao λ)
 |#

(define-type ExprC
  [numC  (n : number)]
  [idC   (s : symbol)]
  [plusC (l : ExprC) (r : ExprC)]
  [multC (l : ExprC) (r : ExprC)]
  [divC  (l : ExprC) (r : ExprC)]
  [expC  (b : ExprC) (p : ExprC)]
  [lamC1 (arg : symbol) (body : ExprC)] ; nomes não são mais necessários
  [lamC2 (arg1 : symbol) (arg2 : symbol) (body : ExprC)]
  [appC1  (fun : ExprC) (arg : ExprC)]
  [appC2  (fun : ExprC) (arg1 : ExprC) (arg2 : ExprC)]
  [ifC   (condição : ExprC) (sim : ExprC) (não : ExprC)]
  [greqC  (l : ExprC) (r : ExprC)] 
  [greC   (l : ExprC) (r : ExprC)]
  [eqC    (l : ExprC) (r : ExprC)]
  [leqC   (l : ExprC) (r : ExprC)]
  [leC    (l : ExprC) (r : ExprC)]
  [noC    (s : ExprC)]
)

; inclui funções
(define-type ExprS
  [numS    (n : number)]
  [idS     (s : symbol)] 
  [lamS1   (arg : symbol) (body : ExprS)] ; muda de acordo
  [lamS2   (arg1 : symbol) (arg2 : symbol) (body : ExprS)]
  [appS1   (fun : ExprS) (arg : ExprS)] 
  [appS2   (fun : ExprS) (arg1 : ExprS) (arg2 : ExprS)] 
  [plusS   (l : ExprS) (r : ExprS)]
  [bminusS (l : ExprS) (r : ExprS)]
  [uminusS (e : ExprS)]
  [multS   (l : ExprS) (r : ExprS)]
  [divS    (l : ExprS) (r : ExprS)]
  [expS    (b : ExprS) (p : ExprS)]
  [ifS     (c : ExprS) (s : ExprS) (n : ExprS)]
  [greqS   (l : ExprS) (r : ExprS)] 
  [greS    (l : ExprS) (r : ExprS)]
  [eqS     (l : ExprS) (r : ExprS)]
  [leqS    (l : ExprS) (r : ExprS)]
  [leS     (l : ExprS) (r : ExprS)]
  [noS     (s : ExprS)]
  )


; agora é preciso tomar cuidado com as modificações
(define (desugar [as : ExprS]) : ExprC  
  (type-case ExprS as
    [numS    (n) (numC n)]
    [idS     (s) (idC s)]
    [lamS1   (a b)  (lamC1 a (desugar b))] ; idem
    [lamS2   (a1 a2 b) (lamC2 a1 a2 (desugar b))]
    [appS1    (fun arg) (appC1 (desugar fun) (desugar arg))] 
    [appS2    (fun arg1 arg2) (appC2 (desugar fun) (desugar arg1) (desugar arg2))] 
    [plusS   (l r) (plusC (desugar l) (desugar r))] 
    [multS   (l r) (multC (desugar l) (desugar r))]
    [bminusS (l r) (plusC (desugar l) (multC (numC -1) (desugar r)))]
    [uminusS (e)   (multC (numC -1) (desugar e))]
    [divS    (l r) (divC (desugar l) (desugar r))]
    [expS    (b p) (expC (desugar b) (desugar p))]
    [ifS     (c s n) (ifC (desugar c) (desugar s) (desugar n))]
    [greqS   (l r) (greqC (desugar l) (desugar r))]
    [greS    (l r)  (greC (desugar l) (desugar r))]
    [eqS     (l r)   (eqC (desugar l) (desugar r))]
    [leqS    (l r)  (leqC (desugar l) (desugar r))]
    [leS     (l r)   (leC (desugar l) (desugar r))]
    [noS     (s)   (noC (desugar s))]
    ))


#|
 | Closure não tem mais o nome, mas precisa do environment
 |#

(define-type Value
  [numV  (n : number)]
  [closV1 (arg : symbol) (body : ExprC) (env : Env)]
  [closV2 (arg1 : symbol) (arg2 : symbol) (body : ExprC) (env : Env)])

; símbolos devem se associar ao número (ou a Value?)
(define-type Binding
      [bind (name : symbol) (val : Value)])

; A lista de associações é o environment
(define-type-alias Env (listof Binding))
(define mt-env empty)        ; ente pronunciar "mt" em inglês e compare com "empty"
(define extend-env cons)     ; sorte, cons faz exatamente o que queremos para estender o env

; novos operadores
(define (num+ [l : Value] [r : Value]) : Value
    (cond
        [(and (numV? l) (numV? r))
             (numV (+ (numV-n l) (numV-n r)))]
        [else
             (error 'num+ "Um dos argumentos não é número")]))

(define (num* [l : Value] [r : Value]) : Value
    (cond
        [(and (numV? l) (numV? r))
             (numV (* (numV-n l) (numV-n r)))]
        [else
             (error 'num* "Um dos argumentos não é número")]))

(define (num/ [l : Value] [r : Value]) : Value
    (cond
        [(and (numV? l) (numV? r))
             (numV (/ (numV-n l) (numV-n r)))]
        [else
             (error 'num* "Um dos argumentos não é número")]))

(define (greq [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r))
     (if (>= (numV-n l) (numV-n r)) (numV 1) (numV 0))]
    [else
      (error 'greq "Um dos argumentos comparados nao e numero")]))
    
(define (gre [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r))
     (if (> (numV-n l) (numV-n r)) (numV 1) (numV 0))]
    [else
      (error 'gre "Um dos argumentos comparados nao e numero")]))

(define (eq [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r))
     (if (= (numV-n l) (numV-n r)) (numV 1) (numV 0))]
    [else
      (error 'eq "Um dos argumentos comparados nao e numero")]))

(define (leq [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r))
     (if (<= (numV-n l) (numV-n r)) (numV 1) (numV 0))]
    [else
      (error 'leq "Um dos argumentos comparados nao e numero")]))

(define (le [l : Value] [r : Value]) : Value
  (cond
    [(and (numV? l) (numV? r))
     (if (< (numV-n l) (numV-n r)) (numV 1) (numV 0))]
    [else
      (error 'le "Um dos argumentos comparados nao e numero")]))

(define (no [s : Value]) : Value
  (cond
    [(numV? s)
     (if (zero? (numV-n s)) (numV 1) (numV 0))]
    [else
      (error 'no "Um dos argumentos comparados nao e numero")]))


; trata agora lamC e appC
(define (interp [a : ExprC] [env : Env]) : Value
  (type-case ExprC a
    [numC (n) (numV n)] 
    [idC (n) (lookup n env)]
    [lamC1 (a b) (closV1 a b env)] ; definição de função captura o environment
    [appC1 (f a)
          (local ([define f-value (interp f env)]) ; f-value descreve melhor a ideia
            (interp (closV1-body f-value)
                    (extend-env 
                        (bind (closV1-arg f-value) (interp a env))
                        (closV1-env f-value) ; não mais mt-env
                        )))]
    [lamC2 (a1 a2 b) (closV2 a1 a2 b env)]
    [appC2 (f a1 a2)
           (local ([define f-value (interp f env)])
             (interp (closV2-body f-value)
                     (extend-env (bind (closV2-arg1 f-value) (interp a1 env))
                                  (extend-env (bind (closV2-arg2 f-value) (interp a2 env)) env))))]
    [plusC (l r) (num+ (interp l env) (interp r env))]
    [multC (l r) (num* (interp l env) (interp r env))]
    [divC  (l r) (num/ (interp l env) (interp r env))]
    [expC  (b p) (let ([pot (interp p env)])
                   (let ([base (interp b env)])
                     (cond 
                       [(> (numV-n pot) 0) (num* base (interp (expC b (plusC (numC  -1) p)) env))]
                       [(< (numV-n pot) 0) (num/ (interp (expC b (plusC (numC  1) p)) env) base)]
                       [(zero? (numV-n pot)) (numV 1)]
                       [else (error 'interp "So e possivel aplicar exponenciacao a numeros de potencia inteiras.")]
                       )))]
    [ifC (c s n) (if (zero? (numV-n (interp c env))) (interp n env) (interp s env))]
    [greqC (l r) (greq (interp l env) (interp r env))]
    [greC  (l r) (gre  (interp l env) (interp r env))]
    [eqC   (l r) (eq   (interp l env) (interp r env))]
    [leqC  (l r) (leq  (interp l env) (interp r env))]
    [leC   (l r) (le   (interp l env) (interp r env))]
    [noC   (s)   (no   (interp s env))]))

; lookup também muda o tipo de retorno
(define (lookup [for : symbol] [env : Env]) : Value
       (cond
            [(empty? env) (error 'lookup (string-append (symbol->string for) " não foi encontrado"))] ; livre (não definida)
            [else (cond
                  [(symbol=? for (bind-name (first env)))   ; achou!
                                 (bind-val (first env))]
                  [else (lookup for (rest env))])]))        ; vê no resto

(define (parse [s : s-expression]) : ExprS
  (cond
    [(s-exp-number? s) (numS (s-exp->number s))]
    [(s-exp-symbol? s) (idS (s-exp->symbol s))] ; pode ser um símbolo livre nas definições de função
    [(s-exp-list? s)
     (let ([sl (s-exp->list s)])
       (case (s-exp->symbol (first sl))
         [(+) (plusS (parse (second sl)) (parse (third sl)))]
         [(*) (multS (parse (second sl)) (parse (third sl)))]
         [(-) (bminusS (parse (second sl)) (parse (third sl)))]
         [(~) (uminusS (parse (second sl)))]
         [(/) (divS (parse (second sl)) (parse (third sl)))]
         [(^) (expS (parse (second sl)) (parse (third sl)))]
         [(func) (cond
                   [(equal? (length sl) 3) 
                    (lamS1 (s-exp->symbol (second sl)) (parse (third sl)))]
                   [(equal? (length sl) 4) 
                    (lamS2 (s-exp->symbol (second sl)) (s-exp->symbol (third sl)) (parse (fourth sl)))]
                   [else (error 'parse "Numbero invalido de argumentos")])]; definição
         [(call) (cond
                   [(equal? (length sl) 3)
                    (appS1 (parse (second sl)) (parse (third sl)))]
                   [(equal? (length sl) 4)
                    (appS2 (parse (second sl)) (parse (third sl)) (parse (fourth sl)))]
                   [else (error 'parse "Numero invalido de argumentos")])]
         [(if) (ifS (parse (second sl)) (parse (third sl)) (parse (fourth sl)))]
         [(>>=) (greqS (parse (second sl)) (parse (third sl)))]
         [(>>)  (greS  (parse (second sl)) (parse (third sl)))]
         [(==)  (eqS   (parse (second sl)) (parse (third sl)))]
         [(<<=) (leqS  (parse (second sl)) (parse (third sl)))]
         [(<<)  (leS   (parse (second sl)) (parse (third sl)))]
         [(!)   (noS (parse (second sl)))]
         [else (error 'parse "invalid list input")]))]
    [else (error 'parse "invalid input")]))

; Facilitador
(define (interpS [s : s-expression]) (interp (desugar (parse s)) mt-env))

; Testes
; divisao
(test (interpS '(/ 1 2)) (numV 1/2))
(test (interpS '(+ (/ 1 2) (/ 1 2))) (numV 1))
; exponenciacao
(test (interpS '(^ 1 2)) (numV 1))
(test (interpS '(^ 2 3)) (numV 8))
(test (interpS '(^ 2 -1)) (numV 1/2))
(test (interpS '(^ (+ 1 2) (- 3 2))) (numV 3))
; relacoes
(test (interpS '(>>= (+ 1 2) 3)) (numV 1))
(test (interpS '(>> 2 1)) (numV 1))
(test (interpS '(>> 1 2)) (numV 0))
(test (interpS '(== 1 1)) (numV 1))
(test (interpS '(== 1 2)) (numV 0))
(test (interpS '(<< 1 2)) (numV 1))
(test (interpS '(<< 2 1)) (numV 0))
(test (interpS '(<<= (+ 1 2) 3)) (numV 1))
(test (interpS '(! (== 1 1))) (numV 0))
; funcoes
(test (interpS '(call (func a b (+ a b)) 1 2)) (numV 3))
(test (interpS '(call (func a b (* a (+ a b))) 1 2)) (numV 3))
