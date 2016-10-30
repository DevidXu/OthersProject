#include "stdafx.h"
#include "Table.h"
#include <graphics.h>     
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include "ball.h"

extern int BallSize;

void InitialTable(int m_Length,int m_Width)
{
	initgraph(m_Length / 4 * 5, m_Width / 3 * 4);      //等比运行窗口大小
	setorigin(m_Length / 8 * 5, m_Width / 3 * 2);      //设置坐标原点
	m_Length = m_Length / 2+BallSize/5; m_Width = m_Width / 2+BallSize/5;
	/* line(-m_Length / 13 * 12, m_Width, -m_Length / 13 ,m_Width);
	line(m_Length / 13 * 12, m_Width, m_Length / 13, m_Width);
	line(-m_Length / 13 * 12, -m_Width, -m_Length / 13, -m_Width);
	line(m_Length / 13 * 12, -m_Width, m_Length / 13, -m_Width);
	line(-m_Length, -m_Width / 19 * 16, -m_Length, m_Width / 19 * 16);
	line(m_Length, -m_Width / 19 * 16, m_Length, m_Width / 19 * 16);
	arc(-m_Length / 13 * 14, -m_Width / 19 * 22, -m_Length / 13 * 12, -m_Width / 19 * 16,0.3,4.49);
	arc(-m_Length / 13 * 14, m_Width / 19 * 22, -m_Length / 13 * 12, m_Width / 19 * 16, 1.84, -0.3);
	arc(m_Length / 13 * 14, -m_Width / 19 * 22, m_Length / 13 * 12, -m_Width / 19 * 16, -1.27, 2.84);
	arc(m_Length / 13 * 14, m_Width / 19 * 22, m_Length / 13 * 12, m_Width / 19 * 16, -2.84, 1.30);
	arc(-m_Length / 13, m_Width / 19 * 22, m_Length / 13, m_Width / 19 * 16, -2.88, -0.26);
	arc(-m_Length / 13, -m_Width / 19 * 22, m_Length / 13, -m_Width / 19 * 16, 0.26, 2.88);
	roundrect(m_Length / 13 * 14, m_Width / 19 * 22, -m_Length / 13 * 14, -m_Width / 19 * 22, m_Length / 13 * 2, m_Length / 13 * 2);*/
	IMAGE ImageP;
	loadimage(&ImageP,L"Table.jpg",m_Length/13*30,m_Width/19*50,true);
	putimage(-m_Length / 13 * 15, -m_Width / 19 * 25, &ImageP, MERGECOPY);
}        //画出边线，初始化球桌

void InitialPosition(int m_Length, int m_Width)
{

}

void InitialBall(double& m_x, double& m_y)
{
	MOUSEMSG MSG = GetMouseMsg();
	while (!(MSG.mkLButton)) 
	{ 
		FlushMouseMsgBuffer(); 
		Sleep(10);
		if (MouseHit()) MSG = GetMouseMsg();
	}
	m_x = MSG.x; m_y = MSG.y;
}

double Pendular(double m_V1,double m_x, double m_y, int m_Length,int m_Width)
{
	double Angle=0;
	int LineLength = m_Length / 18;       //起始角度与线长
	int x, y;                        //线的摆动点的位置
	Ball b1 = Ball(m_x, m_y, BallSize, 0, 0, White); 
	using namespace std;
	MOUSEMSG MSG = GetMouseMsg();
	while (!(MSG.mkLButton))
	{
		Angle = Angle + m_V1/500;
		x = m_x-LineLength*cos(Angle);
		y = m_y - LineLength*sin(Angle);   //求出末点坐标
		clearcircle(m_x, m_y, LineLength + 1);
		line(x, y, m_x, m_y);     //画出线段
		Sleep(10);
		if (MouseHit()) MSG=GetMouseMsg();       //鼠标信息,此处若没有if将延迟至接收到数据
	};
	return Angle;
}

double Strength(double m_V1,double m_x, double m_y, int m_Length, int m_Width)
{
	double Height = 0;
	int LineLength = m_Width / 5;
	int y;
	using namespace std;
	MOUSEMSG MSG = GetMouseMsg();
	FlushMouseMsgBuffer();
	while (!(MSG.mkLButton))
	{
		Height = Height + m_V1 / 500;
		y = -m_Width/2+Height*LineLength;   //求出末点坐标
		clearrectangle(m_x+m_Length/17,m_y-LineLength-2,m_x+m_Length/13,m_y+2);
		line(m_x+m_Length / 17,m_y- LineLength, m_x+m_Length / 13, m_y - LineLength);
		fillrectangle(m_x+m_Length / 17, m_y - Height*LineLength,m_x+m_Length/13,m_y);   //画出线段
		Sleep(10);
		if (MouseHit()) MSG = GetMouseMsg();       //鼠标信息,此处若没有if将延迟至接收到数据
		if (Height < 0) m_V1 = -m_V1;
		if (Height > 1) m_V1 = -m_V1;          //边界限制
	};
	Sleep(500);
	clearrectangle(m_x-m_Length / 18, m_y - LineLength - 2, m_x+m_Length / 13, m_y + 2);
	Ball b1 = Ball(m_x, m_y, BallSize, 0, 0,White);
	b1.ClearBall();
	return Height;
}

