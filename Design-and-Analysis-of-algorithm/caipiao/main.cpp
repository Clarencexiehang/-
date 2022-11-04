#include<iostream>
#include<cstdlib>
using namespace std;

void init(int *track,bool *used,int n){
    for(int i=0;i<n;i++){
        if(i!=6)
            track[i]=-1;
        used[i]=false;
    }
}

void AddTrack(int *track,int elem){
    for(int i=0;i<6;i++)
        if(track[i]==-1){
            track[i]=elem;
            break;
        }
}

void DeleteTrack(int *track){
    for(int i=0;i<6;i++)
        if(track[i]==-1){
            track[i-1]=-1;
            break;
        }
}

void OutPut(int *track){
    for(int i=0;i<6;i++)
        cout<<track[i]<<" ";
    cout<<endl;
}

void BackTrack(int *l,int *&track,bool *used,int n,int step){
    if(step==6){
        OutPut(track);
        cout<<endl;
        return ;
    }

    for(int i=0;i<n-6;i++){
        for(int j=i+1;j<=n;j++){
            if(!used[i+j]){
                used[i+j]= true;
                AddTrack(track,l[i+step]);
                BackTrack(l,track,used,n,step+1);
                used[i+j]=false;
                DeleteTrack(track);
            }
        }

    }
}


int main(){
    int n;
    while(cin>>n){
        int *l=new int[n];
        for(int i=0;i<n;i++){
            cin>>l[i];
        }
        int *track=new int[6];
        bool used[n];
        init(track,used,n);
        BackTrack(l,track,used,n,1);
    }

    return 0;
}