/*
��ͷ�ļ��涨Ϊ����ѧϰ--�����������ı�׼���̣�����������Ϊʵ����󣬽�ThreeChess����а���

��Ҫ���˷���Ӧ���ڲ�ͬ�����࣬���޸ķ�װ���������༴��
*/
#ifndef _CHESSLEARN_H__
#define _CHESSLEARN_H__

class ChessLearn
{
private:
	ChessPointer* begin;                               //beginΪ��ʼ���̽ṹ����
	ChessPointer* p_chess;                              //p_chessΪ��ǰĿ������ָ��

	double w[7];

public:
	ChessLearn();
	~ChessLearn();
	void Init();

	void Restart();                    //ɾ��begin���ָ�룬���¿�ʼ
	void NextStep(Result);                   //����λ�ÿ��ߵ�ǰ���£�Ѱ����һ�����Ž�
	void Backdate();                   //�ص�ǰָ��p_chess����ǰ������
	bool CheckEnd();                   //���鵱ǰ�����Ƿ��ڽ���״̬
	Result GetWinner();                //����Ӯ��
	void PrintW();                     //���w����
	double GetW(int);                  //�õ�w[i]��ֵ
	void GiveState(int*);              //���õ���board��ֵ����
	void GetState(int*);               //�����������һ��board��ֵ����

};

#endif