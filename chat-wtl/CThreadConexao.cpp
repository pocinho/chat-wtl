#include "stdafx.h"
#include "CThreadConexao.h"
#include "MainDialog.h"

CThreadConexao::CThreadConexao(MainDialog * md, SOCKET socket) : dlg(md), m_socket(socket)
{
	dlg->IncrementarContador();
}

CThreadConexao::~CThreadConexao()
{
// quando a thread termina, a execução pára
// limpar socket no vector de ligações
}

BOOL CThreadConexao::Initialize()
{
	return 0;
}

DWORD CThreadConexao::Run()
{
	// inicializar motd
	CT2CA pszConvertedAnsiString(dlg->tb_motd_texto);
	std::string motd("Message Of The Day: ");
	motd.append(pszConvertedAnsiString);
	motd.append("\n");

	// enviar motd quando o cliente se conecta
	send(m_socket, motd.c_str(), motd.size(), 0);

	// buffer de dados transmitidos
	char server_reply[2000];

	// numero de bytes enviados
	int resultado;

	do
	{
		resultado = recv(m_socket, server_reply, 2000, 0);

		if (IsAborted()) // servidor a desligar e a terminar ligações
			break;

		if (resultado == 0 || resultado == -1) // cliente a desconectar ligacao
		{
			dlg->TerminarLigacao(m_socket);
			break;
		}
		else
		{
			// ter a certeza que terminamos a string
			server_reply[resultado] = '\0';

			// Converter para wchar_t*
			size_t origsize = strlen(server_reply) + 1;
			const size_t newsize = 2000;
			size_t convertedChars = 0;
			wchar_t wcstring[newsize];
			mbstowcs_s(&convertedChars, wcstring, origsize, server_reply, _TRUNCATE);

			// apresentar mensagem
			dlg->EscreverMsg(wcstring);

			// encaminhar mensagem
			for each (auto const &ligacao in dlg->ligacoes)
				send(ligacao->GetSocket(), server_reply, resultado, 0);

		}
	} while (!IsAborted() && resultado > 0);

	return 0;
}
