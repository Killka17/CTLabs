init(N) :-
    eratosthenes_sieve(2, N); true.

eratosthenes_sieve(I, N) :-
    R is I * I,
    R =< N,
    assertz(composite(R)),
    \+ composite(I),
    set_comp(I, R, N),
    I1 is I + 1,
    eratosthenes_sieve(I1, N).
eratosthenes_sieve(I, N) :-
    R is I * I,
    R =< N,
    I1 is I + 1,
    eratosthenes_sieve(I1, N).

set_comp(I, C, N) :-
    C =< N, !,
    assertz(composite(C)),
    NC is C + I,
    set_comp(I, NC, N).

prime(N) :- N > 1, \+ composite(N).

prime_divisors(1, []) :- !.
prime_divisors(N, [H|T]) :-
    min_div(N, 2, H),
    N1 is N // H,
    prime_divisors(N1, T).

min_div(N, D, D) :-
    N mod D =:= 0,
     prime(D), !.
min_div(N, D, R) :-
    D1 is D + 1,
    min_div(N, D1, R).

prime_index(2, 1) :- !.
prime_index(P, N) :-
    prime(P),
    prime_index_check(P, N, 2, 1).

prime_index_check(P, N, P, N).

prime_index_check(P, N, Current, Count) :-
    Current < P,
    Next is Current + 1,
    \+ composite(Current),
    NextCount is Count + 1,
    prime_index_check(P, N, Next, NextCount).

prime_index_check(P, N, Current, Count) :-
    Current < P,
    Next is Current + 1,
    \+ prime(Current),
    prime_index_check(P, N, Next, Count).