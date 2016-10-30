
// BeautyTellDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "cv.h"
#include "highgui.h"

// CBeautyTellDlg 对话框
class CBeautyTellDlg : public CDialogEx
{
// 构造
public:
	CBeautyTellDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BEAUTYTELL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//软件实现
	CString FilePath;
public:
	afx_msg void OnBnClickedButtonFilepath();
	CEdit m_test;     //用于测试的编辑框
	CvSeq* objects;    //存储头像信息
	IPicture* pPic;    //pPic为指向原始图片的IPicture指针，用于输出图像
	bool WorkArea[50];
	afx_msg void OnBnClickedButtonFind();
	int iWndWidth;
	int iWndHeight;
	long hmWidth;
	long hmHeight;
	void FindFace();   //查找人脸
	void SkinAnalysis();

	struct FACE
	{
		int Brow, NoseL, NoseR;
		int SkinPoint;
	};

	FACE face[50];

	afx_msg void OnBnClickedButtonIntro();
	afx_msg void OnStnClickedStaticImg();
	~CBeautyTellDlg();
	bool FinishFind;
	int FaceNum;
	afx_msg void OnBnClickedButtonRank();
};
