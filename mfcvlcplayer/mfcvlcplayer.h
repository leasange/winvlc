
// mfcvlcplayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfcvlcplayerApp: 
// �йش����ʵ�֣������ mfcvlcplayer.cpp
//

class CmfcvlcplayerApp : public CWinApp
{
public:
	CmfcvlcplayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfcvlcplayerApp theApp;