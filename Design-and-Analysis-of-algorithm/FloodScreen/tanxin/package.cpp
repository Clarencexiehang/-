#include <iostream>
#include <algorithm>

using namespace std;

struct thing{
    float value;
    int wi;
    int ci;
};

bool comp(thing a,thing b){
    return a.value>b.value;
}

int main() {
    float v,n;
    cin>>v>>n;
    struct thing t[(int)n];
    for(int i=0;i<n;i++){
        cin>>t[i].wi>>t[i].ci;
        t[i].value=(float )t[i].wi/(float )t[i].ci;
        //cout<<t[i].value<<endl;
    }


    sort(t,t+(int)n,comp);
    float ans=0;  int PackV=0;
    for(int j=0;j<n;j++){
        if(v>=PackV+t[j].ci){
            PackV+=t[j].ci;
            ans+=t[j].wi;   //cout<<t[j].ci<<" ";
        }
    }

    cout<<ans<<endl;
    return 0;
}