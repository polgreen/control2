%%%%%%%%%%
% 
% Simple Magnetic Suspension System
% 
% Extracted from:
%   Feedback Control of Dynamics Systems, 6th ed
%   Franklin, G. F.; Powell, J. D.; Emami-Naemi
% Written by:
%   Iury Bessa
%   Manaus, 2016
%%%%%%%%%%
%%


num=[2500];
den=[1,0,-1000];
magsuspension_tf_cont=tf(num,den)

%% Discretizing with Ts=1

ts=1;
magsuspension_tf_disc1=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.001

ts=0.001;
magsuspension_tf_disc2=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.5

ts=0.5;
magsuspension_tf_disc3=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.2

ts=0.2;
magsuspension_tf_disc4=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.1

ts=0.1;
magsuspension_tf_disc5=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.05

ts=0.05;
magsuspension_tf_disc6=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.01

ts=0.01;
magsuspension_tf_disc7=c2d(magsuspension_tf_cont,ts);

%% Discretizing with Ts=0.005

ts=0.005;
magsuspension_tf_disc8=c2d(magsuspension_tf_cont,ts);


%% Saving

save('benchmark_tf','magsuspension_tf_disc1','magsuspension_tf_disc2','magsuspension_tf_disc3','magsuspension_tf_disc4',...
    'magsuspension_tf_disc5','magsuspension_tf_disc6','magsuspension_tf_disc7','magsuspension_tf_disc8','-append')