#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;


int main(){
    cin>>n;
    vector<int> s;
    vector<int> m;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
        s.push_back(a[i]);
        m.push_back(a[i]);
    }

    sort(s.begin(),s.end());
    sort(m.begin(),m.end());
    int max=0; int min=0xfffffff;
    for(int i=0;i<n-1;i++){
        s.push_back(s[0]*s[1]+1);
        s.erase(s.begin(),s.begin()+1);
        sort(s.begin(),s.end());

        m.push_back(m[n-2]*m[n-1]+1);
        m.erase(m.begin()+n-2,m.begin()+n-1);
        sort(m.begin(),m.end());
    }
    max=s[0];   min=m[0];
    cout<<max-min<<endl;
    return 0;
}
