#include<iostream>
#include<algorithm>
using namespace std;

struct Rank{
    int WaterTime;
    int Pos;
};

class SortOfPeople{
    int n;
public:
    SortOfPeople(int n){
        this->n=n;
    }

    static bool cmp(Rank a,Rank b){
        return a.WaterTime<b.WaterTime;
    }

    void sortOfRank(Rank *time){
        sort(time,time+n,cmp);
    }

    float AverageWaitingTime(Rank *time){
        int t=0; float result=0;
        for(int i=0;i<n-1;i++){
            t+=time[i].WaterTime;
            result+=t;
        }
        return result;
    }

    void Output(Rank *time){
//        for(int i=0;i<n;i++){
//            cout<<time[i].Pos<<" ";
//        }
        int t= AverageWaitingTime(time);
//        cout<<endl;
        cout<<t<<endl;
    }
};



int main(){
    int n;  cin>>n;
    Rank time[n];
    for(int i=0;i<n;i++){
        cin>>time[i].WaterTime;
        time[i].Pos=i+1;
    }

    SortOfPeople a(n);
    a.sortOfRank(time);
    a.Output(time);

    return 0;
}

