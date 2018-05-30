%%%%%%%%%%
% 
% Ball Maglev
% 
% Extracted from:
%   V. A. Oliveira, E. F. Costa and J. B. Vargas, "Digital implementation 
%   of a magnetic suspension control system for laboratory experiments," in 
%   IEEE Transactions on Education, vol. 42, no. 4, pp. 315-322, Nov 1999. 
%   doi: 10.1109/13.804538
% Written and adapted by:
%   Iury Bessa
%   Manaus, 2018
%%%%%%%%%%

k1=0.77;
k2=39.6;
R=19.9;
L=0.52;
m=22.6e-3;
A=[0,1,0;k2/m,0,-k1/m;0,0,-R/L];
B=[0,0,1/L]';
C=[1,0,0];
D=0;

ballmaglev_ss_cont = ss(A,B,C,D);

%% Discretizing with Ts=0.1

ts=0.1;
ballmaglev_ss_disc1=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc1=tf(ss2tf(ballmaglev_ss_disc1.A,ballmaglev_ss_disc1.B,...
    ballmaglev_ss_disc1.C,ballmaglev_ss_disc1.D),ts);

%% Discretizing with Ts=0.05

ts=0.05;
ballmaglev_ss_disc2=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc2=tf(ss2tf(ballmaglev_ss_disc2.A,ballmaglev_ss_disc2.B,...
    ballmaglev_ss_disc2.C,ballmaglev_ss_disc2.D),ts);


%% Discretizing with Ts=0.025

ts=0.025;
ballmaglev_ss_disc3=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc3=tf(ss2tf(ballmaglev_ss_disc3.A,ballmaglev_ss_disc3.B,...
    ballmaglev_ss_disc3.C,ballmaglev_ss_disc3.D),ts);


%% Discretizing with Ts=0.025

ts=0.025;
ballmaglev_ss_disc3=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc3=tf(ss2tf(ballmaglev_ss_disc3.A,ballmaglev_ss_disc3.B,...
    ballmaglev_ss_disc3.C,ballmaglev_ss_disc3.D),ts);

%% Discretizing with Ts=0.075

ts=0.075;
ballmaglev_ss_disc4=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc4=tf(ss2tf(ballmaglev_ss_disc4.A,ballmaglev_ss_disc4.B,...
    ballmaglev_ss_disc4.C,ballmaglev_ss_disc4.D),ts);

%% Discretizing with Ts=0.005

ts=0.005;
ballmaglev_ss_disc5=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc5=tf(ss2tf(ballmaglev_ss_disc5.A,ballmaglev_ss_disc5.B,...
    ballmaglev_ss_disc5.C,ballmaglev_ss_disc5.D),ts);


%% Discretizing with Ts=0.001

ts=0.001;
ballmaglev_ss_disc6=c2d(ballmaglev_ss_cont,ts);
ballmaglev_tf_disc6=tf(ss2tf(ballmaglev_ss_disc6.A,ballmaglev_ss_disc6.B,...
    ballmaglev_ss_disc6.C,ballmaglev_ss_disc6.D),ts);



%% Saving

save('benchmark_tf','ballmaglev_tf_disc1','ballmaglev_tf_disc2','ballmaglev_tf_disc3','ballmaglev_tf_disc4',...
    'ballmaglev_tf_disc5','ballmaglev_tf_disc6','-append')

save('benchmark_ss','ballmaglev_ss_disc1','ballmaglev_ss_disc2','ballmaglev_ss_disc3','ballmaglev_ss_disc4',...
    'ballmaglev_ss_disc5','ballmaglev_ss_disc6','-append')

