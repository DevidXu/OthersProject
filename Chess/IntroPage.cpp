// IntroPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chess.h"
#include "IntroPage.h"
#include "afxdialogex.h"


// CIntroPage �Ի���

IMPLEMENT_DYNAMIC(CIntroPage, CDialogEx)

CIntroPage::CIntroPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIntroPage::IDD, pParent)
{

}

CIntroPage::~CIntroPage()
{
}

void CIntroPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIntroPage, CDialogEx)
END_MESSAGE_MAP()


// CIntroPage ��Ϣ�������
