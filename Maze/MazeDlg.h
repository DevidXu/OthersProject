
// MazeDlg.h : 头文件
//

#pragma once

#define Change_pace 3

// CMazeDlg 对话框
class CMazeDlg : public CDialogEx
{
// 构造
public:
	CMazeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAZE_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	int Width;
	int Height;
	CDC *pDC;   //图片控件的句柄
	CBrush brush;  //画刷
	int Lead_i, Lead_j;    //起始点的位置
	int Visit[103][103], Wall_hor[103][103], Wall_ver[103][103],Maze[103][103];
	int Way;
	bool game_begin;
	afx_msg void OnBnClickedButtonForm();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_Pace;
	int m_Tracker;
	int Tracker_x[503], Tracker_y[503];
	void Random_Tracker();   //用于生成开始时候各个追捕者的位置
	void Tracker_Position();     //用于推测下一步追捕者的方向
	void Success();
	afx_msg void OnBnClickedButtonAgain();
	afx_msg void OnBnClickedButtonIntro();
};
