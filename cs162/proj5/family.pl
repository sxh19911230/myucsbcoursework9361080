% geneology example
%
% some possible queries:
% ?- father(adam, peter).
% ?- son(peter, adam).
% ?- mother(M, peter).
% ?- daughter(D, P).
% ?- siblings(A, B).
% ?- descendent(paul, A).
% ?- ancestor(A, paul).

% facts: adam, peter, paul, bob, and charles are men
man(adam).
man(peter).
man(paul).
man(bob).
man(charles).

% facts: mary, eve, alice, and dolores are women
woman(mary).
woman(eve).
woman(alice).
woman(dolores).

% facts: adam is the parent of peter and paul, eve is the parent of
% peter, mary is the parent of paul, bob and alice are the parents of
% adam, charles and dolores are the parents of mary
parent(adam, peter).
parent(eve, peter).
parent(adam, paul).
parent(mary, paul).
parent(bob, adam).
parent(alice, adam).
parent(charles, mary).
parent(dolores, mary).

% F is the father of C if F is a man and F is the parent of C
father(F, C) :- man(F), parent(F, C).

% M is the mother of C if M is a woman and M is the parent of C
mother(M, C) :- woman(M), parent(M, C).

% S is the son of P if S is a man and P is the parent of S
son(S, P) :- man(S), parent(P, S).

% D is the daughter of P if D is a woman and P is the parent of D
daughter(D, P) :- woman(D), parent(P, D).

% A and B are siblings if they are distinct and have a parent in common
siblings(A, B) :- parent(P, A), parent(P, B), A \= B.

% U is the uncle of N if U is a man, U has a sibling P, and P is the
% parent of N
uncle(U, N) :- man(U), siblings(U, P), parent(P, N).

% A is the aunt of N if A is a woman, A has a sibling P, and P is the
% parent of N
aunt(A, N) :- woman(A), siblings(A, P), parent(P, N).

% H is human if H is a man or a woman
human(H) :- man(H).
human(H) :- woman(H).

% D is a descendent of A if A is a parent of D or if there is a person
% P such that P is a parent of D and P is a descendent of A
descendent(D, A) :- parent(A, D).
descendent(D, A) :- parent(P, D), descendent(P, A).

% A is an ancestor of D if D is a descendent of A
ancestor(A, D) :- descendent(D, A).
