// Created by xie hang on 2022/11/26.
#include<iostream>
#include "cstdlib"
#include "vector"
#include "time.h"
using namespace std;

float MissingPageNUM = 0;
float PageFaultRate = 0;
int lastIndex = 0;

typedef struct page{
    int pageID;     //页面号ID
    int pageIndex;  //页面在队列中的位置
}page;


vector<page> pagesQueue;      //页面队列
vector<page> pagesFrame;      //页框

void createPages(int L){
    for(int i=0;i<L;i++){
        page newPage;
        newPage.pageID = rand()%20;
        newPage.pageIndex=i+1;
        pagesQueue.push_back(newPage);
    }
}

void showPagesQueue(){
    cout<<"页面ID:  ";
    for(int i=0;i<pagesQueue.size();i++)
        cout<<pagesQueue[i].pageID<<" ";
    cout<<"\n\n";
}

void showPagesFrame(){
    cout<<"页框中页面ID: ";
    for(int i=0;i<pagesFrame.size();i++)
        cout<<pagesFrame[i].pageID<<" ";
    cout<<"\n";
}

int OPT_FindNextPos(page p){
    int pos = lastIndex+1;
    while(pos<pagesQueue.size()){
        //cout<<"-----"<<pagesQueue[pos]->pageID;
        if(pagesQueue[pos].pageID == p.pageID){
            break;
        }
        pos++;
    }
    return pos;
}

void OPT(page p,int m){
    //先检查页框中是否已经存在该页表
    for(vector<page >::iterator it=pagesFrame.begin();it!=pagesFrame.end();it++){
        if((*it).pageID == p.pageID){
            (*it).pageIndex = p.pageIndex;        //更新下标
            return;
        }
    }

    if(pagesFrame.size()<m){
        pagesFrame.push_back(p);
        lastIndex = p.pageIndex;
        //cout<<"last:  "<<lastIndex<<" ";
    }else{
        //找到最近调入页面的位置，并且排序，淘汰最近的未来最久不再使用的页。
        int NearestPos[m];
        for(int i=0;i<m;i++){
            NearestPos[i]= OPT_FindNextPos(pagesFrame[i]);
        }
        int farthestPos = NearestPos[0];
        int farthestFramePos=0;
        for(int i=1;i<m;i++){
            if(NearestPos[i]>farthestPos){
                farthestPos = NearestPos[i];
                farthestFramePos = i;
            }
        }
        //替换页面
        lastIndex = p.pageIndex;
        cout<<"换出的页序号: "<<pagesFrame[farthestFramePos].pageID<<"   ";
        pagesFrame.erase(pagesFrame.begin()+farthestFramePos);
        pagesFrame.insert(pagesFrame.begin()+farthestFramePos,p);
        MissingPageNUM++;
    }
}

void FIFO(page p,int m){
    //先检查页框中是否已经存在该页表
    for(vector<page>::iterator it=pagesFrame.begin();it!=pagesFrame.end();it++){
        if((*it).pageID == p.pageID)
            return;
    }

    if(pagesFrame.size()<m){
        pagesFrame.push_back(p);
    }else{
        int minIndex = pagesFrame[0].pageIndex;
        int changedFramePos=0;
        for(int i=1;i<m;i++){
            if(minIndex > pagesFrame[i].pageIndex){
                minIndex = pagesFrame[i].pageIndex;
                changedFramePos = i;
            }
        }
        cout<<"换出的页序号: "<<pagesFrame[changedFramePos].pageID<<"   ";
        pagesFrame.erase(pagesFrame.begin()+changedFramePos);
        pagesFrame.insert(pagesFrame.begin()+changedFramePos,p);
        MissingPageNUM++;
    }
}

void LRU(page p,int m){
    //先检查页框中是否已经存在该页表
    for(vector<page >::iterator it=pagesFrame.begin();it!=pagesFrame.end();it++){
        if((*it).pageID == p.pageID){
            (*it).pageIndex = p.pageIndex;        //更新下标
            return;
        }
    }

    if(pagesFrame.size()<m){
        pagesFrame.push_back(p);
    }else{
        int minIndex = pagesFrame[0].pageIndex;     //找到页框中最近最久未使用的页面的位置minIndex
        int changedFramePos=0;
        for(int i=1;i<m;i++){
            if(minIndex > pagesFrame[i].pageIndex){
                minIndex = pagesFrame[i].pageIndex;
                changedFramePos = i;
            }
        }
        cout<<"换出的页序号: "<<pagesFrame[changedFramePos].pageID<<"   ";
        pagesFrame.erase(pagesFrame.begin()+changedFramePos);
        pagesFrame.insert(pagesFrame.begin()+changedFramePos,p);
        MissingPageNUM++;
    }
}


int main() {
    srand((int)time(0));

    int L,m;
    cout<<"输入页面走向长度:";  cin>>L;
    cout<<"输入页框数:"; cin>>m;
    if(L<10||L>20){
        cout<<"页面走向长度输入错误，请重新输入！";
        exit(0);
    }
    if(m<3||m>5){
        cout<<"页框数输入错误，请重新输入！";
        exit(0);
    }

    createPages(L);
    showPagesQueue();

    //使用最佳页面置换（OPT）算法
    cout<<"使用最佳页面置换（OPT）算法"<<endl;
    MissingPageNUM = 0;

    for(int i=0;i<L;i++){
        OPT(pagesQueue[i],m);
        showPagesFrame();
    }
    PageFaultRate = MissingPageNUM/L;
    cout<<"缺页率为："<< PageFaultRate<<"\n\n";


    //先进先出（FIFO）算法
    cout<<"先进先出（FIFO）算法"<<endl;
    MissingPageNUM = 0;
    pagesFrame.clear();
    for(int i=0;i<L;i++){
        FIFO(pagesQueue[i],m);
        showPagesFrame();
    }
    PageFaultRate = MissingPageNUM/L;
    cout<<"缺页率为："<< PageFaultRate<<"\n\n";


    //最近最久未使用（LRU）算法
    cout<<"最近最久未使用（LRU）算法"<<endl;
    MissingPageNUM = 0;
    pagesFrame.clear();
    for(int i=0;i<L;i++){
        LRU(pagesQueue[i],m);
        showPagesFrame();
    }
    PageFaultRate = MissingPageNUM/L;
    cout<<"缺页率为："<< PageFaultRate<<"\n\n";

    return 0;
}
