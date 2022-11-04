#include <iostream>
using namespace std;

int Forbid(int k,int x,int row){
    if(x<=(((1+k)*k/2))){
        for(row;row<=k;row++){
            int a=(row+1)*row/2;
            int b=(row+2)*(row+1)/2;
            if(a<=x&&x<=b){
                return row+1;
            }
        }
    }

    else{
        int preNum=(k+1)*k/2;
        for(row=k+1;row<2*k-1;row++){
            int a=(2*k-row+k-1)*(row-k)/2+preNum;
            int b=(2*k-row-1+k-1)*(row+1-k)/2+preNum;
            if(x<=a){
                return row;
            }
        }
    }
}

int main() {
    int n;  cin>>n;
    int k[n];   int num[n];
    for(int i=0;i<n;i++){
        cin>>k[i]>>num[i];

    }

    for(int i=0;i<n;i++){
        cout<<Forbid(k[i],num[i],0)<<endl;
    }
    return 0;
}
