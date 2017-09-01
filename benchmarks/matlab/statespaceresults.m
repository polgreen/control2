boundspec=1.0;
xmax=1.0;


% State-Space Benchmarks: 
% Benchmark Id 	A 	B 	C 	D 	K (feedback matrix)
%% dcmotor_ss_disc1 

i=1;
name='dcmotor_ss_disc1';
A=[0.90122,1.3429e-08;7.4506e-09,0];
B=[128;0];
C=[0.0014826,189.0217];
D=[0];
K=[0,-0.0039062];
bound=maxstate(A,xmax);
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc2

i=i+1;
name='dcmotor_ss_disc2';
A=[1.3678,-0.73569;0.5,0];
B=[0.015625;0];
C=[0.0047087,0.0067641];
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc3

i=i+1;
name='dcmotor_ss_disc3';
A= [0.94933,0;1,0]; 
B=[0.25;0];
C=[0.38902,0.00075955];
D=[0];
K=[-0.0039062,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc4

i=i+1;
name='dcmotor_ss_disc4';
A=[0.97941,0;1,0];
B=[0.25;0];
C=[0.15756,0.00078362];
D=[0];
K=[0.99609,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc5

i=i+1;
name='dcmotor_ss_disc5';
A=[0.98965,1.4747e-08;7.4506e-09,0];
B=[128;0];
C=[0.00015389,207.5687];
D=[0];
K=[0,-0.0039062];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc6

i=i+1;
name='dcmotor_ss_disc6';
A=[0.99481,-1.4824e-08;7.4506e-09,0];
B=[128;0];
C=[7.6368e-05,208.6509];
D=[0];
K=[0,-0.0039062];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc7

i=i+1;
name='dcmotor_ss_disc7';
A=[0.99901,-0.0058054;0.0078125,0];
B=[0.125;0];
C=[0.014393,0.20451];
D=[0];
K=[0.99609,-0.0078125];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% dcmotor_ss_disc8

i=i+1;
name='dcmotor_ss_disc8';
A=[1.0062,-0.10775;0.0625,0];
B=[0.0625;0];
C=[0.012819,0.04911];
D=[0];
K=[0.54688,1];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% ballmaglev_ss_disc1

i=i+1;
name='ballmaglev_ss_disc1';
A=[1.001,0.001,-1.686e-05;1.867,1.001,-0.03349;0,0,0.9585];
B=[-1.2e-08;3.587e-05;0.002083];
C=[1,0,0];
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruiseHSCC_ss_disc1

i=i+1;
name='cruiseHSCC_ss_disc1';
A=[0.998];
B=[0.125];
C=[0.2112];
D=[0];
K=[-0.015625];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% springmassdamperHSCC_ss_disc1

i=i+1;
name='springmassdamperHSCC_ss_disc1';
A=[2,-1.001;1,0];
B=[0.0078125;0];
C=[0.0064,0.0064];
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc1

i=i+1;
name='pendulum_ss_disc1';
A=[-1.9999,-1;1,0];
B=[4;0];
C=[-1.7569,-1.7495];
D=[9.8];
K=[-0.58984,-0.19141];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc2

i=i+1;
name='pendulum_ss_disc2';
A=[-0.028501,-1;1,0];
B=[2;0];
C=[-0.99605,-2.5603];
D=[9.8];
K=[0.085938,-0.0039062];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc3

i=i+1;
name='pendulum_ss_disc3';
A=[0.0095007,-1;1,0];
B=[2;0];
C=[-2.5271,-0.96267];
D=[9.8];
K=[0.074219,-0.058594];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc4

i=i+1;
name='pendulum_ss_disc4';
A=[1.6203,-1;1,0];
B=[1;0];
C=[-1.5829,0.2514];
D=[9.8];
K=[0.70312,-1.0625];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc5

i=i+1;
name='pendulum_ss_disc5';
A=[1.9027,-1;1,0];
B=[1;0];
C=[-0.65262,0.31144];
D=[9.8];
K=[1.2969,-0.48438];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc6

i=i+1;
name='pendulum_ss_disc6';
A=[1.9755,-1;1,0];
B=[0.5;0];
C=[-0.57382,0.40218];
D=[9.8];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc7

i=i+1;
name='pendulum_ss_disc7';
A=[1.999,-1;1,0];
B=[0.25;0];
C=[-0.20285,0.18909];
D=[9.8];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% pendulum_ss_disc8 	

i=i+1;
name='pendulum_ss_disc8';
A=[1.9998,-1;1,0];
B=[0.25;0];
C=[-0.099716,0.096276];
D=[9.8];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_pendang_ss_disc1 	

i=i+1;
name='invpendulum_pendang_ss_disc1';
A=[2.2553,-1;1,0]; 	
B=[0.5;0]; 	
C=[0.25525,0.25525]; 	
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
		
%% invpendulum_pendang_ss_disc2 	

i=i+1;
name='invpendulum_pendang_ss_disc2';
A=[2.0401,-1;1,0];
B=[0.25;0];
C=[0.080267,0.080267];
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
			
%% invpendulum_pendang_ss_disc3 	

i=i+1;
name='invpendulum_pendang_ss_disc3';
A=[2.01,-1;1,0];
B=[0.125;0];
C=[0.040033,0.040033];
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
			
%% invpendulum_pendang_ss_disc4 	

i=i+1;
name='invpendulum_pendang_ss_disc4';
A=[2.0025,-1;1,0];
B=[0.0625;0]; 	
C=[0.020004,0.020004];
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
			
%% invpendulum_pendang_ss_disc5 	

i=i+1;
name='invpendulum_pendang_ss_disc5';
A=[2.0001,-1;1,0]; 	
B=[0.0078125;0];
C=[0.0064001,0.0064001]; 	
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
				
%% invpendulum_pendang_ss_disc6 	

i=i+1;
name='invpendulum_pendang_ss_disc6';
A=[2,-1;1,0]; 		
B=[0.0039062;0];
C=[0.0032,0.0032]; 	
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
			
%% invpendulum_pendang_ss_disc7 	

i=i+1;
name='invpendulum_pendang_ss_disc7';
A=[2,-1;1,0]; 		
B=[0.00097656;0];
C=[0.000512,0.000512];
D=[0];	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
			
%% invpendulum_pendang_ss_disc8 	

i=i+1;
name='invpendulum_pendang_ss_disc8';
A=[2,-1;1,0]; 		
B=[0.00048828;0]; 	
C=[0.000256,0.000256]; 	
D=[0];
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
			
%% invpendulum_cartpos_ss_disc1 

i=i+1;
name='invpendulum_cartpos_ss_disc1';
A=[4.2553,-1.6276,1.0638,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[0.25;0;0;0]; 	
C=[0.10524,0.01434,-0.050254,-0.076565];
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc2 	

i=i+1;
name='invpendulum_cartpos_ss_disc2';
A=[4.0401,-1.5201,1.01,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[0.0625;0;0;0]; 	
C=[0.029774,0.0062389,-0.0098528,-0.017296]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc3 

i=i+1;
name='invpendulum_cartpos_ss_disc3';
A=[4.01,-1.505,1.0025,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[0.03125;0;0;0]; 	
C=[0.0077141,0.0017783,-0.0022289,-0.0041574]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc4 

i=i+1;
name='invpendulum_cartpos_ss_disc4';
A=[4.0025,-1.5013,1.0006,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[0.0078125;0;0;0];
C=[0.0039283,0.00094454,-0.0010571,-0.0020392]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc5 

i=i+1;
name='invpendulum_cartpos_ss_disc5';
A=[4.0001,-1.5001,1,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[0.00097656;0;0;0]; 	
C=[0.00025517,6.3313e-05,-6.4753e-05,-0.00012855]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc6 

i=i+1;
name='invpendulum_cartpos_ss_disc6';
A=[4,-1.5,1,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[0.00024414;0;0;0]; 	
C=[0.00012782,3.1836e-05,-3.2196e-05,-6.4152e-05]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc7 

i=i+1;
name='invpendulum_cartpos_ss_disc7';
A=[4,-1.5,1,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[3.0518e-05;0;0;0]; 	
C=[8.1971e-06,2.0477e-06,-2.0524e-06,-4.1016e-06]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% invpendulum_cartpos_ss_disc8 

i=i+1;
name='invpendulum_cartpos_ss_disc8';
A=[4,-1.5,1,-0.5;4,0,0,0;0,1,0,0;0,0,0.5,0]; 	
B=[7.6294e-06;0;0;0]; 	
C=[4.0973e-06,1.0239e-06,-1.0251e-06,-2.0494e-06]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
							
%% suspension_ss_disc1 	

i=i+1;
name='suspension_ss_disc1';
A=[-5.915e-06,-2.7472e-06,3.3912e-52,-1.264e-208;3.8147e-06,0,0,0;0,3.8147e-06,0,0;0,0,3.8147e-06,0]; 	
B=[131072;0;0;0]; 	
C=[1.9074e-06,1,131072.5481,-59566.752]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
						
%% suspension_ss_disc2

i=i+1;
name='suspension_ss_disc2';
A=[-6.8455e-09,-4.5533e-09,6.245e-78,0;7.4506e-09,0,0,0;0,7.4506e-09,0,0;0,0,1.4901e-08,0]; 	
B=[67108864;0;0;0]; 	
C=[3.7253e-09,1,67108864.3062,-10279829.3183]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
						
%% suspension_ss_disc3

i=i+1;
name='suspension_ss_disc3';
A=[0.00074795,-0.0016575,1.8415e-26,-1.1243e-104;0.0019531,0,0,0;0,0.0019531,0,0;0,0,0.0019531,0]; 	
B=[256;0;0;0]; 	
C=[0.00097712,0.99991,255.4721,-172.6768]; 	
D=[0]; 	
K=[0,-0.0078125,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
						
%% suspension_ss_disc4 	

i=i+1;
name='suspension_ss_disc4';
A=[-0.15905,-0.1019,8.849e-11,-6.0477e-42;0.0625,0,0,0;0,0.0625,0,0;0,0,0.0625,0]; 	
B=[16;0;0;0]; 	
C=[0.019589,0.60479,4.3085,-5.6516]; 	
D=[0]; 	
K=[-0.0039062,-0.015625,-0.0625,0.015625];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% suspension_ss_disc5 			

i=i+1;
name='suspension_ss_disc5';
A=[0.02366,-0.31922,0.0012041,-4.0292e-17;0.25,0,0,0;0,0.0019531,0,0;0,0,0.0019531,0]; 	
B=[256;0;0;0]; 	
C=[0.001404,0.0097416,1.3492,-390.7199]; 	
D=[0]; 
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% suspension_ss_disc6 		

i=i+1;
name='suspension_ss_disc6';
A=[0.76995,-0.56916,0.049073,-1.2695e-08;0.5,0,0,0;0,0.03125,0,0;0,0,0.03125,0]; 	
B=[16;0;0;0]; 	
C=[0.016561,0.049179,-0.032149,-17.4724]; 	
D=[0]; 	
K=[0.039062,0.027344,0.0078125,-0.0039062];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% suspension_ss_disc7 	

i=i+1;
name='suspension_ss_disc7';
A=[2.0727,-0.6801,0.26975,-0.091745;2,0,0,0;0,0.5,0,0;0,0,0.0625,0]; 	
B=[1;0;0;0]; 	
C=[0.047193,0.026528,-0.035467,-0.66128]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
						
%% magsuspension_ss_disc1

i=i+1;
name='magsuspension_ss_disc1';
A=[54149865291660.41,-806895.8713;524288,0]; 	
B=[8388608;0]; 	
C=[8068958.7134,15.4245]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc2 		

i=i+1;
name='magsuspension_ss_disc2';
A=[2.001,-1;1,0]; 	
B=[0.0625;0]; 	
C=[0.020002,0.020002]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc3 	

i=i+1;
name='magsuspension_ss_disc3';
A=[7358659.2048,-0.99373;1,0]; 	
B=[4096;0]; 	
C=[2245.684,2245.684]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc4 	

i=i+1;
name='magsuspension_ss_disc4';
A=[558.1114,-1;1,0]; 	
B=[32;0]; 	
C=[21.7231,21.7231]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc5 	

i=i+1;
name='magsuspension_ss_disc5';
A=[23.6667,-1;1,0]; 	
B=[8;0]; 	
C=[3.3854,3.3854]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc6 	

i=i+1;
name='magsuspension_ss_disc6';
A=[5.0662,-1;1,0]; 	
B=[2;0]; 	
C=[1.9164,1.9164]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc7 	

i=i+1;
name='magsuspension_ss_disc7';
A=[2.1008,-1;1,0]; 	
B=[0.5;0]; 	
C=[0.25209,0.25209]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magsuspension_ss_disc8 	

i=i+1;
name='magsuspension_ss_disc8';
A=[2.0251,-1;1,0]; 	
B=[0.25;0]; 	
C=[0.12526,0.12526]; 	
D=[0]; 	
K=[0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruise_ss_disc1 	

i=i+1;
name='cruise_ss_disc1';
A=[0.95123]; 	
B=[0.03125]; 	
C=[0.031213]; 	
D=[0]; 	
K=[-0.31641];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
		
%% cruise_ss_disc2 	

i=i+1;
name='cruise_ss_disc2';
A=[0.92774]; 	
B=[0.03125]; 	
C=[0.046244]; 	
D=[0]; 	
K=[-1.0508];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruise_ss_disc3 	

i=i+1;
name='cruise_ss_disc3';
A=[0.97531]; 	
B=[0.03125]; 	
C=[0.015802]; 	
D=[0]; 	
K=[-0.55859];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruise_ss_disc4 	

i=i+1;
name='cruise_ss_disc4';
A=[0.99005]; 	
B=[0.015625]; 	
C=[0.012736]; 	
D=[0]; 	
K=[-0.082031];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruise_ss_disc5 	

i=i+1;
name='cruise_ss_disc5';
A=[0.99501]; 	
B=[0.0078125]; 	
C=[0.012768]; 	
D=[0]; 	
K=[-0.51953];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruise_ss_disc6 	

i=i+1;
name='cruise_ss_disc6';
A=[0.9975]; 	
B=[0.0078125]; 	
C=[0.006392]; 	
D=[0]; 	
K=[-0.26172];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cruise_ss_disc7 	

i=i+1;
name='cruise_ss_disc7';
A=[0.9995]; 	
B=[0.0039062]; 	
C=[0.0025594]; 	
D=[0]; 	
K=[-0.125];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
		
%% tapedriver_ss_disc1

i=i+1;
name='tapedriver_ss_disc1';
A=[4.6764e-166,0,0;1,0,0;0,1,0]; 	
B=[0.125;0;0]; 	
C=[0.16,-1.3979e-166,0]; 	
D=[0]; 	
K=[-0.98047,0.023438,-0.29688];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
	
%% tapedriver_ss_disc2 			

i=i+1;
name='tapedriver_ss_disc2';
A=[2.2259e-248,0,0;1,0,0;0,1,0]; 	
B=[0.125;0;0]; 	
C=[0.16,1.1844e-249,0]; 	
D=[0]; 	
K=[-0.98047,0.023438,-0.29688];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% tapedriver_ss_disc3 		

i=i+1;
name='tapedriver_ss_disc3';
A=[-4.8229e-83,-2.8204e-83,1.3166e-98;3.2944e-83,0,0;0,3.2944e-83,0]; 	
B=[0.25;0;0]; 	
C=[0.08,0.090775,1.5117e-16]; 	
D=[0]; 	
K=[-0.97266,0.22266,-0.39844];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% tapedriver_ss_disc4 	

i=i+1;
name='tapedriver_ss_disc4';
A=[1.0758e-33,-1.2605e-33,1.0518e-48;7.7037e-34,0,0;0,7.7037e-34,0]; 	
B=[0.125;0;0]; 	
C=[0.16,0.010291,-4.425e-16]; 	
D=[0]; 	
K=[0.31641,0.72266,0.875];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% tapedriver_ss_disc5 	

i=i+1;
name='tapedriver_ss_disc5';
A=[5.5197e-17,-3.5503e-17,6.2468e-32;2.7756e-17,0,0;0,2.7756e-17,0]; 	
B=[0.25;0;0]; 	
C=[0.08,-0.04887,-1.0309e-16]; 	
D=[0]; 	
K=[-0.0039062,-0.0039062,0.0039062];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% tapedriver_ss_disc6 	

i=i+1;
name='tapedriver_ss_disc6';
A=[-1.0862e-08,-4.2133e-09,1.0669e-22;7.4506e-09,0,0;0,7.4506e-09,0]; 	
B=[0.25;0;0]; 	
C=[0.08,0.047793,-1.2708e-15]; 	
D=[0]; 	
K=[-0.97266,0.22266,-0.39844];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% tapedriver_ss_disc7 	

i=i+1;
name='tapedriver_ss_disc7';
A=[-0.044641,-0.01595,0.0007445;0.03125,0,0;0,0.00097656,0]; 	
B=[0.25;0;0]; 	
C=[0.081851,0.056338,-0.0026246]; 	
D=[0]; 	
K=[0.03125,0.054688,1.25];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% tapedriver_ss_disc8 	

i=i+1;
name='tapedriver_ss_disc8';
A=[-0.044641,-0.01595,0.0007445;0.03125,0,0;0,0.00097656,0]; 	
B=[0.25;0;0]; 	
C=[0.081851,0.056338,-0.0026246]; 	
D=[0]; 	
K=[0.03125,0.054688,1.25];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc1 	

i=i+1;
name='helicopter_ss_disc1';
A=[2.6207,-1.1793,0.65705;2,0,0;0,0.5,0]; 	
B=[8;0;0]; 	
C=[1.8914,1.1162,2.1819]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc2 		

i=i+1;
name='helicopter_ss_disc2';
A=[2.9996,-1.4996,0.49979;2,0,0;0,1,0]; 	
B=[0.125;0;0]; 	
C=[0.078364,-0.078383,0.039202]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc3 	

i=i+1;
name='helicopter_ss_disc3';
A=[2.8067,-1.3142,0.81058;2,0,0;0,0.5,0]; 	
B=[4;0;0]; 	
C=[1.2672,-0.5204,1.5142]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc4 	

i=i+1;
name='helicopter_ss_disc4';
A=[2.9194,-1.4198,0.45972;2,0,0;0,1,0]; 	
B=[2;0;0]; 	
C=[0.93264,-0.86041,0.51252]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc5 	

i=i+1;
name='helicopter_ss_disc5';
A=[2.9589,-1.4589,0.47943;2,0,0;0,1,0]; 	
B=[2;0;0]; 	
C=[0.47287,-0.4697,0.24838]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc6 	

i=i+1;
name='helicopter_ss_disc6';
A=[2.9792,-1.4792,0.48961;2,0,0;0,1,0]; 	
B=[1;0;0]; 	
C=[0.48009,-0.48233,0.2461]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc7 	

i=i+1;
name='helicopter_ss_disc7';
A=[2.9958,-1.4958,0.4979;2,0,0;0,1,0]; 	
B=[0.5;0;0]; 	
C=[0.19512,-0.19555,0.098049]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% helicopter_ss_disc8 	

i=i+1;
name='helicopter_ss_disc8';
A=[2.9979,-1.4979,0.49895;2,0,0;0,1,0]; 	
B=[0.25;0;0]; 	
C=[0.19555,-0.19578,0.098022]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc1 	

i=i+1;
name='uscgtampa_ss_disc1';
A=[2.7612,-1.2619,0.76262;2,0,0;0,0.5,0]; 	
B=[0.125;0;0]; 	
C=[-0.067525,0.002616,0.061417]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc2 	

i=i+1;
name='uscgtampa_ss_disc2';
A=[2.6629,-1.1644,0.66598;2,0,0;0,0.5,0]; 	
B=[0.25;0;0]; 	
C=[-0.072867,0.0041338,0.063212]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc3 	

i=i+1;
name='uscgtampa_ss_disc3';
A=[2.8729,-1.3731,0.43664;2,0,0;0,1,0]; 	
B=[0.0625;0;0]; 	
C=[-0.035232,0.00069897,0.0168]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc4 	

i=i+1;
name='uscgtampa_ss_disc4';
A=[2.9472,-1.4472,0.47362;2,0,0;0,1,0]; 	
B=[0.03125;0;0]; 	
C=[-0.011571,9.3147e-05,0.0056769]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc5 	

i=i+1;
name='uscgtampa_ss_disc5';
A=[2.9732,-1.4733,0.48663;2,0,0;0,1,0]; 	
B=[0.015625;0;0]; 	
C=[-0.0058365,2.3603e-05,0.0028907]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc6 	

i=i+1;
name='uscgtampa_ss_disc6';
A=[2.9865,-1.4865,0.49327;2,0,0;0,1,0]; 	
B=[0.0078125;0;0]; 	
C=[-0.0029311,5.9409e-06,0.0014586]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc7 	

i=i+1;
name='uscgtampa_ss_disc7';
A=[2.9973,-1.4973,0.49865;2,0,0;0,1,0]; 	
B=[0.00097656;0;0]; 	
C=[-0.00094125,3.8228e-07,0.00047018]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% uscgtampa_ss_disc8 	

i=i+1;
name='uscgtampa_ss_disc8';
A=[2.9986,-1.4986,0.49932;2,0,0;0,1,0]; 	
B=[0.00048828;0;0]; 	
C=[-0.00047083,9.5635e-08,0.0002353]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc1

i=i+1;
name='magneticpointer_ss_disc1';
A=[2.7612,-1.2619,0.76262;2,0,0;0,0.5,0]; 	
B=[0.125;0;0]; 	
C=[-0.067525,0.002616,0.061417]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc2 	

i=i+1;
name='magneticpointer_ss_disc2';
A=[2.6629,-1.1644,0.66598;2,0,0;0,0.5,0]; 	
B=[0.25;0;0]; 	
C=[-0.072867,0.0041338,0.063212]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc3 

i=i+1;
name='magneticpointer_ss_disc3';
A=[2.8729,-1.3731,0.43664;2,0,0;0,1,0]; 	
B=[0.0625;0;0]; 	
C=[-0.035232,0.00069897,0.0168]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc4 

i=i+1;
name='magneticpointer_ss_disc4';
A=[2.9472,-1.4472,0.47362;2,0,0;0,1,0]; 	
B=[0.03125;0;0]; 	
C=[-0.011571,9.3147e-05,0.0056769]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc5 

i=i+1;
name='magneticpointer_ss_disc5';
A=[2.9732,-1.4733,0.48663;2,0,0;0,1,0]; 	
B=[0.015625;0;0]; 	
C=[-0.0058365,2.3603e-05,0.0028907]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc6 

i=i+1;
name='magneticpointer_ss_disc6';
A=[2.9865,-1.4865,0.49327;2,0,0;0,1,0]; 	
B=[0.0078125;0;0]; 	
C=[-0.0029311,5.9409e-06,0.0014586]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc7 

i=i+1;
name='magneticpointer_ss_disc7';
A=[2.9973,-1.4973,0.49865;2,0,0;0,1,0]; 	
B=[0.00097656;0;0]; 	
C=[-0.00094125,3.8228e-07,0.00047018]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% magneticpointer_ss_disc8 

i=i+1;
name='magneticpointer_ss_disc8';
A=[2.9986,-1.4986,0.49932;2,0,0;0,1,0]; 	
B=[0.00048828;0;0]; 	
C=[-0.00047083,9.5635e-08,0.0002353]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex1_ss_disc1 		

i=i+1;
name='chen_ex1_ss_disc1';
A=[1.1975,-0.44055,0.19915;1,0,0;0,0.25,0]; 	
B=[0.25;0;0]; 	
C=[0.040611,0.079143,0.036246]; 	
D=[0]; 	
K=[0.019531,0.0039062,-0.0039062];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
				
%% chen_ex2_ss_disc1 	

i=i+1;
name='chen_ex2_ss_disc1';
A=[2.1367,-0.93121,0.40868,-0.18243,0.079967,-0.031022,0.016188,-0.0089465;2,0,0,0,0,0,0,0;0,1,0,0,0,0,0,0;0,0,0.5,0,0,0,0,0;0,0,0,0.25,0,0,0,0;0,0,0,0,0.125,0,0,0;0,0,0,0,0,0.03125,0,0;0,0,0,0,0,0,0.0078125,0];
B=[8;0;0;0;0;0;0;0]; 	
C=[1.4874,-1.2555,0.82551,-0.5381,0.41321,-0.32305,-0.84838,-0.70995]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% chen_ex3_ss_disc1

i=i+1;
name='chen_ex3_ss_disc1';
A=[0.72945,-0.27618,0.1439,-0.078461,0.068149,-0.026174,0.070795;1,0,0,0,0,0,0;0,1,0,0,0,0,0;0,0,0.5,0,0,0,0;0,0,0,0.5,0,0,0;0,0,0,0,0.25,0,0;0,0,0,0,0,0.125,0]; 
B=[1;0;0;0;0;0;0]; 	
C=[0.36493,0.53172,-0.35409,-0.37212,-0.089752,-0.042864,0.003396]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% chen_ex4_ss_disc1 	

i=i+1;
name='chen_ex4_ss_disc1';
A=[1.9074,-1.1002,0.94978,-0.69169,0.4293,-0.21007,0.18079,-0.1152,0.17774;2,0,0,0,0,0,0,0,0;0,1,0,0,0,0,0,0,0;0,0,1,0,0,0,0,0,0;0,0,0,1,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,0.5,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[0.25;0;0;0;0;0;0;0;0]; 	
C=[0.00296,0.052478,0.19369,0.14433,0.013366,0.0022535,0.001854,-0.00087103,-0.0001678]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
												
%% chen_ex1_ss_disc2

i=i+1;
name='chen_ex1_ss_disc2';
A=[2.0379,-0.68301,0.30119;2,0,0;0,0.5,0]; 	
B=[0.0625;0;0]; 	
C=[0.015883,0.023651,0.0087169]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex2_ss_disc2 	

i=i+1;
name='chen_ex2_ss_disc2';
A=[4.1268,-1.8035,0.86672,-0.49754,0.34668,-0.14193,0.061825,-0.043532;4,0,0,0,0,0,0,0;0,2,0,0,0,0,0,0;0,0,1,0,0,0,0,0;0,0,0,0.5,0,0,0,0;0,0,0,0,0.5,0,0,0;0,0,0,0,0,0.25,0,0;0,0,0,0,0,0,0.0625,0]; 
B=[4;0;0;0;0;0;0;0]; 	
C=[1.5028,-1.2836,0.89825,-0.6566,0.52539,-0.2186,0.089673,-0.13619]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% chen_ex3_ss_disc2

i=i+1;
name='chen_ex3_ss_disc2';
A=[3.8935,-1.7088,0.87775,-0.56968,0.23382,-0.11272,0.099574;4,0,0,0,0,0,0;0,2,0,0,0,0,0;0,0,1,0,0,0,0;0,0,0,1,0,0,0;0,0,0,0,0.5,0,0;0,0,0,0,0,0.125,0]; 
B=[0.25;0;0;0;0;0;0]; 	
C=[0.16579,0.017986,-0.051382,0.03485,-0.010863,0.001424,0.00074408]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% chen_ex4_ss_disc2

i=i+1;
name='chen_ex4_ss_disc2';
A=[6.424,-2.3739,2.1185,-1.2574,1.0295,-0.58132,0.21833,-0.099009,0.082649;8,0,0,0,0,0,0,0,0;0,2,0,0,0,0,0,0,0;0,0,2,0,0,0,0,0,0;0,0,0,1,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,1,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[0.0078125;0;0;0;0;0;0;0;0]; 	
C=[0.0006277,0.0029058,0.0039745,-0.0013446,-0.000788,0.00085065,-0.00011484,-7.373e-05,4.0926e-06]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
													
%% chen_ex1_ss_disc3

i=i+1;
name='chen_ex1_ss_disc3';
A=[2.4644,-1.0088,0.54881;2,0,0;0,0.5,0]; 	
B=[0.03125;0;0]; 	
C=[0.0045962,0.0079218,0.0034049]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex2_ss_disc3 

i=i+1;
name='chen_ex2_ss_disc3';
A=[5.5403,-3.3211,2.2485,-0.93933,0.49537,-0.32169,0.11746,-0.073766;4,0,0,0,0,0,0,0;0,2,0,0,0,0,0,0;0,0,2,0,0,0,0,0;0,0,0,1,0,0,0,0;0,0,0,0,0.5,0,0,0;0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0.125,0]; 
B=[4;0;0;0;0;0;0;0]; 	
C=[0.80792,-0.94532,0.93329,-0.5032,0.32001,-0.24103,0.10105,-0.07564]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% chen_ex3_ss_disc3

i=i+1;
name='chen_ex3_ss_disc3';
A=[5.4333,-3.2034,2.1257,-0.85738,0.4205,-0.23229,0.11157;4,0,0,0,0,0,0;0,2,0,0,0,0,0;0,0,2,0,0,0,0;0,0,0,1,0,0,0;0,0,0,0,0.5,0,0;0,0,0,0,0,0.25,0]; 
B=[0.125;0;0;0;0;0;0]; 	
C=[0.062724,-0.017986,-0.012149,0.013221,-0.0086889,0.0048137,-0.0018854]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% chen_ex4_ss_disc3

i=i+1;
name='chen_ex4_ss_disc3';
A=[7.8747,-3.4742,1.8033,-1.2136,1.0981,-0.66796,0.2634,-0.1222,0.10164;8,0,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0,0;0,0,2,0,0,0,0,0,0;0,0,0,1,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,1,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[0.00097656;0;0;0;0;0;0;0;0]; 	
C=[0.00012192,0.00049245,0.00018044,-0.00025341,6.3227e-05,9.7953e-05,-4.4031e-05,-1.4948e-06,4.9182e-06]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
														
%% chen_ex1_ss_disc4

i=i+1;
name='chen_ex1_ss_disc4';
A=[2.7168,-1.2291,0.74082;2,0,0;0,0.5,0]; 	
B=[0.0078125;0;0]; 	
C=[0.0024748,0.0045933,0.00213]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex2_ss_disc4

i=i+1;
name='chen_ex2_ss_disc4';
A=[6.5864,-4.73,1.9348,-0.98595,0.64086,-0.2594,0.11954,-0.096025;4,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0;0,0,2,0,0,0,0,0;0,0,0,1,0,0,0,0;0,0,0,0,1,0,0,0;0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0.125,0]; 
B=[2;0;0;0;0;0;0;0]; 	
C=[0.83814,-1.1857,0.71615,-0.47894,0.3832,-0.18358,0.09767,-0.089268]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% chen_ex3_ss_disc4 	

i=i+1;
name='chen_ex3_ss_disc4';
A=[6.2276,-2.0843,1.5553,-0.69857,0.37778,-0.22775,0.11809;8,0,0,0,0,0,0;0,2,0,0,0,0,0;0,0,2,0,0,0,0;0,0,0,1,0,0,0;0,0,0,0,0.5,0,0;0,0,0,0,0,0.25,0]; 
B=[0.0625;0;0;0;0;0;0]; 	
C=[0.025781,-0.0076105,0.00083244,0.0025878,-0.0030208,0.0026469,-0.001673]; 	
D=[0];
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex4_ss_disc4	

i=i+1;
name='chen_ex4_ss_disc4';
A=[8.4899,-4.0127,2.2173,-1.5786,0.7508,-0.47712,0.39064,-0.18696,0.15941;8,0,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0,0;0,0,2,0,0,0,0,0,0;0,0,0,2,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,0.5,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[0.00012207;0;0;0;0;0;0;0;0]; 	
C=[2.5938e-05,9.1152e-05,8.847e-06,-5.3791e-05,2.1235e-05,3.4135e-06,-1.3686e-05,4.257e-06,2.6631e-06]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex1_ss_disc5

i=i+1;
name='chen_ex1_ss_disc5';
A=[2.9407,-1.4412,0.47088;2,0,0;0,1,0]; 	
B=[0.00097656;0;0]; 	
C=[0.00016813,0.00033125,8.1579e-05]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% chen_ex2_ss_disc5 	

i=i+1;
name='chen_ex2_ss_disc5';
A=[7.6805,-3.2256,1.5479,-0.92843,0.71268,-0.34187,0.18739,-0.17973;8,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0;0,0,2,0,0,0,0,0;0,0,0,1,0,0,0,0;0,0,0,0,1,0,0,0;0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0.125,0]; 
B=[1;0;0;0;0;0;0;0]; 	
C=[0.34668,-0.29027,0.2083,-0.16607,0.15887,-0.091179,0.058141,-0.063552]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% chen_ex3_ss_disc5

i=i+1;
name='chen_ex3_ss_disc5';
A=[6.8489,-2.5132,2.0497,-1.0031,0.58919,-0.38456,0.21518;8,0,0,0,0,0,0;0,2,0,0,0,0,0;0,0,2,0,0,0,0;0,0,0,1,0,0,0;0,0,0,0,0.5,0,0;0,0,0,0,0,0.25,0]; 
B=[0.0078125;0;0;0;0;0;0]; 	
C=[0.0067729,-0.0030726,0.0016178,0.00022863,-0.0010316,0.0014254,-0.0012967]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% chen_ex4_ss_disc5 		

i=i+1;
name='chen_ex4_ss_disc5';
A=[8.9075,-4.4083,2.5455,-1.89,0.93559,-0.61757,0.52417,-0.25954,0.22848;8,0,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0,0;0,0,2,0,0,0,0,0,0;0,0,0,2,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,0.5,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[3.8147e-06;0;0;0;0;0;0;0;0]; 	
C=[2.2791e-07,6.6719e-07,-1.6294e-07,-3.575e-07,3.0798e-07,-1.022e-07,-1.2357e-07,1.2213e-07,4.7749e-08]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
														
%% chen_ex1_ss_disc6

i=i+1;
name='chen_ex1_ss_disc6';
A=[2.9702,-1.4703,0.48522;2,0,0;0,1,0]; 	
B=[0.00024414;0;0]; 	
C=[8.4696e-05,0.00016813,4.1718e-05]; 	
D=[0]; 	
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					
%% chen_ex2_ss_disc6

i=i+1;
name='chen_ex2_ss_disc6';
A=[7.8377,-3.3593,1.6454,-1.0074,0.78947,-0.38666,0.21642,-0.21197;8,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0;0,0,2,0,0,0,0,0;0,0,0,1,0,0,0,0;0,0,0,0,1,0,0,0;0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0.125,0]; 
B=[1;0;0;0;0;0;0;0]; 	
C=[0.17415,-0.14905,0.10934,-0.089125,0.087172,-0.051155,0.033355,-0.037282]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% chen_ex3_ss_disc6

i=i+1;
name='chen_ex3_ss_disc6';
A=[6.9247,-2.5689,2.1179,-1.0477,0.62192,-0.41022,0.23194;8,0,0,0,0,0,0;0,2,0,0,0,0,0;0,0,2,0,0,0,0;0,0,0,1,0,0,0;0,0,0,0,0.5,0,0;0,0,0,0,0,0.25,0]; 
B=[0.0039062;0;0;0;0;0;0]; 	
C=[0.0032933,-0.0015691,0.00090345,5.9383e-05,-0.00050952,0.00075567,-0.00072054]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
											
%% chen_ex4_ss_disc6

i=i+1;
name='chen_ex4_ss_disc6';
A=[8.9544,-4.4546,2.5854,-1.9294,0.95987,-0.63674,0.54307,-0.2702,0.239;8,0,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0,0;0,0,2,0,0,0,0,0,0;0,0,0,2,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,0.5,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[4.7684e-07;0;0;0;0;0;0;0;0]; 	
C=[5.5796e-08,1.5849e-07,-4.7782e-08,-8.157e-08,7.9134e-08,-3.099e-08,-2.9265e-08,3.3914e-08,1.277e-08]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
														
%% chen_ex1_ss_disc7

i=i+1;
name='chen_ex1_ss_disc7';
A=[2.994,-1.494,0.49701;2,0,0;0,1,0]; 	
B=[3.0518e-05;0;0]; 	
C=[5.4531e-06,1.089e-05,2.7184e-06]; 	
D=[0]; 	
K=[];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					
%% chen_ex2_ss_disc7 

i=i+1;
name='chen_ex2_ss_disc7';
A=[7.9671,-3.4713,1.7285,-1.0759,0.85715,-0.42681,0.24289,-0.24188;8,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0;0,0,2,0,0,0,0,0;0,0,0,1,0,0,0,0;0,0,0,0,1,0,0,0;0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0.125,0]; 
B=[0.5;0;0;0;0;0;0;0]; 	
C=[0.069931,-0.060919,0.045488,-0.037739,0.037572,-0.022443,0.014896,-0.016949]; 	
D=[0]; 	
K=[];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
											
%% chen_ex3_ss_disc7 	

i=i+1;
name='chen_ex3_ss_disc7';
A=[6.985,-2.6138,2.1735,-1.0844,0.64925,-0.43191,0.24628;8,0,0,0,0,0,0;0,2,0,0,0,0,0;0,0,2,0,0,0,0;0,0,0,1,0,0,0;0,0,0,0,0.5,0,0;0,0,0,0,0,0.25,0]; 
B=[0.00097656;0;0;0;0;0;0]; 	
C=[0.00051499,-0.00025503,0.00015689,1.9586e-06,-8.0349e-05,0.00012656,-0.00012536]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
											
%% chen_ex4_ss_disc7 		

i=i+1;
name='chen_ex4_ss_disc7';
A=[8.991,-4.491,2.6171,-1.9609,0.97946,-0.65232,0.55857,-0.27901,0.24776;8,0,0,0,0,0,0,0,0;0,4,0,0,0,0,0,0,0;0,0,2,0,0,0,0,0,0;0,0,0,2,0,0,0,0,0;0,0,0,0,1,0,0,0,0;0,0,0,0,0,0.5,0,0,0;0,0,0,0,0,0,0.5,0,0;0,0,0,0,0,0,0,0.125,0]; 
B=[7.4506e-09;0;0;0;0;0;0;0;0]; 	
C=[1.1233e-09,3.1098e-09,-1.0909e-09,-1.5371e-09,1.6527e-09,-7.2768e-10,-5.6783e-10,7.5365e-10,2.7591e-10]; 	
D=[0]; 	
K=[0,0,0,0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% guidance_chen_ss_disc1 												

i=i+1;
name='guidance_chen_ss_disc1';
A=[3.2769,-1.2111,1.0607,-0.52951,0.44345;4,0,0,0,0;0,1,0,0,0;0,0,1,0,0;0,0,0,0.25,0]; 	
B=[0.0625;0;0;0;0]; 	
C=[0.063559,-0.0078177,-0.00041472,0.015477,-0.022118]; 	
D=[0]; 	
K=[0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
							
%% flexbeam_ss_disc1 	

i=i+1;
name='flexbeam_ss_disc1';
A=[-0.55847,0.53024,0.81679,0.087248,-0.35117,-0.60774;2,0,0,0,0,0;0,1,0,0,0,0;0,0,1,0,0,0;0,0,0,1,0,0;0,0,0,0,0.5,0]; 	
B=[1;0;0;0;0;0]; 	
C=[0.17068,0.34996,0.56452,0.49595,0.24775,0.1063]; 	
D=[0]; 	
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
							
%% flexbeam_ss_disc2 	

i=i+1;
name='flexbeam_ss_disc2';
A=[2.0176,-0.96507,0.85493,-0.75977,0.77079,-0.81939;2,0,0,0,0,0;0,1,0,0,0,0;0,0,1,0,0,0;0,0,0,1,0,0;0,0,0,0,0.5,0]; 	
B=[0.25;0;0;0;0;0]; 	
C=[0.1011,0.058327,0.070737,0.078161,0.049365,0.088751]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
								
%% flexbeam_ss_disc3 	

i=i+1;
name='flexbeam_ss_disc3';
A=[2.7685,-1.4118,0.49765,-0.62249,0.61489,-0.4526;2,0,0,0,0,0;0,2,0,0,0,0;0,0,1,0,0,0;0,0,0,1,0,0;0,0,0,0,0.5,0]; 	
B=[0.125;0;0;0;0;0]; 	
C=[0.058645,-0.009401,0.0036547,0.00025816,-0.0037133,0.028375]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% flexbeam_ss_disc4 	

i=i+1;
name='flexbeam_ss_disc4';
A=[4.9098,-2.6672,1.679,-1.306,0.59083,-0.47571;4,0,0,0,0,0;0,2,0,0,0,0;0,0,1,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[0.0625;0;0;0;0;0]; 	
C=[0.031637,-0.01742,0.0052726,0.0045195,-0.0084182,0.015637]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
								
%% flexbeam_ss_disc5 	

i=i+1;
name='flexbeam_ss_disc5';
A=[5.9441,-3.6917,2.4532,-0.91984,0.36904,-0.24752;4,0,0,0,0,0;0,2,0,0,0,0;0,0,2,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[0.015625;0;0;0;0;0]; 	
C=[0.005254,-0.0039026,0.0013038,0.00063755,-0.0009698,0.0013109]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% flexbeam_ss_disc6 	

i=i+1;
name='flexbeam_ss_disc6';
A=[5.9835,-3.7323,2.4851,-0.93151,0.37273,-0.24876;4,0,0,0,0,0;0,2,0,0,0,0;0,0,2,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[0.0078125;0;0;0;0;0]; 	
C=[0.0026341,-0.0019718,0.00065894,0.00032586,-0.00049148,0.00065788]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% flexbeam_ss_disc7 	

i=i+1;
name='flexbeam_ss_disc7';
A=[5.9985,-3.7483,2.4984,-0.93676,0.37466,-0.24975;4,0,0,0,0,0;0,2,0,0,0,0;0,0,2,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[0.0019531;0;0;0;0;0]; 	
C=[0.00042223,-0.0003167,0.00010564,5.2706e-05,-7.9127e-05,0.00010554]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc1 	

i=i+1;
name='acrobot_ss_disc1';
A=[3.7437,-3.4384,0.86901,-0.43261;-3.9731,8.3694,-0.49989,1.451;17.1225,-23.5989,3.7437,-3.4384;-27.2686,48.8701,-3.9731,8.3694]; 	
B=[-0.77107;1.5237;-5.1767;10.1667]; 	
C=[1,0,1,0]; 	
D=[0]; 	
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc2 	

i=i+1;
name='acrobot_ss_disc2';
A=[1.2734,-0.28758,0.21758,-0.01817;-0.3323,1.6603,-0.020996,0.24203;2.9809,-3.262,1.2734,-0.28758;-3.7692,7.3693,-0.3323,1.6603]; 	
B=[-0.067459;0.13492;-0.75706;1.5099]; 	
C=[1,0,1,0]; 	
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc3 

i=i+1;
name='acrobot_ss_disc3';
A=[1.0639,-0.064914,0.10211,-0.0021341;-0.075008,1.1512,-0.002466,0.10498;1.3063,-1.3431,1.0639,-0.064914;-1.552,3.1132,-0.075008,1.1512]; 	
B=[-0.015373;0.030823;-0.31705;0.63514]; 	
C=[1,0,1,0]; 	
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc4 

i=i+1;
name='acrobot_ss_disc4';
A=[1.0157,-0.015812,0.050261,-0.00026262;-0.018271,1.037,-0.00030346,0.050614;0.63157,-0.63798,1.0157,-0.015812;-0.73719,1.4898,-0.018271,1.037]; 
B=[-0.0037543;0.0075321;-0.15135;0.30358]; 	
C=[1,0,1,0]; 	
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc5 

i=i+1;
name='acrobot_ss_disc5';
A=[54.3529,-83.2992,9.9443,-13.2174;-96.2524,166.4149,-15.2728,27.7256;315.7245,-512.7647,54.3529,-83.2992;-592.5009,1005.5443,-96.2524,166.4149]; 
B=[-17.7937;34.6793;-108.6741;211.312]; 	
C=[1,0,1,0]; 	
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc6 

i=i+1;
name='acrobot_ss_disc6';
A=[1.0002,-0.00015676,0.0050003,-2.6126e-07;-0.00018114,1.0004,-3.0189e-07,0.0050006;0.062457,-0.062711,1.0002,-0.00015676;-0.072463,0.14682,-0.00018114,1.0004]; 
B=[-3.7253e-05;7.4756e-05;-0.014902;0.029905]; 	
C=[1,0,1,0]; 	
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% acrobot_ss_disc7 

i=i+1;
name='acrobot_ss_disc7';
A=[1,-6.27e-06,0.001,-2.09e-09;-7.245e-06,1,-2.415e-09,0.001;0.01249,-0.01254,1,-6.27e-06;-0.01449,0.02936,-7.245e-06,1]; 	
B=[-1.49e-06;2.99e-06;-0.00298;0.00598]; 	
C=[1,0,1,0]; 	
D=[0];
K=[0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% antenna_ss_disc1 

i=i+1;
name='antenna_ss_disc1';
A=[2.0821,-1.1843,0.24633,-0.17578,0.062759,-0.011888;1,0,0,0,0,0;0,0.5,0,0,0,0;0,0,0.25,0,0,0;0,0,0,0.125,0,0;0,0,0,0,0.015625,0]; 	
B=[0.0078125;0;0;0;0;0]; 	
C=[0.001954,0.0011217,-0.002757,0.00020125,-0.00158,-0.0015487]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% antenna_ss_disc2 	

i=i+1;
name='antenna_ss_disc2';
A=[1.5036,0.12107,-0.6991,0.014361,0.13227,-0.097548;1,0,0,0,0,0;0,1,0,0,0,0;0,0,1,0,0,0;0,0,0,0.5,0,0;0,0,0,0,0.125,0]; 	
B=[0.0039062;0;0;0;0;0]; 	
C=[0.00025321,0.0017233,6.3664e-05,-0.00096216,-0.00060948,-0.00012727]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% antenna_ss_disc3 

i=i+1;
name='antenna_ss_disc3';
A=[2.8944,-0.85925,0.64616,-0.37851,0.27503,-0.15616;4,0,0,0,0,0;0,1,0,0,0,0;0,0,1,0,0,0;0,0,0,0.5,0,0;0,0,0,0,0.25,0]; 	
B=[0.00097656;0;0;0;0;0]; 	
[5.4223e-05,0.00020042,0.00015142,-0.00021694,-0.00016517,-1.9176e-05]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% antenna_ss_disc4 

i=i+1;
name='antenna_ss_disc4';
A=[4.4738,-2.1401,1.1326,-0.70192,0.24006,-0.13972;4,0,0,0,0,0;0,2,0,0,0,0;0,0,1,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[0.00012207;0;0;0;0;0]; 	
C=[1.7197e-05,8.4911e-05,4.8886e-05,-5.7178e-05,-2.7197e-05,-3.6148e-06]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% antenna_ss_disc5 

i=i+1;
name='antenna_ss_disc5';
A=[1.9667,-0.93366,-0.13119,-0.031757,0.0068325,-0.00028264;1,0,0,0,0,0;0,0.25,0,0,0,0;0,0,0.03125,0,0,0;0,0,0,0.015625,0,0;0,0,0,0,0.00024414,0]; 
B=[0.015625;0;0;0;0;0]; 	
C=[0.0035721,0.00099761,-0.003178,-0.0038652,-0.0024608,-0.0074411]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
									
%% antenna_ss_disc6 

i=i+1;
name='antenna_ss_disc6';
A=[5.8691,-3.5893,2.3422,-0.85999,0.33693,-0.22007;4,0,0,0,0,0;0,2,0,0,0,0;0,0,2,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[4.7684e-07;0;0;0;0;0]; 	
C=[5.3504e-08,3.2736e-07,2.5412e-07,-1.2899e-07,-7.8269e-08,-1.2265e-08]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% antenna_ss_disc7 

i=i+1;
name='antenna_ss_disc7';
A=[5.9744,-3.7181,2.4682,-0.92165,0.3671,-0.24371;4,0,0,0,0,0;0,2,0,0,0,0;0,0,2,0,0,0;0,0,0,1,0,0;0,0,0,0,0.25,0]; 	
B=[1.4901e-08;0;0;0;0;0]; 	
C=[5.5696e-10,3.4663e-09,2.7566e-09,-1.3824e-09,-8.5889e-10,-1.3685e-10]; 	
D=[0];
K=[0,0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
										
%% cstr_ss_disc1 	

i=i+1;
name='cstr_ss_disc1';
A=[2.7663,-1.2677,0.76913;2,0,0;0,0.5,0]; 	
B=[0.0039062;0;0]; 	
C=[-0.0028193,0.00010658,0.0025725]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					
%% cstr_ss_disc2 	

i=i+1;
name='cstr_ss_disc2';
A=[2.8998,-1.4001,0.45016;2,0,0;0,1,0]; 	
B=[0.0019531;0;0]; 	
C=[-0.0009483,1.4742e-05,0.00045708]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					
%% cstr_ss_disc3 	

i=i+1;
name='cstr_ss_disc3';
A=[2.5817,-1.0867,0.59156;2,0,0;0,0.5,0]; 	
B=[0.0078125;0;0]; 	
C=[-0.0052027,0.00037556,0.0043325]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
						
%% cstr_ss_disc4 	

i=i+1;
name='cstr_ss_disc4';
A=[2.4352,-0.94519,0.45498;2,0,0;0,0.5,0]; 	
B=[0.015625;0;0]; 	
C=[-0.0054176,0.00055995,0.0041191]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
						
%% cstr_ss_disc5 					

i=i+1;
name='cstr_ss_disc5';
A=[2.5817,-1.0867,0.59156;2,0,0;0,0.5,0]; 	
B=[0.0078125;0;0]; 	
C=[-0.0052027,0.00037556,0.0043325]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% cstr_ss_disc6 	

i=i+1;
name='cstr_ss_disc6';
A=[2.9974,-1.4974,0.49869;2,0,0;0,1,0]; 	
B=[3.0518e-05;0;0]; 	
C=[-3.9206e-05,1.5513e-08,1.9585e-05]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					
%% cstr_ss_disc7 	

i=i+1;
name='cstr_ss_disc7';
A=[2.9995,-1.4995,0.49974;2,0,0;0,1,0]; 	
B=[7.6294e-06;0;0]; 	
C=[-6.2773e-06,4.9693e-10,3.1381e-06]; 	
D=[0];
K=[0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					
%% regulator_ss_disc1 	

i=i+1;
name='regulator_ss_disc1';
A=[0.90484,0.21006,0.020663,0.065048,0.37553;0,0.7788,0.090335,0.31561,2.3967;0,0,0.00079275,0.0063085,0.56374;0,0,0,3.7267e-06,0.033671;0,0,0,0,0.0067379]; 
B=[1.9852;23.3261;52.2281;8.899;2.9798]; 	
C=[1,0,0,0,0]; 	
D=[0];
K=[0,0,0,0,0];
		
%% regulator_ss_disc2 	

i=i+1;
name='regulator_ss_disc2';
A=[0.96079,0.093253,0.0071032,0.018144,0.060432;0,0.90484,0.098385,0.31768,1.5372;0,0,0.057498,0.40585,5.7645;0,0,0,0.0067379,0.64299;0,0,0,0,0.13534]; 
B=[0.09677;3.6646;29.9669;7.0104;2.594]; 	
C=[1,0,0,0,0]; 	
D=[0];
K=[0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
		
%% regulator_ss_disc3 	

i=i+1;
name='regulator_ss_disc3';
A=[0.9802,0.048282,0.0025532,0.0046577,0.0084477;0,0.95123,0.082606,0.20664,0.53308;0,0,0.23979,1.2609,6.5212;0,0,0,0.082085,1.429;0,0,0,0,0.36788]; 
B=[0.005922;0.50923;10.1543;3.9743;1.8964]; 	
C=[1,0,0,0,0]; 	
D=[0];
K=[0,0,0,0,0];
		
%% regulator_ss_disc4 	

i=i+1;
name='regulator_ss_disc4';
A=[0.99005,0.024567,0.00078929,0.00088967,0.00082683;0,0.97531,0.056386,0.091173,0.11724;0,0,0.48968,1.6245,3.5776;0,0,0,0.2865,1.6001;0,0,0,0,0.60653]; 
B=[0.00026887;0.049718;2.2139;1.6211;1.1804]; 	
C=[1,0,0,0,0]; 	
D=[0];
K=[0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
		
%% regulator_ss_disc5 	

i=i+1;
name='regulator_ss_disc5';
A=[0.99501,0.012391,0.00022139,0.00014001,6.5483e-05;0,0.98758,0.033417,0.031007,0.019718;0,0,0.69977,1.3153,1.3364;0,0,0,0.53526,1.2177;0,0,0,0,0.7788]; 
B=[1.0233e-05;0.0039331;0.37094;0.52956;0.6636]; 	
C=[1,0,0,0,0]; 	
D=[0];
K=[0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% regulator_ss_disc6 	

i=i+1;
name='regulator_ss_disc6';
A=[0.998,0.0049825,3.8072e-05,1.0352e-05,1.9403e-06;0,0.99501,0.014872,0.0060129,0.0015148;0,0,0.86693,0.7046,0.27286;0,0,0,0.7788,0.63018;0,0,0,0,0.90484]; 
B=[1.1836e-07;0.00011647;0.028439;0.10024;0.28549]; 	
C=[1,0,0,0,0]; 	
D=[0]; 	
K=[0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end

%% regulator_ss_disc7 	

i=i+1;
name='regulator_ss_disc7';
A=[0.999,0.0024956,9.7547e-06,1.3592e-06,1.2742e-07;0,0.9975,0.0077113,0.0016047,0.00020139;0,0,0.93109,0.38851,0.074026;0,0,0,0.8825,0.34366;0,0,0,0,0.95123]; 
B=[3.8543e-09;7.6465e-06;0.0037784;0.02654;0.14631]; 	
C=[1,0,0,0,0]; 	
D=[0]; 	
K=[0,0,0,0,0];
results{i}.name=name;
if bound>boundspec
    results{i}.truth=0;
else
    results{i}.truth=1;
end
					

