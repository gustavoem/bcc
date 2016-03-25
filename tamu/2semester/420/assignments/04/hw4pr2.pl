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

parent(anne, peter).
parent(anne, zara).
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


dated(george, mum).
dated(spencer, kydd).
dated(philip, elizabeth).
dated(charles, dianna).
dated(mark, anne).
dated(andrew, sarah).
dated(edward, sophie).

couple(X, Y) :- dated(X, Y).
couple(X, Y) :- dated(Y, X).


grandchild(X, Y) :- parent(Y, Z), parent(Z, X).
