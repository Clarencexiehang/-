#include <iostream>
#include <algorithm>
using namespace std;

int DivideCard(int n,int *cardNum){
    int TotalNum=0;
    for(int i=0;i<n;i++)
        TotalNum+=cardNum[i];

    int differAverage[n];
    for(int i=0;i<n;i++){
        differAverage[i]=cardNum[i]-TotalNum/n;
    }
    //sort(differAverage,differAverage+n);

    int step=0;

    for(int i=0;i<n;i++){
        if(differAverage[i]==0) continue;
        differAverage[i+1]+=differAverage[i];
        step++;
    }

/*    bool flag= false;
    while(!flag){
        differAverage[n-1]+=differAverage[0];
        differAverage[0]=0;
        sort(differAverage,differAverage+n);
        step++;

        for(int i=0;i<n;i++){
            if(differAverage[i]!=0){
                flag= false;
            }
            else flag= true;
        }
    }*/
    return step;

}

int main(){
    int n;  cin>>n;
    int cardNum[n];
    for(int i=0;i<n;i++){
        cin>>cardNum[i];
    }

    cout<<DivideCard(n,cardNum);

    return 0;
}