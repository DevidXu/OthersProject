
// ChessDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "IntroPage.h"

// CChessDlg 对话框
class CChessDlg : public CDialogEx
{
// 构造
public:
	CChessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHESS_DIALOG };

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
public:

public:
	CDC *pDC;
	RECT rtWnd;
	CBrush brush;
	int iWndWidth, iWndHeight;
	long hmWidth, hmHeight;
	CStatic m_Chessboard;
	IPicture* pPic;    //pPic为指向棋盘的IPicture指针
	int PR_num;        //计算的参数的量
	int player;        //判断先手还是后手
	double w[100];     //参数列表
	int board[5][5];   //棋盘状态参数
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedRadioFormer();
	afx_msg void OnBnClickedRadioLatter();
	afx_msg void OnBnClickedButtonIntro();
	afx_msg void OnStnClickedStaticChess();
	CString m_Hint;
	int m_Trainnum;
	afx_msg void OnBnClickedButtonTrain();
};
