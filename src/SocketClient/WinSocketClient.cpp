#include "WinSocketClient.h"
#include <iostream>

bool WinSocketClient::Connect(std::string serverIP, WORD serverPort)
{
	WSAData wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_clientSocket == INVALID_SOCKET)
	{
		return false;
	}
	unsigned long ul = 1;
	ioctlsocket(_clientSocket, FIONBIO, &ul);

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serverPort);
	addr.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str());

	while (true)
	{
		int ret = connect(_clientSocket, (sockaddr*)&addr, sizeof(addr));
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (r == WSAEWOULDBLOCK || r == WSAEINVAL)
			{
				Sleep(20);
				continue;
			}
			else if (r == WSAEISCONN)//�׽���ԭ���Ѿ����ӣ���  
			{
				break;
			}
			else
			{
				std::cout << "��������" << std::endl;
				return false;
			}
		}
		if (ret == 0)
		{
			break;
		}
	}
	_isConnected = true;
	return true;
}

void WinSocketClient::Send(std::string msg)
{
	
}

void WinSocketClient::Send(unsigned char *data, int dataLen)
{
	while (_isConnected)//�Ƿ������������  
	{
		int ret = send(_clientSocket, (const char*)data, dataLen, 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (r == WSAEWOULDBLOCK)
			{
				std::cout << "���ݷ���ʧ�ܣ�" << std::endl;
				Sleep(20);
				continue;
			}
			else
			{
				std::cout << "���ݷ���ʧ�ܣ�" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "���ͳɹ�����" << std::endl;
			break;
		}
	}
}

void WinSocketClient::TryReceiveData()
{

}
