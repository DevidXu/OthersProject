/*
该头文件是针对不同的棋的规则进行设定，本处为三子棋；当然亦可以修改为五子棋
将该棋类进行封装
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
	常量
	白子二连子数量：
	黑子二连子数量：
	中心加四中白子数量：
	中心加四中黑子数量：
	白子三连子数量：
	黑子三连子数量：
	*/
	Result result;

public:
	int board[5][5];

public:
	ThreeChess();
	~ThreeChess(){};

	Result CheckAndUpdate();                    //返回调查结果并更新w[i]的值
	void NextChess(ThreeChess*, ThreeChess*, double*, int);
	double GetTrain(double*);
	void UpdateWeight(ThreeChess*, double, double*);
	/*
	考虑的是3*3的棋盘，而周围则设置为空，不可置棋，这样有利于数据结构的取用
	由于棋子特性：规定0为无棋子，1为白子，2为黑子
	*/
};
struct ChessPointer
{
	ThreeChess chess;
	ChessPointer* next;
	ChessPointer* front;
};

#endif