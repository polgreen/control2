%%%%%%%%%%
% 
% Flexible beam
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

num=[1.65,-0.331,576,90.6,19080];
den=[1,0.996,463,97.8,12131,8.11,0];
flexbeamct=tf(num,den);


%% Discretizing with Ts=0.5

ts=0.5;
flexbeam_tf_disc1=c2d(flexbeamct,ts);
flexbeam_ss_disc1=ss(flexbeam_tf_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
flexbeam_tf_disc2=c2d(flexbeamct,ts);
flexbeam_ss_disc2=ss(flexbeam_tf_disc2);


%% Discretizing with Ts=0.1

ts=0.1;
flexbeam_tf_disc3=c2d(flexbeamct,ts);
flexbeam_ss_disc3=ss(flexbeam_tf_disc3);

%% Discretizing with Ts=0.05

ts=0.05;
flexbeam_tf_disc4=c2d(flexbeamct,ts);
flexbeam_ss_disc4=ss(flexbeam_tf_disc4);


%% Discretizing with Ts=0.01

ts=0.01;
flexbeam_tf_disc5=c2d(flexbeamct,ts);
flexbeam_ss_disc5=ss(flexbeam_tf_disc5);

%% Discretizing with Ts=0.005

ts=0.005;
flexbeam_tf_disc6=c2d(flexbeamct,ts);
flexbeam_ss_disc6=ss(flexbeam_tf_disc6);

%% Discretizing with Ts=0.001

ts=0.001;
flexbeam_tf_disc7=c2d(flexbeamct,ts);
flexbeam_ss_disc7=ss(flexbeam_tf_disc7);

%% Saving

save('benchmark_tf','flexbeam_tf_disc1','flexbeam_tf_disc2','flexbeam_tf_disc3',...
    'flexbeam_tf_disc4','flexbeam_tf_disc5','flexbeam_tf_disc6','flexbeam_tf_disc7',...
    '-append')

save('benchmark_ss','flexbeam_ss_disc1','flexbeam_ss_disc2','flexbeam_ss_disc3',...
    'flexbeam_ss_disc4','flexbeam_ss_disc5','flexbeam_ss_disc6','flexbeam_ss_disc7',...
    '-append')
