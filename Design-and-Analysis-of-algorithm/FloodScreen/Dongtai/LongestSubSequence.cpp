#include<iostream>
#include <algorithm>
using namespace std;

int Max(int a,int b){
    return a>b?a:b;
}

int main(){
    string X,Z;
    while(cin>>X>>Z){
        int table[X.size()+1][Z.size()+1];
        for(int i=0;i<X.size()+1;i++)
            table[i][0]=0;
        for(int i=0;i<Z.size()+1;i++)
            table[0][i]=0;

        for(int i=1;i<X.size()+1;i++)
            for(int j=1;j<Z.size()+1;j++){
                if(X[i-1]==Z[j-1])
                    table[i][j]=table[i-1][j-1]+1;
                else
                    table[i][j]=Max(table[i-1][j],table[i][j-1]);
            }

        cout<<table[X.size()][Z.size()]<<endl;
    }

    return 0;
}