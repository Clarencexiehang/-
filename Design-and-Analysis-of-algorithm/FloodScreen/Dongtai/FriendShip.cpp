#include<iostream>
#include <algorithm>

using namespace std;

typedef struct pairCity{
    int north;
    int south;
};

void IntersectionNum(pairCity *c,int n,int *A){
    for(int i=0;i<n;i++){
        A[i]=0;
    }

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(c[i].north<c[j].north&&c[i].south>c[j].south){
                A[i]++;//cout<<i<<" "<<j<<endl;
            }
            if(c[i].north>c[j].north&&c[i].south<c[j].south)
                A[i]++;
        }

}


bool comp(pairCity a,pairCity b){
    return a.north>b.north;
}


int main(){
    int n;  cin>>n;
    pairCity c[n];

    for(int i=0;i<n;i++)
        cin>>c[i].north>>c[i].south;

    sort(c,c+n,comp);

    int *A=new int[n];
    IntersectionNum(c,n,A);
    int flag[n];
    for(int i=0;i<n;i++){
        flag[i]=1;
    }

    cout<<A[0]<<endl;



    return 0;
}