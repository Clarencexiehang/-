#include <stdlib.h>
#include <stdio.h>
typedef int ElementType;
struct SqList{
    ElementType *Data;
    int N; /* N为表中元素个数 */
    int MaxSize; /* 表的最大容量 */
};
struct SqList * CreateList(int M) {
    struct SqList * L;
    L = (SqList*)malloc(sizeof(struct SqList));
    L->Data = (int*)malloc(sizeof(ElementType) * M);
    L->N = 0; /* 初始时元素个数为0 */
    L->MaxSize = M;
    return L;
}

void Printf(struct SqList *L ){
    int i=0;
    for(i=0;i<L->N;i++){
        printf("%d\n",L->Data[i]);
    }
}

int main()
{   struct SqList *L;
    L=CreateList(100);
    int i=1;
    srand((unsigned)time(NULL));
    for(i=1;i<100;i++){
        L->Data[i]=(rand()%101+100);
    }
    Printf(L);
    return 0;
}