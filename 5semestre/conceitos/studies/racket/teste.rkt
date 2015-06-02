#lang plai
(let ([x 10])
  (begin 
    (display x)
    ((lambda (a) (set! a 20)) x)
    (display x)
    ))
