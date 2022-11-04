#include<iostream>
using namespace std;

typedef struct {
    int w;  //体积
    int c;  //价值
}pack;

int max(int a,int b){
    return a>b?a:b;
}

class FullBackPack{
    int PackCapacity;
    int num;
    int **dp;
    pack *p;
public:
    FullBackPack(int packCapacity,int num) : PackCapacity(packCapacity+1),num(num+1){}

    void init(){
        dp=new int*[num];
        p=new pack[num];
        for(int i=0;i<num;i++){
            dp[i]=new int [PackCapacity];

        }
        for(int i=1;i<=num-1;i++)
            cin>>p[i].w>>p[i].c;

        for(int i=0;i<num;i++)
            for(int j=0;j<PackCapacity;j++){
                dp[i][j]=0;
            }
    }

    void Solution(){
        for(int i=1;i<num;i++)
            for(int j=1;j<PackCapacity;j++){
                dp[i][j]=dp[i-1][j];
                if(j>=p[i].w){
                    dp[i][j]=max(dp[i][j],dp[i-1][j-p[i].w]+p[i].c);
                }
            }

        int Max=0;
        for(int i=1;i<num;i++){
            if(dp[i][PackCapacity-1]>Max)
                Max=dp[i][PackCapacity-1];
        }
        cout<<Max<<endl;
    }
};

int main(){
    int m,n;
    cin>>m>>n;
    FullBackPack a(m,n);
    a.init();
    a.Solution();
    return 0;
}