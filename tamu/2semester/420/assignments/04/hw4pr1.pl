my_min(A, [A]).
my_min(A, [Head|Tail]) :- my_min(B, Tail), A is min(Head, B).

my_sort([S], [S]).
my_sort([Head1|Tail1], List) :- my_min(Head1, List), delete(List, Head1, UpdatedList), my_sort(Tail1, UpdatedList).
