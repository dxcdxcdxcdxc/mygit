#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <process.h>
#include "CBlockingSocket.h"


using namespace std;

DWORD WINAPI serverthread(LPVOID lpParameter)
{
	CBlockingSocket *cs = (CBlockingSocket *)lpParameter;
	CBlockingSocket ClientSocket = *cs;//用局部变量保存线程传进来的地址传递的参数，防止主线程中socket被改写。

	BYTE filename[100] = { 0 };
	if (ClientSocket.Read(filename, 100) != -1)//recv()
	{
		cout << "  File requested from the client: " << filename << endl;
		ifstream infile((char *)filename, ios::in | ios::binary);

		infile.seekg(0, ios::end);
		int fileLength = infile.tellg();
		infile.seekg(0, ios::beg);
		bool flag = true;
		if (!infile)
		{
			cout << "Open file failed!" << endl;
			flag = false;
		}
		else
		{
			BYTE file[201] = { 0 };
			while (fileLength >= 200)//循环发送长度为200的内容
			{
				infile.read((char *)file, 200);
				file[200] = '\0';//字符串结束标记
				flag = ClientSocket.Send(file, 200);
				fileLength -= 200;
			}
			infile.read((char *)file, fileLength);
			file[fileLength] = '\0';
			flag = ClientSocket.Send(file, fileLength);
		}
		if (flag)
		{
			cout << "  Send file back to the client: " << filename << endl;
		}
		else
		{
			cout << " Send file failed!" << endl;
		}
	}

	ClientSocket.Close();
	return 0;
}



int main(int argc, char *argv[])
{

	
	if (argc != 2)
	{
		cout << "Server.exe 8888" << endl;
		return 1;
	}

	CBlockingSocket ListenSocket;//实例化一个类
	CBlockingSocket::Initialize();
	ListenSocket.HintsAndResult(NULL, argv[1]);
	ListenSocket.Open();//创建一个socket
	ListenSocket.Bind();//绑定一个socket
	ListenSocket.Listen(argv[1]);
	cout << "listening..." <<  endl;
	while (1)
	{
		cout << "Waiting for a connection…" << endl;

		struct sockaddr client_addr;
		struct sockaddr_in client_addrin;
		CBlockingSocket ClientSocket = ListenSocket.Accept(client_addr);
		memcpy(&client_addrin, &client_addr, sizeof(client_addr));
		cout << "Accepted connection from " << inet_ntoa(client_addrin.sin_addr) << endl;
		HANDLE server;
		server = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)serverthread, &ClientSocket, 0, NULL);

	}
    ListenSocket.Close();
	CBlockingSocket::Cleanup();
	return 0;
}

