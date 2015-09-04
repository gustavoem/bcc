#lang racket
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
                            [(dispara) (begin ((first LC))
                                              (set! LC (rest LC)))]
                            [(registra) (lambda (k1 k2) (begin (set! LC (append LC (list k1)))
                                                               (k2)
                                                               ))]
                            [(mtd-name) (lambda (var) val)] 
                        ...))))
            self)))]))


; 2-
(define-syntax (object/self-2 x)
  (syntax-case x ()
    [(object [mtd-name (var) val] ...)
    (with-syntax ([self (datum->syntax x 'self)])
      #'(let ([self (lambda (msg) (error 'object/self-2 "Objeto vazio"))])
        (begin
            (set! self
                (let ([LC (list)])
                      [yield (call/cc (lambda (k) ((self registra) k (self dispara))))]
                    (lambda (msg)
                        (case msg
                            [(dispara) (begin ((first LC))
                                              (set! LC (rest LC)))]
                            [(registra) (lambda (k1 k2) (begin (set! LC (append LC (list k1)))
                                                               (k2)
                                                               (display "LC depois: ")
                                                               (display LC)
                                                               ;(display (list? LC))
                                                               (display "\n")
                                                               ))]
                            [(mtd-name) (lambda (var) val)] 
                        ...))))
            self)))]))


