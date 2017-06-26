%%%%%%%%%%
% 
% Voltage regulator
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

A=[-0.2,0.5,0,0,0;0,-0.5,1.6,0,0;0,0,-14.28,85.71,0;zeros(2,3),[-25,75;0,-10]];
B=[0,0,0,0,30]';
C=[1,0,0,0,0];
D=0;

regulatorct=ss(A,B,C,D);


%% Discretizing with Ts=0.5

ts=0.5;
regulator_ss_disc1=c2d(regulatorct,ts);
regulator_tf_disc1=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
regulator_ss_disc2=c2d(regulatorct,ts);
regulator_tf_disc2=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.1

ts=0.1;
regulator_ss_disc3=c2d(regulatorct,ts);
regulator_tf_disc3=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.05

ts=0.05;
regulator_ss_disc4=c2d(regulatorct,ts);
regulator_tf_disc4=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.025

ts=0.025;
regulator_ss_disc5=c2d(regulatorct,ts);
regulator_tf_disc5=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.01

ts=0.01;
regulator_ss_disc6=c2d(regulatorct,ts);
regulator_tf_disc6=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.005

ts=0.005;
regulator_ss_disc7=c2d(regulatorct,ts);
regulator_tf_disc7=tf(regulator_ss_disc1);

%% Discretizing with Ts=0.001

ts=0.001;
regulator_ss_disc8=c2d(regulatorct,ts);
regulator_tf_disc8=tf(regulator_ss_disc1);

%% Saving

save('benchmark_tf','regulator_tf_disc1','regulator_tf_disc2','regulator_tf_disc3',...
    'regulator_tf_disc4','regulator_tf_disc5','regulator_tf_disc6','regulator_tf_disc7',...
    '-append')

save('benchmark_ss','regulator_ss_disc1','regulator_ss_disc2','regulator_ss_disc3',...
    'regulator_ss_disc4','regulator_ss_disc5','regulator_ss_disc6','regulator_ss_disc7',...
    '-append')
