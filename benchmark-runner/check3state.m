
%DCMOTOR
%K = [0.015625, 0, -0.7578125];
%A = [0.9905,0.075687,0.021033;0.125,0,0;0,0.015625,0] ;
%B = [16;0;0] ;

%mag suspension
K = [17.4384765625, -0.0537109375];
A = [2.001,-1;1,0] 
B = [0.0625;0] 

%inv pendulum
%A = [2.2553,-1;1,0] 
%B = [0.5;0] 
%K = [4.75, -1]


%Helicopter
%K = [0.234375, -0.1484375, 0.078125];
%A = [2.6207,-1.1793,0.65705;2,0,0;0,0.5,0] ;
%B = [8;0;0] ;

%inv pendum cart pos
%K = [17.01953125, -13.01171875, 5.0078125, -2.046875];
%A = [4.2553,-3.2553,1.0638,-0.5;2,0,0,0;0,2,0,0;0,0,0.5,0] 
%B = [0.25;0;0;0] 

%tape whatever
%K=[-1, -1.86328125, -0.00390625]
% A = [4.6764e-166,0,0;5.1253e-144,0,0;0,2.5627e-144,0] 
% B = [0.125;0;0] 

%pendulum ss
%K = [-4.7421875, -1]
%A = [-1.9999,-1;1,0] 
%B = [0.5;0]  

loops = 50;
if (abs((eig(A - B*K))) < 1)
    msg = 'stable'
else
    msg = 'unstable'
    eig(A - B*K)
end
%states = [1;1;1];
states = [1;1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 
%states = [1;1;-1];
states = [1;-1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 
%states = [1;-1;1];
states = [-1;1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 
states = [-1;-1];
%states = [1;-1;-1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 

states = [-1;1;1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 

states = [-1;1;-1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 

states = [-1;-1;1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 

states = [-1;-1;-1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
    end
end 
msg = 'done'