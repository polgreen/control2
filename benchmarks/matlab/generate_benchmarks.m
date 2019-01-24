
% Acrobot - Robot Manipulator


A=[zeros(2,2),eye(2);[12.49,-12.54;-14.49,29.36],zeros(2,2)];
B=[0,0,-2.98,5.98]';
C=[1,0,1,0];
D=0;
time_discretisation(ss(A,B, C, D),'acrobot')

% Antenna
antenna=ss(tf(zpk([-1],[0,0,-6,-11.5,[roots([1,8,256])]'],1)));
time_discretisation(antenna, 'antenna');

% Ball maglev
k1=0.77;
k2=39.6;
R=19.9;
L=0.52;
m=22.6e-3;
A=[0,1,0;k2/m,0,-k1/m;0,0,-R/L];
B=[0,0,1/L]';
C=[1,0,0];
D=0;

time_discretisation(ss(A,B,C,D), 'ballmaglev');

% chen
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


time_discretisation(ss(chen_ex1),'chen_ex1');
time_discretisation(ss(chen_ex2),'chen_ex2');
time_discretisation(ss(chen_ex3),'chen_ex3');
time_discretisation(ss(chen_ex4),'chen_ex4');

% cruise

m=1000; b=50;
num=[1/m];
den=[1,b/m];
cruise_tf_cont=tf(num,den);
time_discretisation(ss(cruise_tf_cont),'cruise');


%bioreact
% bioreact=tf([-5.9],[5.89,-1],'InputDelay',1);
% bioreact_wo_delay=tf(bioreact.num,bioreact.den);
% 
% time_discretisations = [0.5, 0.1, 0.05, 0.001, 0.0005, 0.0001, 0.00005, 0.00001, 0.000005, 0.000001];
% 
% for ts = time_discretisations
%     pade_delay1=thiran(bioreact.InputDelay,ts);
%     bioreact_tf=pade_delay1*c2d(bioreact,ts);
%     disc1=genvarname('bioreact', who);
%     eval([disc1 ' =ss(bioreact_tf)'])   
%     
%     save('benchmark_ss', disc1, '-append');
%    
% end

%cstr
cstrct=tf([-0.9580e-4,-0.01197e-4],[1,0.5250,0.01265,0.000078]);
time_discretisation(ss(cstrct),'cstr');

%cstr2
cstrtempct=tf([0.15,0.0063],[1,0.048631,-0.003359]);
time_discretisation(ss(cstrtempct),'cstrtemp');

%dcmotor

Jm=0.01;
b=0.001;
Kt=0.02;
Ke=Kt;
Ra=10;
L=1e-2;


num=[Kt];
den=[[conv([L,Ra],[Jm,b])]+[0,0,Kt*Ke]];
dcmotor_tf_cont=tf(num,den);
[A,B,C,D]=tf2ss(num,den);
dcmotor_ss_cont=ss(A,B,C,D);
time_discretisation(dcmotor_ss_cont,'dcmotor');

% flexbeam
num=[1.65,-0.331,576,90.6,19080];
den=[1,0.996,463,97.8,12131,8.11,0];
flexbeamct=tf(num,den);
time_discretisation(ss(flexbeamct),'flexbeam');

%guidance chen
num=0.00484*[1,-0.492,-0.0261,0.974,-0.348];
den=[1.2184,-3.9926,5.9024,-5.1692,2.5806,-0.5403];
guidance_chen=tf(num,den);
time_discretisation(ss(guidance_chen),'guidance_chen');

%helicopter
num=9.8*[1,-0.5,6.3];
den=conv([1,0.66],[1,-0.24,0.15]);
helicopter_tf_cont=tf(num,den);
time_discretisation(ss(helicopter_tf_cont),'helicopter');

%inverted pendulum
mp=0.1;
mc=0.2;

num=[1];
den=[1,0,-1];
invpendulum_pendang_tf_cont=tf(num,den);
time_discretisation(ss(invpendulum_pendang_tf_cont),'invpendulum_pendang');


num=[1,(-1+(3*mp/(4*mc+4*mp)))];
den=[conv([1,0,0],[1,0,-1])];
invpendulum_cartpos_tf_cont=tf(num,den);
time_discretisation(ss(invpendulum_cartpos_tf_cont),'invpendulum_cartpos');

%mag pointer
I=40e-6;
k=4e-6;
Km=4e-6;
b=0.08;

num=[Km];
den=[I,b,k];
magneticpointer_tf_cont=tf(zpk([-0.0068],[0,-0.2647,-0.0063],-0.0184));
time_discretisation(ss(magneticpointer_tf_cont),'magneticpointer');

%magsuspension
num=[2500];
den=[1,0,-1000];
magsuspension_tf_cont=tf(num,den);
time_discretisation(ss(magsuspension_tf_cont),'magsuspension');

%pendulum
g=9.81;
l=1;
num=9.8*[1,-0.5,6.3];
den=[1,0,g/l];
pendulum_tf_cont=tf(num,den);
time_discretisation(ss(pendulum_tf_cont),'pendulum');

%regulator

A=[-0.2,0.5,0,0,0;0,-0.5,1.6,0,0;0,0,-14.28,85.71,0;zeros(2,3),[-25,75;0,-10]];
B=[0,0,0,0,30]';
C=[1,0,0,0,0];
D=0;
time_discretisation(ss(A,B,C,D),'regulator');

%suspension
m1=20;
m2=375;
ks=13e4;
kw=1e6;
b=9.8e3;

num=(kw*b/(m1*m2))*[1,ks/b];
den=[1,b*(1/m1+1/m2),(ks/m1+ks/m2+kw/m1),(kw*b/(m1*m2)),(kw*ks/(m1*m2))];
suspension_tf_cont=tf(num,den);
time_discretisation(ss(suspension_tf_cont),'suspension');

%tapedriver
J1=5e-5;
B1=1e-2;
r1=2e-2;
Kt=3e-2;
K=2e4;
B=20;
r2=2e-2;
J2=2e-5;
B2=2e-2;
F=6;

num=(Kt*r1)*[J2,(B2+(r2^2)*B),(r2^2)*K];
den=[J1*J2,J1*B2+B1*J2+(r2^2)*J1*B+(r1^2*J2*B),B1*B2+(r2^2)*J1*K+(r2^2)*B1*B+(r1^2)*J2*K+(r1^2)*B2*B,(r2^2)*B1*K+(r1^2)*B2*K];
tapedriver_tf_cont=tf(num,den);
time_discretisation(ss(tapedriver_tf_cont),'tapedriver');

%usgtampa
uscgtampa_tf_cont=tf(zpk([-0.0068],[0,-0.2647,-0.0063],-0.0184));

time_discretisation(ss(uscgtampa_tf_cont),'uscgtampa');


%steamdrum
% 
% steamdrumd=0.547*tf([-0.418],[1.06,1,0],'InputDelay',0.1);
% steamdrum_wo_delay=tf(steamdrumd.num,steamdrumd.den);
% 
% for ts = time_discretisations
%     pade_delay1=thiran(steamdrumd.InputDelay,ts);
%     steamdrum_tf=pade_delay1*c2d(steamdrumd,ts);
%     disc1=genvarname('steamdrum', who);
%     eval([disc1 ' =ss(steamdrum_tf)'])   
%     
%     save('benchmark_ss', disc1, '-append');
%    
% end








