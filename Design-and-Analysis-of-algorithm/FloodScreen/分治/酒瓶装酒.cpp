#include<iostream>
#include "algorithm"
#include "vector"
using namespace std;

int main(){
    int m,n;
    cin>>m>>n;
    while(m!=0&&n!=0){
        float Max=max(m,n);
        float Min=min(m,n);
        bool flag= false;
        for(int i=1;i<10;i++){
            if (Min*i>Max){
                    for(int j=1;j<10;j++)
                        if((Min*i-Max)*j==Max/2){
                            cout<<"Y"<<endl;
                            flag= true;
                            break;
                }
            }
        }
        if(flag== false)    cout<<"N"<<endl;
        cin>>m>>n;
    }
    return 0;
}