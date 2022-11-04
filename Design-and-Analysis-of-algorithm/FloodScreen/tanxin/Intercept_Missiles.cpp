#include <iostream>
#include <algorithm>
#include<vector>
#include <cstring>

using namespace std;

int systemRequiredNum(vector<int> &h,int n){
    int SystemNum=1;
    int minHeight[100];
    minHeight[1]=h[0];

    int p;  //代表一套系统
    //外层循环i表示第i颗导弹，内层循环j表示第j套拦截系统
    for(int i=1;i<n;i++){
        p=0;
        for(int j=1;j<=SystemNum;j++){
            //如果原来系统能截止导弹，找到其中最低的系统赋值给系统p
            if(minHeight[j]>=h[i]){
                if(p==0)    p=j;
                else if(minHeight[j]<minHeight[p])  p=j;
            }
        }
        //如果原来的系统不能截止，就新增一套系统
        if(p==0){
            SystemNum++;
            minHeight[SystemNum]=h[i];
        }
        else
            minHeight[p]=h[i];
    }
    return SystemNum;
}

int InterceptMaxNum(vector<int> &h,int n){
    int a[n];

    for(int i=0;i<n;i++)
        a[i]=1;

    for(int i=0;i<n-1;i++){
        int max=0;
        //找出从0到第i颗中拦截系统标记在a数组中最大的值
        for(int j=0;j<=i;j++){
            if(a[j]>max&&h[j]>=h[i+1]){
                max=a[j];
            }
        }
        //第i+1颗导弹是第pos个导弹后被拦截
        a[i+1]=max+1;

    }
    sort(a,a+n);
    return a[n-1];
}

int main(){
   vector<int> h;
   int height;
   int n=0;
   while(scanf("%d",&height)!=EOF){
       h.push_back(height);
       n++;
       if(getchar()=='\n')
           break;
   }
   cout<<InterceptMaxNum(h,n)<<endl;
   cout<<systemRequiredNum(h,n);
   return 0;
}