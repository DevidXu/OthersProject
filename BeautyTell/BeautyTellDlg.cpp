
// BeautyTellDlg.cpp : 实现文件
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


// CBeautyTellDlg 对话框



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


// CBeautyTellDlg 消息处理程序

BOOL CBeautyTellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	FinishFind = false;     //用于确定头像是否出现，否则点击无效
	pPic = NULL;
	SetDlgItemText(IDC_STATIC_INTRO, _T("请选择需要载入的图片：   （选择女性照片，判断准确度更高）"));
	FaceNum = 0;      //人脸数目初始化为0

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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBeautyTellDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBeautyTellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击"载入图片"按钮
void CBeautyTellDlg::OnBnClickedButtonFilepath()
{
	// TODO:  在此添加控件通知处理程序代码
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
		pDC[i]->GetWindow()->GetWindowRect(&rtWnd);      //计算输出图像时对应的长和宽
		iWndWidth = rtWnd.right - rtWnd.left;
		iWndHeight = rtWnd.bottom - rtWnd.top;
		pDC[i]->FillSolidRect(0, 0, iWndWidth, iWndHeight, RGB(255, 255, 255));
	}
	ReleaseDC(*pDC);

	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|GIF文件(*.gif)|*.gif|bmp文件(*.bmp)|*.bmp|");  //设置过滤器
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);       //创建“打开”文件框
	if (!IDOK == fileDlg.DoModal())                         //处理打开结果，路径存入FilePath
		MessageBox(_T("打开文件失败！"), _T("打开失败"), MB_ICONWARNING);
	else
	{
		FilePath = fileDlg.GetPathName();

		for (int i = 0; i < 50; i++) WorkArea[i] = TRUE;     //设定所有头像区域为true

		//读取图片并显示
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_STATIC_IMG);    //获得图片控件的句柄
		pWnd->UpdateWindow();

		((CStatic*)GetDlgItem(IDC_STATIC_IMG))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CDC *pDC = NULL;
		pDC=GetDlgItem(IDC_STATIC_IMG)->GetDC(); //获取控件DC
		OleLoadPicturePath(CComBSTR(FilePath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);   //从路径读取文件
		if (NULL == pPic)
		{
			MessageBox(_T("打开文件失败！"),_T("打开失败"),MB_ICONWARNING);
			return;
		}
		// 获取图像宽和高,注意这里的宽和高不是图像的分辨率  
		pPic->get_Width(&hmWidth);
		pPic->get_Height(&hmHeight);

		//修改文件路径名，供给FindFace.cpp使用
		FilePath.Replace(_T("\\"), _T("\\\\"));

		// 获取显示图片窗口的宽度和高度  （此处为硬性规定）
		RECT rtWnd;
		pDC->GetWindow()->GetWindowRect(&rtWnd);
		iWndWidth = 400;
		iWndHeight = 400;
		
		//修改图片控件大小以适合图像
		if (hmWidth > hmHeight)
			iWndHeight = iWndWidth*hmHeight / hmWidth;
		else
			iWndWidth = iWndHeight*hmWidth / hmHeight;
		pWnd->MoveWindow(0, 0, iWndWidth, iWndHeight, true);

		//绘制图像
		if (!(pPic->Render(*pDC, 0, 0, iWndWidth,iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
		{
			//释放内存
			ReleaseDC(pDC);
			//修改指示内容
			SetDlgItemText(IDC_STATIC_INTRO, _T("点击-识别-按钮，开始识别过程。"));
			return;
		}

		ReleaseDC(pDC);	
		return;
	}
}

//"识别"按钮的控制代码
void CBeautyTellDlg::OnBnClickedButtonFind()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pPic == NULL)
	{
		MessageBox(_T("您还没有打开图片文件！"), _T("识别失败"), MB_ICONWARNING);
		return;
	}

	FindFace();
	FaceNum = objects->total;

	CString FindFilePath = _T("D://照片//FindFace.jpg");
	OleLoadPicturePath(CComBSTR(FindFilePath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);

	// 获取图像宽和高,注意这里的宽和高不是图像的分辨率  
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);

	CDC *pDC = NULL;
	pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC(); //获取控件DC

	//显示图片，由于大小为全局变量，故部分程序省略
	if (!(pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		ReleaseDC(pDC);
		FinishFind = true;
		SetDlgItemText(IDC_STATIC_INTRO, _T("请点击希望取消或误选的区域"));
		SetDlgItemInt(IDC_EDIT_NUM,FaceNum);
		return;
	}

	ReleaseDC(pDC);
	return;
}

//操作说明 对话框
void CBeautyTellDlg::OnBnClickedButtonIntro()
{
	// TODO:  在此添加控件通知处理程序代码
	CIntroPage Cintropage;
	Cintropage.DoModal();
	return;
}

//点击消除误选框
void CBeautyTellDlg::OnStnClickedStaticImg()
{
	// TODO:  在此添加控件通知处理程序代码
	//若在找到头像前点击，视为无效
	if (FinishFind == false) return;
	if (FaceNum == 0) return;

	//找出该点坐标  p对应鼠标的位置，而pP对应鼠标在原图中的位置
	POINT p,pP;
	GetCursorPos(&p);

	//设置pDC为图片控件的句柄，获得控件属性数据
	CDC *pDC = NULL;
	pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC();
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);

	//创建指向图像的指针
	IplImage* img;
	const char* tmp = NULL;
	std::string tempname = (LPCSTR)CStringA(FilePath);
	tmp = tempname.c_str();
	img = cvLoadImage(tmp);

	//计算鼠标点在原图中的对应位置
	pP.x = img->width*(p.x - rtWnd.left) / (rtWnd.right - rtWnd.left);
	pP.y = img->height*(p.y - rtWnd.top) / (rtWnd.bottom - rtWnd.top);

	//找出该点所属的头像方块(通过距离法)
	int min = 2000, Findmin = 0, num = 0;     //min为假设最短距离，num为方框序
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

	WorkArea[num] = false;     //设置该区域为虚区域

	//重新绘制图像
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
			4    //线条粗细
			);
	}

	//保存至FindFace.jpg并输出
	cvSaveImage("D://照片//FindFace.jpg", img);
	CString FindFilePath = _T("D://照片//FindFace.jpg");
	OleLoadPicturePath(CComBSTR(FindFilePath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);

	//人脸数目减少，并在编辑框显示
	FaceNum = FaceNum - 1;
	SetDlgItemInt(IDC_EDIT_NUM, FaceNum);

	//释放内存
	ReleaseDC(pDC);
	cvReleaseImage(&img);
	return;
}

