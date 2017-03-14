function synthExecute(type)
% Invoke DSSynth Tool in order to synthesis the controller for a given plant
%
% Function: synthExecute(type)
%
% type: 'ss' for state-space or 'tf' for transfer-fuction;
%
% Author: Lennon Chaves
% 
% March 2017
%

current = pwd;

user = userpath;

if strfind(user,'/Documents/MATLAB') %default folder installation
    install_folder = [user '/Add-Ons/Toolboxes/DSSynth/code'];
else
    install_folder = [user '/Toolboxes/DSSynth/code'];
end

if strcmp(type, 'ss')
  filesystem = 'system.ss';
elseif strcmp (type, 'tf')
  filesystem = 'system.c';
end

cd(install_folder);

cd 'dssynth-tool'
mkdir 'benchmarks'
cd 'benchmarks'
mkdir 'system'
cd 'system'

benchmark = [current '/' filesystem];

copyfile(benchmark);

benchmark_path = pwd;

cd(current);

%TODO: Implement Runner for State-Space
runner = [install_folder '/dssynth-tool/compiler-transfer-function.sh'];
command = ['sh ' runner];
system(command);

logfile = [benchmark_path '/system_bound_simple.log'];

copyfile(logfile);

end
