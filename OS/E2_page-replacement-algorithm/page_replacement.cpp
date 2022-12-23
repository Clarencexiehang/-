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
    int pageID;     //ҳ���ID
    int pageIndex;  //ҳ���ڶ����е�λ��
}page;


vector<page> pagesQueue;      //ҳ�����
vector<page> pagesFrame;      //ҳ��

void createPages(int L){
    for(int i=0;i<L;i++){
        page newPage;
        newPage.pageID = rand()%20;
        newPage.pageIndex=i+1;
        pagesQueue.push_back(newPage);
    }
}

void showPagesQueue(){
    cout<<"ҳ��ID:  ";
    for(int i=0;i<pagesQueue.size();i++)
        cout<<pagesQueue[i].pageID<<" ";
    cout<<"\n\n";
}

void showPagesFrame(){
    cout<<"ҳ����ҳ��ID: ";
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
    //�ȼ��ҳ�����Ƿ��Ѿ����ڸ�ҳ��
    for(vector<page >::iterator it=pagesFrame.begin();it!=pagesFrame.end();it++){
        if((*it).pageID == p.pageID){
            (*it).pageIndex = p.pageIndex;        //�����±�
            return;
        }
    }

    if(pagesFrame.size()<m){
        pagesFrame.push_back(p);
        lastIndex = p.pageIndex;
        //cout<<"last:  "<<lastIndex<<" ";
    }else{
        //�ҵ��������ҳ���λ�ã�����������̭�����δ����ò���ʹ�õ�ҳ��
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
        //�滻ҳ��
        lastIndex = p.pageIndex;
        cout<<"������ҳ���: "<<pagesFrame[farthestFramePos].pageID<<"   ";
        pagesFrame.erase(pagesFrame.begin()+farthestFramePos);
        pagesFrame.insert(pagesFrame.begin()+farthestFramePos,p);
        MissingPageNUM++;
    }
}

void FIFO(page p,int m){
    //�ȼ��ҳ�����Ƿ��Ѿ����ڸ�ҳ��
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
        cout<<"������ҳ���: "<<pagesFrame[changedFramePos].pageID<<"   ";
        pagesFrame.erase(pagesFrame.begin()+changedFramePos);
        pagesFrame.insert(pagesFrame.begin()+changedFramePos,p);
        MissingPageNUM++;
    }
}

void LRU(page p,int m){
    //�ȼ��ҳ�����Ƿ��Ѿ����ڸ�ҳ��
    for(vector<page >::iterator it=pagesFrame.begin();it!=pagesFrame.end();it++){
        if((*it).pageID == p.pageID){
            (*it).pageIndex = p.pageIndex;        //�����±�
            return;
        }
    }

    if(pagesFrame.size()<m){
        pagesFrame.push_back(p);
    }else{
        int minIndex = pagesFrame[0].pageIndex;     //�ҵ�ҳ����������δʹ�õ�ҳ���λ��minIndex
        int changedFramePos=0;
        for(int i=1;i<m;i++){
            if(minIndex > pagesFrame[i].pageIndex){
                minIndex = pagesFrame[i].pageIndex;
                changedFramePos = i;
            }
        }
        cout<<"������ҳ���: "<<pagesFrame[changedFramePos].pageID<<"   ";
        pagesFrame.erase(pagesFrame.begin()+changedFramePos);
        pagesFrame.insert(pagesFrame.begin()+changedFramePos,p);
        MissingPageNUM++;
    }
}


int main() {
    srand((int)time(0));

    int L,m;
    cout<<"����ҳ�����򳤶�:";  cin>>L;
    cout<<"����ҳ����:"; cin>>m;
    if(L<10||L>20){
        cout<<"ҳ�����򳤶�����������������룡";
        exit(0);
    }
    if(m<3||m>5){
        cout<<"ҳ��������������������룡";
        exit(0);
    }

    createPages(L);
    showPagesQueue();

    //ʹ�����ҳ���û���OPT���㷨
    cout<<"ʹ�����ҳ���û���OPT���㷨"<<endl;
    MissingPageNUM = 0;

    for(int i=0;i<L;i++){
        OPT(pagesQueue[i],m);
        showPagesFrame();
    }
    PageFaultRate = MissingPageNUM/L;
    cout<<"ȱҳ��Ϊ��"<< PageFaultRate<<"\n\n";


    //�Ƚ��ȳ���FIFO���㷨
    cout<<"�Ƚ��ȳ���FIFO���㷨"<<endl;
    MissingPageNUM = 0;
    pagesFrame.clear();
    for(int i=0;i<L;i++){
        FIFO(pagesQueue[i],m);
        showPagesFrame();
    }
    PageFaultRate = MissingPageNUM/L;
    cout<<"ȱҳ��Ϊ��"<< PageFaultRate<<"\n\n";


    //������δʹ�ã�LRU���㷨
    cout<<"������δʹ�ã�LRU���㷨"<<endl;
    MissingPageNUM = 0;
    pagesFrame.clear();
    for(int i=0;i<L;i++){
        LRU(pagesQueue[i],m);
        showPagesFrame();
    }
    PageFaultRate = MissingPageNUM/L;
    cout<<"ȱҳ��Ϊ��"<< PageFaultRate<<"\n\n";

    return 0;
}