//点击"排序"按钮
void CBeautyTellDlg::OnBnClickedButtonRank()
{
	// TODO:  在此添加控件通知处理程序代码
	if (FinishFind == false)
	{
		MessageBox(_T("您还没有打开图片文件！"), _T("排序失败"), MB_ICONWARNING);
		return;
	}

	SkinAnalysis();   //得到face[i].SkinPoint数据

	//创建排序数组，用于排序并对应脸部
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

	//冒泡排序
	for (int i = 0; i < objects->total;i++)
	for (int j = i; j < objects->total; j++)
	{
		if (rank[i].point>rank[j].point)
		{
			Exc = rank[j].point; rank[j].point = rank[i].point; rank[i].point = Exc;
			Exc = rank[j].num; rank[j].num = rank[i].num; rank[i].num = Exc;
		}
	}

	//给定路径与五个图片空间的句柄
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
	
	//输出前五名的位置，若不够则不输出
	int N = 0,n = 0;
	while ((N < 5) && (n < objects->total))
	{
		if (WorkArea[rank[n].num] == true)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(objects, rank[n].num);
			cvSetImageROI(img, cvRect(r->x, r->y, r->width, r->height));
			cvSaveImage("D://照片//Rank.jpg", img);        //将面部作为特征区域保存到Rank.jpg图像中
			OleLoadPicturePath(CComBSTR("D://照片//Rank.jpg"), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);   //从路径读取文件
			
			pDC[N]->GetWindow()->GetWindowRect(&rtWnd);      //计算输出图像时对应的长和宽
			iWndWidth = rtWnd.right - rtWnd.left;
			iWndHeight = rtWnd.bottom - rtWnd.top;
			pPic->get_Width(&hmWidth);
			pPic->get_Height(&hmHeight);

			pPic->Render(*pDC[N], 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
			n = n + 1; N = N + 1;     //画完后对面人脸数加一
		}
		else
			n = n + 1;
	}
	cvReleaseImage(&img);
	ReleaseDC(*pDC);
}
