#pragma once
#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "stdafx.h"
#include "resource.h"
#include "CThreadServidor.h"
#include "CThreadConexao.h"

class CThreadServidor;
class CThreadConexao;

// class ligacao para gerir as ligaçoes aos clientes
class Ligacao
{
	CThreadConexao * m_thread;
	SOCKET m_socket;
public:
	Ligacao(CThreadConexao * thread, SOCKET socket) : m_thread(thread), m_socket(socket)
	{
		// iniciar a thread automaticamente quando o objecto é criado
		this->m_thread->Start();
	}

	~Ligacao()
	{
		this->m_thread->Abort();
		shutdown(this->m_socket, SD_SEND);
		closesocket(this->m_socket);
	}

	CThreadConexao * GetThread()
	{
		return this->m_thread;
	}

	SOCKET GetSocket()
	{
		return this->m_socket;
	}
};

// class CEditCtrl para ligar os controlos editbox aos atributos da classe
class CEditCtl : public CWindowImpl<CEditCtl, WTL::CEdit>
{
	BEGIN_MSG_MAP(CEditCtl)
	END_MSG_MAP()
};

class MainDialog : public CDialogImpl<MainDialog>, public CWinDataExchange<MainDialog>
{
public:
	// identifica que esta classe trata deste dialogo
	enum { IDD = IDD_MAINDIALOG };

	// construtor
	MainDialog();

	// destrutor
	virtual ~MainDialog();

	// vector de ligações
	std::vector<Ligacao *> ligacoes;
	int num_ligacoes;

	// apontador para a thread que corre o servidor
	CThreadServidor * m_pThreadServidor;

	// Atributos da classe que conectam aos controlos
	CEditCtl tb_conex_controlo;
	WTL::CString tb_conex_texto;
	int tb_conex_numero;

	CEditCtl tb_ip_controlo;
	WTL::CString tb_ip_texto;

	CEditCtl tb_porta_controlo;
	WTL::CString tb_porta_texto;
	int tb_porta_numero;

	CEditCtl tb_msg_controlo;
	WTL::CString tb_msg_texto;

	CEditCtl tb_motd_controlo;
	WTL::CString tb_motd_texto;

	CEditCtl tb_msg_servidor_controlo;
	WTL::CString tb_msg_servidor_conteudo;

	// Callbacks
	BEGIN_MSG_MAP(MainDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(ID_BTN_FECHAR, BN_CLICKED, OnBnClickedBtnFechar)
		COMMAND_HANDLER(IDC_BTN_LIGAR, BN_CLICKED, OnBnClickedBtnLigar)
		COMMAND_HANDLER(IDC_BTN_DESLIGAR, BN_CLICKED, OnBnClickedBtnDesligar)
		COMMAND_HANDLER(IDC_BTN_ENVIAR_MSG, BN_CLICKED, OnBnClickedBtnEnviarMsg)
		COMMAND_HANDLER(IDC_BTN_ACERCA, BN_CLICKED, OnBnClickedBtnAcerca)
	END_MSG_MAP()

	// Ligar os controlos aos atributos
	BEGIN_DDX_MAP(MainDialog)
		DDX_CONTROL(IDC_TB_CONEX, tb_conex_controlo)
		DDX_TEXT(IDC_TB_CONEX, tb_conex_texto)
		DDX_INT(IDC_TB_CONEX, tb_conex_numero)
		DDX_CONTROL(IDC_TB_IP, tb_ip_controlo)
		DDX_TEXT(IDC_TB_IP, tb_ip_texto)
		DDX_CONTROL(IDC_TB_PORTA, tb_porta_controlo)
		DDX_TEXT(IDC_TB_PORTA, tb_porta_texto)
		DDX_INT(IDC_TB_PORTA, tb_porta_numero)
		DDX_CONTROL(IDC_TB_MSG, tb_msg_controlo)
		DDX_TEXT(IDC_TB_MSG, tb_msg_texto)
		DDX_CONTROL(IDC_TB_MOTD, tb_motd_controlo)
		DDX_TEXT(IDC_TB_MOTD, tb_motd_texto)
		DDX_CONTROL(IDC_TB_MSG_SERVIDOR, tb_msg_servidor_controlo)
		DDX_TEXT(IDC_TB_MSG_SERVIDOR, tb_msg_servidor_conteudo)
	END_DDX_MAP()

	// métodos dos callbacks
	LRESULT OnInitDialog(HWND hwndFocus, LPARAM lParam);
	LRESULT OnBnClickedBtnFechar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnLigar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnDesligar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnEnviarMsg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnAcerca(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	// métodos da classe
	void EscreverMsg(LPTSTR msg);
	void IncrementarContador();
	void DecrementarContador();
	void AtualizarContador();
	void TerminarLigacao(SOCKET socket);
	void TerminarServidor();

};

#endif // !MAINDIALOG_H

