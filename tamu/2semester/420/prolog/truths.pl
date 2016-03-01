sunny.

my_append([], X, X).
my_append(X, [], X).
my_append([Head|Tail], Y, [Head|Z]):-my_append(Tail, Y, Z).

my_min([X], X).
my_min(M, L) :- \+((member(Y, L), Y < M)).


my_min2([X], X).
my_min2([Head|Tail], X) :- my_min(Head, X), my_min(Tail, X).

