m1=1080;
r=18;
t1=m1/r;
[t,x]=ode45('FangCheng9p166',[0 t1],[0 0]);
[t,x]
subplot(221); plot(t,x(:,1),'-');title('油料耗尽前x(t)');
subplot(222);   plot(t,x(:,2),'*');title('油料耗尽前v(t)');pause

[m,n]=size(t);
t1fin=m;%t1fin记录燃料烧尽的时刻;
x1=x(t1fin,1);%x1记录t1fin时刻的高度;
x2=x(t1fin,2);%x2记录t1fin时刻的速度;
[tt,y]=ode45('FangCheng10p166',[0 15],[x1 x2]); 
[tt,y]
z=[x;y];
[m,n]=size(z);
T=1:m;
subplot(223);   plot(T,z(:,1)); title('油料耗尽后x(t)');
subplot(224);   plot(T,z(:,2)); title('油料耗尽后v(t)');