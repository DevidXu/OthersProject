/*
��ͷ�ļ�����Բ�ͬ����Ĺ�������趨������Ϊ�����壻��Ȼ������޸�Ϊ������
����������з�װ
*/
#ifndef _THREECHESS_H__
#define _THREECHESS_H__

enum Result{ NO, WHITE, BLACK, DRAWN };

class ThreeChess
{
private:
	int PM_num;
	double x[7];
	/*
	����
	���Ӷ�����������
	���Ӷ�����������
	���ļ����а���������
	���ļ����к���������
	����������������
	����������������
	*/
	Result result;

public:
	int board[5][5];

public:
	ThreeChess();
	~ThreeChess(){};

	Result CheckAndUpdate();                    //���ص�����������w[i]��ֵ
	void NextChess(ThreeChess*, ThreeChess*, double*, int);
	double GetTrain(double*);
	void UpdateWeight(ThreeChess*, double, double*);
	/*
	���ǵ���3*3�����̣�����Χ������Ϊ�գ��������壬�������������ݽṹ��ȡ��
	�����������ԣ��涨0Ϊ�����ӣ�1Ϊ���ӣ�2Ϊ����
	*/
};
struct ChessPointer
{
	ThreeChess chess;
	ChessPointer* next;
	ChessPointer* front;
};

#endif