
// Crosshairs.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCrosshairsApp:
// �йش����ʵ�֣������ Crosshairs.cpp
//

class CCrosshairsApp : public CWinApp
{
public:
	CCrosshairsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCrosshairsApp theApp;