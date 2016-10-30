
// MazeDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMazeDlg �Ի���



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


// CMazeDlg ��Ϣ�������

BOOL CMazeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMazeDlg::OnPaint()
{
	//ͼƬ�ؼ�����
	pDC = GetDlgItem(IDC_STATIC_MAZE)->GetDC();
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);      //�������ͼ��ʱ��Ӧ�ĳ��Ϳ�
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;
	pDC->FillSolidRect(0, 0, iWndWidth, iWndHeight, RGB(255, 255, 255));

	//�������ǵĳ�ʼλ��
	Lead_i = 1; Lead_j = 1; Way = 0; game_begin = false;

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMazeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��д����

void CMazeDlg::OnBnClickedButtonForm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (game_begin == false) Random_Tracker();
	
	if (m_Pace == 0)
	{
		MessageBox(_T("������仯������"));
		return;
	}

	//����
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);      //�������ͼ��ʱ��Ӧ�ĳ��Ϳ�
	double iWndWidth = rtWnd.right - rtWnd.left;
	double iWndHeight = rtWnd.bottom - rtWnd.top;
	pDC->FillSolidRect(0, 0, (int)iWndWidth, (int)iWndHeight, RGB(255, 255, 255));

	//�����Թ�
	double square = min(iWndWidth * 3 / 4 / Width, iWndHeight * 3 / 4 / Height);
	double x_initial = iWndWidth / 2 - square*Width / 2, y_initial = iWndHeight / 2 - square*Height / 2;

	if (Way % m_Pace == 0)
	{
		for (int i = 0; i <= Height + 1; i++)
		for (int j = 0; j <= Width + 1; j++)
		{

			Visit[i][j] = 0;     //0��ʾδ�����ʹ�
			Wall_hor[i][j] = 1;     //1��ʾ��ǽ
			Wall_ver[i][j] = 1;
			if ((i == 0) || (i == Height + 1) || (j == 0) || (j == Width + 1))
				Visit[i][j] = 1;
		}

		//Visit_numΪ�Ѱݷõ�������Ŀ
		//x��yΪ��ǰλ�ã�m_x��m_yΪȥ��λ�ã�rand_numΪ�����
		int Visit_num = 1, x = 1, y = 1, m_x = 0, m_y = 0, rand_num = 0;

		//���ʱ�����
		srand((int)time(0));

		//��ʼѭ����ֱ�����з���������ʹ�
		while (Visit_num < Width * Height)
		{
			Visit[x][y] = 1;  //��Ǹĵ�Ϊ�ѷ���

			if (Visit[x - 1][y] + Visit[x][y - 1] + Visit[x + 1][y] + Visit[x][y + 1] < 4)   //����Χ����Ϊ���ʵĵ�
			{
				while (Visit[x + m_x][y + m_y] == 1)   //�������
				{
					rand_num = rand() % 4;
					if (rand_num == 0) { m_x = 0; m_y = -1; }
					if (rand_num == 1) { m_x = 1; m_y = 0; }
					if (rand_num == 2) { m_x = 0; m_y = 1; }
					if (rand_num == 3) { m_x = -1; m_y = 0; }
				}
				if ((m_x == 0) && (m_y == -1)) Wall_ver[x][y - 1] = 0;    //��ͨǽ��
				if ((m_x == 0) && (m_y == 1)) Wall_ver[x][y] = 0;
				if ((m_y == 0) && (m_x == -1)) Wall_hor[x][y] = 0;
				if ((m_y == 0) && (m_x == 1)) Wall_hor[x + 1][y] = 0;
				x = x + m_x; y = y + m_y;
				m_x = 0; m_y = 0;     //�������λ��
				Visit_num = Visit_num + 1;     
			}
			else
			{
				do
				{
					x = rand() % Height + 1;
					y = rand() % Width + 1;
				} while (Visit[x][y] == 0);   //���ѷ��ʹ��ĵ�������ҳ�һ�����
			}
		}

		//�����Թ�
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

		//�����ƶ�Բ������
		brush.DeleteObject();   //������ɫ��ˢ
		brush.CreateSolidBrush(RGB(0, 0, 255));
		pDC->SelectObject(brush);
		pDC->Ellipse((int)(x_initial + square*(Lead_j - 1)), (int)(y_initial + square*(Lead_i - 1)),
			(int)(x_initial + square*Lead_j), (int)(y_initial + square*Lead_i));

		//����tracker
		brush.DeleteObject();   //���ú�ɫ��ˢ
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
		//���������ɣ�ֱ����ԭ�����ϻ���
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

		//����Բ��
		brush.DeleteObject();   //������ɫ��ˢ
		brush.CreateSolidBrush(RGB(0, 0, 255));
		pDC->SelectObject(brush);
		pDC->Ellipse((int)(x_initial + square*(Lead_j - 1)), (int)(y_initial + square*(Lead_i - 1)),
			(int)(x_initial + square*Lead_j), (int)(y_initial + square*Lead_i));

		//����tracker
		brush.DeleteObject();   //���ú�ɫ��ˢ
		brush.CreateSolidBrush(RGB(255, 0, 0));
		pDC->SelectObject(brush);
		for (int i = 1; i <= m_Tracker; i++)
		{
			pDC->Ellipse((int)(x_initial + square*(Tracker_y[i] - 1)), (int)(y_initial + square*(Tracker_x[i] - 1)),
				(int)(x_initial + square*Tracker_y[i]), (int)(y_initial + square*Tracker_x[i]));
		}
	}

	if ((Lead_i == Height) && (Lead_j == Width)) Success();     //�ж��Ƿ�ɹ�

	game_begin = true;  //��Ϸ�Ѿ���ʼ���ж��Ƿ���Ҫ����ʼλ��
}

