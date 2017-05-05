% given a list of numbers, compute a new list such that an entry is
% 'even' if the corresponding entry in the number list is even and
% 'odd' otherwise
%
% example query: parity([1,2,3,4], P).
% result: P = [odd, even, odd, even]

iseven(X) :- 0 is X rem 2.
isodd(X) :- 1 is X rem 2.

parity([], []).

parity([Num | NumRest], [Parity | ParityRest]) :-
        iseven(Num),
        Parity = even,
        parity(NumRest, ParityRest).

parity([Num | NumRest], [Parity | ParityRest]) :-
        isodd(Num),
        Parity = odd,
        parity(NumRest, ParityRest).
