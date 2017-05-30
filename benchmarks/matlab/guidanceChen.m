%%%%%%%%%%
% 
% Guidance Control System
% 
% Extracted from:
%   Reduction of Transfer Functions by the Stability-Equation Method. In?
%   Journal of the Franklin Institute 308(4):389–404. October 1979
%   DOI: 10.1016/0016-0032(79)90066-8
% Written by:
%   Iury Bessa
%   Manaus, 2017
%%%%%%%%%%
%% Discretizing with Ts=0.1

ts=0.1;
num=0.00484*[1,-0.492,-0.0261,0.974,-0.348];
den=[1.2184,-3.9926,5.9024,-5.1692,2.5806,-0.5403];
guidance_chen_tf_disc1=tf(num,den,ts);
guidance_chen_ss_disc1=ss(guidance_chen_tf_disc1);

%% Saving

save('benchmark_tf','guidance_chen_tf_disc1', '-append');

save('benchmark_ss',...
    'chen_ex1_ss_disc1','chen_ex2_ss_disc1','chen_ex3_ss_disc1','chen_ex4_ss_disc1',...
    'chen_ex1_ss_disc2','chen_ex2_ss_disc2','chen_ex3_ss_disc2','chen_ex4_ss_disc2',...
    'chen_ex1_ss_disc3','chen_ex2_ss_disc3','chen_ex3_ss_disc3','chen_ex4_ss_disc3',...
    'chen_ex1_ss_disc4','chen_ex2_ss_disc4','chen_ex3_ss_disc4','chen_ex4_ss_disc4',...
    'chen_ex1_ss_disc5','chen_ex2_ss_disc5','chen_ex3_ss_disc5','chen_ex4_ss_disc5',...
    'chen_ex1_ss_disc6','chen_ex2_ss_disc6','chen_ex3_ss_disc6','chen_ex4_ss_disc6',...
    'chen_ex1_ss_disc7','chen_ex2_ss_disc7','chen_ex3_ss_disc7','chen_ex4_ss_disc7',...
    '-append')
