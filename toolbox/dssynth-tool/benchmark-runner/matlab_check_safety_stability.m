
%mag suspension

K = [17.4384765625, -0.0537109375];
A = [558.1114,-1;1,0] 
B = [32;0] 

%inv pendulum
%A = [2.2553,-1;1,0] 
%B = [0.5;0] 
%K = [4.75, -1]


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

states = [1;1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
        i
    end
end 

states = [1;-1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
        i
    end
end 

states = [-1;1];
for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
        i
        return
    end
end 
states = [-1;-1];

for i=0:loops
    input = -K * states;
    states = A * states + B * input;
    if(states > 1 | states < -1)
        msg = 'unsafe'
        states
        i
    end
end 
