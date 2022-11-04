//
// Created by Clarence on 2022/4/6.
//
#include<iostream>
#include "A.h"
using namespace std;
//    A::A() noexcept{
//        cout<<"构建成功了" ;
//    }
    int** A::init(){
        int **a;
        a=new int*[3];
        for(int i=0;i<3;i++)
            a[i]=new int[3];
        return a;
    }
    void A::f(int **a){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>a[i][j];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cout<<a[i][j]<<" ";
    }
