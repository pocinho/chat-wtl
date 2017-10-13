#include "stdafx.h"
#include "MainDialog.h"

CAppModule _Module;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	// inicializar aplicacao multithreaded
	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	AtlInitCommonControls(ICC_WIN95_CLASSES);

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	// Iniciar o Dialog
	MainDialog d;
	int nRet = 0;

	nRet = d.DoModal();

	_Module.Term();
	::CoUninitialize();

	return nRet;
}