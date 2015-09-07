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
;(define o-self-no!
;  (lambda (m)
;    (case m
;      [(add1) (lambda (self x) (msg/self self 'addx x))]
;      [(addx) (lambda (self x)  (+ x 1))])))
;
;(define (msg/self o m . a)
;    (apply (o m) o a))
;
;(test (msg/self o-self-no! 'add1 5) 6)

; Chamada definida em tempo de execução:
; objetos podem invocar funções em outros objetos (?). Isso permite flexibilidade
; e é um dos conceitos mais importantes de o.o.


; Exemplo de árvore binária
;
; folha
(define (mt)
  (let ([self 'dummy])
    (begin
      (set! self
        (lambda (m)
          (case m
            [(add) (lambda () 0)]))) self)))

; no interno
(define (node v l r)
  (let ([self 'dummy])
    (begin 
      (set! self 
        (lambda (m)
          (case m
            [(add) (lambda () (+  v ((l 'add)) (msg r 'add)))]))) self)))

;testee
;(test (msg (node 10 (node 9 (mt) (node -1 (mt) (mt))) (mt)) 'add) 18)
;(test (((node 10 (node 9 (mt) (node -1 (mt) (mt))) (mt)) 'add)) 18)  
; ele interpreta primeiro l e r, que são lambdas, logo, quando eu interpretar lambda,
; vai existir l e r no environment, e tudo vai funcionar.

; Utilização de herança
; Vamos criar um objeto que herda de node
(define (node/size parent-maker v l r)
  (let ([self 'dummy]
        [parent (parent-maker v l r)])
    (begin
      (set! self 
        (lambda (m)
          (case m
            [(size) (lambda () (+ 1 ((l 'size)) ((r 'size)) ))]
            [else ((parent m))]))) self)))

(define (mt/size parent-maker)
  (let ([self 'dummy]
        [parent (parent-maker)])
    (begin
      (set! self 
        (lambda (m)
          (case m
            [(size) (lambda () 0)]
            [else ((parent m))]))) self)))

(test (((node/size node 10 
                   (node/size node 9 
                              (mt/size mt) 
                              (node/size node -1 (mt/size mt) (mt/size mt))) 
                   (mt/size mt)) 'size)) 3)

; Protótipos
; Ao invés de passarmos o construtor do pai, poderiamos passar o objeto pai já criado.
; Para isso usariamos um objeto protótipo, que é uma instancia do objeto pai que esta
; compartilhada pra quem quiser usar.

; Subir ou descer?
; Até agora sempre olhamos para os métodos da classe mais "baixa" e se ela não tem o
; método procurado, subimos na hierarquia, ou seja, nossa preferência é por utilizar
; os métodos das classes mais baixas, e só poderíamos acessar os métodos da classe
; mãe utilizando "super".
; Existe outra abordagem que desce ao invés de subir. Isso acontece porque a 
; preferência está nas classes mais altas, e só permite acessar os métodos das 
; classes mais baixas com a utilização de "inner".