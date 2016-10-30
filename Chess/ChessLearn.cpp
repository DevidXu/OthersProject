/*
����ʵ��Chesslearn�࣬������ֵĿ�ʼ��ѧϰ����
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
	/*ɾ��beginջ����ָ�� (����begin��������ʱ�Զ�ɾ������ֹ�ڴ����)*/
	while (p_chess->front != NULL)
	{
		ChessPointer* fordelete;
		fordelete = p_chess;
		p_chess = p_chess->front;
		delete fordelete;
	}
}

/*�ڸտ�ʼѵ��ʱִ�У�����һЩ��ʼ����*/
void ChessLearn::Init()
{
	begin->next = NULL;
	begin->front = NULL;
	p_chess->front = NULL;
	for (int i = 0; i < 7; i++) w[i] = 0;
}

/*��ǰ���ݽ���������������ϡ�ɾ������ָ�벢��ʼ��һ��ѵ��*/
void ChessLearn::Restart()
{
	//��ǰ����һֱ����ʼָ�룬���Ѻ���ָ��ɾ��
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

/*ǰ�᣺ʤ��δ�֡�����next������Ѱ����һ�����Ž�*/
void ChessLearn::NextStep(Result turn)
{
	/*������һ��ָ������̵�ַ,�������ӳ���*/
	ChessPointer* next=new ChessPointer();
	p_chess->next = next;
	next->front = p_chess;
	next->next = NULL;

	/*���ݵ�ǰָ�룬������һ���Ż������̵��߷������һ������Ϊ��һ������*/
	p_chess->chess.NextChess(&p_chess->chess, &next->chess, w, turn);

	p_chess = next;
}

/*��ǰp_chess�Ѿ��ߵ�β�����Ӵ˴���ʼ���ݲ�����*/
void ChessLearn::Backdate()
{
	double V_train=0;
	Result result;                                       //V_trainΪ��ǰ���̷�����resultΪ��ǰ���
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

	//��p_chessָ���ٴ��ƻص���β״̬
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

