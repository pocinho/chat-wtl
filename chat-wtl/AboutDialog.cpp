#include "stdafx.h"
#include "AboutDialog.h"

LRESULT AboutDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CenterWindow();

	HICON hIcon = AtlLoadIconImage(IDI_CHATWTL, LR_DEFAULTCOLOR, 32, 32);
	HICON hIconSmall = AtlLoadIconImage(IDI_SMALL, LR_DEFAULTCOLOR, 16, 16);

	SetIcon(hIcon, TRUE);
	SetIcon(hIconSmall, FALSE);

	return TRUE;    // deixar o sistema colocar foco
}

LRESULT AboutDialog::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDCANCEL);
	return 0;
}

LRESULT AboutDialog::OnBnClickedOk(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}