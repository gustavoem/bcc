#lang plai

(define new-label
  (let ([n (box 0)])
    (lambda ()
      (begin
        (set-box! n (+ 1 (unbox n)))
        (unbox n)))))

(define table (make-hash empty))

(define (read-number/suspend prompt rest)
  (let ([g (new-label)])
    (begin
        (hash-set! table g rest)
        (display prompt)
        (display "Para continuar, use a label:")
        (display g))))

(define (resume g n)
  (begin
  (display "\nVoce digitou: ")
  ((hash-ref table g) n)))

; Como ler um número, então?
(read-number/suspend "Digite o numero" (lambda (x) (+ x 1)))
(resume 1 10)
