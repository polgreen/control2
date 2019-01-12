function res=get_charpoly()

filename = strcat('charpolys.h')
fileID = fopen(filename,'w');
fprintf(fileID, '#if NSTATES==1\n\n');

for n=9
    
%A = sym('A',[n,n]);
%B = sym('B',[n,1]);
%K = sym('K',[1,n]);
M = sym('m',[n,n]);
I = eye(n);
x = sym('x');

charpoly = det(x*I - M);
res=coeffs(charpoly,x)


fprintf(fileID, '#elif NSTATES==%d \n', n);
fprintf(fileID,'__CPROVER_EIGEN_poly[0]=1;\n');

for k=1:n
  fprintf(fileID,'__CPROVER_EIGEN_poly[%d]= ',k);
  fprintf(fileID, '%s', res(n-k+1));
  fprintf(fileID,';\n');
end  

fprintf(fileID, ' \n');
end
fprintf(fileID, '#endif \n');
  







    