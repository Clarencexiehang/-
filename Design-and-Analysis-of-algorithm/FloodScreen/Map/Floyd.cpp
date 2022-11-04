//Floyd Algorithm in order to get the shortest path
#include<iostream>
using namespace std;
const int INFINITY=0xfffffff;

void init(int **dis,int **path,int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            cin>>dis[i][j];
            path[i][j]=-1;
        }
}

void FLoyd_ShortPath(int **dis,int **path,int n){
    for(int v=0;v<n;v++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(dis[i][j]==0&&(dis[i][v]+dis[v][j])>0&& dis[i][v]!=0 && dis[v][j]!=0&&i!=j){
                    dis[i][j]=dis[i][v]+dis[v][j];
                    path[i][j]=v;
                }

                else if(dis[i][j]>(dis[i][v]+dis[v][j])&& dis[i][v]!=0 && dis[v][j]!=0){
                    dis[i][j]=dis[i][v]+dis[v][j];
                    path[i][j]=v;
                }
            }
}

void Output(int **dis,int **path,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<dis[i][j]<<" ";
        }
        if(i!=n-1)cout<<endl;
    }
}

int main(){
    int n;  cin>>n;
    int **dis;
    int **path;
    dis=new int*[n];
    path=new int *[n];
    for(int i=0;i<n;i++){
        dis[i]=new int[n];
        path[i]=new int[n];
    }

    init(dis,path,n);
    FLoyd_ShortPath(dis,path,n);
    Output(dis,path,n);
    return 0;
}
