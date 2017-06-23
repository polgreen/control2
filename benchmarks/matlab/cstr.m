%%%%%%%%%%
% 
% PH model of a continuous stirred tank reactor (CSTR)
% 
% Extracted from:
%   Control of Neutralization Processes by RobustLoopshaping. In
%   IEEE Transactions on Control Systems Technology, vol. 8, no. 2, 
%   pp. 236-246, Mar 2000.
%   DOI: 10.1109/87.826795
% Written by:
%   Iury Bessa
%   Manaus, 2017
%%%%%%%%%%
%% Continous-time transfer function

cstrct=tf([-0.9580e-4,-0.01197e-4],[1,0.5250,0.01265,0.000078]);


%% Discretizing with Ts=0.5

ts=0.5;
cstr_tf_disc1=c2d(cstrct,ts);
cstr_ss_disc1=ss(cstr_tf_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
cstr_tf_disc2=c2d(cstrct,ts);
cstr_ss_disc2=ss(cstr_tf_disc2);


%% Discretizing with Ts=1

ts=1;
cstr_tf_disc3=c2d(cstrct,ts);
cstr_ss_disc3=ss(cstr_tf_disc3);

%% Discretizing with Ts=1.5

ts=1.5;
cstr_tf_disc4=c2d(cstrct,ts);
cstr_ss_disc4=ss(cstr_tf_disc4);


%% Discretizing with Ts=2

ts=1;
cstr_tf_disc5=c2d(cstrct,ts);
cstr_ss_disc5=ss(cstr_tf_disc5);

%% Discretizing with Ts=5

ts=0.005;
cstr_tf_disc6=c2d(cstrct,ts);
cstr_ss_disc6=ss(cstr_tf_disc6);

%% Discretizing with Ts=0.8

ts=0.001;
cstr_tf_disc7=c2d(cstrct,ts);
cstr_ss_disc7=ss(cstr_tf_disc7);

%% Saving

save('benchmark_tf','cstr_tf_disc1','cstr_tf_disc2','cstr_tf_disc3',...
    'cstr_tf_disc4','cstr_tf_disc5','cstr_tf_disc6','cstr_tf_disc7',...
    '-append')

save('benchmark_ss','cstr_ss_disc1','cstr_ss_disc2','cstr_ss_disc3',...
    'cstr_ss_disc4','cstr_ss_disc5','cstr_ss_disc6','cstr_ss_disc7',...
    '-append')