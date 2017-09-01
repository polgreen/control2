% This script reads the validation results
% Iury Bessa
% Manaus, 2017

num_success=0;
num_benchmarks=153;
for i=1:num_benchmarks 
    results{i}.truth;
    if results{i}.truth==1
        num_success=num_success+1;
    else display(strcat('The controller ',results{i}.name,'is not safe.'))
    end
end

if num_benchmarks==num_success
    display('All controllers are safe.')
end