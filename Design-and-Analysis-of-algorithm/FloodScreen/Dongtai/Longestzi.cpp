#include<iostream>
using namespace std;

void init(int parent[],int a[],int n){
    parent[n-1]=0;    a[n-1]=1;
    for(int i=0;i<n;i++)
        parent[i]=a[i]=-1;
}



void f(int *Len,int *parent,int *a,int n){
    for(int i=n-2;i=1;i--){
        int Max=a[i];   int ParentLoc=i;
        for(int j=i;j<n;j++){
            if(Len[j]>Len[i-1]){
                if(a[j]>Max){
                    Max=a[j];   ParentLoc=j;
                }
            }
        }
        a[i-1]=Max+1;   parent[i-1]=ParentLoc;
    }
}

void Print(int *a,int n){
    int max=a[0];
    for(int i=1;i<n;i++){
        if(a[i]>max)
            max=a[i];
    }
    cout<<max;
}


int main(){
    int n;  cin>>n;
    int Len[n];
    for(int i=0;i<n;i++)
        cin>>Len[i];

    int parent[n];
    int a[n];

    init(parent,a,n);
    f(Len,parent,a,n);
    Print(a,n);
    return 0;
}
