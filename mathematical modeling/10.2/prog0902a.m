clc; clear all;
M=dlmread('data0902.txt');
n=46;
x1=M(:,3);
x2=M(:,4);
x3=M(:,6);
x4=M(:,7);
y=M(:,2);
x=[ones(n,1) x1 x2 x3 x4 ];
[b,bi,r,ri,s]=regress(y,x);
s2=sum(r.^2)/(n-5);
%(double)b;(double)bi,(double)s,(double)s2
fprintf('%.4f\n',s);
figure(1)
plot(x1,r,'+'),
figure(2)
xx=M(:,8);
plot(xx,r,'+');