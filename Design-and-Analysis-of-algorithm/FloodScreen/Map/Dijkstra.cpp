#include<iostream>
using namespace std;
const int INFINITY=0xfffffff;



void init(bool *known,int *dist,int *parent,int n,int s){
    for(int i=0;i<n;i++){
        known[i]= false;
        dist[i]=INFINITY;
        parent[i]=-1;
    }
    known[s]= true;
    dist[s]=0;
}

void shortPath(bool *known,int *dist,int *parent,int **G,int n,int s){
    //从源点开始更改dist数组
    for(int i=0;i<n;i++){
        if(i==s)    continue;
        if(G[s][i]<dist[i]&&G[s][i]!=0){
            dist[i]=G[s][i];
            parent[i]=s;
        }
    }

    int nextNode;
    //循序遍历每一个结点
    for(int it=0;it<n;it++){

        nextNode=-2;
        //
        for(int i=0;i<n;i++)
            if(known[i]==false){
                nextNode=i;
                break;
            }
        //修改后选择未被访问的点中dist最小的点
        int min=INFINITY;
        for(int i=0;i<n;i++){
            if(known[i]== false&&dist[i]<min){
                min=dist[i];    nextNode=i;
            }
        }
        if(nextNode==-2)    break;
        known[nextNode]= true;
        for(int i=0;i<n;i++) {
            if (G[nextNode][i]!=0&&(G[nextNode][i]+dist[nextNode]) < dist[i]) {
                dist[i] = G[nextNode][i]+dist[nextNode];
                parent[i] = nextNode;
            }
        }
    }
}

void outPut(int *dist,int n,int s){
    for(int i=0;i<n;i++){
        if(i==s)    continue;
        if(dist[i]==INFINITY)   cout<<"-1"<<" ";
        else cout<<dist[i]<<" ";
    }
}

int main(){
    int n,s;
    cin>>n>>s;

    int **G;
    G=new int*[n];
    for(int i=0;i<n;i++)
        G[i]=new int[n];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>G[i][j];

    bool known[n];
    int dist[n];
    int parent[n];

    init(known,dist,parent,n,s);
    shortPath(known,dist,parent,G,n,s);
    outPut(dist,n,s);
    return 0;
}