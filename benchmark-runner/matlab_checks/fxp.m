%benchmark magsuspension_ss	
K = [fxp(46.25), fxp(-16)];
%K = [fxp(17.4384765625), fxp(-0.0537109375)]
A = [fxpP(2.001),fxpP(-1);fxpP(1),fxpP(0)] ;
B = [fxpP(0.0625);fxpP(0)] ;

%benchmark invpendulum_pendang_ss
K = [fxp(4.75), fxp(-1)];
A = [fxpP(2.2553),fxpP(-1);fxpP(1),fxpP(0)] 
B = [fxpP(0.5);fxpP(0)] 

%benchmark pendulum ss
K = [fxpP(-4.7421875),fxpP( -1)];
A = [fxpP(-1.9999),fxpP(-1);fxpP(1),fxpP(0)] ;
B = [fxpP(4);fxpP(0)] ;

%benchmark helicopter ss
K = [fxp(0.234375), fxp(-0.1484375), fxp(0.078125)];
A = [2.6207,-1.1793,0.65705;2,0,0;0,0.5,0]; 
B = [8;0;0] ;