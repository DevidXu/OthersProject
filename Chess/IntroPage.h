#pragma once


// CIntroPage �Ի���

class CIntroPage : public CDialogEx
{
	DECLARE_DYNAMIC(CIntroPage)

public:
	CIntroPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIntroPage();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
