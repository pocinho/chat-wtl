#include "stdafx.h"
#include "CThreadCliente.h"
#include "MainDialog.h"

CThreadCliente::CThreadCliente(MainDialog * md, int porta, std::string ip) : dlg(md), m_porta(porta), m_ip(ip)
{
}

CThreadCliente::~CThreadCliente()
{
}

BOOL CThreadCliente::Initialize()
{
	return TRUE;
}

DWORD CThreadCliente::Run()
{
	Ligar();
	return 0;
}

void CThreadCliente::Ligar()
{
	struct sockaddr_in server;
	char server_reply[2000];
	int resultado;

	// é assim que se inicializa a estrutura wsa
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// é assim que se cria um socket para ligar ao servidor
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// é assim que se inicializa a ligação
	inet_pton(AF_INET, m_ip.c_str(), &server.sin_addr.s_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(m_porta);

	// Conectar ao servidor
	connect(server_socket, (struct sockaddr *)&server, sizeof(server));

	do
	{
		resultado = recv(server_socket, server_reply, 2000, 0);

		if (resultado == 0 || resultado == -1) // servidor a desligar
		{
			dlg->TerminarLigacao();
			break;
		}
		else
		{
			server_reply[resultado] = '\0';

			// Converter para wchar_t*
			size_t origsize = strlen(server_reply) + 1;
			const size_t newsize = 2000;
			size_t convertedChars = 0;
			wchar_t wcstring[newsize];
			mbstowcs_s(&convertedChars, wcstring, origsize, server_reply, _TRUNCATE);

			dlg->EscreverMsg(wcstring);
		}
	} while (!IsAborted() && resultado > 0);

	// limpar ligação

	shutdown(server_socket, SD_SEND);
	closesocket(server_socket);
}
