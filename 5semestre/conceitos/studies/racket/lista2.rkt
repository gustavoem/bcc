#lang racket
(define-syntax (object/self x)
  (syntax-case x ()
    [(object [mtd-name (var) val] ...)
    (with-syntax ([self (datum->syntax x 'self)])
      #'(let ([self (lambda (msg) (error 'object/self "Objeto vazio"))])
        (begin
          (set! self
            (let [LC (list)]
                (lambda (msg)
                    (case msg
                        [(queue) lambda () (LC)]
                        [(dispara lambda () (0))]
                        [(mtd-name) (lambda (var) val)] 
                        ...))))
                        self)))]))

(define obj1
  (object/self
    [soma1 (x) (+ x 1)]
    [soma2 (x) ((self 'soma1) ((self 'soma1)x))]))

((obj1 'queue))
