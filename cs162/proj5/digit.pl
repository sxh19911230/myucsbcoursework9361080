% what is the four-digit number in which the first
% digit is one-third the second, the third is the sum
% of the first and second, and the last is three times
% the second?

digit(0).
digit(1).
digit(2).
digit(3).
digit(4).
digit(5).
digit(6).
digit(7).
digit(8).
digit(9).

digits([A, B, C, D]) :-
        digit(A),
        digit(B),
        digit(C),
        digit(D).

isSolution(Number) :-
        digits(Number),
        Number = [A, B, C, D],
        A \== 0, % prevent leading zeros
        A is B // 3,
        C is A + B,
        D is 3 * B.
