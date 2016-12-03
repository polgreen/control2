%%%%%%%%%%
% 
% DC Motor
% 
% Extracted from:
%   Feedback Control of Dynamics Systems, 6th ed
%   Franklin, G. F.; Powell, J. D.; Emami-Naemi
% Written by:
%   Iury Bessa
%   Manaus, 2016
%%%%%%%%%%
%%

Jm=0.01;
b=0.001;
Kt=0.02;
Ke=Kt;
Ra=10;
L=1e-2;


num=[Kt];
den=[[conv([L,Ra],[Jm,b])]+[0,0,Kt*Ke]];
dcmotor_tf_cont=tf(num,den)

%% Discretizing with Ts=1

ts=1;
dcmotor_tf_disc1=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.001

ts=0.001;
dcmotor_tf_disc2=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.5

ts=0.5;
dcmotor_tf_disc3=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.2

ts=0.2;
dcmotor_tf_disc4=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.1

ts=0.1;
dcmotor_tf_disc5=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.05

ts=0.05;
dcmotor_tf_disc6=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.01

ts=0.01;
dcmotor_tf_disc7=c2d(dcmotor_tf_cont,ts);

%% Discretizing with Ts=0.005

ts=0.005;
dcmotor_tf_disc8=c2d(dcmotor_tf_cont,ts);


%% Saving

save('benchmark_tf','dcmotor_tf_disc1','dcmotor_tf_disc2','dcmotor_tf_disc3','dcmotor_tf_disc4',...
    'dcmotor_tf_disc5','dcmotor_tf_disc6','dcmotor_tf_disc7','dcmotor_tf_disc8','-append')