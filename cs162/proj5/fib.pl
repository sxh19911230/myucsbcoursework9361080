% get the nth fibonacci number
fib1(0,0).
fib1(1,1).
fib1(N,A) :-
  N > 1,
  Nm1 is N - 1,
  Nm2 is N - 2,
  fib1(Nm1,A1),
  fib1(Nm2,A2),
  A is A1 + A2.

% all of the following should be true:
% fib1(0,0).
% fib1(1,1).
% fib1(2,1).
% fib1(3,2).
% fib1(4,3).
% fib1(5,5).
% fib1(6,8).
% fib1(7,13).

% get the fibonacci sequence, using what
% we defined above. This is not the best
% way to do it, but it's shown for comparison
% purposes.
fibSeq1(0, [X]) :-
  fib1(0, X).
fibSeq1(N, Seq) :-
  N > 0,
  Nm1 is N - 1,
  fibSeq1(Nm1,Y),
  fib1(N, X),
  append(Y, [X], Seq).

% fibSeq1(3, [0,1,1,2]).
% fibSeq1(10, [0,1,1,2,3,5,8,13,21,34,55]).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Simpler and/or more efficient ways of what we did above:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% get nth fib number
% notice how third clause of this predicate fib2/2 doesn't
% need the check for whether N is greater than 1. If N == 1,
% then it's fine. If N == 0, then succ(N1, 0) cannot be true,
% so it stops trying to use that third clause.
fib2(0,0).
fib2(1,1).
fib2(N,A) :-
  succ(N1,N),
  succ(N2,N1),
  fib2(N1,A1),
  fib2(N2,A2),
  plus(A1,A2,A).

% get sequence of fibonacci numbers (here, produces sequence backwards)
fibSeq2rev(0, [0]).
fibSeq2rev(1, [1,0]).
fibSeq2rev(N, [C,X,Y|Ts]) :-
  succ(Nm1,N),
  fibSeq2rev(Nm1, [X,Y|Ts]),
  plus(X,Y,C).

fibSeq2(N, List) :-
  fibSeq2rev(N, Res),
  reverse(Res, List).

% fibSeq2(3, [0,1,1,2]). % should be true
% fibSeq2(10, [0,1,1,2,3,5,8,13,21,34,55]). % should be true
