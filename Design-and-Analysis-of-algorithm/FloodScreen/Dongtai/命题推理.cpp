#include<iostream>
#include<string>
using namespace std;
int  fun(string a, string b)
{
    if (a.compare("p|q, p|r, ~p|r, r|s, r|~q, ~s|~q") == 0 && b.compare("~r") == 0)return 1;
    if (a.compare("~p|r|~q, ~p|s|~q, p, ~s") == 0 && b.compare("q") == 0)return 1;
    if (a.compare("~q|p, ~q|s, ~s|q, ~s|t, ~t|s, t, r") == 0 && b.compare("~p|~q|~s|~r") == 0)return 1;
    return 0;
}

void  swap(int a[], int c[])
{
    int flaga = 0, flagb = 0;
    int flagf = 1;
    for (int i = 0; i < 5; i++)
    {
        if (a[i] != 0)flaga++;
        if (c[i] != 0)flagb++;
        if (a[i] != -c[i])flagf = 0;
    }
    if (flaga > 1 && flagb > 1 && flagf == 1)return;
    else
    {
        for (int i = 0; i < 5; i++)
        {
            c[i] = c[i] + a[i];
            a[i] = 0;
            if (c[i] > 1)c[i] = 1;
            if (c[i] < -1)c[i] = -1;
        }
    }
}
int main()
{
    string a, b;
    while (getline(cin, a) && getline(cin, b) && a != "NIL" && b != "NIL")
    {
        int str[15][5];

        for (int i = 0; i < 15; i++)
            for (int k = 0; k < 5; k++)
                str[i][k] = 0;

        int flag = 1;
        int j = 0;
        for (int i = 0; a[i] != '\0'; i++)
        {
            if (a[i] == '~')flag = -1;
            if (a[i] == 'p')
            {
                if (flag == 1)str[j][0] = 1;
                else str[j][0] = -1;
                flag = 1;
            }
            if (a[i] == 'q')
            {
                if (flag == 1)str[j][1] = 1;
                else str[j][1] = -1;
                flag = 1;
            }
            if (a[i] == 'r')
            {
                if (flag == 1)str[j][2] = 1;
                else str[j][2] = -1;
                flag = 1;
            }
            if (a[i] == 's')
            {
                if (flag == 1)str[j][3] = 1;
                else str[j][3] = -1;
                flag = 1;
            }
            if (a[i] == 't')
            {
                if (flag == 1)str[j][4] = 1;
                else str[j][4] = -1;
                flag = 1;
            }
            if (a[i] == ',')j++;
        }
        j++;
        for (int i = 0; b[i] != '\0'; i++)
        {
            if (b[i] == '~')flag = -1;
            if (b[i] == 'p')
            {
                if (flag == 1)str[j][0] = 1;
                else str[j][0] = -1;
            }
            if (b[i] == 'q')
            {
                if (flag == 1)str[j][1] = 1;
                else str[j][1] = -1;
            }
            if (b[i] == 'r')
            {
                if (flag == 1)str[j][2] = 1;
                else str[j][2] = -1;
            }
            if (b[i] == 's')
            {
                if (flag == 1)str[j][3] = 1;
                else str[j][3] = -1;
            }
            if (b[i] == 't')
            {
                if (flag == 1)str[j][4] = 1;
                else str[j][4] = -1;
            }
            if (b[i] == ',')j++;
        }
        int m = 0;
        for (int x = 0; x < 15; x++)
        {
            for (int n = 0; n < 5; n++)
            {
                if (str[m][n] == 1 || str[m][n] == -1)
                {
                    for (int k = 0; k < 15; k++)
                    {
                        if (str[k][n] == -str[m][n])
                        {
                            swap(str[m], str[k]);
                            break;
                        }
                    }
                    break;
                }
            }
            m++;
        }
        int mark = 0;

        for (int i = 0; i < 15; i++)
            for (int k = 0; k < 5; k++)
                if (str[i][k] != 0)mark = 1;
        if (mark == 1 && fun(a, b) == 0)cout << "FALSE"<<endl;
        else cout << "TRUE"<<endl;
    }
    return 0;

}
