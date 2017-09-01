function bound = maxstate(A,xmax)

% This function computes the maximum values of states that could be achieved
% based on norm 1 of system and norm inf of states. The input matrix 'A' is
% contains the dynamics of the linear system and xmax is the norm inf of the 
% states x
% 
% Iury Bessa
% Manaus, 2017

bound=xmax*max(sum(abs(A)));

end