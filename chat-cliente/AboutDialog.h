#pragma once
#ifndef ABOUTDIALOG_H_INCLUDED
#define ABOUTDIALOG_H_INCLUDED

#include "resource.h"

class AboutDialog : public CDialogImpl<AboutDialog>
{
public:
	enum { IDD = IDD_ABOUTDIALOG };

	BEGIN_MSG_MAP(AboutDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_HANDLER(IDC_ABOUTDIALOG_BTN_OK, BN_CLICKED, OnBnClickedOk)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


#endif // !ABOUTDIALOG_H_INCLUDED