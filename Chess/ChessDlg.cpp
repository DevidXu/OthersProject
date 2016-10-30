
// ChessDlg.cpp : ʵ���ļ�
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


// CChessDlg �Ի���



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


// CChessDlg ��Ϣ�������

BOOL CChessDlg::OnInitDialog()
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
	CheckDlgButton(IDC_RADIO_FORMER,1);
	OnBnClickedRadioFormer();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChessDlg::OnPaint()
{
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


	pDC = GetDlgItem(IDC_STATIC_CHESS)->GetDC();
	pDC->GetWindow()->GetWindowRect(&rtWnd);                
	iWndWidth = rtWnd.right - rtWnd.left;
	iWndHeight = rtWnd.bottom - rtWnd.top;                   //��ȡͼƬ�ؼ����������

	OleLoadPicturePath(CComBSTR("D://��Ƭ//Chessboard.bmp"), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);                             //�������ͼ����������
	pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);

	for (int i = 0; i < PR_num; i++) w[i] = 0;
	player = 1;
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChessDlg::OnBnClickedButtonReset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
				brush.DeleteObject();   //������ɫ��ˢ
			}
			if (board[i][j] == 2)
			{
				brush.CreateSolidBrush(RGB(255, 0, 0));
				pDC->SelectObject(brush);
				pDC->Ellipse(width * x + width / 5, height * y + height / 5,
					width*x + width * 4 / 5, height*y + height * 4 / 5);
				brush.DeleteObject();   //������ɫ��ˢ
			}
		}
	}

}


void CChessDlg::OnBnClickedRadioFormer()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	player = 1;
}


void CChessDlg::OnBnClickedRadioLatter()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	player = 2;
}


void CChessDlg::OnBnClickedButtonIntro()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CIntroPage intropage;
	if (!intropage.DoModal())
		MessageBox(_T("˵��ҳ����"));
	else
		return;
}


void CChessDlg::OnStnClickedStaticChess()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POINT p;
	GetCursorPos(&p);
	int x = (p.x - rtWnd.left) * 3 / (rtWnd.right - rtWnd.left);
	int y = (p.y - rtWnd.top) * 3 / (rtWnd.bottom - rtWnd.top);    //��ȡ����Ӧ������λ��

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
		MessageBox(_T("��Ӯ�ˣ�"));
		return;
	}
	if ((int)CheckTheResult(&board[0][0]) + player == 3)
	{
		MessageBox(_T("�����ˣ�"));
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
			brush.DeleteObject();   //������ɫ��ˢ
		}
		if (board[i][j] == 2)
		{
			brush.CreateSolidBrush(RGB(255, 0, 0));
			pDC->SelectObject(brush);
			pDC->Ellipse(width * x + width / 5, height * y + height / 5,
				width*x + width * 4 / 5, height*y + height * 4 / 5);
			brush.DeleteObject();   //������ɫ��ˢ
		}
	}

	Sleep(200);

	if (CheckTheResult(&board[0][0]) == player)
	{
		MessageBox(_T("��Ӯ�ˣ�"));
		return;
	}
	if ((int)CheckTheResult(&board[0][0]) + player == 3)
	{
		MessageBox(_T("�����ˣ�"));
		return;
	}

}


void CChessDlg::OnBnClickedButtonTrain()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_STATIC_HINT, _T(""));
	UpdateData(true);
	int num = GetDlgItemInt(IDC_EDIT_TRAINNUM);

	TrainW(num, w, PR_num);                                            //��w��λ�ô���ָ�룬��¼Ȩֵ
	CString m_Hint = _T("��ʾ��ѵ�����! ʤ�ʣ� ");
	CString rate; rate.Format(_T("%7.2f"), w[PR_num]*100);
	m_Hint += rate+_T("%");
	SetDlgItemText(IDC_STATIC_HINT, m_Hint);
}
