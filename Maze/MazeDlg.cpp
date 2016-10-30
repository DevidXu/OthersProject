
// MazeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Maze.h"
#include "MazeDlg.h"
#include "afxdialogex.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "Intro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMazeDlg 对话框



CMazeDlg::CMazeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMazeDlg::IDD, pParent)
	, Width(0)
	, Height(0)
	, m_Pace(0)
	, m_Tracker(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMazeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, Width);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, Height);
	DDV_MinMaxInt(pDX, Height, 1, 200);
	DDX_Text(pDX, IDC_EDIT_PACE, m_Pace);
	DDV_MinMaxInt(pDX, m_Pace, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_TRACKER, m_Tracker);
	DDV_MinMaxInt(pDX, m_Tracker, 0, 100);
}

BEGIN_MESSAGE_MAP(CMazeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FORM, &CMazeDlg::OnBnClickedButtonForm)
	ON_BN_CLICKED(IDC_BUTTON_AGAIN, &CMazeDlg::OnBnClickedButtonAgain)
	ON_BN_CLICKED(IDC_BUTTON_INTRO, &CMazeDlg::OnBnClickedButtonIntro)
END_MESSAGE_MAP()


// CMazeDlg 消息处理程序

BOOL CMazeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMazeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMazeDlg::OnPaint()
{
	//图片控件清屏
	pDC = GetDlgItem(IDC_STATIC_MAZE)->GetDC();
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);      //计算输出图像时对应的长和宽
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;
	pDC->FillSolidRect(0, 0, iWndWidth, iWndHeight, RGB(255, 255, 255));

	//设置主角的初始位置
	Lead_i = 1; Lead_j = 1; Way = 0; game_begin = false;

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMazeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//自写函数

