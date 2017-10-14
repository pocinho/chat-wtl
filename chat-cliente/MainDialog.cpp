#include "stdafx.h"
#include "resource.h"
#include "MainDialog.h"
#include "CThreadCliente.h"
#include "AboutDialog.h"


MainDialog::MainDialog() : tc(nullptr)
{
}

MainDialog::~MainDialog()
{
	DeleteObject(m_hFont);
}

LRESULT MainDialog::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{
	CenterWindow();

	HICON hIcon = AtlLoadIconImage(IDI_CHATCLIENTE, LR_DEFAULTCOLOR, 32, 32);
	HICON hIconSmall = AtlLoadIconImage(IDI_SMALL, LR_DEFAULTCOLOR, 16, 16);

	SetIcon(hIcon, TRUE);
	SetIcon(hIconSmall, FALSE);

	// Seleccionar fonte Segoe UI Symbol para a caixa de texto chat
	m_hFont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI Symbol"));

	// Ligar os atributos da classe com os controlos
	DoDataExchange(false);

	tb_ip_controlo.AppendText(L"127.0.0.1");

	tb_porta_controlo.ReplaceSel(L"696", FALSE);

	tb_nome_controlo.SetFocus();

	tb_chat_controlo.SetFont(m_hFont, TRUE);

	tb_chat_controlo.AppendText(L"Emojis:\n");
	tb_chat_controlo.AppendText(L":) :( <3\n");
	tb_chat_controlo.AppendText(L":yinyang: :caveira: :radioactive:\n");
	tb_chat_controlo.AppendText(L":star: :up: :snowman: :check:\n");

	return 0;
}

void MainDialog::EscreverMsg(std::wstring msg)
{
	tb_chat_controlo.AppendText(msg.c_str());
	tb_chat_controlo.AppendText(L"\n");
}

void MainDialog::TerminarLigacao()
{
	tc = nullptr; // a thread toma conta de fechar a socket
	EscreverMsg(L"Desconectado do Servidor.");
	GetDlgItem(IDC_BTN_LIGAR).EnableWindow(TRUE);
}

LRESULT MainDialog::OnBnClickedBtnFechar(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (tc != nullptr)
	{
		// converter CString em ansi 
		CT2CA pszConvertedAnsiString1(tb_nome_texto);
		// converter em string, para concatenar e colocar o terminador '\0'
		std::string nome(pszConvertedAnsiString1);
		std::string msg(nome + " desconectou-se.");

		send(tc->server_socket, msg.c_str(), msg.size(), 0);
		tc->Abort();
		tc = nullptr;
	}

	WSACleanup();

	EndDialog(wID);

	return 0;
}


LRESULT MainDialog::OnBnClickedBtnLigar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	WTL::CString str;

	DoDataExchange(true);

	if (tb_nome_texto == "")
	{
		MessageBoxEx(NULL, L"Escreve um nome", L"Incompleto", NULL, NULL);
	}
	else
	{
		tb_chat_controlo.AppendText(L"A ligar servidor...\n");

		tb_chat_controlo.AppendText(L"IP: ");
		tb_chat_controlo.AppendText(tb_ip_texto);
		tb_chat_controlo.AppendText(L"\n");

		str.Format(_T("%d"), tb_porta_numero);
		tb_chat_controlo.AppendText(L"Porta: ");
		tb_chat_controlo.AppendText(str);
		tb_chat_controlo.AppendText(L"\n");

		CT2CA pszConvertedAnsiString(tb_ip_texto);
		std::string ip(pszConvertedAnsiString);

		tc = new CThreadCliente(this, tb_porta_numero, ip);
		tc->SetDeleteOnExit(); // thread termina se sair do âmbito (scope) em que é criada
		tc->Start();

		GetDlgItem(IDC_BTN_LIGAR).EnableWindow(FALSE);
	}
	return 0;
}


LRESULT MainDialog::OnBnClickedBtnEnviar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(true);

	if (tc != nullptr)
	{
		CT2CA pszConvertedAnsiString1(tb_nome_texto);
		std::string nome(pszConvertedAnsiString1);

		CT2CA pszConvertedAnsiString2(tb_msg_texto);
		std::string conteudo(pszConvertedAnsiString2);

		std::string msg(nome + ": " + conteudo);

		SOCKET server = tc->server_socket;

		send(server, msg.c_str(), msg.size(), 0);

		tb_msg_controlo.SetSel(0, -1);
		tb_msg_controlo.Clear();
	}

	return 0;
}


LRESULT MainDialog::OnBnClickedBtnDesligar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (tc != nullptr)
	{
		CT2CA pszConvertedAnsiString1(tb_nome_texto);
		std::string nome(pszConvertedAnsiString1);
		std::string msg(nome + " desconectou-se.");

		send(tc->server_socket, msg.c_str(), msg.size(), 0);
		tc->Abort();
		tc = nullptr;

		GetDlgItem(IDC_BTN_LIGAR).EnableWindow(TRUE);
	}
	return 0;
}


LRESULT MainDialog::OnBnClickedBtnAcerca(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	AboutDialog dlg;
	dlg.DoModal();

	return 0;
}
