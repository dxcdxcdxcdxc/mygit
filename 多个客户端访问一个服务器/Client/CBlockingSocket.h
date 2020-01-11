#include <WinSock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class CBlockingSocket
{
private:
	SOCKET m_socket;
public:
	CBlockingSocket();  // create socket
	virtual		~CBlockingSocket();
	BOOL		Open(const char *ip, const char *port);  // connect socket
	BOOL		Close();  // close socket
	BOOL		Listen(const char *port);  // listen socket
	BOOL		Accept();  // accpet the client socket
	BOOL		Send(BYTE *s, UINT count);  // send package
	INT			Read(BYTE *s, UINT count);  // receive package
	INT         Recv(char *recvbuf, int recvbuflen);
	static void Cleanup();
};


