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
{   int name;      /*���̱�ʶ��*/
    int prio;           /*����������*/
    int round;          /*����ʱ��Ƭ��תʱ��Ƭ*/
    int cpuTime;        /*����ռ�� CPU ʱ��*/
    int needTime;       /*���̵���ɻ���Ҫ��ʱ��*/
    char state[10];         /*���̵�״̬*/
}PCB;

vector<PCB*> readyQueue;
vector<PCB*> runningQueue;
vector<PCB*> finishQueue;

//�������ȼ��Ӵ�С����
bool compare(PCB* a,PCB* b){
    return a->prio > b->prio;
}

void insertReadyQueue(PCB* process,int name){
    process = (PCB *) malloc(sizeof(PCB));
    if(process == NULL){
        cout<<"�ڴ�����!"<<endl;
        exit(0);
    }

    process->name = name;
    process->needTime = rand()%50;
    process->prio = maxPrio - process->needTime;
    process->round = 5;
    process->cpuTime = 0;
    strcpy(process->state, "ready");    //Ĭ�ϴ������½����Ǿ���״̬

    //�������ȼ����򣬷����������
    readyQueue.push_back(process);
    sort(readyQueue.begin(),readyQueue.end(), compare);
}


void Random_Create_PCB(int PCB_NUM){
    if(PCB_NUM <= 0){
        cout<<"��ǰ�޽��̷���"<<endl;
        exit(0);
    }

    for(int i=0;i<PCB_NUM;i++){
        PCB* p = NULL;
        insertReadyQueue(p,i);
    }
}


int runProcess(PCB* process){
    strcpy(process->state, "running");
    //������̵�����ִ��ʱ��<ʱ��Ƭ�������ȼ�����0
    if(process->needTime<process->round){
        process->cpuTime += process->needTime;
        process->needTime=0;
        return 0;
    } else{
        process->needTime -= process->round;
        process->cpuTime += process->round;
        int tempPrio = process->prio;
        process->prio = maxPrio;     //����ʱ�Ľ������ȼ����
        return tempPrio;
    }
}

void round(PCB* process){
    runningQueue.erase(runningQueue.begin());
    int tempPrio = runProcess(process);

    //��ʱ��Ƭ��ת�Ľ������·������������
    for(int i=0;i< readyQueue.size();i++){
        readyQueue[i]->prio+=2;     //�������������н������ȼ����2
    }
    if(tempPrio == 0){
        strcpy(process->state, "finished");
        finishQueue.push_back(process);
        cout<<"���� "<<process->name<<" ִ����ϣ�"<<endl;
    }else{
        process->prio = tempPrio-2;
        strcpy(process->state, "ready");
        readyQueue.push_back(process);
        sort(readyQueue.begin(),readyQueue.end(), compare);
    }
}


void showQueue(vector<PCB *> *q){
    for(int i=0;i<q->size();i++){
        cout<<"���̱�ʶ��:"<<(*q)[i]->name<<"    ";
        cout<<"����������:"<<(*q)[i]->prio<<"    ";
        cout<<"ռ��CPUʱ��:"<<(*q)[i]->cpuTime<<"    ";
        cout<<"����ʱ��:"<<(*q)[i]->needTime<<"    ";
        cout<<"����״̬:"<<(*q)[i]->state<<"    ";
        cout<<"\n\n";
    }
}

int main(){
    srand(time(NULL));

    int pcb_num;
    cout<<"���������������: ";     cin>>pcb_num;
    Random_Create_PCB(pcb_num);
    while(true){
        if(readyQueue.empty()){
            cout<<"���н���ִ�����"<<endl;
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

