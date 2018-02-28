%%%%%%%%%%
% 
% Bioreactor 
% 
% Extracted from:
%   Closed loop identification of transfer function model for unstable 
%   bioreactors for tuning PID controllers. In Bioprocess Engineering,
%   vol. 22 , no. 2, 
%   pp. 185-188, Feb 2000.
%   DOI: 10.1007/s004499900077
% Written by:
%   Iury Bessa
%   Manaus, 2018
%%%%%%%%%%
%% Continuous-time transfer function

bioreact=tf([-5.9],[5.89,-1],'InputDelay',1);
bioreact_wo_delay=tf(bioreact.num,bioreact.den);


%% Discretizing with Ts=0.8

ts=0.8;
pade_delay1=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc1=pade_delay1*c2d(bioreact,ts);
bioreact_ss_disc1=ss(bioreact_tf_disc1);

%% Discretizing with Ts=0.5

ts=0.5;
pade_delay2=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc2=pade_delay2*c2d(bioreact,ts);
bioreact_ss_disc2=ss(bioreact_tf_disc2);


%% Discretizing with Ts=1

ts=1;
pade_delay3=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc3=pade_delay3*c2d(bioreact,ts);
bioreact_ss_disc3=ss(bioreact_tf_disc3);


%% Discretizing with Ts=1.2

ts=1.2;
pade_delay4=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc4=pade_delay4*c2d(bioreact,ts);
bioreact_ss_disc4=ss(bioreact_tf_disc4);


%% Discretizing with Ts=1.5

ts=1.5;
pade_delay5=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc5=pade_delay5*c2d(bioreact,ts);
bioreact_ss_disc5=ss(bioreact_tf_disc5);



%% Discretizing with Ts=1.8

ts=1.8;
pade_delay6=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc6=pade_delay6*c2d(bioreact,ts);
bioreact_ss_disc6=ss(bioreact_tf_disc6);


%% Discretizing with Ts=2

ts=2;
pade_delay7=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc7=pade_delay7*c2d(bioreact,ts);
bioreact_ss_disc7=ss(bioreact_tf_disc7);

%% Discretizing with Ts=2.2

ts=2.2;
pade_delay8=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc8=pade_delay8*c2d(bioreact,ts);
bioreact_ss_disc8=ss(bioreact_tf_disc8);


%% Discretizing with Ts=2.5

ts=2.5;
pade_delay9=thiran(bioreact.InputDelay,ts);
bioreact_tf_disc9=pade_delay9*c2d(bioreact,ts);
bioreact_ss_disc9=ss(bioreact_tf_disc9);

%% Saving

save('benchmark_tf','bioreact_tf_disc1','bioreact_tf_disc2','bioreact_tf_disc3',...
    'bioreact_tf_disc4','bioreact_tf_disc5','bioreact_tf_disc6','bioreact_tf_disc7',...
    'bioreact_tf_disc8','bioreact_tf_disc9','-append')

save('benchmark_ss','bioreact_ss_disc1','bioreact_ss_disc2','bioreact_ss_disc3',...
    'bioreact_ss_disc4','bioreact_ss_disc5','bioreact_ss_disc6','bioreact_ss_disc7',...
    'bioreact_ss_disc8','bioreact_ss_disc9','-append')
