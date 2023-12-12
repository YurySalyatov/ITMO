% prime_table(2).
% prime_table(3).
% prime(N):- prime_table(N), !.
% prime(N):- N > 3, \+ 0 is N mod 2, loopp(3, N), D is N, assert(prime_table(D)).

% root(L, N):- Y is L * L, Y < N.
% root(L, N):- Y is L * L, Y = N.

% loopp(S, N):- root(S, N), \+ 0 is N mod S, Z is S + 2, loopp(Z, N).
% loopp(S, N):- \+root(S, N).

% composite(N):- N > 1, \+prime(N).

prime(N):- N > 1, \+composite(N).
init(N):- pred_prime(2, N).

pred_prime(K, N):- S is K * K, S =< N, \+composite(K), !, resheto(S, N, K), Y is K + 1, pred_prime(Y, N).
pred_prime(K, N):- S is K * K, S =< N, composite(K), !, Y is K + 1, pred_prime(Y, N).
pred_prime(K, N):- S is K * K, S > N.
resheto(S, N, K):- S =< N, assert(composite(S)), S1 is S + K, resheto(S1, N, K).
resheto(S, N, K):- S > N.

next_del(N, R):- 0 is (N mod 2), R is N + 1.
next_del(N, R):- 1 is (N mod 2), R is N + 2.

prime_divisors(N, D):- prim_div_table(N, D), !.
prime_divisors(N, D):- list(D), !, chek_ar(N, D, 1, 1), assert(prim_div_table(N, D)).
prime_divisors(N, D):- number(N), composite(N), !, bild_ar(N, D, 2), A is N, assert(prim_div_table(A, D)).
prime_divisors(N, [N]):- number(N), prime(N), !, assert(prim_div_table(N, [N])).
prim_div_table(1, []).

bild_ar(N, D, R):- prim_div_table(N, D), !.
bild_ar(N, [H | T], R):- N > 1, 0 is mod(N, R), H is R, Y is N / R, bild_ar(Y, T, R), assert(prim_div_table(Y, T)).
bild_ar(N, D, R):- N > 1, 0 < mod(N, R), next_del(R, R1), bild_ar(N, D, R1).

chek_ar(N, [], _, N).
chek_ar(N, [H | T], L, R) :- L =< H, prime(H), R1 is R * H, chek_ar(N, T, H, R1), Y is N / R1, assert(prim_div_table(Y, T)).

unique_prime_divisors(N, D):- u_prim_div_table(N, D), !.
unique_prime_divisors(N, D):- u_bild_ar(N, D, 2, 0).

u_prim_div_table(1, []).
u_bild_ar(N, D, R, B):- u_prim_div_table(N, D), !.
u_bild_ar(N, [H | T], R, B):- N > 1, 0 is mod(N, R), B = 0, !, H is R, Y is N / R, u_bild_ar(Y, T, R, 1).
u_bild_ar(N, D, R, B) :- N > 1, 0 is mod(N, R), B = 1, !, Y is N / R, u_bild_ar(Y, D, R, 1).
u_bild_ar(N, D, R, B):- N > 1, 0 < mod(N, R), next_del(R, R1), u_bild_ar(N, D, R1, 0).

gcd(R1, R2, GCD) :- prime_divisors(R1, D1), prime_divisors(R2, D2), find_gcd(D1, D2, GCD).

find_gcd([], _, 1):- !.
find_gcd(_, [], 1):- !.
find_gcd([H | T1], [H | T2], GCD) :- !, find_gcd(T1, T2, GCD1), GCD is GCD1 * H.
find_gcd([H1 | T1], [H2 | T2], GCD) :- H1 < H2, !, find_gcd(T1, [H2 | T2], GCD).
find_gcd([H1 | T1], [H2 | T2], GCD) :- H1 > H2, !, find_gcd([H1 | T1], T2, GCD).

lcm(R1, R2, LCM) :- prime_divisors(R1, D1), prime_divisors(R2, D2), find_lcm(D1, D2, LCM).

find_lcm([], [], 1):- !.
find_lcm([H | T1], [H | T2], LCM) :- !, find_lcm(T1, T2, LCM1), LCM is LCM1 * H.
find_lcm([H1 | T1], [H2 | T2], LCM) :- H1 < H2, !, find_lcm(T1, [H2 | T2], LCM1), LCM is LCM1 * H1.
find_lcm([H1 | T1], [H2 | T2], LCM) :- H1 > H2, !, find_lcm([H1 | T1], T2, LCM1), LCM is LCM1 * H2.
find_lcm([], [H | T], LCM):- !, find_lcm([], T, LCM1), LCM is LCM1 * H.
find_lcm([H | T], [], LCM):- !, find_lcm(T, [], LCM1), LCM is LCM1 * H.


prime_palindrome(N, K):- prime(N), rev_k_sistem(N, K, D), ret_fr_k_sistem(0, R, K, D), R = N.

rev_k_sistem(N, K, [H]) :- N < K, H is N.
rev_k_sistem(N, K, [H | T]):- N >= K, H is N mod K, Y is (N - H) / K, rev_k_sistem(Y, K, T).

ret_fr_k_sistem(R, R, K, []) :- !.
ret_fr_k_sistem(S, R, K, [H | T]) :- S1 is S * K + H, ret_fr_k_sistem(S1, R, K, T).