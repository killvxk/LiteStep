/*
This is a part of the LiteStep Shell Source code.

Copyright (C) 1997-2002 The LiteStep Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef __LITESTEP_H
#define __LITESTEP_H

#include "../utility/common.h"
#include "../lsapi/lsapi.h"
#include "../utility/macros.h"

#include <comdef.h>

// Misc Helpers
#include "../lsapi/ThreadedBangCommand.h"
#include "StartupRunner.h"
#include "DataStore.h"
#include "RecoveryMenu.h"

//Managers
//#include "BangManager.h"
#include "ModuleManager.h"
#include "HookManager.h"
#include "MessageManager.h"

//Services
#include "DDEService.h"
#include "TrayService.h"


// RegisterShellHook flags
#define RSH_UNREGISTER	0
#define RSH_REGISTER	1
#define RSH_PROGMAN		2
#define RSH_TASKMAN		3


// Program Options
const LPCSTR szMainWindowClass = "TApplication";
const LPCSTR szMainWindowTitle = "LiteStep";

#define GWL_CLASSPOINTER	0

// Service Item Definitions
typedef HRESULT (*PFNCLASSFACTORY)(REFIID iid, void **ppvObject);
class ServiceItem
{
public:
	PFNCLASSFACTORY pfnFactory;
	IService** ppService;

	ServiceItem()
	{
		pfnFactory = NULL;
		ppService = NULL;
	};

	ServiceItem(PFNCLASSFACTORY pfnFactory, IService** ppService)
	{
		this->pfnFactory = pfnFactory;
		this->ppService = ppService;
	};

};

class CLiteStep
{
public:
	CLiteStep();
	~CLiteStep();

	HRESULT Start(LPCSTR pszAppPath, LPCSTR pszRcPath, HINSTANCE hInstance, BOOL bRunStartup);


	LRESULT ExternalWndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	static LRESULT CALLBACK InternalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void _Recycle();

	CHAR m_szAppPath[MAX_PATH];
	CHAR m_szRcPath[MAX_PATH];

	// Application instance
	HINSTANCE m_hInstance;

	BOOL m_bAppIsFullScreen; // = FALSE;		// Is there a full screen app active?

	// Windows
	HWND m_hMainWindow; // = NULL;

	// Shell hooks
	UINT WM_ShellHook; // = 0;

	//
	// Manager Related
	//
	ModuleManager* m_pModuleManager; // = NULL;
	//BangManager* gBangManager = NULL;
	DataStore *m_pDataStoreManager; // = NULL;
	MessageManager *m_pMessageManager; // = NULL;

	HRESULT _InitManagers();
	HRESULT _StartManagers();
	HRESULT _StopManagers();
	void _CleanupManagers();

	BOOL bHookManagerStarted; // = FALSE;

	HWND hTrayManager; //= NULL;

	//
	// Service Related
	//
	ServiceItem m_ServiceItems[2];
	int m_cxServiceItems;

	DDEService *m_pDDEService; // = NULL;
	TrayService *m_pTrayService; // = NULL;

	HRESULT _InitServices();
	HRESULT _StartServices();
	HRESULT _StopServices();
	void _CleanupServices();
};

#endif	// __LITESTEP_H





