void CMazeDlg::OnBnClickedButtonForm()
{
	// TODO:  在此添加控件通知处理程序代码

	if (game_begin == false) Random_Tracker();
	
	if (m_Pace == 0)
	{
		MessageBox(_T("请输入变化步数！"));
		return;
	}

	//清屏
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);      //计算输出图像时对应的长和宽
	double iWndWidth = rtWnd.right - rtWnd.left;
	double iWndHeight = rtWnd.bottom - rtWnd.top;
	pDC->FillSolidRect(0, 0, (int)iWndWidth, (int)iWndHeight, RGB(255, 255, 255));

	//绘制迷宫
	double square = min(iWndWidth * 3 / 4 / Width, iWndHeight * 3 / 4 / Height);
	double x_initial = iWndWidth / 2 - square*Width / 2, y_initial = iWndHeight / 2 - square*Height / 2;

	if (Way % m_Pace == 0)
	{
		for (int i = 0; i <= Height + 1; i++)
		for (int j = 0; j <= Width + 1; j++)
		{

			Visit[i][j] = 0;     //0表示未被访问过
			Wall_hor[i][j] = 1;     //1表示有墙
			Wall_ver[i][j] = 1;
			if ((i == 0) || (i == Height + 1) || (j == 0) || (j == Width + 1))
				Visit[i][j] = 1;
		}

		//Visit_num为已拜访的区域数目
		//x，y为当前位置，m_x，m_y为去向位置，rand_num为随机数
		int Visit_num = 1, x = 1, y = 1, m_x = 0, m_y = 0, rand_num = 0;

		//随机时间参数
		srand((int)time(0));

		//开始循环，直到所有方格均被访问过
		while (Visit_num < Width * Height)
		{
			Visit[x][y] = 1;  //标记改点为已访问

			if (Visit[x - 1][y] + Visit[x][y - 1] + Visit[x + 1][y] + Visit[x][y + 1] < 4)   //若周围存在为访问的点
			{
				while (Visit[x + m_x][y + m_y] == 1)   //随机方向
				{
					rand_num = rand() % 4;
					if (rand_num == 0) { m_x = 0; m_y = -1; }
					if (rand_num == 1) { m_x = 1; m_y = 0; }
					if (rand_num == 2) { m_x = 0; m_y = 1; }
					if (rand_num == 3) { m_x = -1; m_y = 0; }
				}
				if ((m_x == 0) && (m_y == -1)) Wall_ver[x][y - 1] = 0;    //打通墙壁
				if ((m_x == 0) && (m_y == 1)) Wall_ver[x][y] = 0;
				if ((m_y == 0) && (m_x == -1)) Wall_hor[x][y] = 0;
				if ((m_y == 0) && (m_x == 1)) Wall_hor[x + 1][y] = 0;
				x = x + m_x; y = y + m_y;
				m_x = 0; m_y = 0;     //修正点的位置
				Visit_num = Visit_num + 1;     
			}
			else
			{
				do
				{
					x = rand() % Height + 1;
					y = rand() % Width + 1;
				} while (Visit[x][y] == 0);   //在已访问过的点中随机找出一点继续
			}
		}

		//绘制迷宫
		for (int i = 1; i <= Height + 1; i++)
		for (int j = 1; j <= Width; j++)
		if (Wall_hor[i][j] == 1)
		{
			pDC->MoveTo((int)(x_initial + square*(j - 1)), (int)(y_initial + square*(i - 1)));
			pDC->LineTo((int)(x_initial + square*j), (int)(y_initial + square*(i - 1)));
		}

		for (int i = 1; i <= Height; i++)
		for (int j = 0; j <= Width; j++)
		if (Wall_ver[i][j] == 1)
		{
			pDC->MoveTo((int)(x_initial + square*j), (int)(y_initial + square*(i - 1)));
			pDC->LineTo((int)(x_initial + square*j), (int)(y_initial + square*i));
		}

		//绘制移动圆（主）
		brush.DeleteObject();   //配置蓝色画刷
		brush.CreateSolidBrush(RGB(0, 0, 255));
		pDC->SelectObject(brush);
		pDC->Ellipse((int)(x_initial + square*(Lead_j - 1)), (int)(y_initial + square*(Lead_i - 1)),
			(int)(x_initial + square*Lead_j), (int)(y_initial + square*Lead_i));

		//绘制tracker
		brush.DeleteObject();   //配置红色画刷
		brush.CreateSolidBrush(RGB(255, 0, 0));
		pDC->SelectObject(brush);
		for (int i = 1; i <= m_Tracker; i++)
		{
			pDC->Ellipse((int)(x_initial + square*(Tracker_y[i] - 1)), (int)(y_initial + square*(Tracker_x[i] - 1)),
				(int)(x_initial + square*Tracker_y[i]), (int)(y_initial + square*Tracker_x[i]));
		}

	}
	else
	{
		//不重新生成，直接在原基础上绘制
		for (int i = 1; i <= Height + 1; i++)
		for (int j = 1; j <= Width; j++)
		if (Wall_hor[i][j] == 1)
		{
			pDC->MoveTo((int)(x_initial + square*(j - 1)), (int)(y_initial + square*(i - 1)));
			pDC->LineTo((int)(x_initial + square*j), (int)(y_initial + square*(i - 1)));
		}

		for (int i = 1; i <= Height; i++)
		for (int j = 0; j <= Width; j++)
		if (Wall_ver[i][j] == 1)
		{
			pDC->MoveTo((int)(x_initial + square*j), (int)(y_initial + square*(i - 1)));
			pDC->LineTo((int)(x_initial + square*j), (int)(y_initial + square*i));
		}

		//绘制圆形
		brush.DeleteObject();   //配置蓝色画刷
		brush.CreateSolidBrush(RGB(0, 0, 255));
		pDC->SelectObject(brush);
		pDC->Ellipse((int)(x_initial + square*(Lead_j - 1)), (int)(y_initial + square*(Lead_i - 1)),
			(int)(x_initial + square*Lead_j), (int)(y_initial + square*Lead_i));

		//绘制tracker
		brush.DeleteObject();   //配置红色画刷
		brush.CreateSolidBrush(RGB(255, 0, 0));
		pDC->SelectObject(brush);
		for (int i = 1; i <= m_Tracker; i++)
		{
			pDC->Ellipse((int)(x_initial + square*(Tracker_y[i] - 1)), (int)(y_initial + square*(Tracker_x[i] - 1)),
				(int)(x_initial + square*Tracker_y[i]), (int)(y_initial + square*Tracker_x[i]));
		}
	}

	if ((Lead_i == Height) && (Lead_j == Width)) Success();     //判断是否成功

	game_begin = true;  //游戏已经开始，判断是否需要生初始位置
}

//游戏开始，随机所有追踪者的位置
void CMazeDlg::Random_Tracker()
{
	//从编辑框读取宽度与高度
	UpdateData(true);
	Width = GetDlgItemInt(IDC_EDIT_WIDTH);
	Height = GetDlgItemInt(IDC_EDIT_HEIGHT);
	m_Pace = GetDlgItemInt(IDC_EDIT_PACE);
	m_Tracker = GetDlgItemInt(IDC_EDIT_TRACKER);

	for (int i = 0; i < 103; i++)
	for (int j = 0; j < 103; j++)
		Maze[i][j] = 0;    //0表示该点没有圆

	Maze[1][1] = 1;

	srand((int)time(0));
	for (int i = 1; i <= m_Tracker; i++)
	{
		do
		{
			Tracker_x[i] = rand() % Height + 1;
			Tracker_y[i] = rand() % Width + 1;
		} while (Maze[Tracker_x[i]][Tracker_y[i]] == 1);   //在已访问过的点中随机找出一点继续
		Maze[Tracker_x[i]][Tracker_y[i]] = 1;
	}

	Maze[1][1] = 0;
}

