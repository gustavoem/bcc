#lang plai
;(define o-1
;  (lambda (name)
;    (case name
;      [(add1) (lambda (x) (+ x 1))]
;      [(sub1) (lambda (x) (- x 1))])))
;
;
;(msg o-1 'add1 1 2 3)


(define (msg o m . a)
  (apply (o m) a))


; Construtores
; perceba que exite estado. a variável x é local para cada objeto.
; x está no eviroment do lambda (m)
;
(define (o-constr1 x)
  (lambda (m)
    (case m
      [(addX) (lambda (y) (+ x y))])))

(test (let ([obj (o-constr1 20)]) (msg obj 'addX 21)) 41)
(test (((o-constr1 10) 'addX) 1) 11)

; Membros privados
;
(define (o-state-2 init)
  (let ([count init])
    (lambda (m)
      (case m
        [(inc) (lambda () (set! count (+ count 1)))]
        [(dec) (lambda () (set! count (- count 1)))]
        [(get) (lambda () count)]))))

  (((o-state-2 10) 'get))

