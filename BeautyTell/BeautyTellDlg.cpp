
// BeautyTellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BeautyTell.h"
#include "BeautyTellDlg.h"
#include "afxdialogex.h"
#include "Findface.h"
#include "SkinAnalysis.h"
#include "IntroPage.h"
#include "math.h"

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


// CBeautyTellDlg �Ի���



CBeautyTellDlg::CBeautyTellDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBeautyTellDlg::IDD, pParent)
	, iWndWidth(0)
	, iWndHeight(0)
	, hmWidth(0)
	, hmHeight(0)
	, FinishFind(false)
	, FaceNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBeautyTellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEST, m_test);
}

BEGIN_MESSAGE_MAP(CBeautyTellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILEPATH, &CBeautyTellDlg::OnBnClickedButtonFilepath)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CBeautyTellDlg::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_INTRO, &CBeautyTellDlg::OnBnClickedButtonIntro)
	ON_STN_CLICKED(IDC_STATIC_IMG, &CBeautyTellDlg::OnStnClickedStaticImg)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CBeautyTellDlg::OnBnClickedButtonRank)
END_MESSAGE_MAP()


// CBeautyTellDlg ��Ϣ�������

BOOL CBeautyTellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	FinishFind = false;     //����ȷ��ͷ���Ƿ���֣���������Ч
	pPic = NULL;
	SetDlgItemText(IDC_STATIC_INTRO, _T("��ѡ����Ҫ�����ͼƬ��   ��ѡ��Ů����Ƭ���ж�׼ȷ�ȸ��ߣ�"));
	FaceNum = 0;      //������Ŀ��ʼ��Ϊ0

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

CBeautyTellDlg::~CBeautyTellDlg()
{
}

void CBeautyTellDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBeautyTellDlg::OnPaint()
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
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBeautyTellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//���"����ͼƬ"��ť
void CBeautyTellDlg::OnBnClickedButtonFilepath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RECT rtWnd;
	CDC *pDC[5];
	for (int i = 0; i < 5; i++) pDC[i] = NULL;
	pDC[0] = GetDlgItem(IDC_STATIC_RANK1)->GetDC();
	pDC[1] = GetDlgItem(IDC_STATIC_RANK2)->GetDC();
	pDC[2] = GetDlgItem(IDC_STATIC_RANK3)->GetDC();
	pDC[3] = GetDlgItem(IDC_STATIC_RANK4)->GetDC();
	pDC[4] = GetDlgItem(IDC_STATIC_RANK5)->GetDC();
	for (int i = 0; i < 5; i++)
	{
		pDC[i]->GetWindow()->GetWindowRect(&rtWnd);      //�������ͼ��ʱ��Ӧ�ĳ��Ϳ�
		iWndWidth = rtWnd.right - rtWnd.left;
		iWndHeight = rtWnd.bottom - rtWnd.top;
		pDC[i]->FillSolidRect(0, 0, iWndWidth, iWndHeight, RGB(255, 255, 255));
	}
	ReleaseDC(*pDC);

	TCHAR szFilter[] = _T("JPEG�ļ�(*.jpg)|*.jpg|GIF�ļ�(*.gif)|*.gif|bmp�ļ�(*.bmp)|*.bmp|");  //���ù�����
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);       //�������򿪡��ļ���
	if (!IDOK == fileDlg.DoModal())                         //����򿪽����·������FilePath
		MessageBox(_T("���ļ�ʧ�ܣ�"), _T("��ʧ��"), MB_ICONWARNING);
	else
	{
		FilePath = fileDlg.GetPathName();

		for (int i = 0; i < 50; i++) WorkArea[i] = TRUE;     //�趨����ͷ������Ϊtrue

		//��ȡͼƬ����ʾ
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_STATIC_IMG);    //���ͼƬ�ؼ��ľ��
		pWnd->UpdateWindow();

		((CStatic*)GetDlgItem(IDC_STATIC_IMG))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CDC *pDC = NULL;
		pDC=GetDlgItem(IDC_STATIC_IMG)->GetDC(); //��ȡ�ؼ�DC
		OleLoadPicturePath(CComBSTR(FilePath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);   //��·����ȡ�ļ�
		if (NULL == pPic)
		{
			MessageBox(_T("���ļ�ʧ�ܣ�"),_T("��ʧ��"),MB_ICONWARNING);
			return;
		}
		// ��ȡͼ���͸�,ע������Ŀ�͸߲���ͼ��ķֱ���  
		pPic->get_Width(&hmWidth);
		pPic->get_Height(&hmHeight);

		//�޸��ļ�·����������FindFace.cppʹ��
		FilePath.Replace(_T("\\"), _T("\\\\"));

		// ��ȡ��ʾͼƬ���ڵĿ�Ⱥ͸߶�  ���˴�ΪӲ�Թ涨��
		RECT rtWnd;
		pDC->GetWindow()->GetWindowRect(&rtWnd);
		iWndWidth = 400;
		iWndHeight = 400;
		
		//�޸�ͼƬ�ؼ���С���ʺ�ͼ��
		if (hmWidth > hmHeight)
			iWndHeight = iWndWidth*hmHeight / hmWidth;
		else
			iWndWidth = iWndHeight*hmWidth / hmHeight;
		pWnd->MoveWindow(0, 0, iWndWidth, iWndHeight, true);

		//����ͼ��
		if (!(pPic->Render(*pDC, 0, 0, iWndWidth,iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
		{
			//�ͷ��ڴ�
			ReleaseDC(pDC);
			//�޸�ָʾ����
			SetDlgItemText(IDC_STATIC_INTRO, _T("���-ʶ��-��ť����ʼʶ����̡�"));
			return;
		}

		ReleaseDC(pDC);	
		return;
	}
}

//"ʶ��"��ť�Ŀ��ƴ���
void CBeautyTellDlg::OnBnClickedButtonFind()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pPic == NULL)
	{
		MessageBox(_T("����û�д�ͼƬ�ļ���"), _T("ʶ��ʧ��"), MB_ICONWARNING);
		return;
	}

	FindFace();
	FaceNum = objects->total;

	CString FindFilePath = _T("D://��Ƭ//FindFace.jpg");
	OleLoadPicturePath(CComBSTR(FindFilePath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);

	// ��ȡͼ���͸�,ע������Ŀ�͸߲���ͼ��ķֱ���  
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);

	CDC *pDC = NULL;
	pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC(); //��ȡ�ؼ�DC

	//��ʾͼƬ�����ڴ�СΪȫ�ֱ������ʲ��ֳ���ʡ��
	if (!(pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		ReleaseDC(pDC);
		FinishFind = true;
		SetDlgItemText(IDC_STATIC_INTRO, _T("����ϣ��ȡ������ѡ������"));
		SetDlgItemInt(IDC_EDIT_NUM,FaceNum);
		return;
	}

	ReleaseDC(pDC);
	return;
}

//����˵�� �Ի���
void CBeautyTellDlg::OnBnClickedButtonIntro()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CIntroPage Cintropage;
	Cintropage.DoModal();
	return;
}

//���������ѡ��
void CBeautyTellDlg::OnStnClickedStaticImg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ҵ�ͷ��ǰ�������Ϊ��Ч
	if (FinishFind == false) return;
	if (FaceNum == 0) return;

	//�ҳ��õ�����  p��Ӧ����λ�ã���pP��Ӧ�����ԭͼ�е�λ��
	POINT p,pP;
	GetCursorPos(&p);

	//����pDCΪͼƬ�ؼ��ľ������ÿؼ���������
	CDC *pDC = NULL;
	pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC();
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);

	//����ָ��ͼ���ָ��
	IplImage* img;
	const char* tmp = NULL;
	std::string tempname = (LPCSTR)CStringA(FilePath);
	tmp = tempname.c_str();
	img = cvLoadImage(tmp);

	//����������ԭͼ�еĶ�Ӧλ��
	pP.x = img->width*(p.x - rtWnd.left) / (rtWnd.right - rtWnd.left);
	pP.y = img->height*(p.y - rtWnd.top) / (rtWnd.bottom - rtWnd.top);

	//�ҳ��õ�������ͷ�񷽿�(ͨ�����뷨)
	int min = 2000, Findmin = 0, num = 0;     //minΪ������̾��룬numΪ������
	for (int i = 0; i < (objects ? objects->total : 0); i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);
		Findmin = (int)sqrt((r->x + r->width / 2 - pP.x)*(r->x + r->width / 2 - pP.x) + 
			(r->y + r->height / 2 - pP.y)*(r->y + r->height / 2 - pP.y));
		if (Findmin < min)
		{
			min = Findmin;
			num = i;
		}
	}

	WorkArea[num] = false;     //���ø�����Ϊ������

	//���»���ͼ��
	static CvScalar colors[] = {
		{ { 0, 0, 255 } }, { { 0, 128, 255 } }, { { 0, 255, 255 } }, { { 0, 255, 0 } },
		{ { 255, 128, 0 } }, { { 255, 255, 0 } }, { { 255, 0, 0 } }, { { 255, 0, 255 } }
	};
	for (int i = 0; i < (objects ? objects->total : 0); i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);
		if (WorkArea[i]==true)
		cvRectangle(
			img,
			cvPoint(r->x, r->y),
			cvPoint(r->x + r->width, r->y + r->height),
			colors[i % 8],
			4    //������ϸ
			);
	}

	//������FindFace.jpg�����
	cvSaveImage("D://��Ƭ//FindFace.jpg", img);
	CString FindFilePath = _T("D://��Ƭ//FindFace.jpg");
	OleLoadPicturePath(CComBSTR(FindFilePath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);

	//������Ŀ���٣����ڱ༭����ʾ
	FaceNum = FaceNum - 1;
	SetDlgItemInt(IDC_EDIT_NUM, FaceNum);

	//�ͷ��ڴ�
	ReleaseDC(pDC);
	cvReleaseImage(&img);
	return;
}

