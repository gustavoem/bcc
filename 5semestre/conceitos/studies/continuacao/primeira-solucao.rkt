#lang plai-typed

(define new-label
  (let ([n (box 0)])
    (lambda ()
      (begin
        (set-box! n (+ 1 (unbox n)))
        (unbox n)))))

(define table (make-hash empty))
(define-type-alias label number)

(define (read-number/suspend [prompt : string] rest)
  (let ([g (new-label)])
    (begin
        (hash-set! table g rest)
        (display prompt)
        (display "Para continuar, use a label:")
        (display g))))

(define (resume [g : label] [n : number])
  (begin
  (display "\nVoce digitou: ")
  ((some-v (hash-ref table g)) n)))

; Como ler um número, então?
(read-number/suspend "Digite o numero" (lambda (x) x))
(resume 1 10)

; usando cookies
(define cookie '-100)
(read-number/suspend "\nFirst number (cookie)"
    (lambda (v1)
      (begin
        (set! cookie v1)
        (read-number/suspend "\nSecond number (cookie)"
            (lambda (v2)
              (display (+ cookie v2)))))))
