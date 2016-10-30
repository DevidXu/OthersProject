// Collision_Ball.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Table.h"
#include "ball.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>

extern int Length = 714;
extern int Width = 358;   //关于桌子的尺寸设计(全局常量)
extern double Accel =0.025;
extern int BallSize = 10;
extern int V_Pendular = 5;    //指针与力摆摆动速度:0为静止，10为满速度

int main()
{
	InitialTable(Length, Width);    //初始化球桌
	
	Onball b0; Onball b1; Onball b2; Onball b3; Onball b4; Onball b5;
	Onball b6; Onball b7; Onball b8; Onball b9; Onball b10; 
	b0.ball = Ball(-Length/4,0, BallSize,0, 0, White);
	b0.front = NULL; b0.next = &b1;
	b1.ball = Ball(Length/4-5*BallSize, 0, BallSize, 0, 0, Yellow);
	b1.front = &b0; b1.next = &b2;
	b2.ball = Ball(Length/4-3*BallSize, 1.2*BallSize, BallSize, 0, 0, Blue);
	b2.front = &b1; b2.next = &b3;
	b3.ball = Ball(Length/4-3*BallSize, -1.2*BallSize, BallSize, 0, 0, Purple);
	b3.front = &b2; b3.next = &b4;
	b4.ball = Ball(Length/4-BallSize, 2.4*BallSize, BallSize, 0, 0, Red);
	b4.front = &b3; b4.next = &b5;
	b5.ball = Ball(Length/4-BallSize, 0, BallSize, 0, 0, Green);
	b5.front = &b4; b5.next = &b6;
	b6.ball = Ball(Length/4-BallSize, -2.4*BallSize, BallSize, 0, 0, Brown);
	b6.front = &b5; b6.next = &b7;
	b7.ball = Ball(Length/4+BallSize, 3.6*BallSize, BallSize, 0, 0, Orange);
	b7.front = &b6; b7.next = &b8;
	b8.ball = Ball(Length/4+BallSize, 1.2*BallSize, BallSize, 0, 0, DYellow);
	b8.front = &b7; b8.next = &b9;
	b9.ball = Ball(Length/4+BallSize, -1.2*BallSize, BallSize, 0, 0, DRed);
	b9.front = &b8; b9.next = &b10;
	b10.ball = Ball(Length/4+BallSize, -3.6*BallSize, BallSize, 0, 0, DGreen); 
	b10.front = &b9; b10.next = NULL;        //初始化11个球（白+1+2+3+4），他们为同一结构（发现这里用结构比较方便）
	                                        //同时，这里的命名不用数组主要由于颜色， 同时也可能带来关于类型的误解
	Onball* M0;    Onball* MM0;          //M0为白色球，作为遍历的起点

	M0 = &b0; MM0 = M0->next;
	while (M0 != NULL)
	{
		M0->ball.ShowBall();
		M0 = M0->next;
	}
	Sleep(100);

	double V1, V2;

	while (b0.next != NULL)
	{
		GetInitial(b0.ball.X(), b0.ball.Y(), V1, V2);
		b0.ball.GiveVx(V1); b0.ball.GiveVy(V2);       //将速度赋值给白球

		while (1)
		{
			M0 = &b0;
			while (M0 != NULL)
			{
				M0->ball.forward();
				if (M0->ball.HitHole()) M0->cutout();
				M0->ball.CollisionWall();
				M0 = M0->next;
			}

			M0 = &b0;
			while (M0 != NULL)
			{
				MM0 = M0->next;
				while (MM0 != NULL)
				{
					CollisionBall(M0, MM0);
					MM0 = MM0->next;
				}
				M0 = M0->next;
			}               //判断任意两球之间是否发生碰撞
			M0 = &b0;
			while (M0 != NULL)
			{
				M0->ball.ShowBall();
				M0 = M0->next;
			}                //画出所有球

			Sleep(10);

			if (AllStop(&b0))
			{
				break;
			}
			M0 = &b0;
			while (M0 != NULL)
			{
				M0->ball.ClearBall();
				M0 = M0->next;
			}               //清除所有球
		};
	}
	_getch();
}
 