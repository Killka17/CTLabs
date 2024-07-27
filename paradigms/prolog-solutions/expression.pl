:- load_library('alice.tuprolog.lib.DCGLibrary').
find(K, [(K, V) | _], V).
find(K, [_ | T], V) :- find(K, T, V).

nonvar(V, _) :- var(V).
nonvar(V, T) :- nonvar(V), call(T).

operation(op_add, A, B, R) :- R is A + B.
operation(op_subtract, A, B, R) :- R is A - B.
operation(op_multiply, A, B, R) :- R is A * B.
operation(op_divide, A, B, R) :- R is A / B.
operation(op_negate, A, R) :- R is -A.
operation(op_cube, A, R) :- R is A**3.
operation(op_cbrt, A, R) :- A < 0, R is -1 * abs(A)**(1/3); R is A**(1/3).

evaluate(const(A), _, A) :- !.
evaluate(variable(N), Variables, R) :- find(N, Variables, R), !.
evaluate(operation(Operaion, A, B), Variables, R) :-
    evaluate(A, Variables, AR),
    evaluate(B, Variables, BR),
    operation(Operaion, AR, BR, R), !.
evaluate(operation(Operaion, A), Variables, R) :-
    evaluate(A, Variables, AR),
    operation(Operaion, AR, R), !.

digits_p([]) --> [].
digits_p([H | T]) -->
  { member(H, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '-'])},
  [H],
  digits_p(T).

op_sign(op_add) --> ['+'].
op_sign(op_subtract) --> ['-'].
op_sign(op_multiply) --> ['*'].
op_sign(op_divide) --> ['/'].
op_sign(op_cube) --> ['c', 'u', 'b', 'e'].
op_sign(op_cbrt) --> ['c', 'b', 'r', 't'].
op_sign(op_negate) --> ['n', 'e', 'g', 'a', 't', 'e'].

skipWhiteSpaces --> [].
skipWhiteSpaces --> [' '], skipWhiteSpaces.

expr_p(variable(Name)) --> skipWhiteSpaces, [Name], { member(Name, [x, y, z]) }, skipWhiteSpaces.

expr_p(const(Value)) -->
  skipWhiteSpaces,
  { nonvar(Value, number_chars(Value, Chars)) },
  digits_p(Chars),
  { Chars = [_ | _], \+ Chars = ['-'], \+ Chars = ['.'], number_chars(Value, Chars) }, skipWhiteSpaces.

expr_p(operation(Operaion, A, B)) --> skipWhiteSpaces, ['('], skipWhiteSpaces, op_sign(Operaion), [' '], expr_p(A), [' '], expr_p(B), [')'], skipWhiteSpaces.
expr_p(operation(Operaion, A)) --> skipWhiteSpaces, ['('], skipWhiteSpaces, op_sign(Operaion), [' '], expr_p(A), [')'], skipWhiteSpaces.

prefix_str(E, A) :- ground(E), phrase(expr_p(E), C), atom_chars(A, C), !.
prefix_str(E, A) :- atom(A), atom_chars(A, C), phrase(expr_p(E), C), !.
