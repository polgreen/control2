function y = synthesize(system, intBits, fracBits, rangeMax, rangeMin, property)

% system - tf or ss format (use class command to identify the type of input

% property: stability? quantization error?

%- get the paraments from the plant and implementation, and then translate in a ANSI-C file;
%- call the command line for TF-synthesis and execute the synthesis (prepare a shell script to execute DSSynth);
%- get .log file generated, and extract the controller synthesized by DSSynth;
%- Print the system synthesized in Worskpace (and save in a .MAT file?)


%Order of the Scripts:

%synthParse (translate ANSI-C File)
%synthExecute (call DSSynth)
%synthExtract (extract controller from .log file)
%synthReport (print controller synthesized and outputs generated)

type = class(system);

if (strcmp(type,'tf'))

ds.plant = system;
ds.controller = system;
ds.impl.frac_bits = fracBits;
ds.impl.int_bits = intBits;
ds.range.max = rangeMax;
ds.range.min = rangeMin;

synthParse(ds,'tf');

end



y = 0;

end
