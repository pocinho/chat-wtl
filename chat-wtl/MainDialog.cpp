#include "stdafx.h"
#include "resource.h"
#include "MainDialog.h"
#include "CThreadServidor.h"
#include "AboutDialog.h"

MainDialog::MainDialog() : m_pThreadServidor(nullptr), ligacoes(0)
{
}

MainDialog::~MainDialog()
{
}

LRESULT MainDialog::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{
	CenterWindow();

	HICON hIcon = AtlLoadIconImage(IDI_CHATWTL, LR_DEFAULTCOLOR, 32, 32);
	HICON hIconSmall = AtlLoadIconImage(IDI_SMALL, LR_DEFAULTCOLOR, 16, 16);

	SetIcon(hIcon, TRUE);
	SetIcon(hIconSmall, FALSE);

	// Ligar os atributos da classe com os controlos
	DoDataExchange(false);

	tb_ip_controlo.AppendText(L"multicast");

	tb_porta_controlo.ReplaceSel(L"696", 1);

	tb_motd_controlo.AppendText(L"Já foste!");

	tb_motd_controlo.SetFocus();

	return 0;
}


LRESULT MainDialog::OnBnClickedBtnFechar(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (m_pThreadServidor != nullptr)
	{
		TerminarServidor();
	}

	WSACleanup();

	EndDialog(wID);

	return 0;
}

LRESULT MainDialog::OnBnClickedBtnLigar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	WTL::CString str;

	DoDataExchange(true);

	tb_msg_servidor_controlo.AppendText(L"A ligar servidor...\n");

	tb_msg_servidor_controlo.AppendText(L"IP: ");
	tb_msg_servidor_controlo.AppendText(tb_ip_texto);
	tb_msg_servidor_controlo.AppendText(L"\n");

	str.Format(_T("%d"), tb_porta_numero);
	tb_msg_servidor_controlo.AppendText(L"Porta: ");
	tb_msg_servidor_controlo.AppendText(str);
	tb_msg_servidor_controlo.AppendText(L"\n");

	m_pThreadServidor = new CThreadServidor(this, tb_porta_numero);
	m_pThreadServidor->Start();

	GetDlgItem(IDC_BTN_LIGAR).EnableWindow(FALSE);

	return 0;
}


LRESULT MainDialog::OnBnClickedBtnDesligar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (m_pThreadServidor != nullptr)
	{
		TerminarServidor();
	}

	GetDlgItem(IDC_BTN_LIGAR).EnableWindow(TRUE);

	return 0;
}

void MainDialog::EscreverMsg(LPTSTR msg)
{
	tb_msg_servidor_controlo.AppendText(msg);
	tb_msg_servidor_controlo.AppendText(L"\n");
}

void MainDialog::IncrementarContador()
{
	num_ligacoes++;
	AtualizarContador();
}

void MainDialog::DecrementarContador()
{
	num_ligacoes--;
	if (num_ligacoes < 0)
		num_ligacoes = 0;
	AtualizarContador();
}

void MainDialog::AtualizarContador()
{
	DoDataExchange(true);

	CString str;
	str.Format(_T("%d"), num_ligacoes);

	tb_conex_controlo.SetSel(0, -1);
	tb_conex_controlo.ReplaceSel(str, FALSE);
}

void MainDialog::TerminarLigacao(SOCKET socket)
{
	for (int i = 0; i < ligacoes.size(); ++i)
	{
		if (ligacoes[i]->GetSocket() == socket)
		{
			// recuperar memória com delete, visto o objecto ter sido criado com new
			// por sua vez, o destrutor é chamado e o socket é limpo
			delete ligacoes[i];

			// remover esta ligação
			ligacoes.erase(ligacoes.begin() + i);
			break;
		}
	}
	EscreverMsg(L"Cliente desconectado.");
	DecrementarContador();
}

void MainDialog::TerminarServidor()
{
	// recuperar memória, pois os objectos são criados com new

	for (int i = 0; i < ligacoes.size(); ++i)
	{
		ligacoes[i]->GetThread()->Abort(); // enviar o sinal de abortar para a thread
		delete ligacoes[i]; // sockets são limpos no destrutor

							// os clientes recebem socket inválido e terminam a ligação
	}

	ligacoes.clear();

	num_ligacoes = 0;
	AtualizarContador();

	m_pThreadServidor->Abort();
	// temos de chamar Limpar() manualmente pois o accept esta ativo
	m_pThreadServidor->Limpar();
	m_pThreadServidor = nullptr;

	tb_msg_servidor_controlo.AppendText(L"Servidor parado.\n");
}


LRESULT MainDialog::OnBnClickedBtnEnviarMsg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(true);

	CT2CA pszConvertedAnsiString(tb_msg_texto);
	std::string strStd(pszConvertedAnsiString);

	std::string msg("Servidor: " + strStd);

	for (int i = 0; i < ligacoes.size(); ++i)
	{
		send(ligacoes[i]->GetSocket(), msg.c_str(), msg.size(), 0);
	}

	// Converter para wchar_t*
	size_t origsize = strlen(pszConvertedAnsiString) + 1;
	const size_t newsize = 2000;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, pszConvertedAnsiString, _TRUNCATE);

	std::wstring msg2(L"Servidor: ");
	msg2.append(wcstring);
	msg2.append(L"\n");

	tb_msg_servidor_controlo.AppendText(msg2.c_str());

	tb_msg_controlo.SetSel(0, -1);
	tb_msg_controlo.Clear();

	return 0;
}

LRESULT MainDialog::OnBnClickedBtnAcerca(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	AboutDialog dlg;
	dlg.DoModal();

	return 0;
}
