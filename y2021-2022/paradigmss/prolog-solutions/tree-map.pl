map_build_(0, [], null).
map_build_(N, ListMap, TreeMap) :- N1 is (N - 1) // 2, N2 is N - 1 - N1, find_root(ListMap, P, R1, R2, N, 1), map_build_(N1, R1, L),
		map_build_(N2, R2, R), TreeMap = node(P, L, R), !.
map_build(ListMap, TreeMap) :- len(ListMap, N), map_build_(N, ListMap, TreeMap).

map_get(TreeMap, Key, Value) :- node((Key, Value), _, _) = TreeMap, !.
map_get(TreeMap, Key, Value) :- node((K, V), L, _) = TreeMap, Key < K, !, \+ L = null, map_get(L, Key, Value).
map_get(TreeMap, Key, Value) :- node((K, V), _, R) = TreeMap, Key > K, !, \+ R = null, map_get(R, Key, Value).

len([], 0).
len([H | T], R):- len(T, R1), R is R1 + 1.

find_root([H | List], Parent, [H | R1], R2, Len, N) :- S is N + N, S < Len, N1 is N + 1,
		find_root(List, Parent, R1, R2, Len, N1).
find_root([H | List], Parent, R1, R2, Len, N):- S is N + N, S >= Len, R1 = [], R2 = List, Parent = H.

map_minKey(node((K, _), null, _), K):- !.
map_minKey(node((K, _), L, _), Key):-map_minKey(L, Key).

map_maxKey(node((K, _), _, null), K):- !.
map_maxKey(node((K, _), _, R), Key):-map_maxKey(R, Key).