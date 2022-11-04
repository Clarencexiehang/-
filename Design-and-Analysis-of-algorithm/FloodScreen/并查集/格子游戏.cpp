#include<iostream>
using namespace std;

struct step{
    int x;
    int y;
    char direct;
};

int  main(){
    int n,m;
    cin>>n>>m;
    step s[m+1];
    for(int i=1;i<=m;i++)
        cin>>s[i].x>>s[i].y>>s[i].direct;

    int parent[n+1][n+1];
    for(int i=1;i<=m;i++){
            int d=0;
            switch (s[i].direct) {
                case 'D':   parent[s[i].x][s[i].y+1]=1;break;
                case 'R':   parent[s[i].x+1][s[i].y]=1;break;
            }

        }

    return 0;
}