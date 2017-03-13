msg = 'cruiseHSCC_ss_disc1.ss'
K = [fxp(0.5)];
A = [ 0.998 ];
B = [ 0.125 ];
INPUT = [-1,1];
%run fixedpointcheck.m %single state = checked manually

msg = 'dcmotor_ss_disc1.ss'
K = [fxp(0), fxp(-0.96875)];
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