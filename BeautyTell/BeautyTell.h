
// BeautyTell.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBeautyTellApp: 
// �йش����ʵ�֣������ BeautyTell.cpp
//

class CBeautyTellApp : public CWinApp
{
public:
	CBeautyTellApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBeautyTellApp theApp;