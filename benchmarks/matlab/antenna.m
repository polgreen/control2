%%%%%%%%%%
% 
% Antenna Control System
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

antennact=tf(zpk([-1],[0,0,-6,-11.5,[roots([1,8,256])]'],1));


%% Discretizing with Ts=0.5

ts=0.5;
antenna_tf_disc1=c2d(antennact,ts);
antenna_ss_disc1=ss(antenna_tf_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
antenna_tf_disc2=c2d(antennact,ts);
antenna_ss_disc2=ss(antenna_tf_disc2);


%% Discretizing with Ts=0.1

ts=0.1;
antenna_tf_disc3=c2d(antennact,ts);
antenna_ss_disc3=ss(antenna_tf_disc3);

%% Discretizing with Ts=0.05

ts=0.05;
antenna_tf_disc4=c2d(antennact,ts);
antenna_ss_disc4=ss(antenna_tf_disc4);


%% Discretizing with Ts=1

ts=1;
antenna_tf_disc5=c2d(antennact,ts);
antenna_ss_disc5=ss(antenna_tf_disc5);

%% Discretizing with Ts=1.5

ts=0.005;
antenna_tf_disc6=c2d(antennact,ts);
antenna_ss_disc6=ss(antenna_tf_disc6);

%% Discretizing with Ts=0.8

ts=0.001;
antenna_tf_disc7=c2d(antennact,ts);
antenna_ss_disc7=ss(antenna_tf_disc7);

%% Saving

save('benchmark_tf','antenna_tf_disc1','antenna_tf_disc2','antenna_tf_disc3',...
    'antenna_tf_disc4','antenna_tf_disc5','antenna_tf_disc6','antenna_tf_disc7',...
    '-append')

save('benchmark_ss','antenna_ss_disc1','antenna_ss_disc2','antenna_ss_disc3',...
    'antenna_ss_disc4','antenna_ss_disc5','antenna_ss_disc6','antenna_ss_disc7',...
    '-append')
