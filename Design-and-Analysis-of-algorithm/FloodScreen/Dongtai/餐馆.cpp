#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int n;  cin>>n;
    while(n!=0){
        //Input
        int mi[n];
        int pi[n];
        int k;
        for(int i=0;i<n;i++)    cin>>mi[i];
        for(int i=0;i<n;i++)    cin>>pi[i];
        cin>>k;

        int dp[n];  dp[0]=pi[0];
        for(int i=1;i<n;i++){
            dp[i]=dp[i-1];
            int tempMax=dp[i];
            for(int j=i-1;j>=0;j--){

                if(mi[i]-mi[j]>=k&&(dp[j]+pi[i])>tempMax){
                    dp[i]=max(dp[i-1],dp[j]+pi[i]);
                    tempMax=dp[i];
                }
            }
        }
        cout<<dp[n-1]<<endl;
        cin>>n;
    }
    return 0;
}