parent(mum, elizabeth).
parent(mum, margaret).
parent(george, elizabeth).
parent(george, margaret).

parent(kydd, diana).
parent(spencer, diana).

parent(elizabeth, charles).
parent(elizabeth, anne).
parent(elizabeth, andrew).
parent(elizabeth, edward).
parent(philip, charles).
parent(philip, anne).
parent(philip, andrew).
parent(philip, edward).

parent(diana, william).
parent(diana, harry).
parent(charles, william).
parent(charles, harry).

parent(anne, zara).
parent(anne, peter).
parent(mark, peter).
parent(mark, zara).

parent(sarah, beatrice).
parent(sarah, eugenie).
parent(andrew, beatrice).
parent(andrew, eugenie).

parent(sophie, louise).
parent(sophie, james).
parent(edward, louise).
parent(edward, james).


woman(mum).
woman(kydd).
woman(elizabeth).
woman(margaret).
woman(diana).
woman(anne).
woman(sarah).
woman(sophie).
woman(zara).
woman(beatrice).
woman(eugenie).
woman(louise).

man(X) :- \+(woman(X)).


dated(george, mum).
dated(spencer, kydd).
dated(philip, elizabeth).
dated(charles, dianna).
dated(mark, anne).
dated(andrew, sarah).
dated(edward, sophie).

couple(X, Y) :- dated(Y, X).
couple(X, Y) :- dated(X, Y).


grandchild(X, Y) :- parent(Y, Z), parent(Z, X).


greatgrandparent(X, Y) :- parent(X, Z), parent(Z, W), parent(W, Y).


ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, W), ancestor(W, Y).


brother(X, Y) :- parent(W, X), woman(W), parent(W, Y), man(X), X\= Y.
sister(X, Y) :- parent(W, X), woman(W), parent(W, Y), woman(X), X \= Y.
sibling(X, Y) :- brother(X, Y).
sibling(X, Y) :- sister(X, Y).


daughter(X, Y) :- parent(Y, X), woman(X).
son(X, Y) :- parent(Y, X), man(X).

first_cousin(X, Y) :- grandchild(X, W), grandchild(Y, W), woman(W), X \= Y.

brother_in_law(X, Y) :- couple(W, Y), brother(X, W).
brother_in_law(X, Y) :- couple(X, W), sister(W, Y).

aunt(X, Y) :- parent(W, Y), sister(X, W).
