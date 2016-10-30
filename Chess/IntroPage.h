#pragma once


// CIntroPage 对话框

class CIntroPage : public CDialogEx
{
	DECLARE_DYNAMIC(CIntroPage)

public:
	CIntroPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIntroPage();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
