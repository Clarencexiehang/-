#include "competitionSchedule.h"
#include<iostream>
#include<cmath>
using namespace std;

string chessBoard[9][9];

void initBoard(){
    for(int i=1;i<=8;i++)
        for(int y=1;y<=8;y++)
        for(char j='a';j<='h';j++){
            chessBoard[i][y][0]=j;
            chessBoard[i][y][1]=i+48;
        }

}

int main(){
    initBoard();
    for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
            cout<<chessBoard[i][j]<<" ";
    return 0;
}