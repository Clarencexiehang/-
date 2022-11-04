#include<iostream>
#include <vector>
#include <cstring>
#include "set"
using namespace std;

set< pair<int , int> >S;    //人与人之间的关系，如果有交集则存入
vector<int> V[100];     //某人与其他人对应的没有交集

int n,m;
int a,b,k;

bool DFS(int now,int pre,bool *ifVisit){
    ifVisit[now]= true;
    if(S.count(make_pair(now,pre)))
        return true;
    for(int i=0;i<V[now].size();i++){
        if(DFS(V[now][i],pre,ifVisit))
            return true;
    }
    return false;
}

int main(){
    while(cin>>n>>m){
        if(n==0&m==0)
            break;

        S.clear();
        //init
        for(int i=0;i<n;i++){
            V[i].clear();
            S.insert(make_pair(i,i));
        }
        //input data
        for(int i=0;i<n;i++){
            cin>>a>>b>>k;
            if(k==1){
                V[a].push_back(b);
            }else{
                S.insert(make_pair(a,b));
                S.insert(make_pair(b,a));
            }
        }

        bool flag= true;
        bool ifVisit[n];
        for(int i=0;i<n;i++){
            memset(ifVisit,false,sizeof(ifVisit));
            for(int j=0;j<V[i].size();j++){
                if(ifVisit[V[i][j]])
                    continue;
                if(DFS(V[i][j],i,ifVisit)){
                    flag= false;
                    break;
                }
            }
            if(!flag)   break;
        }
        if(flag)    cout<<"consistent"<<endl;
        else    cout<<"inconsistent"<<endl;
    }

    return 0;
}
