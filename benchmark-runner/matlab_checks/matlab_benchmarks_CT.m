%benchmark pendulum ss file 1 - axelerator
msg = 'pendulum ss file 1 - axelerator'
K = [fxp(-0.61328125),fxp(-0.125)];
A = [-1.9999,-1;1,0] ;
B = [4;0] ;
INPUT = [-10,10];

run fixedpointcheck.m

msg = 'cruise file 1 - axelerator'
K = [fxp(0.5)];
A = [0.95123] ;
B = [0.03125] ;
INPUT = [-10,10];
%run fixedpointcheck.m

msg = 'dcmotor file 1 - axelerator'
K =[fxp(0), fxp(-0.96875)];
A = [0.90122,1.3429e-08;7.4506e-09,0] ;
B = [128;0] ;
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'helicopter file 1 - axelerator'
K =[fxp(0.234375), fxp(-0.1484375), fxp(0.078125)];
A = [2.6207,-1.1793,0.65705;2,0,0;0,0.5,0] ;
B = [8;0;0] ;
INPUT = [-10,10];
run fixedpointcheck.m

%msg = 'ballmaglev file 1 - axelerator'
K = [];
A = [1.001,0.001,-1.686e-05;1.867,1.001,-0.03349;0,0,0.9585] ;
B = [-1.2e-08;3.587e-05;0.002083] ;
INPUT = [-10,10];
%run fixedpointcheck.m

msg = 'magsuspension file 2 - axelerator'
K = [fxp(40.17578125), fxp(-15.953125)];
A = [2.001,-1;1,0] ;
B = [0.0625;0] ;
INPUT = [-10,10];

run fixedpointcheck.m

msg = 'pendangss file 1 - axelerator'
K = [fxp(3.999755859375), fxp(-2.0030517578125)];
A = [2.2553,-1;1,0] ;
B = [0.5;0] ;
INPUT = [-1000,1000];

run fixedpointcheck.m
msg = 'cartpos file 1 - axelerator'
K = [];
A = [4.2553,-3.2553,1.0638,-0.5;2,0,0,0;0,2,0,0;0,0,0.5,0] ;
B = [0.25;0;0;0];
INPUT = [-10,10];

