#pragma once


// CIntro �Ի���

class CIntro : public CDialogEx
{
	DECLARE_DYNAMIC(CIntro)

public:
	CIntro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIntro();

// �Ի�������
	enum { IDD = IDD_DIALOG_INTRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
