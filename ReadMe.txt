=====================================================================
Data: 7/10/2017
Turma: TPSI-CS-0117
Formando: Paulo Pocinho
Formador: D�rio Quental

=====================================================================
PROJECTO

/bin-x64 -> execut�veis 64 bits
/bin-x86 -> execut�veis 32 bits
/chat-cliente -> c�digo do projecto cliente
/chat-wtl -> c�digo do projecto servidor
/wtl -> bibliotecas wtl
chat-wtl.sln -> solu��o de visual studio 2017
ReadMe.txt -> este ficheiro

=====================================================================
UTILIZA��O

Feito em Visual Studio 2017 com as bibliotecas ATL instaladas.

As bibliotecas WTL vem incluidas no projecto (pasta wtl).
S�o uma extens�o �s bibliotecas ATL da Microsoft. 

=====================================================================
FUNCIONAMENTO

Correr o execut�vel 'chat-servidor.exe' e clicar em ligar.
Correr clientes com o execut�vel 'chat-cliente.exe'.

O servidor escuta e serve nas liga��es de rede dispon�veis.
(Ver configura��es de placa de rede do computador.)

Para cada cliente, preencher nome, IP de rede onde o servidor se
encontra (IP atribuido a placa de rede ou ent�o 127.0.0.1)
e clicar em ligar.

Se a liga��o for feita com sucesso vemos o 'message of the day'.

Para sair da aplica��o clicar no bot�o 'Fechar'.

=====================================================================
BUGS / CAVEATS

Por motivos did�ticos, as mensagens t�m um limite de 2000 caracteres.


