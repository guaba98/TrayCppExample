
// TrayCppExample.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTrayCppExampleApp:
// �� Ŭ������ ������ ���ؼ��� TrayCppExample.cpp�� �����Ͻʽÿ�.
//

class CTrayCppExampleApp : public CWinApp
{
public:
	CTrayCppExampleApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTrayCppExampleApp theApp;