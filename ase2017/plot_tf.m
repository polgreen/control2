plant = tf([0.1898 1.8027*10^-4],[1 -0.9012, -1.0006*10^-16],2);
controller = tf([-0.3466796875 0.015625],[0.5 0.19921875 0],2);

syscl= feedback(series(plant,controller),1);

num_cl = cell2mat(syscl.Numerator);
den_cl = cell2mat(syscl.Denominator);

dstep(num_cl,den_cl)
set(findall(gcf,'-property','LineWidth'),'LineWidth',2)
