#include<iostream>
using namespace std;
#define max 100
int a[max][max];
int f[max][max];

int Max(int a,int b){
    return a>b?a:b;
}

int DFS(int x,int y,int n){
    if(f[x][y]==-1){
        if(x==n-1)    f[x][y]=a[x][y];
        else f[x][y]=a[x][y]+Max(DFS(x+1,y,n), DFS(x+1,y+1,n));
    }
    return f[x][y];
}

int main(){
    int n;
    cin>>n;
    while(n!=0){
        for(int i=0;i<n;i++)
            for(int j=0;j<=i;j++){
                cin>>a[i][j];
                f[i][j]=-1;
            }


        DFS(0,0,n);
        cout<<f[0][0]<<endl;
        cin>>n;
    } 
    return 0;
}