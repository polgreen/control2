function parserss2ss (system, inputs, intBits, fracBits, maxrange, minrange, K, name)
% Translate the matlab systems to a ss file
%
% Function: parserss2ss(system, inputs, intBits, fracBits, maxrange, minrange, K, name)
%
%  system: the physical plant in state-space format
%  inputs: the inputs for the state-space system
%  intBits: integer bits implementation
%  fracBits: fractional bits implementation
%  maxrange: maximum dynamic range
%  minrange: minimum dynamic range
%  K: feedback matrix for closed-loop systems
%  name: the name for the .ss file produced
%
% Author: Lennon Chaves
% June 2017
%
A = system.A;
B = system.B;
C = system.C;
D = system.D;
sampletime = system.Ts;

[rA,cA] = size(A);
nStates = rA;
[rB,cB] = size(B);
nInputs = cB;
[rC,cC] = size(C);
nOutputs = rC;

file_name = [name '.ss'];

fid = fopen(file_name, 'wt' );

fprintf(fid,'implementation <%d,%d>\n', intBits, fracBits);
fprintf(fid,'range [%d,%d]\n', maxrange, minrange);
fprintf(fid,'states = %d;\n', nStates);
fprintf(fid,'inputs = %d;\n', nInputs);
fprintf(fid,'outputs = %d;\n', nOutputs);
fprintf(fid,'A = %s \n', matrix2string(A));
fprintf(fid,'B = %s \n', matrix2string(B));
fprintf(fid,'C = %s \n', matrix2string(C));
fprintf(fid,'D = %s \n', matrix2string(D));
fprintf(fid,'inputs = %s \n', matrix2string(inputs));
fprintf(fid,'Ts = %s; \n', num2str(sampletime));
if isempty(K) == 0
   fprintf(fid,'K = %s \n', matrix2string(K));
end
fclose(fid);

end
