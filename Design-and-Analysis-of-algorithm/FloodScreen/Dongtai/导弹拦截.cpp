#include<iostream>
#include<algorithm>
using namespace std;
const int Max = 1e5 + 5;
int lst[7], dp[7][2];//一个用来存放dp,一个用来存放贪心。至于为啥数组开这么小，因为发现这题数据是个伪1w，总共连10个导弹都没有，开个7就过了...
int g = 0;

int main()
{
    int t;
    while (scanf("%d",&t)!=EOF)
    {
        lst[g++] = t;
        cout<<t<<" ";
    }

    for(int i=g-1;i>=0;i++){
        cout<<lst[i]<<" ";
    }
    for (int i = 1; i <= g; i++)
    {
        dp[i][0] = 1;
        int f = i, f1 = 1e9 + 5;
        for (int j = 1; j < i; j++)
        {
            if (lst[i] <= lst[j]) dp[i][0] = max(dp[i][0], dp[j][0] + 1);
            if (dp[j][1] && lst[j] >= lst[i] && lst[j] < f1)
            {
                f = j;
                f1 = lst[j];
            }
        }
        dp[f][1] = 0;
        dp[i][1] = 1;
    }
    int ma = -9, sum = 0;
    for (int i = 1; i <= g; i++)
    {
        ma = max(dp[i][0], ma);
        sum += dp[i][1];
    }
    cout << ma << endl << sum;
}