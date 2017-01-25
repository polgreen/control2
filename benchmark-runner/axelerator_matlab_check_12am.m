%FINAL RESULTS AT 01:35

msg = 'cruiseHSCC_ss_disc1.ss'
K = [fxp(0.5)];
A = [ 0.998 ];
B = [ 0.125 ];
INPUT = [-1,1];
%run fixedpointcheck.m %single state, checked safe

msg = 'dcmotor_ss_disc1.ss' %UNSAFE
K = [fxp(0.0078125), fxp(-0.0078125)];
A = [ 0.90122,1.3429e-08;7.4506e-09,0 ];
B = [ 128;0 ];
INPUT = [-1,1];
run fixedpointcheck.m

msg = 'helicopter_ss_disc1.ss'
K = [fxp(0.234375), fxp(-0.1484375), fxp(0.078125)];
A = [ 2.6207,-1.1793,0.65705;2,0,0;0,0.5,0 ];
B = [ 8;0;0 ];
INPUT = [-1,1];
run fixedpointcheck.m

msg = 'magsuspension_ss_disc2.ss'
K = [fxp(28.546875), fxp(-11.0234375)];
A = [ 2.001,-1;1,0 ];
B = [ 0.0625;0 ];
INPUT = [-1000,1000];
run fixedpointcheck.m

msg = 'invpendulum_pendang_ss_disc1.ss'
K = [fxp(4.75), fxp(-1)];
A = [ 2.2553,-1;1,0 ];
B = [ 0.5;0 ];
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'pendulum_ss_disc1.ss'
K = [fxp(-0.61328125), fxp(-0.125)];
A = [ -1.9999,-1;1,0 ];
B = [ 4;0 ];
INPUT = [-10,10];
run fixedpointcheck.m