//���"����"��ť
void CBeautyTellDlg::OnBnClickedButtonRank()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (FinishFind == false)
	{
		MessageBox(_T("����û�д�ͼƬ�ļ���"), _T("����ʧ��"), MB_ICONWARNING);
		return;
	}

	SkinAnalysis();   //�õ�face[i].SkinPoint����

	//�����������飬�������򲢶�Ӧ����
	struct RANK
	{
		int point;
		int num;
	};
	RANK rank[50]; int Exc;
	for (int i = 0; i < objects->total; i++)
	{
		rank[i].point = face[i].SkinPoint;
		rank[i].num = i;
	}

	//ð������
	for (int i = 0; i < objects->total;i++)
	for (int j = i; j < objects->total; j++)
	{
		if (rank[i].point>rank[j].point)
		{
			Exc = rank[j].point; rank[j].point = rank[i].point; rank[i].point = Exc;
			Exc = rank[j].num; rank[j].num = rank[i].num; rank[i].num = Exc;
		}
	}

	//����·�������ͼƬ�ռ�ľ��
	IplImage* img;
	const char* tmp = NULL;
	std::string tempname = (LPCSTR)CStringA(FilePath);
	tmp = tempname.c_str();
	img = cvLoadImage(tmp);
	RECT rtWnd;
	CDC *pDC[5];
	for (int i = 0; i < 5; i++) pDC[i] = NULL;
	pDC[0] = GetDlgItem(IDC_STATIC_RANK1)->GetDC();
	pDC[1] = GetDlgItem(IDC_STATIC_RANK2)->GetDC();
	pDC[2] = GetDlgItem(IDC_STATIC_RANK3)->GetDC();
	pDC[3] = GetDlgItem(IDC_STATIC_RANK4)->GetDC();
	pDC[4] = GetDlgItem(IDC_STATIC_RANK5)->GetDC();
	
	//���ǰ������λ�ã������������
	int N = 0,n = 0;
	while ((N < 5) && (n < objects->total))
	{
		if (WorkArea[rank[n].num] == true)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(objects, rank[n].num);
			cvSetImageROI(img, cvRect(r->x, r->y, r->width, r->height));
			cvSaveImage("D://��Ƭ//Rank.jpg", img);        //���沿��Ϊ�������򱣴浽Rank.jpgͼ����
			OleLoadPicturePath(CComBSTR("D://��Ƭ//Rank.jpg"), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);   //��·����ȡ�ļ�
			
			pDC[N]->GetWindow()->GetWindowRect(&rtWnd);      //�������ͼ��ʱ��Ӧ�ĳ��Ϳ�
			iWndWidth = rtWnd.right - rtWnd.left;
			iWndHeight = rtWnd.bottom - rtWnd.top;
			pPic->get_Width(&hmWidth);
			pPic->get_Height(&hmHeight);

			pPic->Render(*pDC[N], 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
			n = n + 1; N = N + 1;     //����������������һ
		}
		else
			n = n + 1;
	}
	cvReleaseImage(&img);
	ReleaseDC(*pDC);
}
