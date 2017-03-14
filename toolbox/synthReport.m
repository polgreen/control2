function controller = synthReport(ds, type)
% Get the controller extracted and translate the system synthesized in MATLAB System.
%
% Function: controller = synthReport(ds, type)
%
%  ds: digital plant with specifications about plant, implementation and dynamical ranges;
%  type: 'ss' for state-space or 'tf' for transfer-fuction;
%
% Author: Lennon Chaves
% 
% March 2017
%

controller_file = 'controller.out';
fid = fopen(controller_file);

if (strcmp(type,'tf'))
 numLine = fgetl(fid);
 numerator = str2num(numLine);
 denLine = fgetl(fid);
 denominator = str2num(denLine);
 sample = ds.plant.Ts;
 controller = tf(numerator, denominator, sample);

elseif (strcmp(type,'ss'))
 controller = str2num(fgetl(fid));
end

fclose(fid);

delete(controller_file);

end
