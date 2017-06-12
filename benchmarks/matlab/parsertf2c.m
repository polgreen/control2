function parsertf2c (plant, intBits, fracBits, minRange, maxRange, name)

ap = cell2mat(plant.Denominator);
nAp = length(ap);
bp = cell2mat(plant.Numerator);
nBp = length(bp);

% generating the controller structure inside the ansi-c file
nAc = nAp;
ac = zeros(1,nAc);
nBc = nBp;
bc = zeros(1,nBc);

sample_time = plant.Ts;

file_name = [name '.c'];

fid = fopen(file_name, 'wt' );
fprintf(fid,'%s\n\n', '#include <dsverifier.h>');

%controller not synthesized
fprintf(fid,'%s\n\t', 'digital_system controller = { ');
fprintf(fid,'%s %s },\n\t','.b = { ', poly2strc(bc));
fprintf(fid,'%s %s },\n\t','.b_uncertainty = { ', poly2strc(bc));
fprintf(fid,'%s %d,\n\t','.b_size = ', nBc);
fprintf(fid,'%s %s },\n\t','.a = { ', poly2strc(ac));
fprintf(fid,'%s %s },\n\t','.a_uncertainty = { ', poly2strc(ac));
fprintf(fid,'%s %d,\n\t','.a_size = ', nAc);
fprintf(fid,'%s %d\n','.sample_time =', sample_time);
fprintf(fid,'%s\n\n','};');

fprintf(fid,'%s\n\t','implementation impl = { ');
fprintf(fid,'%s %d,\n\t','.int_bits = ', intBits);
fprintf(fid,'%s %d,\n\t','.frac_bits =  ', fracBits);
fprintf(fid,'%s %f,\n\t','.max = ', maxRange);
fprintf(fid,'%s %f\n\t','.min = ', minRange);
fprintf(fid,'%s\n\n','};');

fprintf(fid,'%s\n\t', 'digital_system plant = { ');
fprintf(fid,'%s %s },\n\t','.b = { ', poly2strc(bp));
fprintf(fid,'%s %s },\n\t','.b_uncertainty = { ', poly2strc(bc));
fprintf(fid,'%s %d,\n\t','.b_size = ', nBp);
fprintf(fid,'%s %s },\n\t','.a = { ', poly2strc(ap));
fprintf(fid,'%s %d \n\t','.a_size = ', nAp);
fprintf(fid,'%s %s },\n\t','.a_uncertainty = { ', poly2strc(ac));
fprintf(fid,'%s\n\n','};');
fclose(fid);

end
