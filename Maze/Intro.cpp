// Intro.cpp : 实现文件
//

#include "stdafx.h"
#include "Maze.h"
#include "Intro.h"
#include "afxdialogex.h"


// CIntro 对话框

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


// CIntro 消息处理程序
