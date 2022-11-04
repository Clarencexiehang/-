function dx=FangCheng10p166(t,x)
 m0=1600;
 m1=1080;
 g=9.8;
 k=0.3;
 dx=zeros(2,1); 
 dx(1)=x(2);
 dx(2)=(-k*x(2)^2)/(m0-m1)-g