//��Ϸ��ʼ���������׷���ߵ�λ��
void CMazeDlg::Random_Tracker()
{
	//�ӱ༭���ȡ�����߶�
	UpdateData(true);
	Width = GetDlgItemInt(IDC_EDIT_WIDTH);
	Height = GetDlgItemInt(IDC_EDIT_HEIGHT);
	m_Pace = GetDlgItemInt(IDC_EDIT_PACE);
	m_Tracker = GetDlgItemInt(IDC_EDIT_TRACKER);

	for (int i = 0; i < 103; i++)
	for (int j = 0; j < 103; j++)
		Maze[i][j] = 0;    //0��ʾ�õ�û��Բ

	Maze[1][1] = 1;

	srand((int)time(0));
	for (int i = 1; i <= m_Tracker; i++)
	{
		do
		{
			Tracker_x[i] = rand() % Height + 1;
			Tracker_y[i] = rand() % Width + 1;
		} while (Maze[Tracker_x[i]][Tracker_y[i]] == 1);   //���ѷ��ʹ��ĵ�������ҳ�һ�����
		Maze[Tracker_x[i]][Tracker_y[i]] = 1;
	}

	Maze[1][1] = 0;
}

//���ܼ�����Ϣ���������Ҽ�
BOOL CMazeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
					MessageBox(_T("����׷����ץ������Ϸ������"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1)
				{
					MessageBox(_T("����׷����ץ������Ϸ������"));
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
					MessageBox(_T("����׷����ץ������Ϸ������"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1) 
				{
					MessageBox(_T("����׷����ץ������Ϸ������"));
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
					MessageBox(_T("����׷����ץ������Ϸ������"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1) 
				{
					MessageBox(_T("����׷����ץ������Ϸ������"));
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
					MessageBox(_T("����׷����ץ������Ϸ������"));
					Lead_i = 1; Lead_j = 1; game_begin = false;
					OnBnClickedButtonForm();
				}
				Tracker_Position();OnBnClickedButtonForm();
				if (Maze[Lead_i][Lead_j] == 1) 
				{
					MessageBox(_T("����׷����ץ������Ϸ������"));
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

//����׷���ߵ�λ��
void CMazeDlg::Tracker_Position()
{
	int i_distance = 0, j_distance = 0,choice=0; 
	bool D[4];   //Direction  :0�� 1�� 2�� 3��
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

//������������
void CMazeDlg::OnBnClickedButtonAgain()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Lead_i = 1; Lead_j = 1; Way = 0; game_begin = false;
	m_Pace = 0; m_Tracker = 0;
	for (int i = 0; i <= 500; i++)
	{
		Tracker_x[i] = 0; Tracker_y[i] = 0;
	}
	OnBnClickedButtonForm();
}

//��Ϸ�������˵��
void CMazeDlg::OnBnClickedButtonIntro()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CIntro cintro;
	cintro.DoModal();
	return;
}

//��ҳɹ�����ʾף�ز����¿�ʼ
void CMazeDlg::Success()
{
	MessageBox(_T("��ϲ�������ɹ������谭�������յ㣡��"));
	OnBnClickedButtonAgain();
}