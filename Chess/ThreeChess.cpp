/*
用于实现三子棋类，鉴定三子棋的胜利规则
*/

#include "stdafx.h"
#include "ThreeChess.h"
#include "stdlib.h"
#include "time.h"

double tau = 0.00001;                                      //指定变化速率

ThreeChess::ThreeChess()
{
	PM_num = 7;
	for (int i = 0; i < PM_num; i++) x[i] = 0;
	x[0] = 1;

	for (int i = 0; i < 5;i++)
	for (int j = 0; j < 5; j++)
		board[i][j] = 0;                                 //将棋盘初状态设为空棋

	result = NO;                                         //双方都未获胜
}

/*
对棋盘进行核查与更新数据 处理
查看是否有一方胜利
更新x[i]的信息
返回：无，白赢，黑赢，和棋
白棋胜利为100.黑棋胜利为-100
*/
Result ThreeChess::CheckAndUpdate()
{	
	Result win;                       //win是否赢；left，right左右是否有棋子
	int num, sequence;              //num对当前棋子的总二目数，sequence单排上的二目数
	win = NO;

	/*检查赢与二目数，更新x[1]与x[2]*/
	for (int i = 1; i < 4; i++)
	for (int j = 1; j < 4; j++)
	{
		num = 0; sequence = 0;                               //初始化数据

		if (board[i][j] == 0) continue;                      //若当前点为0，则无判断意义

		/*查看所有排的序列，统计二目数，并判断是否有一方赢棋*/
		sequence = (board[i][j] == board[i - 1][j]) + (board[i][j] == board[i + 1][j]);
		if (sequence == 2) win = (Result)board[i][j];
		num += sequence;

		sequence = (board[i][j] == board[i - 1][j - 1]) + (board[i][j] == board[i + 1][j + 1]);
		if (sequence == 2) win = (Result)board[i][j];
		num += sequence;

		sequence = (board[i][j] == board[i][j - 1]) + (board[i][j] == board[i][j + 1]);
		if (sequence == 2) win = (Result)board[i][j];
		num += sequence;

		sequence = (board[i][j] == board[i - 1][j + 1]) + (board[i][j] == board[i + 1][j - 1]);
		if (sequence == 2) win = (Result)board[i][j];
		num += sequence;

		if (board[i][j] == 1) x[1] += num;
		if (board[i][j] == 2) x[2] += num;
	}
	x[1] /= 2; x[2] /= 2;

	/*更新x[3]与x[4]*/
	if (board[2][1] == 1) x[3] += 1; if (board[2][1] == 2) x[4] += 1;
	if (board[1][2] == 1) x[3] += 1; if (board[1][2] == 2) x[4] += 1;
	if (board[2][2] == 1) x[3] += 1; if (board[2][2] == 2) x[4] += 1;
	if (board[3][2] == 1) x[3] += 1; if (board[3][2] == 2) x[4] += 1;
	if (board[2][3] == 1) x[3] += 1; if (board[2][3] == 2) x[4] += 1;

	/*更新x[5]与x[6]*/
	if (win == WHITE) x[5] = 100;
	if (win == BLACK) x[6] = 100;

	/*处理核查结果*/
	if (win == NO)
	{
		/*判断是否填满，若填满为和棋*/
		bool fill = true;
		for (int i = 1; i < 4; i++)
		for (int j = 1; j < 4; j++)
		if (board[i][j] == 0) fill = false;

		if (fill == true) return DRAWN; else return NO;
	}
	else
		return win;
}

/*
当前情况：结局未定，尚有空位
计算下一步如何行动：列举所有情况，计算相应的x[i]；
穷举知道下一步所有情况，并利用当前权值选择下一棋盘，传递回去
chessplayer:白为1，黑为2
ChessPointer: p_chess当前位置指针   next下一盘位置指针
*/
void ThreeChess::NextChess(ThreeChess* p_chess, ThreeChess* next, double* w, int chessplayer)
{
	int m_i[10], m_j[10], num;                    //存储走子位置,num为下一步候选数
	num = 0;
	for (int i = 0; i < 10; i++)
	{
		m_i[i] = 0; m_j[i] = 0;
	}

	ThreeChess test;                   //创建测试棋盘
	double maxpoint, C_point;                     //存储最大分值情况
	C_point = 0; 
	if (chessplayer == WHITE) maxpoint = -1000000;
	if (chessplayer == BLACK) maxpoint = 1000000;
	for (int i = 1; i < 4; i++)
	for (int j = 1; j < 4; j++)
	/*遍历棋盘，如果有空格，则置子于此*/
	if (p_chess->board[i][j] == 0)
	{
		for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
			test.board[x][y] = p_chess->board[x][y];
		test.board[i][j] = chessplayer;

		/*计算当前情况、当前评估系统下的得分，记录应子位置(m_i,m_j)*/
		test.CheckAndUpdate();
		C_point = 0;
		if (chessplayer == WHITE)
		{
			for (int k = 0; k < PM_num; k++)
				C_point += test.x[k] * w[k];
			if (C_point >= maxpoint)
			{
				m_i[num] = i; m_j[num] = j;
				num += 1;
				maxpoint = C_point;
			}
		}
		else
		{
			for (int k = 0; k < PM_num; k++)
				C_point += test.x[k] * w[k];
			if (C_point <= maxpoint)
			{
				m_i[num] = i; m_j[num] = j;
				num += 1;
				maxpoint = C_point;
			}
		}
	}

	/*返回应该的下一步结果*/
	for (int x = 0; x < 5; x++)
	for (int y = 0; y < 5; y++)
		next->board[x][y] = p_chess->board[x][y];

	/*从候选出的所有有效结果中随机选取，增强训练的广泛性*/
	srand((unsigned)time(NULL));
	int m_num = rand() % num;
	next->board[m_i[m_num]][m_j[m_num]] = (int)chessplayer;
}

/*
函数：传入w[i]，对x[i]计算该情况对应的分数
从而将其评价传递给其前端
*/
double ThreeChess::GetTrain(double* w)
{
	double point = 0;
	for (int i = 0; i < PM_num; i++)
		point += x[i] * w[i];
	return point;
}

/*传入当前棋盘得分，更新权值*/
void ThreeChess::UpdateWeight(ThreeChess* chess, double V_train, double* w)
{
	double current_train = chess->GetTrain(w);                 //得到当前棋盘分数
	for (int i = 0; i < PM_num; i++)
		w[i] += tau*(V_train - current_train)*x[i];
}