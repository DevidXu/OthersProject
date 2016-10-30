// MachLearn.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "MachLearn.h"

double* TrainW(int num, double* w, int PR_num)
{
	int loop = 1;
	Result turn = WHITE;                              //loop��ѭ������   turn����һ������
	/*���������̣���ʼ������ָ��*/
	ChessLearn Newchess;
	Newchess.Init();

	int WhiteWin = 0, BlackWin = 0;

	for (int i = 0; i < PR_num; i++) w[i] = 0;

	/*ѭ��ѧϰ��������1000*/
	while (loop <num)
	{
		loop++;

		Newchess.Restart();

		turn = WHITE;
		while (Newchess.CheckEnd() == false)
		{
			Newchess.NextStep(turn);
			if (turn == WHITE) turn = BLACK; else turn = WHITE;
		}

		if (loop * 2 < num)
		{
			if (Newchess.GetWinner() == WHITE) WhiteWin += 1;
		}
		else
		{
			if (Newchess.GetWinner() == BLACK) WhiteWin += 1;
		}

		Newchess.Backdate();
	}

	for (int i = 0; i < PR_num; i++)
		w[i] = Newchess.GetW(i);

	w[PR_num] = (double)WhiteWin / num;
	return w;
}

Result CheckTheResult(int* board)
{
	ChessLearn Newchess;
	Newchess.Init();
	Newchess.GiveState(board);
	return Newchess.GetWinner();
}

void NextStep(double* w, int* board, int player)
{
	ChessLearn Newchess;
	Newchess.Init();
	Newchess.GiveState(board);
	int player2 = 3 - player;
	Newchess.NextStep((Result)player2);
	Newchess.GetState(board);
}