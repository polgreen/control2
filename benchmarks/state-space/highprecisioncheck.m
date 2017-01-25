
global FiSettings ;
global FiSettingsP ;

FiSettings = fimath('ProductMode',...
                   'SpecifyPrecision',... 
                   'ProductWordLength',16,... 
                   'ProductFractionLength',8, ...
                   'RoundingMethod','Zero',...
                   'SumMode', 'SpecifyPrecision',...
                   'SumWordLength',16, ...
                   'SumFractionLength', 8, ...
                   'OverflowAction', 'Wrap');
               
 FiSettingsP = fimath('ProductMode',...
                   'SpecifyPrecision',... 
                   'ProductWordLength',64,... 
                   'ProductFractionLength',32, ...
                   'RoundingMethod','Floor',...
                   'SumMode', 'SpecifyPrecision',...
                   'SumWordLength',64, ...
                   'SumFractionLength', 32, ...
                   'OverflowAction', 'Wrap');              
               
digits(256);             
fxp=@(v) fi(double(v),1,16,8,FiSettings);
fxpP = @(v) vpa(v);% fi(v,0.5,64,32,FiSettingsP);

msg = 'dcmotor_ss_disc1.ss' %UNSAFE
K = [fxp(0.0078125), fxp(-0.0078125)];
A = fxpP([ 0.90122,1.3429e-08;7.4506e-09,0 ]);
B = fxpP([ 128;0 ]);

loops = 50;
numstates = numel(B);

if(numstates==2)
    statematrix = [fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5) ; fxpP(-0.5),fxpP(0.5),fxpP(-0.5), fxpP(0.5)];
elseif (numstates==3)
    statematrix = [fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5); ...
                   fxpP(-0.5),fxpP(-0.5),fxpP(0.5), fxpP(0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5); ...
                   fxpP(-0.5),fxpP(0.5),fxpP(-0.5), fxpP(0.5),fxpP(-0.5),fxpP(0.5),fxpP(-0.5),fxpP(0.5)];
elseif (numstates==4)   
    statematrix = [fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5); ...
                   fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5); ...
                   fxpP(-0.5),fxpP(-0.5),fxpP(0.5), fxpP(0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5), fxpP(0.5),fxpP(-0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5); ...
                   fxpP(-0.5),fxpP(0.5),fxpP(-0.5), fxpP(0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5),fxpP(-0.5),fxpP(0.5),fxpP(-0.5), fxpP(0.5),fxpP(-0.5),fxpP(0.5),fxpP(0.5),fxpP(0.5)];
end

  
for j=1:2^(numstates)
 % states = statematrix(:,j) ;
 states = fxpP([-0.5;0.5]);
  for i=1:loops

    tmp = fxp(states)  
    input = -K * fxp(states)
    tmp_input = fxpP(input)
    if(input>INPUT(2) || input< INPUT(1))
        msg = 'input too big'
        return
    end    
    states = A * (states) + B * double(input)
    for idx = 1: numel(states)
        if(states(idx) > 1 || states(idx) < -1)
            msg = '!!!!!UNSAFE!!!!!'
            i
            states
            statematrix(:,j)
            return
        end  
    end
  end 
end
msg = 'safe and stable'