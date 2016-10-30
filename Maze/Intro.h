#pragma once


// CIntro 对话框

class CIntro : public CDialogEx
{
	DECLARE_DYNAMIC(CIntro)

public:
	CIntro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIntro();

// 对话框数据
	enum { IDD = IDD_DIALOG_INTRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
