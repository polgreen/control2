function res=get_charpoly(n)


A = sym('a',[n,n]);
B = sym('b',[n,1]);
K = sym('k',[1,n]);
I = eye(n);
x = sym('x');

charpoly = det(x*I - (A-B*K));
res = coeffs(charpoly,x)

    