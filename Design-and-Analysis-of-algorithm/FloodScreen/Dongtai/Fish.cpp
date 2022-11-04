#include<iostream>
using namespace std;

int main(){
    int n; int h;
    cin>>n>>h;
    int Fi[n];  int di[n];  int ti[n-1];

    for(int i=0;i<n;i++){
        cin>>Fi[i];
    }
    for(int i=0;i<n;i++){
        cin>>di[i];
    }
    for(int i=0;i<n-1;i++){
        cin>>ti[i];
    }


    return 0;
}