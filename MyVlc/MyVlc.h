
// MyVlc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyVlcApp:
// �йش����ʵ�֣������ MyVlc.cpp
//

class CMyVlcApp : public CWinAppEx
{
public:
	CMyVlcApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyVlcApp theApp;