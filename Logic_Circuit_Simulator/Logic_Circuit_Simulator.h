
// Logic_Circuit_Simulator.h : Logic_Circuit_Simulator ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CLogic_Circuit_SimulatorApp:
// �� Ŭ������ ������ ���ؼ��� Logic_Circuit_Simulator.cpp�� �����Ͻʽÿ�.
//

class CLogic_Circuit_SimulatorApp : public CWinApp
{
public:
	CLogic_Circuit_SimulatorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLogic_Circuit_SimulatorApp theApp;
