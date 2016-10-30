/*
����ʵ���������࣬�����������ʤ������
*/

#include "stdafx.h"
#include "ThreeChess.h"
#include "stdlib.h"
#include "time.h"

double tau = 0.00001;                                      //ָ���仯����

ThreeChess::ThreeChess()
{
	PM_num = 7;
	for (int i = 0; i < PM_num; i++) x[i] = 0;
	x[0] = 1;

	for (int i = 0; i < 5;i++)
	for (int j = 0; j < 5; j++)
		board[i][j] = 0;                                 //�����̳�״̬��Ϊ����

	result = NO;                                         //˫����δ��ʤ
}

/*
�����̽��к˲���������� ����
�鿴�Ƿ���һ��ʤ��
����x[i]����Ϣ
���أ��ޣ���Ӯ����Ӯ������
����ʤ��Ϊ100.����ʤ��Ϊ-100
*/
Result ThreeChess::CheckAndUpdate()
{	
	Result win;                       //win�Ƿ�Ӯ��left��right�����Ƿ�������
	int num, sequence;              //num�Ե�ǰ���ӵ��ܶ�Ŀ����sequence�����ϵĶ�Ŀ��
	win = NO;

	/*���Ӯ���Ŀ��������x[1]��x[2]*/
	for (int i = 1; i < 4; i++)
	for (int j = 1; j < 4; j++)
	{
		num = 0; sequence = 0;                               //��ʼ������

		if (board[i][j] == 0) continue;                      //����ǰ��Ϊ0�������ж�����

		/*�鿴�����ŵ����У�ͳ�ƶ�Ŀ�������ж��Ƿ���һ��Ӯ��*/
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

	/*����x[3]��x[4]*/
	if (board[2][1] == 1) x[3] += 1; if (board[2][1] == 2) x[4] += 1;
	if (board[1][2] == 1) x[3] += 1; if (board[1][2] == 2) x[4] += 1;
	if (board[2][2] == 1) x[3] += 1; if (board[2][2] == 2) x[4] += 1;
	if (board[3][2] == 1) x[3] += 1; if (board[3][2] == 2) x[4] += 1;
	if (board[2][3] == 1) x[3] += 1; if (board[2][3] == 2) x[4] += 1;

	/*����x[5]��x[6]*/
	if (win == WHITE) x[5] = 100;
	if (win == BLACK) x[6] = 100;

	/*����˲���*/
	if (win == NO)
	{
		/*�ж��Ƿ�������������Ϊ����*/
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
��ǰ��������δ�������п�λ
������һ������ж����о����������������Ӧ��x[i]��
���֪����һ����������������õ�ǰȨֵѡ����һ���̣����ݻ�ȥ
chessplayer:��Ϊ1����Ϊ2
ChessPointer: p_chess��ǰλ��ָ��   next��һ��λ��ָ��
*/
void ThreeChess::NextChess(ThreeChess* p_chess, ThreeChess* next, double* w, int chessplayer)
{
	int m_i[10], m_j[10], num;                    //�洢����λ��,numΪ��һ����ѡ��
	num = 0;
	for (int i = 0; i < 10; i++)
	{
		m_i[i] = 0; m_j[i] = 0;
	}

	ThreeChess test;                   //������������
	double maxpoint, C_point;                     //�洢����ֵ���
	C_point = 0; 
	if (chessplayer == WHITE) maxpoint = -1000000;
	if (chessplayer == BLACK) maxpoint = 1000000;
	for (int i = 1; i < 4; i++)
	for (int j = 1; j < 4; j++)
	/*�������̣�����пո��������ڴ�*/
	if (p_chess->board[i][j] == 0)
	{
		for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
			test.board[x][y] = p_chess->board[x][y];
		test.board[i][j] = chessplayer;

		/*���㵱ǰ�������ǰ����ϵͳ�µĵ÷֣���¼Ӧ��λ��(m_i,m_j)*/
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

	/*����Ӧ�õ���һ�����*/
	for (int x = 0; x < 5; x++)
	for (int y = 0; y < 5; y++)
		next->board[x][y] = p_chess->board[x][y];

	/*�Ӻ�ѡ����������Ч��������ѡȡ����ǿѵ���Ĺ㷺��*/
	srand((unsigned)time(NULL));
	int m_num = rand() % num;
	next->board[m_i[m_num]][m_j[m_num]] = (int)chessplayer;
}

/*
����������w[i]����x[i]����������Ӧ�ķ���
�Ӷ��������۴��ݸ���ǰ��
*/
double ThreeChess::GetTrain(double* w)
{
	double point = 0;
	for (int i = 0; i < PM_num; i++)
		point += x[i] * w[i];
	return point;
}

/*���뵱ǰ���̵÷֣�����Ȩֵ*/
void ThreeChess::UpdateWeight(ThreeChess* chess, double V_train, double* w)
{
	double current_train = chess->GetTrain(w);                 //�õ���ǰ���̷���
	for (int i = 0; i < PM_num; i++)
		w[i] += tau*(V_train - current_train)*x[i];
}