% Preprocessing of char poly
%
% E Polgreen
%
% script gets discretized benchmarks and writes header files
%
%
clear all;
makebenchmarks; %Iury's script to discretize benchmarks

SS_benchmarks = load('benchmark_ss.mat');
SS_names = fieldnames(SS_benchmarks);

directory = '../headerfiles/';

for i=1:size(SS_names,1)
    Benchmark = SS_benchmarks.(SS_names{i});
    %if(isfield(Benchmark, 'a')==0)
     %   msg = 'error'
      %  break;
    %end
    A = Benchmark.A;
    B = Benchmark.B;
    states = size(B,1);
    inputs = size(B,2); %check this
    outputs = size(B,2); %check this
    
    SS_names(i) = strcat(directory,SS_names(i),'.h');
    
    fileID = fopen(SS_names{i},'w')
    %'w' = discard existing contents. change to 'a' to append
    
    %write benchmark
    fprintf(fileID,'#ifndef BENCHMARK_H_ \n#define BENCHMARK_H_ \n\n');
    fprintf(fileID,'// time discretisation %d \n',Benchmark.Ts);
    fprintf(fileID,'#ifndef INT_BITS \n#define INT_BITS 8\n#define FRAC_BITS 8\n#endif\n');
    fprintf(fileID,'#define NSTATES %d \n#include "control_types.h"\n',states);
    fprintf(fileID,'#define NINPUTS %d \n#define NOUTPUTS %d\n',inputs, outputs);
    fprintf(fileID,'#define INPUT_UPPERBOUND (__plant_precisiont)1\n');
    fprintf(fileID,'#define INPUT_LOWERBOUND (__plant_precisiont)-1\n');
    fprintf(fileID,'const __plant_typet _controller_A[NSTATES][NSTATES] = {' );
    
    if states==1
        fprintf(fileID,' interval(%d)};\n ',A(1,1)); %row 1, col 1
    else    
    for k=1:states
      if(k==1) 
        fprintf(fileID,'{ interval(%d), ',A(k,1)); %row 1, col 1
      else  
        fprintf(fileID,',\n{ interval(%d), ',A(k,1)); %row 2->n, col 1
      end
        for j=2:states-1
            fprintf(fileID,' interval(%d), ',A(k,j)); %col 2->n-1
        end
        fprintf(fileID,' interval(%d)}',A(k,states)); %col n
    end   
    fprintf(fileID,'};\n');
        
    fprintf(fileID,'const __plant_typet _controller_B[NSTATES] = {');
    for k=1:states-1
        fprintf(fileID,'interval(%d), ',B(k));
    end
    fprintf(fileID,'interval(%d)};\n',B(states));
    
    end
    



%build symbolic controller
K= sym(zeros(1, states));
x = sym('x');
for i=1:states
    K(i) = sym(sprintf('k%d', i));
end
M = (A - B*K) - x*eye(states);
C = coeffs(det(M),x);
K = fliplr(K); % for some reason Matlab gives coefficients in a weird order otherwise
constant = zeros(states+1);

%builds a matrix of constants:
%row 1 = the constant of the char poly
%row 2 = x coefficient of the char poly
%row 3 = x^2 coefficient of the char poly etc
%column 1  = constants
%column 2 = k1
%column 3 = k2 etc.
%then flip upside down to match C file
%top row = highest coeff, bottom row = constant


for j=1:states+1
       coefficients = coeffs(C(j),K);
       sz = size(coefficients,2);
     for h=states:-1:1
        if(has(C(j),K(h)))
            constant(j,h+1) = coefficients(sz);
            sz = sz-1; 
            if(sz==0)
                break;
            end
        end
     end
        if(sz==1)
            constant(j,1) = coefficients(1);
        end       
end

constant = flipud(constant);

%output header file

fprintf(fileID,'const __plant_typet __char_poly_const[%d][%d] = \n {', states+1,states+1);

for i=1:states+1
   if(i==1) 
        fprintf(fileID,'{ %d, ',constant(i,1));
   else
        fprintf(fileID,',\n{ %d, ',constant(i,1));
   end     
   for j=2:states
        fprintf(fileID,' %d, ',constant(i,j));
   end
   fprintf(fileID,' %d}',constant(i,states+1));
end   
fprintf(fileID,'};\n');

fprintf(fileID,'\n#endif /*BENCHMARK_H_*/');

fclose(fileID);
end