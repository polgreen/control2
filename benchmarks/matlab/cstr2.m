%%%%%%%%%%
% 
% Reaction temperature of a continuous stirred tank reactor (cstrtemp)
% 
% Extracted from:
%   Advanced PID Control. 
%   Karl J. Åström , Tore Hägglund
% Written by:
%   Iury Bessa
%   Manaus, 2018
%%%%%%%%%%
%% Continous-time transfer function

cstrtempct=tf([0.15,0.0063],[1,0.048631,-0.003359]);


%% Discretizing with Ts=0.5

ts=0.5;
cstrtemp_tf_disc1=c2d(cstrtempct,ts);
cstrtemp_ss_disc1=ss(cstrtemp_tf_disc1);

%% Discretizing with Ts=0.2

ts=0.2;
cstrtemp_tf_disc2=c2d(cstrtempct,ts);
cstrtemp_ss_disc2=ss(cstrtemp_tf_disc2);


%% Discretizing with Ts=1

ts=1;
cstrtemp_tf_disc3=c2d(cstrtempct,ts);
cstrtemp_ss_disc3=ss(cstrtemp_tf_disc3);

%% Discretizing with Ts=1.5

ts=1.5;
cstrtemp_tf_disc4=c2d(cstrtempct,ts);
cstrtemp_ss_disc4=ss(cstrtemp_tf_disc4);


%% Discretizing with Ts=2

ts=1;
cstrtemp_tf_disc5=c2d(cstrtempct,ts);
cstrtemp_ss_disc5=ss(cstrtemp_tf_disc5);

%% Discretizing with Ts=5

ts=0.005;
cstrtemp_tf_disc6=c2d(cstrtempct,ts);
cstrtemp_ss_disc6=ss(cstrtemp_tf_disc6);

%% Discretizing with Ts=0.8

ts=0.8;
cstrtemp_tf_disc7=c2d(cstrtempct,ts);
cstrtemp_ss_disc7=ss(cstrtemp_tf_disc7);

%% Saving

save('benchmark_tf','cstrtemp_tf_disc1','cstrtemp_tf_disc2','cstrtemp_tf_disc3',...
    'cstrtemp_tf_disc4','cstrtemp_tf_disc5','cstrtemp_tf_disc6','cstrtemp_tf_disc7',...
    '-append')

save('benchmark_ss','cstrtemp_ss_disc1','cstrtemp_ss_disc2','cstrtemp_ss_disc3',...
    'cstrtemp_ss_disc4','cstrtemp_ss_disc5','cstrtemp_ss_disc6','cstrtemp_ss_disc7',...
    '-append')