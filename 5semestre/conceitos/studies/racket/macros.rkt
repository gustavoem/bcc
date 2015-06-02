#lang plai

(define-syntax my-let-1
  (syntax-rules ()
    [(my-let-1 (var val) body)
     ((lambda (var) body) val)]))

(test (my-let-1 (x 10) (- x 9)) 1)


(define-syntax (my-let-3 x)
  (syntax-case x ()
    [(my-let-3 (var val) body)
     #'((lambda (var) body) val)]))

(test (my-let-1 (x 10) (- x 9)) 1)


(define-syntax (my-or-3 x) 
  (syntax-case x () 
    [(my-or-3) #'#f]
    [(my-or-3 a) #'a]
    [(my-or-3 a b ...) #'(if a a (my-or-3 b ...))]))

(test (my-or-3 #t #f #f) #t)
(test (my-or-3 #f) #f)


; Protegendo a avaliacao
; Se duplicarmos uma avaliação na expansão de uma expressão podemos causar
; avaliações desnecessárias e até problemas de estado (imagine um i++)!
(define-syntax (my-or-4 x) 
  (syntax-case x () 
    [(my-or-4) #'#f]
    [(my-or-4 a) #'a]
    [(my-or-4 a b ...) 
     #'(let ([v a])
        (if v v (my-or-4 b ...)))]))

(test (my-or-4 #t #f #f) #t)
(test (my-or-4 #f) #f)


; Higiene
; (let ([v #t]) (my-or-4 #f v))
; (v -> #t)   (my-or-4 #f v)
; (v -> #t)   (let ([v #f]) (if v v v))
; Ele sabe quem é v de quem
; (v' -> #t)


; As vezes a higiene atrapalha, pois podemos querer usar referências que vem de fora.
; Exemplo: definição de objetos com auto-referencia
;(define-syntax object/self-1
;  (syntax-rules ()
;    [(object [mtd-name (var) val] ...)
;     (let ([self (lambda (msg) (error 'object/self-1 "Objeto vazio"))])
;       (begin
;         (set! self
;           (lambda (msg)
;             (case msg
;               [(mtd-name) (lambda (var) val)]
;               ...)))
;         self))]))
;
;(define obj
;  (object/self-1 
;    [first (x) ((self 'second) (+ x 1))] ; unbound identifier in module in: self
;    [second (x)  (+ x 1)])) 
;
;((obj 'first) 1)

; (obj [first x bf] [second x bs])
; self -> (lambda (msg) case msg [first lambda (x) bf] [second lambda (x) bs]), self

; Isso NÃO vai funcionar porque o self do obj vai ser diferente do self de dentro do
; construtor.
; Uma solução é trazer o self para a definição (construção) do objeto.
(define-syntax object/self-2
  (syntax-rules ()
    [(object self [mtd-name (var) val] ...)
      (let ([self (lambda (msg) (error 'object/self-2 "Objeto vazio"))])
        (begin
          (set! self
            (lambda (msg)
              (case msg
              [(mtd-name) (lambda (var) val)] ...)))
         self))]))
(define obj-2
  (object/self-2 self
    [first (x) ((self 'second) (+ x 1))] ; unbound identifier in module in: self
    [second (x)  (+ x 1)])) 

(test ((obj-2 'first) 1) 3)
; Funciona mas é chato sempre ficar passando o self para criar objetos

(define-syntax (object/self-3 x)
  (syntax-case x ()
    [(object [mtd-name (var) val] ...)
    (with-syntax ([self (datum->syntax x 'self)])
      #'(let ([self (lambda (msg) (error 'object/self-3 "Objeto vazio"))])
        (begin
          (set! self
            (lambda (msg)
              (case msg
              [(mtd-name) (lambda (var) val)] 
              ...)))
         self)))]))

(define obj-3
  (object/self-3
    [first (x) ((self 'second) (+ x 1))]
    [second (x)  (+ x 1)])) 

(test ((obj-3 'first) 1) 3)
