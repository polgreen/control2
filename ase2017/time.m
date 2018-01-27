c = categorical({'cruise-HSCC','cruise','dc-motor','helicopter','invpendulum-cartpos','invpendulum-pendang', 'magnetic-pointer', 'magsuspension','pendulum','satellite', 'suspension','tapedriver','uscgtampa','flexible beam', 'uav', 'acrobot','guidance system', 'atenna'});

ss= [4.596 0 10.86 1.314875 1.8225 65.912 1.342 281.0743333 25.452 6.172 281.0776667 15.672 1.320875 1.874 38.897 2.07225 1.718285714 1.857528571];
tf = [497 0 34821 30222 1874 67895 1345 1647 1042 48576.33333 1350 471 0 67981 325.78 67981 48238 67234];

bar(c,ss)
legend('state-space')
ylabel ('Time (s)')
set(findall(gcf,'-property','LineWidth'),'LineWidth',2)
set(findall(gcf,'-property','FontSize'),'FontSize',18);

figure
bar(c,tf)
legend('transfer-function')
ylabel ('Time (s)')
set(findall(gcf,'-property','LineWidth'),'LineWidth',2)
set(findall(gcf,'-property','FontSize'),'FontSize',18);

figure
data = [ss' tf'];
bar(c,data)
legend('state-space','transfer-function')
set(findall(gcf,'-property','LineWidth'),'LineWidth',2)
set(findall(gcf,'-property','FontSize'),'FontSize',18);

figure
plot(ss,'r');
hold on
plot(tf,'b');
hold off
legend('state-space','transfer-function')
set(findall(gcf,'-property','FontSize'),'FontSize',18);
