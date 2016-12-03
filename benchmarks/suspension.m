%%%%%%%%%%
% 
% Suspension model
% 
% Extracted from:
%   Feedback Control of Dynamics Systems, 6th ed
%   Franklin, G. F.; Powell, J. D.; Emami-Naemi
% Written by:
%   Iury Bessa
%   Manaus, 2016
%%%%%%%%%%
%%

m1=20;
m2=375;
ks=13e4;
kw=1e6;
b=9.8e3;

num=(kw*b/(m1*m2))*[1,ks/b];
den=[1,b*(1/m1+1/m2),(ks/m1+ks/m2+kw/m1),(kw*b/(m1*m2)),(kw*ks/(m1*m2))];
suspension_tf_cont=tf(num,den)

%% Discretizing with Ts=1

ts=1;
suspension_tf_disc1=c2d(suspension_tf_cont,ts,'matched');

%% Discretizing with Ts=1.5

ts=1.5;
suspension_tf_disc2=c2d(suspension_tf_cont,ts,'matched');

%% Discretizing with Ts=0.5

ts=0.5;
suspension_tf_disc3=c2d(suspension_tf_cont,ts,'matched');

%% Discretizing with Ts=0.2

ts=0.2;
suspension_tf_disc4=c2d(suspension_tf_cont,ts,'matched');

%% Discretizing with Ts=0.1

ts=0.1;
suspension_tf_disc5=c2d(suspension_tf_cont,ts,'matched');

%% Discretizing with Ts=0.05

ts=0.05;
suspension_tf_disc6=c2d(suspension_tf_cont,ts,'matched');

%% Discretizing with Ts=0.01

ts=0.01;
suspension_tf_disc7=c2d(suspension_tf_cont,ts,'matched');

%% Saving

save('benchmark_tf','suspension_tf_disc1','suspension_tf_disc2','suspension_tf_disc3','suspension_tf_disc4',...
    'suspension_tf_disc5','suspension_tf_disc6','suspension_tf_disc7','-append')