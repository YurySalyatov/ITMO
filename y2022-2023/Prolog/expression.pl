all_member([], _).
all_member([H | T], Values) :- member(H, Values), all_member(T, Values).

nvar(V, T) :- var(V).
nvar(V, T) :- nonvar(V), call(T).


evaluate(const(R), _, R).
evaluate(variable(E), [(E, R) | T], R).
evaluate(variable(E), [_ | T], R) :- evaluate(variable(E), T, R).
 
evaluate(operation(Op, A, B), D, R):- evaluate(A, D, AR), evaluate(B, D, BR), oper(Op, AR, BR, R).
oper(op_add, A, B, R) :- R is A + B.
oper(op_subtract, A, B, R) :- R is A - B.
oper(op_multiply, A, B, R) :- R is A * B.
oper(op_divide, A, B, R) :- R is A / B.

evaluate(operation(Op, A), D, R):- evaluate(A, D, AR), oper(Op, AR, R).
oper(op_negate, A, R) :- R is 0 - A.
example(E):-
	E = operation(op_subtract,
        operation(op_multiply,
            const(2),
            variable(x)
        ),
        const(3)
    ).

:- load_library('alice.tuprolog.lib.DCGLibrary').
expr_suf_p(variable(Name)) -->
	{ nvar(Name, atom_chars(Name, Chars)) },
	chars_p(Chars),
	{ Chars = [_ | _], atom_chars(Name, Chars) }.
chars_p([]) --> [].
chars_p([' ' | T]) --> chars_p(T).
chars_p(['X' | T]) --> ['x'], {chekT(T)}.
chars_p(['Y' | T]) --> ['y'], {chekT(T)}.
chars_p(['Z' | T]) --> ['z'], {chekT(T)}.
chars_p(['x' | T]) --> ['x'], {chekT(T)}.
chars_p(['y' | T]) --> ['y'], {chekT(T)}.
chars_p(['z' | T]) --> ['z'], {chekT(T)}.
chekT([]).
chekT([H | T]) :- member(H, ['x', 'y', 'z', 'X', 'Y', 'Z', ' ']), chekT(T).
expr_suf_p(const(Value)) --> 
	{ nvar(Value, number_chars(Value, Chars)) },
  digits_p(Chars),
  { Chars = [_ | _], number_chars(Value, Chars) }.
digits_p([]) --> [].
digits_p([H | T]) -->
	{ member(H, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'])},
  [H],
  digits_p(T).
digits_p([' '| T]) --> digits_p(T).
op_p(op_add) --> ['+'].
op_p(op_subtract) --> ['-'].
op_p(op_multiply) --> ['*'].
op_p(op_divide) --> ['/'].
op_p(op_negate) --> ['n', 'e', 'g', 'a', 't', 'e'].

expr_suf_p(operation(Op, A, B)) -->
	['('], expr_suf_p(A), [' '], expr_suf_p(B), [' '], op_p(Op), [')'].

suffix_str(E, A) :- ground(E), phrase(expr_suf_p(E), C), atom_chars(A, C).
suffix_str(E, A) :- atom(A), atom_chars(A, C), phrase(expr_suf_p(E), C).