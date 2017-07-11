%FINAL RESULTS AT 01:35

msg = 'cruiseHSCC_ss_disc1.ss'
K = [ 0.0859375 ];
A = [ 0.998 ];
B = [ 0.125 ];
INPUT = [-1,1];
%run fixedpointcheck.m %single state, checked safe

msg = 'dcmotor_ss_disc1.ss' 
K = [0 , -0.0078125];
A = [ 0.90122,1.3429e-08;7.4506e-09,0 ];
B = [ 128;0 ];
INPUT = [-1,1];
run fixedpointcheck.m

msg = 'helicopter_ss_disc1.ss'
K = [ 0.31640625 ,  -0.12109375 ,  0.0703125 ];
A = [ 2.6207,-1.1793,0.65705;2,0,0;0,0.5,0 ];
B = [ 8;0;0 ];
INPUT = [-1,1];
run fixedpointcheck.m

msg = 'invpendulum_pendang_ss_disc1.ss'
K = [ 5.73046875 ,  -1.99609375 ];
A = [ 2.2553,-1;1,0 ];
B = [ 0.5;0 ];
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'magneticpointer_ss_disc3.ss'
K = [ 45.96875 ,  -20.7421875 ,  13.97265625 ];
A = [2.8729,-1.3731,0.87328;2,0,0;0,0.5,0] ;
B = [0.0625;0;0] ;
INPUT = [-100,100] ;
run fixedpointcheck.m


msg = 'magsuspension_ss_disc2.ss'
K = [ 30.82421875 ,  -15.984375 ];
A = [ 2.001,-1;1,0 ];
B = [ 0.0625;0 ];
INPUT = [-1000,1000];
run fixedpointcheck.m


msg = 'pendulum_ss_disc1.ss'
K = [ -0.46484375 ,  -0.25390625 ];
A = [ -1.9999,-1;1,0 ];
B = [ 4;0 ];
INPUT = [-10,10];
run fixedpointcheck.m

msg = 'satellite_ss_disc1.ss'
K = [ 1.79296875 ,  -1.28125 ];
A = [2,-1;1,0] ;
B = [1;0] ;
INPUT = [-10,10];
run fixedpointcheck.m


