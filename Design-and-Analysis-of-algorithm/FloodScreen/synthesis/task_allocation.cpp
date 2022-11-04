#include<iostream>
#include <algorithm>

using namespace std;


int main(){
    int n;

    while(cin>>n){
        if(n==0)    return 0;

        int t[n];
        for(int i=0;i<n;i++){
            cin>>t[i];
        }
        int minTime=0xfffffff;
        for(int i=0;i<(1<<n);i++){
            int sum1=0,sum2=0;
            int temp=i;
            for(int j=0;j<n;j++){
                if((temp&1)==0)
                    sum1+=t[j];
                else if((temp&1)==1)
                    sum2+=t[j];
                temp>>=1;
            }

            if(abs(sum2-sum1)<minTime){
                minTime=abs(sum2-sum1);
            }
        }
        cout<<minTime<<endl;

    }

}