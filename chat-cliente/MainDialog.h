#pragma once
#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "stdafx.h"
#include "resource.h"
#include "CThreadCliente.h"

class CEditCtl : public CWindowImpl<CEditCtl, WTL::CEdit>
{
	BEGIN_MSG_MAP(CEditCtl)
	END_MSG_MAP()
};

class MainDialog : public CDialogImpl<MainDialog>, public CWinDataExchange<MainDialog>
{
public:

	// ligar esta classe ao dialogo
	enum { IDD = IDD_MAINDIALOG };

	// construtor
	MainDialog();

	// destrutor virtual, visto estarmos a herdar de um template
	virtual ~MainDialog();

	// apontador para a thread cliente que vai efetuar a ligação
	CThreadCliente * tc;

	// Atributos da classe que conectam aos controlos
	CEditCtl tb_nome_controlo;
	WTL::CString tb_nome_texto;

	CEditCtl tb_ip_controlo;
	WTL::CString tb_ip_texto;

	CEditCtl tb_porta_controlo;
	WTL::CString tb_porta_texto;
	int tb_porta_numero;

	CEditCtl tb_msg_controlo;
	WTL::CString tb_msg_texto;

	CEditCtl tb_chat_controlo;
	WTL::CString tb_chat_texto;

	HFONT hFont;

	// ligar callbacks aos métodos da classe
	BEGIN_MSG_MAP(MainDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER(IDC_BTN_FECHAR, BN_CLICKED, OnBnClickedBtnFechar)
		COMMAND_HANDLER(IDC_BTN_LIGAR, BN_CLICKED, OnBnClickedBtnLigar)
		COMMAND_HANDLER(IDC_BTN_ENVIAR, BN_CLICKED, OnBnClickedBtnEnviar)
		COMMAND_HANDLER(IDC_BTN_DESLIGAR, BN_CLICKED, OnBnClickedBtnDesligar)
		COMMAND_HANDLER(IDC_BTN_ACERCA, BN_CLICKED, OnBnClickedBtnAcerca)
	END_MSG_MAP()

	// Ligar os controlos aos atributos da classe
	BEGIN_DDX_MAP(MainDialog)
		DDX_CONTROL(IDC_TB_NOME, tb_nome_controlo)
		DDX_TEXT(IDC_TB_NOME, tb_nome_texto)
		DDX_CONTROL(IDC_TB_IP, tb_ip_controlo)
		DDX_TEXT(IDC_TB_IP, tb_ip_texto)
		DDX_CONTROL(IDC_TB_PORTA, tb_porta_controlo)
		DDX_TEXT(IDC_TB_PORTA, tb_porta_texto)
		DDX_INT(IDC_TB_PORTA, tb_porta_numero)
		DDX_CONTROL(IDC_TB_CHAT, tb_chat_controlo)
		DDX_TEXT(IDC_TB_CHAT, tb_chat_texto)
		DDX_CONTROL(IDC_TB_MSG, tb_msg_controlo)
		DDX_TEXT(IDC_TB_MSG, tb_msg_texto)
	END_DDX_MAP()

	// métodos da classe
	LRESULT OnInitDialog(HWND hwndFocus, LPARAM lParam);
	LRESULT OnBnClickedBtnFechar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnLigar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnEnviar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnDesligar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnAcerca(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void EscreverMsg(LPTSTR msg);
	void TerminarLigacao();
};

#endif // !MAINDIALOG_H

