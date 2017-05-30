%%%%%%%%%%
% 
% Examples from Chen et. al
% 
% Extracted from:
%   Reduction of Transfer Functions by the Stability-Equation Method. In?
%   Journal of the Franklin Institute 308(4):389–404. October 1979
%   DOI: 10.1016/0016-0032(79)90066-8
% Written by:
%   Iury Bessa
%   Manaus, 2017
%%%%%%%%%%
%% Continous-time transfer function

num=[1];
den=[1,6,11,6];
chen_ex1=tf(num,den);


num=[35,1086,13825,82402,278376,511812,482964,194480];
den=[1,33,437,3017,11870,27470,37492,28880,9600];
chen_ex2=tf(num,den);

num=[1,32.5,380,2070,5424,2240];
den=[1,15,124,630,2144,4600,5856,2880];
chen_ex3=tf(num,den);

num=[1,35,291,1093,1700];
den=[1,9,66,294,1029,2541,4684,5856,4929,1700];
chen_ex4=tf(num,den);

%% Discretizing with Ts=0.5

ts=0.5;
chen_ex1_tf_disc1=c2d(chen_ex1,ts);
chen_ex2_tf_disc1=c2d(chen_ex2,ts);
chen_ex3_tf_disc1=c2d(chen_ex3,ts);
chen_ex4_tf_disc1=c2d(chen_ex4,ts);

chen_ex1_ss_disc1=ss(chen_ex1_tf_disc1);
chen_ex2_ss_disc1=ss(chen_ex2_tf_disc1);
chen_ex3_ss_disc1=ss(chen_ex3_tf_disc1);
chen_ex4_ss_disc1=ss(chen_ex4_tf_disc1);


%% Discretizing with Ts=0.2

ts=0.2;
chen_ex1_tf_disc2=c2d(chen_ex1,ts);
chen_ex2_tf_disc2=c2d(chen_ex2,ts);
chen_ex3_tf_disc2=c2d(chen_ex3,ts);
chen_ex4_tf_disc2=c2d(chen_ex4,ts);

chen_ex1_ss_disc2=ss(chen_ex1_tf_disc2);
chen_ex2_ss_disc2=ss(chen_ex2_tf_disc2);
chen_ex3_ss_disc2=ss(chen_ex3_tf_disc2);
chen_ex4_ss_disc2=ss(chen_ex4_tf_disc2);


%% Discretizing with Ts=0.1

ts=0.1;
chen_ex1_tf_disc3=c2d(chen_ex1,ts);
chen_ex2_tf_disc3=c2d(chen_ex2,ts);
chen_ex3_tf_disc3=c2d(chen_ex3,ts);
chen_ex4_tf_disc3=c2d(chen_ex4,ts);

chen_ex1_ss_disc3=ss(chen_ex1_tf_disc3);
chen_ex2_ss_disc3=ss(chen_ex2_tf_disc3);
chen_ex3_ss_disc3=ss(chen_ex3_tf_disc3);
chen_ex4_ss_disc3=ss(chen_ex4_tf_disc3);


%% Discretizing with Ts=0.05

ts=0.05;
chen_ex1_tf_disc4=c2d(chen_ex1,ts);
chen_ex2_tf_disc4=c2d(chen_ex2,ts);
chen_ex3_tf_disc4=c2d(chen_ex3,ts);
chen_ex4_tf_disc4=c2d(chen_ex4,ts);

chen_ex1_ss_disc4=ss(chen_ex1_tf_disc4);
chen_ex2_ss_disc4=ss(chen_ex2_tf_disc4);
chen_ex3_ss_disc4=ss(chen_ex3_tf_disc4);
chen_ex4_ss_disc4=ss(chen_ex4_tf_disc4);


%% Discretizing with Ts=0.01

ts=0.01;
chen_ex1_tf_disc5=c2d(chen_ex1,ts);
chen_ex2_tf_disc5=c2d(chen_ex2,ts);
chen_ex3_tf_disc5=c2d(chen_ex3,ts);
chen_ex4_tf_disc5=c2d(chen_ex4,ts);

