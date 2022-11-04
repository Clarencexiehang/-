#include <iostream>
#include <algorithm>
using namespace std;

float Cost(int n){
    float price=0;
    if(n<=4)    return 10;
    else if(n>4&&n<=7)  return 10+(n-4)*2;
    else{
        while (n>8)
        {
            price += 18;
            n = n - 8;
        }
        if (n<=4)
        {
            price += n * 2.4;

        }
        else
        {
            price += (10 + (n - 4) * 2);
        }
        return price;
    }
}

int main(){
    int n; cin>>n;
    while(n!=0){
        cout<<Cost(n)<<endl;

        cin>>n;
    }
    return 0;
}
