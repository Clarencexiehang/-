#ifndef PCB_H
#define PCB_H

#include "vector"
using namespace std;


class PCB
{
public:
    int name;           /*进程标识符*/
    int prio;           /*进程优先数*/
    int round;          /*进程时间片轮转时间片*/
    int cpuTime;        /*进程占用 CPU 时间*/
    int needTime;       /*进程到完成还需要的时间*/
    char state[10];     /*进程的状态*/

public:
    PCB();


    void Random_Create_PCB();


};

#endif // PCB_H
