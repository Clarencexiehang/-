// Created by Clarence on 2022/10/29.
#include<iostream>
#include "cstdlib"
#include "vector"
#include "algorithm"
#include "cstring"
#include "time.h"
using namespace std;
#define maxPrio 50



typedef struct node
{   int name;      /*进程标识符*/
    int prio;           /*进程优先数*/
    int round;          /*进程时间片轮转时间片*/
    int cpuTime;        /*进程占用 CPU 时间*/
    int needTime;       /*进程到完成还需要的时间*/
    char state[10];         /*进程的状态*/
}PCB;

vector<PCB*> readyQueue;
vector<PCB*> runningQueue;
vector<PCB*> finishQueue;

//按照优先级从大到小排序
bool compare(PCB* a,PCB* b){
    return a->prio > b->prio;
}

void insertReadyQueue(PCB* process,int name){
    process = (PCB *) malloc(sizeof(PCB));
    if(process == NULL){
        cout<<"内存已满!"<<endl;
        exit(0);
    }

    process->name = name;
    process->needTime = rand()%50;
    process->prio = maxPrio - process->needTime;
    process->round = 5;
    process->cpuTime = 0;
    strcpy(process->state, "ready");    //默认创建的新进程是就绪状态

    //根据优先级排序，放入就绪队列
    readyQueue.push_back(process);
    sort(readyQueue.begin(),readyQueue.end(), compare);
}


void Random_Create_PCB(int PCB_NUM){
    if(PCB_NUM <= 0){
        cout<<"当前无进程分配"<<endl;
        exit(0);
    }

    for(int i=0;i<PCB_NUM;i++){
        PCB* p = NULL;
        insertReadyQueue(p,i);
    }
}


int runProcess(PCB* process){
    strcpy(process->state, "running");
    //如果进程的所需执行时间<时间片，则优先级返回0
    if(process->needTime<process->round){
        process->cpuTime += process->needTime;
        process->needTime=0;
        return 0;
    } else{
        process->needTime -= process->round;
        process->cpuTime += process->round;
        int tempPrio = process->prio;
        process->prio = maxPrio;     //运行时的进程优先级最大
        return tempPrio;
    }
}

void round(PCB* process){
    runningQueue.erase(runningQueue.begin());
    int tempPrio = runProcess(process);

    //将时间片轮转的进程重新放入就绪队列中
    for(int i=0;i< readyQueue.size();i++){
        readyQueue[i]->prio+=2;     //就绪队列中所有进程优先级提高2
    }
    if(tempPrio == 0){
        strcpy(process->state, "finished");
        finishQueue.push_back(process);
        cout<<"进程 "<<process->name<<" 执行完毕！"<<endl;
    }else{
        process->prio = tempPrio-2;
        strcpy(process->state, "ready");
        readyQueue.push_back(process);
        sort(readyQueue.begin(),readyQueue.end(), compare);
    }
}


void showQueue(vector<PCB *> *q){
    for(int i=0;i<q->size();i++){
        cout<<"进程标识符:"<<(*q)[i]->name<<"    ";
        cout<<"进程优先数:"<<(*q)[i]->prio<<"    ";
        cout<<"占用CPU时间:"<<(*q)[i]->cpuTime<<"    ";
        cout<<"还需时间:"<<(*q)[i]->needTime<<"    ";
        cout<<"进程状态:"<<(*q)[i]->state<<"    ";
        cout<<"\n\n";
    }
}

int main(){
    srand(time(NULL));

    int pcb_num;
    cout<<"请输入产生进程数: ";     cin>>pcb_num;
    Random_Create_PCB(pcb_num);
    while(true){
        if(readyQueue.empty()){
            cout<<"所有进程执行完毕"<<endl;
            break;
        }
        cout<<"**************  ready  *************"<<"\n\n";
        showQueue(&readyQueue);
        PCB * rp = readyQueue[0];
        readyQueue.erase(readyQueue.begin());
        runningQueue.push_back(rp);
        round(rp);
        system("pause");
    }
    cout<<"**********  finish **********"<<"\n\n";
    showQueue(&finishQueue);
    return 0;
}

