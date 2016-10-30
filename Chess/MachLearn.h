/*
对“训练”按钮的响应：
得到训练值，输出胜率

训练完成后返回对应的权值，开始下棋
决定先手后手
*/
#include "ThreeChess.h"
#include "ChessLearn.h"

double* TrainW(int, double*, int);

double* NextChess(double*, int);

Result CheckTheResult(int*);

void NextStep(double*, int*, int);