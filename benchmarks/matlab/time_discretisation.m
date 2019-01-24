function result  = time_discretisation( ss_cont, name )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


time_discretisations = [0.5, 0.1, 0.05, 0.001, 0.0005, 0.0001, 0.00005, 0.00001, 0.000005, 0.000001];

    name=strcat(name,'_ss_disc');
    disc1=genvarname(name, who);

for ts = time_discretisations
    
    disc1=genvarname(name, who);
    eval([disc1 ' =c2d(ss_cont,ts)'])   
    save('benchmark_ss',disc1,'-append')

end
end

