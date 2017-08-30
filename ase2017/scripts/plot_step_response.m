num = [-0.06875 0 0];
den = [1.0000 -1.696 0.7089];
plant = tf(num,den,0.002);
controller = tf([-0.9983 0.09587 0.1926], [1 0.5665 0.75], 0.002);

syscl = feedback(series(plant,controller),1);

num_cl = cell2mat(syscl.Numerator);
den_cl = cell2mat(syscl.Denominator);

dstep(num_cl,den_cl)
set(findall(gcf,'-property','LineWidth'),'LineWidth',2)
