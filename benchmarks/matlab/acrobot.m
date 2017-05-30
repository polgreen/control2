%%%%%%%%%%
% 
% Acrobot - Robot Manipulator
% 
% Extracted from:
%   Optimal Control of Weakly Coupled Systems and Applications
%   Z. Gaji\'c, M-T. Lim, D. Skatari\'c, W-C. Su, V. Kecman
%   Taylor & Francis (CRC Press), 2008
% Written by:
%   Iury Bessa
%   Manaus, 2017
%%%%%%%%%%
%% Continous-time transfer function
A=[zeros(2,2),eye(2);[12.49,-12.54;-14.49,29.36],zeros(2,2)];
B=[0,0,-2.98,5.98]';
C=[1,0,1,0];
D=0;
acrobotct=ss(A,B,C,D);


%% Discretizing with Ts=0.5

ts=0.5;
acrobot_ss_disc1=c2d(acrobotct,ts);
acrobot_tf_disc1=tf(acrobot_ss_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
acrobot_ss_disc2=c2d(acrobotct,ts);
acrobot_tf_disc2=tf(acrobot_ss_disc2);


%% Discretizing with Ts=0.1

ts=0.1;
acrobot_ss_disc3=c2d(acrobotct,ts);
acrobot_tf_disc3=tf(acrobot_ss_disc3);

%% Discretizing with Ts=0.05

ts=0.05;
acrobot_ss_disc4=c2d(acrobotct,ts);
acrobot_tf_disc4=tf(acrobot_ss_disc4);


%% Discretizing with Ts=1

ts=1;
acrobot_ss_disc5=c2d(acrobotct,ts);
acrobot_tf_disc5=tf(acrobot_ss_disc5);

%% Discretizing with Ts=1.5

ts=0.005;
acrobot_ss_disc6=c2d(acrobotct,ts);
acrobot_tf_disc6=tf(acrobot_ss_disc6);

%% Discretizing with Ts=0.8

ts=0.001;
acrobot_ss_disc7=c2d(acrobotct,ts);
acrobot_tf_disc7=tf(acrobot_ss_disc7);

%% Saving

save('benchmark_tf','acrobot_tf_disc1','acrobot_tf_disc2','acrobot_tf_disc3',...
    'acrobot_tf_disc4','acrobot_tf_disc5','acrobot_tf_disc6','acrobot_tf_disc7',...
    '-append')

save('benchmark_ss','acrobot_ss_disc1','acrobot_ss_disc2','acrobot_ss_disc3',...
    'acrobot_ss_disc4','acrobot_ss_disc5','acrobot_ss_disc6','acrobot_ss_disc7',...
    '-append')
    