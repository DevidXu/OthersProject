#include "stdafx.h"
#include "ball.h"
#include "Table.h"
#include <iostream>
#include <cmath>
#include <graphics.h>     
#include <stdio.h>

extern int Length;
extern int Width;
extern double Accel;
extern int BallSize;
extern int V_Pendular;

Ball::Ball()
{
	x = 0;y = 0;
	Vx = 0;Vy = 0;
	V_Angle = 0;
	In = 0;
	C = White;
}

Ball::~Ball(){}

Ball::Ball(double m_x, double m_y, double m_r, double m_Vx, double m_Vy, Color m_C)
{
	x = m_x; y = m_y; r = m_r;
	Vx = m_Vx; Vy = m_Vy;
	In = 0; C = m_C;
}

void Ball::forward()
{
	if (Vx != 0) V_Angle = atan(Vy / Vx); else V_Angle = 1.57;
	x = x + Vx;
	y = y + Vy;
	if (Vx>0) Vx = fabs(Vx) - fabs(Accel*cos(V_Angle));
	else Vx = -fabs(Vx) + fabs(Accel*cos(V_Angle));
	if (Vy>0) Vy = fabs(Vy) -fabs(Accel*sin(V_Angle));
	else Vy = -fabs(Vy) + fabs(Accel*sin(V_Angle));
}

bool Ball::ifstop()
{
	if ((fabs(Vx) <= fabs(Accel*cos(V_Angle))) && (fabs(Vy) <= fabs(Accel*sin(V_Angle)))) return true;
	else return false;
}

void Ball::CollisionWall()
{
	if (fabs(x) + r >= Length / 2) Vx = -Vx;
	if (fabs(y) + r >= Width / 2) Vy = -Vy;
}

bool Ball::HitHole()
{
	if ((fabs(x) + BallSize > Length*0.485) && (fabs(y) + BallSize > Width*0.485)) 
	{
		In = 1;
		return true;
	}
	if ((fabs(x)<BallSize*1.2) && (fabs(y) + BallSize>Width*0.48))
	{
		In = 1;
		return true;
	}
	return false;
}

void Ball::ShowBall()
{
	using namespace std;
	if (C==0) setfillcolor(WHITE);
	if (C == 1) setfillcolor(RGB(255, 255,0));
	if (C == 2) setfillcolor(RGB(0, 0, 255));
	if (C == 3) setfillcolor(RGB(128, 0, 128));
	if (C == 4) setfillcolor(RGB(255, 0, 0));
	if (C == 5) setfillcolor(RGB(100,255,0));
	if (C == 6) setfillcolor(RGB(139,69, 19));
	if (C == 7) setfillcolor(RGB(255, 165, 0));
	if (C == 8) setfillcolor(RGB(139, 0, 0));
	if (C == 9) setfillcolor(RGB(184, 134,11));
	if (C == 10) setfillcolor(RGB(100, 100, 0));
	fillcircle(x, y, r);
	Sleep(2);
}

void Ball::ClearBall()
{
	clearcircle(x, y, r+1);
}

void GetInitial(double m_x, double m_y, double& m_V1, double& m_V2)
{
	double Angle, Power;
	Angle = Pendular(V_Pendular, m_x, m_y, Length, Width);    //确定发射角度
	Power = Strength(V_Pendular, m_x, m_y, Length, Width);   //确定发射力度
	m_V1 = -10 * cos(Angle)*Power;
	m_V2 = -10 * sin(Angle)*Power;     //计算发射初速度
}

void CollisionBall(Onball* m_M0, Onball* m_MM0)
{
	double Xdistance, Ydistance,m1_Vx,m1_Vy,m2_Vx,m2_Vy;
	Xdistance = m_M0->ball.X() - m_MM0->ball.X();
	Ydistance = m_M0->ball.Y() - m_MM0->ball.Y();
	double Angle; 
	if (Xdistance == 0) Angle = 1.57; else Angle = atan(Ydistance / Xdistance);
	if (Xdistance*Xdistance + Ydistance*Ydistance < 4 * (BallSize+1)*(BallSize+1))       //距离到达危险值
	{
		if ((m_MM0->ball.VX()*cos(Angle) + m_MM0->ball.VY()*sin(Angle) -
			m_M0->ball.VX()*cos(Angle)*cos(Angle) - m_M0->ball.VY()*sin(Angle)*cos(Angle))*Xdistance>0)
		{
			m1_Vx = m_M0->ball.VX()*sin(Angle)*sin(Angle) + m_M0->ball.VY()*cos(Angle)*sin(Angle) +
				0.5*m_MM0->ball.VX()*cos(Angle)*cos(Angle) + 0.5*m_MM0->ball.VY()*sin(Angle)*cos(Angle);
			m1_Vy = m_M0->ball.VX()*sin(Angle)*cos(Angle) + m_M0->ball.VY()*cos(Angle)*cos(Angle) +
				0.5*m_MM0->ball.VX()*cos(Angle)*sin(Angle) + 0.5*m_MM0->ball.VY()*sin(Angle)*sin(Angle);
			m_M0->ball.GiveVx(m1_Vx); m_M0->ball.GiveVy(m1_Vy);
			m2_Vx = m_MM0->ball.VX()*sin(Angle)*sin(Angle) + m_MM0->ball.VY()*cos(Angle)*sin(Angle) +
				0.5*m_M0->ball.VX()*cos(Angle)*cos(Angle) + 0.5*m_M0->ball.VY()*sin(Angle)*cos(Angle);
			m2_Vy = m_MM0->ball.VX()*sin(Angle)*cos(Angle) + m_MM0->ball.VY()*cos(Angle)*cos(Angle) +
				0.5*m_M0->ball.VX()*cos(Angle)*sin(Angle) + 0.5*m_M0->ball.VY()*sin(Angle)*sin(Angle);    //此处前面有系数，否则速度将会叠加增大
			m_MM0->ball.GiveVx(m2_Vx); m_MM0->ball.GiveVy(m2_Vy);
		}
	};
}                      //此处为观察两小球是否碰撞，以及碰撞后利用动量进行处理

bool AllStop(Onball* m_b0)
{
	while (m_b0 != NULL)
	{
		if (!m_b0->ball.ifstop()) return false;
		m_b0 = m_b0->next;
	}
	return true;
}                     //判断是否所有球都已停下