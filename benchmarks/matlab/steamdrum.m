%%%%%%%%%%
% 
% Level control of boiler steam drum
% 
% Extracted from:
%   Luyben, W.L., 1998. External versus internal unstable processes. 
%   Ind. Eng. Chem. Res. 37, 2713�2720
%   DOI: 10.1021/ie9800400
% Written by:
%   Iury Bessa
%   Manaus, 2018
%%%%%%%%%%
%% Continuous-time transfer function

steamdrum=0.547*tf([-0.418],[1.06,1,0],'InputDelay',0.1);
steamdrum_wo_delay=tf(steamdrum.num,steamdrum.den);


%% Discretizing with Ts=0.1

ts=0.1;
pade_delay1=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc1=pade_delay1*c2d(steamdrum,ts);
steamdrum_ss_disc1=ss(steamdrum_tf_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
pade_delay2=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc2=pade_delay2*c2d(steamdrum,ts);
steamdrum_ss_disc2=ss(steamdrum_tf_disc2);


%% Discretizing with Ts=0.25

ts=0.25;
pade_delay3=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc3=pade_delay3*c2d(steamdrum,ts);
steamdrum_ss_disc3=ss(steamdrum_tf_disc3);


%% Discretizing with Ts=0.6

ts=0.6;
pade_delay4=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc4=pade_delay4*c2d(steamdrum,ts);
steamdrum_ss_disc4=ss(steamdrum_tf_disc4);


%% Discretizing with Ts=0.75

ts=0.75;
pade_delay5=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc5=pade_delay5*c2d(steamdrum,ts);
steamdrum_ss_disc5=ss(steamdrum_tf_disc5);



%% Discretizing with Ts=1.2

ts=1.2;
pade_delay6=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc6=pade_delay6*c2d(steamdrum,ts);
steamdrum_ss_disc6=ss(steamdrum_tf_disc6);


%% Discretizing with Ts=1.5

ts=1.5;
pade_delay7=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc7=pade_delay7*c2d(steamdrum,ts);
steamdrum_ss_disc7=ss(steamdrum_tf_disc7);

%% Discretizing with Ts=1.75

ts=1.75;
pade_delay8=thiran(steamdrum.InputDelay,ts);
steamdrum_tf_disc8=pade_delay8*c2d(steamdrum,ts);
steamdrum_ss_disc8=ss(steamdrum_tf_disc8);



%% Saving

save('benchmark_tf','steamdrum_tf_disc1','steamdrum_tf_disc2','steamdrum_tf_disc3',...
    'steamdrum_tf_disc4','steamdrum_tf_disc5','steamdrum_tf_disc6','steamdrum_tf_disc7',...
    'steamdrum_tf_disc8','-append')

save('benchmark_ss','steamdrum_ss_disc1','steamdrum_ss_disc2','steamdrum_ss_disc3',...
    'steamdrum_ss_disc4','steamdrum_ss_disc5','steamdrum_ss_disc6','steamdrum_ss_disc7',...
    'steamdrum_ss_disc8','-append')
