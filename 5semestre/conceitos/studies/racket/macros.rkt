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


(define-syntax (my-or x) 
  (syntax-case x () 
    [(my-or-3) #'#f]
    [(my-or-3 a) #'a]
    [(my-or-3 a b ...) #'(if a a (my-or-3 b ...))]))

(test (my-or #t #f #f) #t)
(test (my-or #f) #f)


; Protegendo a avaliacao
; Se duplicarmos uma avaliação na expansão de uma expressão podemos causar
; avaliações desnecessárias e até problemas de estado (imagine um i++)!
(define-syntax (my-or x) 
  (syntax-case x () 
    [(my-or-3) #'#f]
    [(my-or-3 a) #'a]
    [(my-or-3 a b ...) 
     (let ([v a])
     #'(if v v (my-or-3 b ...)))]))

