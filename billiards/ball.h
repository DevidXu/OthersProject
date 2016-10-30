enum Color { White, Yellow, Blue, Purple, Red, Green, Brown, Orange, DRed, DYellow, DGreen };

class Ball
{
private:
	double r,In;
	double x, y;
	double V_Angle;
	double Vx, Vy;
	enum Color C;
public:
	Ball();
	Ball(double m_x,double m_y,double m_r,double m_Vx,double m_Vy,enum Color m_C);
	~Ball();
	double X(){ return x; }; double Y(){ return y; }; 
	double VX(){ return Vx; }; double VY(){ return Vy; };
	void GiveVx(double m_Vx){ Vx = m_Vx; }; void GiveVy(double m_Vy){ Vy = m_Vy; };
	void forward();
	bool ifstop();
	void CollisionWall();
	bool HitHole();
	void ShowBall();
	void ClearBall();
	friend void BallMotion(double, double, double, double);
};

struct Onball
{
	Ball ball;
	struct Onball* front;
	struct Onball* next;
	int items;
	bool isempty()
	{
		if (items == 0) return true; else return false;
	};
	void add(Onball* m_Onball)
	{
		if (items != 0)
		{
			if (next != NULL)
			{
				next->front = m_Onball;
				m_Onball->front = this;
				m_Onball->next = next;
				next = m_Onball;
			}
			else
			{
				m_Onball->front = this;
				m_Onball->next = NULL;
				next = m_Onball;
			};
		}
		else
		{
			m_Onball->front = NULL;
			m_Onball->next = NULL;
		};
	};
	void cutout()
	{
		items--;
		if (front != NULL) front->next = next;
		if (next != NULL) next->front = front;
		front = NULL; next = NULL;
	};
};


void BallMotion(double, double, double, double);

void GetInitial(double, double, double&, double&);

void CollisionBall(Onball*, Onball*);

bool AllStop(Onball*);