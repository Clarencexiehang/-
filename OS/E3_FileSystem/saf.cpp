#include<iostream>
#include <algorithm>
#include "vector"
#include "cstdlib"
#include "time.h"
using namespace std;


int startPosition;          //磁头初始位置
vector<int>getOrderList;    //磁道访问序列

vector<int>::iterator it;


//start若在 p 中，返回true
bool In(int start,vector<int> p){
    vector<int>::iterator move;
    for (move = p.begin(); move != p.end(); move++) {
        if (start == *move){
            return true;
        }
    }

    return false;
}


float FindPath () {
    vector<int> mov;
    mov = getOrderList;

    float ttp = 0;

    vector<int>::iterator tptr;

    sort(mov.begin(),mov.end());
    int start = startPosition;
    int end = startPosition;

    tptr = mov.begin();

    int left = *mov.begin();
    int right = *--mov.end();

    while(!In(start,getOrderList)){
        if (start < left){
            start++;
        }
        else{
            start--;
        }
    }

    ttp=ttp+abs(start-end);
    end = start;                   //磁头移到第一个请求访问的磁道
    while(*tptr != start){       //将迭代器移动至第一个请求访问的磁道
        tptr++;
    }

    mov.erase(tptr);
    cout<<"磁头移动顺序 ："<<endl;

    while(start > left){
        tptr--;
        start = *tptr;
        cout<<start<<",";
        ttp=ttp+abs(end-start);
        end = start;
        mov.erase(tptr);
    }

    while(!mov.empty()){
        start = *tptr;
        cout<<start<<",";
        ttp=ttp+abs(end-start);
        end = start;
        mov.erase(tptr);
    }

    return ttp;
}

float SSFT() {
    int start = startPosition;
    int end = startPosition;

    vector<int>strp;
    float acc = 0;

    strp =getOrderList;
    vector<int>::iterator move;

    sort(strp.begin(),strp.end());
    cout<<endl;

    for (move = strp.begin(); move != strp.end(); ++move){
        if (start >= *move && start <= *(move+1)){
            if (abs(*move - start) > abs(*(move + 1)-start)){
                move++;
            }
            break;
        }
        if (start < *move){
            break;
        }
        if (move > (strp.end()-1)){
            move = strp.end()-1;
            break;
        }
    }
    cout<<"SSFT顺序为："<<endl;
    while(!strp.empty()){
        start = *move;
        end = start;

        cout<<start<<",";
        acc=acc+abs(end-start);

        if (move == strp.end()-1){       //如果最外的磁道访问过后，则逐次往里访问
            move--;
            strp.erase(strp.end()-1);
            continue;
        }
        strp.erase(move);
        if (*(move-1)){
            if (abs(*(move-1)-start) < abs(*move-start)){
                move--;
            }
        }
    }
    return acc;
}

int main (){
    srand((unsigned int) time(NULL));
    startPosition = rand()%200;

    for (int i=0;i<10;i++){
        //随机创建十条进程请求访问磁道
        //且磁道数为在200以内的随机整数
        getOrderList.push_back(rand()%200);
    }
    cout<<"磁道请求顺序："<<endl;
    for (it = getOrderList.begin(); it != getOrderList.end(); ++it){
        cout<<*it<<",";
    }

    vector<int>tpro = getOrderList;
    sort(tpro.begin(),tpro.end());
    cout<<endl;

    for (it = tpro.begin(); it != tpro.end(); ++it){
        cout<<*it<<",";
    }
    cout<<endl;
    cout<<"磁头起始位置--------------- "<<startPosition<<endl;

    float l1 = FindPath()/10;

    cout<<endl;
    float lsl = SSFT()/10;
    cout<<endl;

    cout<<"电梯法平均寻道长度："<<l1<<endl;
    cout<<"最短寻道时间法平均寻道长度："<<lsl<<endl;

    return 0;
}
