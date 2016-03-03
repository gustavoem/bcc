even(0).
even(X) :- Y is X - 2, Y >= 0, even(Y).
even(X) :- Y is X + 2, Y =< 0, even(Y).
