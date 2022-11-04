#include<iostream>
#include "algorithm"
#include "vector"
using namespace std;

int Merge(vector<int>& prices, int l, int r)
{
    if(l >= r)
    {
        return 0;
    }
    int mid = (l+r)>>1;
    int x1 = Merge(prices,l,mid-1);
    int x2 = Merge(prices,mid+1,r);
    int l_min = prices[mid], r_max = prices[mid];
    for(int i = mid;i >= 0;i--)
        l_min = min(prices[i], l_min);
    for(int i = mid;i <= r;i++)
        r_max = max(r_max, prices[i]);
    int x3 = r_max - l_min;
    return max(max(x1,x2), x3);
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    return Merge(prices,0,n-1);
}

int main(){
    int n;
    while(cin>>n){
        vector<int> price;
        for (int i = 0; i < n; i++) {int temp; cin >>temp; price.push_back(temp); }
        cout<<Merge(price,0,n-1)<<endl;
    }
    return 0;
}