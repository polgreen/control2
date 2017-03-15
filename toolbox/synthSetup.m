function ds = synthSetup(system, fracBits, intBits, rangeMax, rangeMin, type)
% Organize the parameters provided for the digital plant, and then translate it to a struct in MATLAB
%
% Function: ds = synthSetup(system, intBits, fracBits, rangeMax, rangeMin,type)
%
%  system: plant designed as transfer-function or state-space representation (See also TF and SS.)
%  intBits: represents the integer bits part;
%  fracBits: represents the fractionary bits part;
%  rangeMax: represents the maximum dynamical range;
%  rangeMin: represents the minimum dynamical range;
%  type: the type of digital plant: state-space (ss) or transfer-function (tf);
%
% Author: Lennon Chaves
% 
% March 2017
%
 if (strcmp(type,'tf'))
    ds.plant = system;
    ds.controller = system;
 elseif (strcmp(type,'ss'))
    ds.system = system;
 end

  ds.impl.frac_bits = fracBits;
  ds.impl.int_bits = intBits;
  ds.range.max = rangeMax;
  ds.range.min = rangeMin;

end
