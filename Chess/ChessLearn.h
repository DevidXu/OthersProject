/*
该头文件规定为机器学习--函数鉴定法的标准过程，并以三子棋为实验对象，将ThreeChess类进行包含

若要将此方法应用于不同的棋类，则修改封装的三子棋类即可
*/
#ifndef _CHESSLEARN_H__
#define _CHESSLEARN_H__

class ChessLearn
{
private:
	ChessPointer* begin;                               //begin为初始棋盘结构变量
	ChessPointer* p_chess;                              //p_chess为当前目标棋盘指针

	double w[7];

public:
	ChessLearn();
	~ChessLearn();
	void Init();

	void Restart();                    //删除begin后的指针，重新开始
	void NextStep(Result);                   //在有位置可走的前提下，寻找下一步最优解
	void Backdate();                   //沿当前指针p_chess，向前方回溯
	bool CheckEnd();                   //检验当前棋盘是否处于结束状态
	Result GetWinner();                //返回赢家
	void PrintW();                     //输出w数组
	double GetW(int);                  //得到w[i]的值
	void GiveState(int*);              //将得到的board的值传入
	void GetState(int*);               //将计算出的下一步board的值传出

};

#endif