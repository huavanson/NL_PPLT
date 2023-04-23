% Khai bao trang thai
state([0,0,0,0]).
state([1,0,1,0]).
state([0,0,1,0]).
state([1,1,1,0]).
state([0,1,0,0]).
state([1,1,0,1]).
state([0,1,0,1]).
state([1,0,1,1]).
state([0,0,1,0]).
state([1,1,1,1]).

% Khai bao rang buoc
en([X,_,Y,Y]) :- X\=Y.
en([X,Y,Y,_]) :- X\=Y.

% Khai bao hanh dong
action([X, X, Goat, Cab], [Y, Y, Goat, Cab]) :-
    state([Y, Y, Goat, Cab]),
    \+ en([Y, Y, Goat, Cab]),
    X\=Y .

action([X, Wolf, X, Cab], [Y, Wolf, Y, Cab]) :-
    state([Y, Wolf, Y, Cab]),
    \+ en([Y, Wolf, Y, Cab]),
    X\=Y.

action([X, Wolf, Goat, X], [Y, Wolf, Goat, Y]) :-
    state([Y, Wolf, Goat, Y]),
    \+ en([Y, Wolf, Goat, Y]),
    X\=Y .

action([X, Wolf, Goat, Cab], [Y, Wolf, Goat,Cab]) :-
    state([Y, Wolf, Goat,Cab]),
    \+ en([Y, Wolf, Goat,Cab]),
    X\=Y .

% Kiem tra trang thai ket thuc
goal([0,0,0,0]).

% Dinh nghia ham DFS
dfs(X, Path, [X|Path]) :- goal(X).

dfs(X,Path, Solution) :-
    action(X,Next),
    \+member(Next,Path),
    dfs(Next,[X|Path],Solution) .



