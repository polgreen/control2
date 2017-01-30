msg = 'magsuspension_ss_disc2.ss'
K = [fxp(46.25), fxp(-16) ];
A = [ 2.001,-1;1,0 ];
B = [ 0.0625;0 ];
INPUT = [-1000,1000];
run fixedpointcheck.m

msg = 'invpendulum_pendang_ss_disc1.ss'
K = [fxp(6.9765625), fxp(-0.8828125) ];
A = [ 2.2553,-1;1,0 ];
B = [ 0.5;0 ];
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'satellite_ss_disc1.ss'
K = [fxp(1.96875), fxp(-0.0390625) ];
A = [ 2,-1;1,0 ];
B = [ 1;0 ];
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'tapedriver_ss_disc1.ss'
K = [fxp(-0.9921875), fxp(-0.96484375), fxp(0.00390625) ];
A = [ 4.6764e-166,0,0;5.1253e-144,0,0;0,2.5627e-144,0 ];
B = [ 0.125;0;0 ];
INPUT = [-1,1];
run fixedpointcheck.m

msg = 'pendulum_ss_disc1.ss'
K = [fxp(-0.5078125), fxp(-0.0859375) ];
A = [ -1.9999,-1;1,0 ];
B = [ 4;0 ];
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'cruiseHSCC_ss_disc1.ss'
K = [fxp(-0.015625) ];
A = [ 0.998 ];
B = [ 0.125 ];
INPUT = [-1,1];
%run fixedpointcheck.m

msg = 'dcmotor_ss_disc1.ss'
K = [fxp(0), fxp(0.00390625) ];
A = [ 0.90122,1.3429e-08;7.4506e-09,0 ];
B = [ 128;0 ];
INPUT = [-1,1];
run fixedpointcheck.m

msg = 'suspension_ss_disc3.ss'
K = [fxp(0), fxp(-0.00390625), fxp(0), fxp(0) ];
A = [ 0.00074795,-0.0016575,1.8415e-26,-1.1243e-104;0.0019531,0,0,0;0,0.0019531,0,0;0,0,0.0019531,0 ];
B = [ 256;0;0;0 ];
INPUT = [-1000000,1000000];
run highprecisioncheck.m