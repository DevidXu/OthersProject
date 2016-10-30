
// BeautyTellDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "cv.h"
#include "highgui.h"

// CBeautyTellDlg �Ի���
class CBeautyTellDlg : public CDialogEx
{
// ����
public:
	CBeautyTellDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BEAUTYTELL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//���ʵ��
	CString FilePath;
public:
	afx_msg void OnBnClickedButtonFilepath();
	CEdit m_test;     //���ڲ��Եı༭��
	CvSeq* objects;    //�洢ͷ����Ϣ
	IPicture* pPic;    //pPicΪָ��ԭʼͼƬ��IPictureָ�룬�������ͼ��
	bool WorkArea[50];
	afx_msg void OnBnClickedButtonFind();
	int iWndWidth;
	int iWndHeight;
	long hmWidth;
	long hmHeight;
	void FindFace();   //��������
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
