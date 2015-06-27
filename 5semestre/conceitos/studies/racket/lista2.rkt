#lang racket
(let ([test (list "aqui o car funciona\n")]) (display (car test)))
(list? (append (list) 1))
; 1-
(define-syntax (object/self x)
  (syntax-case x ()
    [(object [mtd-name (var) val] ...)
    (with-syntax ([self (datum->syntax x 'self)])
      #'(let ([self (lambda (msg) (error 'object/self "Objeto vazio"))])
        (begin
            (set! self
                (let ([LC (list)])
                    (lambda (msg)
                        (case msg
                            [(dispara) (car LC)]
                            [(registra) (lambda (k1 k2) (begin (set! LC (append LC (list k1)))
                                                               (k2)
                                                               ;(display "LC depois: ")
                                                               ;(display LC)
                                                               ;(display (list? LC))
                                                               ;(display "\n")
                                                               ))]
                            [(mtd-name) (lambda (var) val)] 
                        ...))))
            self)))]))

(define obj1
  (object/self
    [soma1 (x) (+ x 1)]
    [soma2 (x) ((self 'soma1) ((self 'soma1)x))]))

((obj1 'registra) (lambda () (display "entra esse na lista de continuacoes")) (lambda () "wow, i'm the next!"))
(obj1 'dispara)
((obj1 'registra) (lambda () (display "mais um em LC")) (lambda () "wow, i'm the next!"))

