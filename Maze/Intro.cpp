// Intro.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Maze.h"
#include "Intro.h"
#include "afxdialogex.h"


// CIntro �Ի���

IMPLEMENT_DYNAMIC(CIntro, CDialogEx)

CIntro::CIntro(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIntro::IDD, pParent)
{

}

CIntro::~CIntro()
{
}

void CIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIntro, CDialogEx)
END_MESSAGE_MAP()


// CIntro ��Ϣ�������
