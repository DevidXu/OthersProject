/*
用于实现Chesslearn类，关于棋局的开始与学习过程
*/

#include "stdafx.h"
#include "ThreeChess.h"
#include "ChessLearn.h"
#include "iostream"


ChessLearn::ChessLearn()
{
	begin = new ChessPointer();
	p_chess = begin;
}

ChessLearn::~ChessLearn()
{
	/*删除begin栈所有指针 (除了begin，在析构时自动删除，防止内存出错)*/
	while (p_chess->front != NULL)
	{
		ChessPointer* fordelete;
		fordelete = p_chess;
		p_chess = p_chess->front;
		delete fordelete;
	}
}

/*在刚开始训练时执行，定义一些初始变量*/
void ChessLearn::Init()
{
	begin->next = NULL;
	begin->front = NULL;
	p_chess->front = NULL;
	for (int i = 0; i < 7; i++) w[i] = 0;
}

/*当前回溯结束，数据利用完毕。删除后续指针并开始新一轮训练*/
void ChessLearn::Restart()
{
	//往前回溯一直到开始指针，并把后续指针删除
	while (p_chess->front != NULL)
	{
		ChessPointer* fordelete;
		fordelete = p_chess;
		p_chess = p_chess->front;
		delete fordelete;
	}

	begin->next = NULL;
	begin->front = NULL;
}

/*前提：胜负未分。创建next变量，寻找下一步最优解*/
void ChessLearn::NextStep(Result turn)
{
	/*创建下一步指向的棋盘地址,增加链接长度*/
	ChessPointer* next=new ChessPointer();
	p_chess->next = next;
	next->front = p_chess;
	next->next = NULL;

	/*传递当前指针，返回下一步优化后棋盘的走法，最后一个参数为哪一方走子*/
	p_chess->chess.NextChess(&p_chess->chess, &next->chess, w, turn);

	p_chess = next;
}

/*当前p_chess已经走到尾部，从此处开始回溯并更新*/
void ChessLearn::Backdate()
{
	double V_train=0;
	Result result;                                       //V_train为当前棋盘分数，result为当前结果
	while (p_chess->front != NULL)
	{
		result = p_chess->chess.CheckAndUpdate();
		switch (result)
		{
		case WHITE: V_train = 100; break;
		case BLACK: V_train = -100; break;
		case DRAWN: V_train = 0; break;
		case NO: V_train = p_chess->next->chess.GetTrain(w); break;
		default: break;
		}

		p_chess->chess.UpdateWeight(&p_chess->chess, V_train, w);

		p_chess = p_chess->front;
	}

	//将p_chess指针再次推回到队尾状态
	while (p_chess->next != NULL) p_chess = p_chess->next;
}

bool ChessLearn::CheckEnd()
{
	if (p_chess->chess.CheckAndUpdate() != NO) return true;
	return false;
}

void ChessLearn::PrintW()
{
	for (int i = 0; i < 7; i++)
		std::cout << "w[ " << i << " ]= " << w[i] << std::endl;
}

double ChessLearn::GetW(int i)
{
	return w[i];
}

void ChessLearn::GiveState(int* board)
{
	for (int i = 0; i < 5; i++)
	for (int j = 0; j < 5; j++)
		p_chess->chess.board[i][j] = board[i*5+j];
}

void ChessLearn::GetState(int* board)
{
	for (int i = 0; i < 5; i++)
	for (int j = 0; j < 5; j++)
		board[i * 5 + j] = p_chess->chess.board[i][j];
}

Result ChessLearn::GetWinner()
{
	return p_chess->chess.CheckAndUpdate();
}

