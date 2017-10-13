#pragma once
#include "stdafx.h"


class MainDialog;

class CThreadConexao : public CThreadImpl<CThreadConexao>
{
public:
	MainDialog * dlg;
	SOCKET m_socket;

	// construtor
	CThreadConexao(MainDialog * md, SOCKET socket);

	// destrutor
	virtual ~CThreadConexao();

	BOOL Initialize();

	// Run() corre automaticamente.
	DWORD Run();
};
