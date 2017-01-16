A = [4.6764e-166,0.0,0.0; 5.1253e-144,0.0,0.0; 0,2.5627e-144,0.0];
B = [0.125; 0 ; 0];
K = [0.0009765625  800 0.5];

states = [9; 9; 9];
input = 1;



if (abs(eig(A - B*K)) > 1)
    msg = 'unstable'
end

for i=0:150
    input = -K * states;
    states = A * states + B * input;
    if(states > 10 | states < -10)
        msg = 'unsafe'
    end
end    
msg = 'safe and stable'