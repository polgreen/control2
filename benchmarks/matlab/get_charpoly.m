function res=get_charpoly(n)


A = sym('A',[n,n]);
B = sym('B',[n,1]);
K = sym('K',[1,n]);
I = eye(n);
x = sym('x');

charpoly = det(x*I - (A-B*K));
res = coeffs(charpoly,x)

    