
// ChessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chess.h"
#include "ChessDlg.h"
#include "afxdialogex.h"
#include "MachLearn.h"
#include "Windows.h"

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


// CChessDlg 对话框



CChessDlg::CChessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChessDlg::IDD, pParent)
	, m_Hint(_T(""))
	, m_Trainnum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CHESS, m_Chessboard);
	DDX_Text(pDX, IDC_STATIC_HINT, m_Hint);
	DDX_Text(pDX, IDC_EDIT_TRAINNUM, m_Trainnum);
	DDV_MinMaxInt(pDX, m_Trainnum, 0, 100000);
}

BEGIN_MESSAGE_MAP(CChessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CChessDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_RADIO_FORMER, &CChessDlg::OnBnClickedRadioFormer)
	ON_BN_CLICKED(IDC_RADIO_LATTER, &CChessDlg::OnBnClickedRadioLatter)
	ON_BN_CLICKED(IDC_BUTTON_INTRO, &CChessDlg::OnBnClickedButtonIntro)
	ON_STN_CLICKED(IDC_STATIC_CHESS, &CChessDlg::OnStnClickedStaticChess)
	ON_BN_CLICKED(IDC_BUTTON_TRAIN, &CChessDlg::OnBnClickedButtonTrain)
END_MESSAGE_MAP()


// CChessDlg 消息处理程序

BOOL CChessDlg::OnInitDialog()
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
	CheckDlgButton(IDC_RADIO_FORMER,1);
	OnBnClickedRadioFormer();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChessDlg::OnPaint()
{
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


	pDC = GetDlgItem(IDC_STATIC_CHESS)->GetDC();
	pDC->GetWindow()->GetWindowRect(&rtWnd);                
	iWndWidth = rtWnd.right - rtWnd.left;
	iWndHeight = rtWnd.bottom - rtWnd.top;                   //获取图片控件句柄及长宽

	OleLoadPicturePath(CComBSTR("D://照片//Chessboard.bmp"), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);                             //获得棋盘图像句柄及长宽
	pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);

	for (int i = 0; i < PR_num; i++) w[i] = 0;
	player = 1;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChessDlg::OnBnClickedButtonReset()
{
	// TODO:  在此添加控件通知处理程序代码
	pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);

	for (int i = 0; i < 5;i++)
	for (int j = 0; j < 5; j++)
		board[i][j] = 0;

	bool finish = false;

	if (player == 2)
	{
		Sleep(500);

		NextStep(w, &board[0][0], player);

		int width = (rtWnd.right - rtWnd.left) / 3;
		int height = (rtWnd.bottom - rtWnd.top) / 3;
		int x, y;

		for (int i = 1; i < 4; i++)
		for (int j = 1; j < 4; j++)
		{
			x = i - 1; y = j - 1;
			if (board[i][j] == 1)
			{
				brush.CreateSolidBrush(RGB(0, 255, 0));
				pDC->SelectObject(brush);
				pDC->Ellipse(width * x + width / 5, height * y + height / 5,
					width*x + width * 4 / 5, height*y + height * 4 / 5);
				brush.DeleteObject();   //配置蓝色画刷
			}
			if (board[i][j] == 2)
			{
				brush.CreateSolidBrush(RGB(255, 0, 0));
				pDC->SelectObject(brush);
				pDC->Ellipse(width * x + width / 5, height * y + height / 5,
					width*x + width * 4 / 5, height*y + height * 4 / 5);
				brush.DeleteObject();   //配置蓝色画刷
			}
		}
	}

}


void CChessDlg::OnBnClickedRadioFormer()
{
	// TODO:  在此添加控件通知处理程序代码
	player = 1;
}


void CChessDlg::OnBnClickedRadioLatter()
{
	// TODO:  在此添加控件通知处理程序代码
	player = 2;
}


void CChessDlg::OnBnClickedButtonIntro()
{
	// TODO:  在此添加控件通知处理程序代码
	CIntroPage intropage;
	if (!intropage.DoModal())
		MessageBox(_T("说明页出错！"));
	else
		return;
}


void CChessDlg::OnStnClickedStaticChess()
{
	// TODO:  在此添加控件通知处理程序代码
	POINT p;
	GetCursorPos(&p);
	int x = (p.x - rtWnd.left) * 3 / (rtWnd.right - rtWnd.left);
	int y = (p.y - rtWnd.top) * 3 / (rtWnd.bottom - rtWnd.top);    //获取鼠标对应的棋盘位置

	int width = (rtWnd.right - rtWnd.left)/3;
	int height = (rtWnd.bottom - rtWnd.top)/3;

	if (board[x+1][y+1] == 0) board[x+1][y+1] = player;

	if (board[x+1][y+1] == 1)
	{
		brush.CreateSolidBrush(RGB(0, 255, 0));
		pDC->SelectObject(brush);
		pDC->Ellipse(width * x + width / 5, height * y + height / 5,
			width*x + width * 4 / 5, height*y + height * 4 / 5);
		brush.DeleteObject();
	}
	if (board[x+1][y+1] == 2)
	{
		brush.CreateSolidBrush(RGB(255, 0, 0));
		pDC->SelectObject(brush);
		pDC->Ellipse(width * x + width / 5, height * y + height / 5,
			width*x + width * 4 / 5, height*y + height * 4 / 5);
		brush.DeleteObject();
	}
	
	Sleep(300);

	if (CheckTheResult(&board[0][0]) == player)
	{
		MessageBox(_T("你赢了！"));
		return;
	}
	if ((int)CheckTheResult(&board[0][0]) + player == 3)
	{
		MessageBox(_T("你输了！"));
		return;
	}

	NextStep(w, &board[0][0], player);

	for (int i = 1; i < 4; i++)
	for (int j = 1; j < 4; j++)
	{
		x = i - 1; y = j - 1;

		if (board[i][j] == 1)
		{
			brush.CreateSolidBrush(RGB(0, 255, 0));
			pDC->SelectObject(brush);
			pDC->Ellipse(width * x + width / 5, height * y + height / 5,
				width*x + width * 4 / 5, height*y + height * 4 / 5);
			brush.DeleteObject();   //配置蓝色画刷
		}
		if (board[i][j] == 2)
		{
			brush.CreateSolidBrush(RGB(255, 0, 0));
			pDC->SelectObject(brush);
			pDC->Ellipse(width * x + width / 5, height * y + height / 5,
				width*x + width * 4 / 5, height*y + height * 4 / 5);
			brush.DeleteObject();   //配置蓝色画刷
		}
	}

	Sleep(200);

	if (CheckTheResult(&board[0][0]) == player)
	{
		MessageBox(_T("你赢了！"));
		return;
	}
	if ((int)CheckTheResult(&board[0][0]) + player == 3)
	{
		MessageBox(_T("你输了！"));
		return;
	}

}


void CChessDlg::OnBnClickedButtonTrain()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_STATIC_HINT, _T(""));
	UpdateData(true);
	int num = GetDlgItemInt(IDC_EDIT_TRAINNUM);

	TrainW(num, w, PR_num);                                            //将w的位置传入指针，记录权值
	CString m_Hint = _T("提示：训练完成! 胜率： ");
	CString rate; rate.Format(_T("%7.2f"), w[PR_num]*100);
	m_Hint += rate+_T("%");
	SetDlgItemText(IDC_STATIC_HINT, m_Hint);
}
