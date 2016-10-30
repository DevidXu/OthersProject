// Collision_Ball.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Table.h"
#include "ball.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>

extern int Length = 714;
extern int Width = 358;   //�������ӵĳߴ����(ȫ�ֳ���)
extern double Accel =0.025;
extern int BallSize = 10;
extern int V_Pendular = 5;    //ָ�������ڰڶ��ٶ�:0Ϊ��ֹ��10Ϊ���ٶ�

int main()
{
	InitialTable(Length, Width);    //��ʼ������
	
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
	b10.front = &b9; b10.next = NULL;        //��ʼ��11���򣨰�+1+2+3+4��������Ϊͬһ�ṹ�����������ýṹ�ȽϷ��㣩
	                                        //ͬʱ���������������������Ҫ������ɫ�� ͬʱҲ���ܴ����������͵����
	Onball* M0;    Onball* MM0;          //M0Ϊ��ɫ����Ϊ���������

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
		b0.ball.GiveVx(V1); b0.ball.GiveVy(V2);       //���ٶȸ�ֵ������

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
			}               //�ж���������֮���Ƿ�����ײ
			M0 = &b0;
			while (M0 != NULL)
			{
				M0->ball.ShowBall();
				M0 = M0->next;
			}                //����������

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
			}               //���������
		};
	}
	_getch();
}
 