//接受键盘消息，上下左右键
BOOL CMazeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			if (Wall_hor[Lead_i][Lead_j] == 0)
			{
				Way = Way + 1;Lead_i = Lead_i - 1;
				if (Maze[Lead_i][Lead_j] == 1)
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1)
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
			}
			break;
		case VK_DOWN:
			if (Wall_hor[Lead_i+1][Lead_j] == 0)
			{
				Way = Way + 1;Lead_i = Lead_i + 1;
				if (Maze[Lead_i][Lead_j] == 1)
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1) 
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
			}
			break;
		case VK_LEFT:
			if (Wall_ver[Lead_i][Lead_j-1] == 0)
			{
				Way = Way + 1;Lead_j = Lead_j - 1;
				if (Maze[Lead_i][Lead_j] == 1)
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1) 
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
			}
			break;
		case VK_RIGHT:
			if (Wall_ver[Lead_i][Lead_j] == 0)
			{
				Way = Way + 1;Lead_j = Lead_j + 1;
				if (Maze[Lead_i][Lead_j] == 1)
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1) 
				{
					MessageBox(_T("您被追捕者抓到，游戏结束！"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
			}
			break;
		default:break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//给出追踪者的位置
void CMazeDlg::Tracker_Position()
{
	int i_distance = 0, j_distance = 0,choice=0; 
	bool D[4];   //Direction  :0上 1下 2左 3右
	srand((int)time(0));
	for (int i = 1; i <= m_Tracker; i++)
	{
		i_distance = Lead_i - Tracker_x[i];
		j_distance = Lead_j - Tracker_y[i];
		D[0] = true; D[1] = true; D[2] = true; D[3] = true;
		if ((i_distance > 0)||(Wall_hor[Tracker_x[i]][Tracker_y[i]]==1)) D[0] = false;
		if ((i_distance < 0) || (Wall_hor[Tracker_x[i] + 1][Tracker_y[i]] == 1)) D[1] = false;
		if ((j_distance > 0) || (Wall_ver[Tracker_x[i]][Tracker_y[i] - 1] == 1)) D[2] = false;
		if ((j_distance < 0) || (Wall_ver[Tracker_x[i]][Tracker_y[i]] == 1)) D[3] = false;

		if ((D[0] == false) && (D[1] == false) && (D[2] == false) && (D[3] == false)) Maze[Tracker_x[i]][Tracker_y[i]] = 1;
		else
		{
			do
			{
				choice = rand() % 4;
			} while (D[choice] == false);
			switch (choice)
			{
			case 0:
				Maze[Tracker_x[i]][Tracker_y[i]] = 0;
				Tracker_x[i] = Tracker_x[i] - 1;
				Maze[Tracker_x[i]][Tracker_y[i]] = 1;
				break;
			case 1:
				Maze[Tracker_x[i]][Tracker_y[i]] = 0;
				Tracker_x[i] = Tracker_x[i] + 1;
				Maze[Tracker_x[i]][Tracker_y[i]] = 1;
				break;
			case 2:
				Maze[Tracker_x[i]][Tracker_y[i]] = 0;
				Tracker_y[i] = Tracker_y[i] - 1;
				Maze[Tracker_x[i]][Tracker_y[i]] = 1;
				break;
			case 3:
				Maze[Tracker_x[i]][Tracker_y[i]] = 0;
				Tracker_y[i] = Tracker_y[i] + 1;
				Maze[Tracker_x[i]][Tracker_y[i]] = 1;
				break;
			default: break;
			}
		}
	}

}

//重置所有数据
void CMazeDlg::OnBnClickedButtonAgain()
{
	// TODO:  在此添加控件通知处理程序代码
	Lead_i = 1; Lead_j = 1; Way = 0; game_begin = false;
	m_Pace = 0; m_Tracker = 0;
	for (int i = 0; i <= 500; i++)
	{
		Tracker_x[i] = 0; Tracker_y[i] = 0;
	}
	OnBnClickedButtonForm();
}

//游戏规则介绍说明
void CMazeDlg::OnBnClickedButtonIntro()
{
	// TODO:  在此添加控件通知处理程序代码
	CIntro cintro;
	cintro.DoModal();
	return;
}

//玩家成功，显示祝贺并重新开始
void CMazeDlg::Success()
{
	MessageBox(_T("恭喜您，您成功穿破阻碍，到达终点！！"));
	OnBnClickedButtonAgain();
}