A = [-1.999909737361046 -1.000000000000000;1 0];
B = [4;0], 
C = [-1.756887232846049 -1.749455660776409];
D = 9.800000000000000
K = [-0.5898 -0.1914];

A_ = A-B*K;
B_ = B;
C_= C-D*K;
D_= D;

sys = ss(A,B,C,D, 0.002);

roots = eig(F);

dstep(A_,B_,C_,D_)

set(findall(gcf,'-property','FontSize'),'FontSize',22)

