%%%%%%%%%%
% 
% Helicopter Longitudinal Motion
% 
% Extracted from:
%   Feedback Control of Dynamics Systems, 6th ed
%   Franklin, G. F.; Powell, J. D.; Emami-Naemi
% Written by:
%   Iury Bessa
%   Manaus, 2016
%%%%%%%%%%
%%


num=9.8*[1,-0.5,6.3];
den=conv([1,0.66],[1,-0.24,0.15]);
helicopter_tf_cont=tf(num,den)

%% Discretizing with Ts=1

ts=1;
helicopter_tf_disc1=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.001

ts=0.001;
helicopter_tf_disc2=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.5

ts=0.5;
helicopter_tf_disc3=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.2

ts=0.2;
helicopter_tf_disc4=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.1

ts=0.1;
helicopter_tf_disc5=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.05

ts=0.05;
helicopter_tf_disc6=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.01

ts=0.01;
helicopter_tf_disc7=c2d(helicopter_tf_cont,ts);

%% Discretizing with Ts=0.005

ts=0.005;
helicopter_tf_disc8=c2d(helicopter_tf_cont,ts);


%% Saving

save('benchmark_tf','helicopter_tf_disc1','helicopter_tf_disc2','helicopter_tf_disc3','helicopter_tf_disc4',...
    'helicopter_tf_disc5','helicopter_tf_disc6','helicopter_tf_disc7','helicopter_tf_disc8','-append')