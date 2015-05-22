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
;(define (o-constr1 x)
;  (lambda (m)
;    (case m
;      [(addX) (lambda (y) (+ x y))])))
;
;(test (let ([obj (o-constr1 20)]) (msg obj 'addX 21)) 41)
;(test (((o-constr1 10) 'addX) 1) 11)

; Membros privados
;
;(define (o-state-2 init)
;  (let ([count init])
;    (lambda (m)
;      (case m
;        [(inc) (lambda () (set! count (+ count 1)))]
;        [(dec) (lambda () (set! count (- count 1)))]
;        [(get) (lambda () count)]))))
;  (((o-state-2 10) 'get))


; Membros estáticos!
;

;(define (o-static-1)
;  (let ([count 0]) ; esse count vai entrar pro env do construtor! Ou seja, pra esse 
;                   ; count aumentar tem que fazer um let pro construtor e usá-lo para
;                   ; todos os objetos que voce quiser instanciar
;    (lambda (base)
;      (begin
;      (set! count (+ 1 count))
;      (lambda (m)
;        (case m
;          [(addX) (lambda (x) (+ base x))]
;          [(incB) (lambda () (+ 1 base))]
;          [(getCounter) (lambda () (display count))]
;      ))))))
;(let ([const (o-static-1)]) (begin (((const 10) 'getCounter)) (((const 10) 'getCounter)) ))

; Objetos com Auto-referencia usando let

;(define o-self!
;  (let ([self 'dummy])
;    (begin 
;      (set! self
;        (lambda (m)
;          (case m
;            [(add1) (lambda (x) (+ ((self 'one)) x))]
;            [(one) (lambda () 1)]))) self)))
;
;(test ((o-self! 'add1) 10) 11)


; Usando combinador Y :(
;
(define o-self-no!
  (lambda (m)
    (case m
      [(add1) (lambda (self x) (msg/self self 'addx x))]
      [(addx) (lambda (self x)  (+ x 1))])))

(define (msg/self o m . a)
    (apply (o m) o a))

(test (msg/self o-self-no! 'first 5) 7)

