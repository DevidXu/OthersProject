
// ChessDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "IntroPage.h"

// CChessDlg �Ի���
class CChessDlg : public CDialogEx
{
// ����
public:
	CChessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHESS_DIALOG };

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
public:

public:
	CDC *pDC;
	RECT rtWnd;
	CBrush brush;
	int iWndWidth, iWndHeight;
	long hmWidth, hmHeight;
	CStatic m_Chessboard;
	IPicture* pPic;    //pPicΪָ�����̵�IPictureָ��
	int PR_num;        //����Ĳ�������
	int player;        //�ж����ֻ��Ǻ���
	double w[100];     //�����б�
	int board[5][5];   //����״̬����
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedRadioFormer();
	afx_msg void OnBnClickedRadioLatter();
	afx_msg void OnBnClickedButtonIntro();
	afx_msg void OnStnClickedStaticChess();
	CString m_Hint;
	int m_Trainnum;
	afx_msg void OnBnClickedButtonTrain();
};