chen_ex1_ss_disc5=ss(chen_ex1_tf_disc5);
chen_ex2_ss_disc5=ss(chen_ex2_tf_disc5);
chen_ex3_ss_disc5=ss(chen_ex3_tf_disc5);
chen_ex4_ss_disc5=ss(chen_ex4_tf_disc5);

%% Discretizing with Ts=0.005

ts=0.005;
chen_ex1_tf_disc6=c2d(chen_ex1,ts);
chen_ex2_tf_disc6=c2d(chen_ex2,ts);
chen_ex3_tf_disc6=c2d(chen_ex3,ts);
chen_ex4_tf_disc6=c2d(chen_ex4,ts);

chen_ex1_ss_disc6=ss(chen_ex1_tf_disc6);
chen_ex2_ss_disc6=ss(chen_ex2_tf_disc6);
chen_ex3_ss_disc6=ss(chen_ex3_tf_disc6);
chen_ex4_ss_disc6=ss(chen_ex4_tf_disc6);


%% Discretizing with Ts=0.001

ts=0.001;
chen_ex1_tf_disc7=c2d(chen_ex1,ts);
chen_ex2_tf_disc7=c2d(chen_ex2,ts);
chen_ex3_tf_disc7=c2d(chen_ex3,ts);
chen_ex4_tf_disc7=c2d(chen_ex4,ts);

chen_ex1_ss_disc7=ss(chen_ex1_tf_disc7);
chen_ex2_ss_disc7=ss(chen_ex2_tf_disc7);
chen_ex3_ss_disc7=ss(chen_ex3_tf_disc7);
chen_ex4_ss_disc7=ss(chen_ex4_tf_disc7);




%% Saving

save('benchmark_tf',...
    'chen_ex1_tf_disc1','chen_ex2_tf_disc1','chen_ex3_tf_disc1','chen_ex4_tf_disc1',...
    'chen_ex1_tf_disc2','chen_ex2_tf_disc2','chen_ex3_tf_disc2','chen_ex4_tf_disc2',...
    'chen_ex1_tf_disc3','chen_ex2_tf_disc3','chen_ex3_tf_disc3','chen_ex4_tf_disc3',...
    'chen_ex1_tf_disc4','chen_ex2_tf_disc4','chen_ex3_tf_disc4','chen_ex4_tf_disc4',...
    'chen_ex1_tf_disc5','chen_ex2_tf_disc5','chen_ex3_tf_disc5','chen_ex4_tf_disc5',...
    'chen_ex1_tf_disc6','chen_ex2_tf_disc6','chen_ex3_tf_disc6','chen_ex4_tf_disc6',...
    'chen_ex1_tf_disc7','chen_ex2_tf_disc7','chen_ex3_tf_disc7','chen_ex4_tf_disc7',...
    '-append')

save('benchmark_ss',...
    'chen_ex1_ss_disc1','chen_ex2_ss_disc1','chen_ex3_ss_disc1','chen_ex4_ss_disc1',...
    'chen_ex1_ss_disc2','chen_ex2_ss_disc2','chen_ex3_ss_disc2','chen_ex4_ss_disc2',...
    'chen_ex1_ss_disc3','chen_ex2_ss_disc3','chen_ex3_ss_disc3','chen_ex4_ss_disc3',...
    'chen_ex1_ss_disc4','chen_ex2_ss_disc4','chen_ex3_ss_disc4','chen_ex4_ss_disc4',...
    'chen_ex1_ss_disc5','chen_ex2_ss_disc5','chen_ex3_ss_disc5','chen_ex4_ss_disc5',...
    'chen_ex1_ss_disc6','chen_ex2_ss_disc6','chen_ex3_ss_disc6','chen_ex4_ss_disc6',...
    'chen_ex1_ss_disc7','chen_ex2_ss_disc7','chen_ex3_ss_disc7','chen_ex4_ss_disc7',...
    '-append')
