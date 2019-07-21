%  A=xlsread('2.xlsx');
% A=xlsread('3.xlsx');
A=xlsread('4.xlsx');
% A=xlsread('5.xlsx');
% A1=A(1,:);
% A2=A(2,:);
% A3=A(3,:);%加分号后不在脚本中输出
% A1=A(5,:);
% A2=A(6,:);
% A3=A(7,:);

A1=A(9,:);
A2=A(10,:);
A3=A(11,:);

plot(A1,A2,'pk-','LineWidth',1.5);
hold on;
plot(A1,A3,'k-d','LineWidth',1.5);
%  set(gca,'xtick',(0:5:30));   %设置x轴
% set(gca,'ytick',(150:50:450));   %设置y轴
grid minor
set(gca,'Gridalpha',0.4)
% set(gca,'LineWidth',2)
set(gca, 'minorgridcolor','k')
set(gca, 'minorgridalpha',0.7)  %透明度在0-1之间
%  axis([150 450 0 35])
%  axis([5 35 0 35])
%    axis([8 32 0 45])
  axis([127 203 0 20])
%  xlabel('The number of layer nodes : n ')
%   xlabel('The number of layer turning nodes : tn')
%   xlabel('The number of source nodes : sou')
  xlabel('The number of destination nodes : des')
 ylabel('The scheduling round number')
 set(gca,'FontWeight','bold')
 set(gca,'FontSize',15)
%title('comparison of average CDS spectral-efficiency')
legend('Algorithm 1','Algorithm 2')