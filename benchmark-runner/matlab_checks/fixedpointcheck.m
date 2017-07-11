global FiSettings ;
global FiSettingsP ;

FiSettings = fimath('ProductMode',...
                   'SpecifyPrecision',... 
                   'ProductWordLength',16,... 
                   'ProductFractionLength',8, ...
                   'RoundingMethod','Floor',...
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
               
               
fxp=@(v) fi(v,1,16,8,FiSettings);
fxpP = @(v) v;% fi(v,0.5,64,32,FiSettingsP);

loops = get_completeness(A, B, K )+1;
numstates = numel(B);

for i=1:numstates
    K(i) = fxp(K(i));
end


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
  states = statematrix(:,j) ;
  for i=1:loops

    input = -K * fxp(states);
    tmp_input = double(input);
    if(input>INPUT(2) || input< INPUT(1))
        msg = 'input too big'
        return
    end    
    states = A * (states) + B * double(input);
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