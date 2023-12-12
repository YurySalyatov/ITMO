prime(N):- prime_table(N).
composite(N) :- composite_table(N).
init(N):- pred_prime(2, N).

pred_prime(K, N):- S is K * K, (S < N ; S = N), \+composite(K), !, assert(prime_table(K)), resheto(S, N, K), Y is K + 1, pred_prime(Y, N).
pred_prime(K, N):- S is K * K, (S < N ; S = N), composite(K), !, Y is K + 1, pred_prime(Y, N).
pred_prime(K, N):- S is K * K, S > N.
resheto(S, N, K):- (S < N ; S = N), assert(composite_table(S)), S1 is S + K, resheto(S1, N, K).
resheto(S, N, K):- S > N.
