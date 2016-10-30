
// MazeDlg.h : ͷ�ļ�
//

#pragma once

#define Change_pace 3

// CMazeDlg �Ի���
class CMazeDlg : public CDialogEx
{
// ����
public:
	CMazeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAZE_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	int Width;
	int Height;
	CDC *pDC;   //ͼƬ�ؼ��ľ��
	CBrush brush;  //��ˢ
	int Lead_i, Lead_j;    //��ʼ���λ��
	int Visit[103][103], Wall_hor[103][103], Wall_ver[103][103],Maze[103][103];
	int Way;
	bool game_begin;
	afx_msg void OnBnClickedButtonForm();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_Pace;
	int m_Tracker;
	int Tracker_x[503], Tracker_y[503];
	void Random_Tracker();   //�������ɿ�ʼʱ�����׷���ߵ�λ��
	void Tracker_Position();     //�����Ʋ���һ��׷���ߵķ���
	void Success();
	afx_msg void OnBnClickedButtonAgain();
	afx_msg void OnBnClickedButtonIntro();
};
