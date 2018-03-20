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
			else if (r == WSAEISCONN)//套接字原来已经连接！！  
			{
				break;
			}
			else
			{
				std::cout << "发生错误" << std::endl;
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
	Send((unsigned char *)msg.c_str(), msg.length());
}

void WinSocketClient::Send(unsigned char *data, int dataLen)
{
	while (_isConnected)//是否与服务器连接  
	{
		int ret = send(_clientSocket, (const char*)data, dataLen, 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (r == WSAEWOULDBLOCK)
			{
				std::cout << "数据发送失败！" << std::endl;
				Sleep(20);
				continue;
			}
			else
			{
				std::cout << "数据发送失败！" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "发送成功！！" << std::endl;
			break;
		}
	}
}

void WinSocketClient::TryReceiveData()
{
	char *recvBuff = new char[10240];
	int ret = recv(_clientSocket, recvBuff, 1024, 0);
	if (ret == SOCKET_ERROR)
	{
		int r = WSAGetLastError();
		if (r == WSAEWOULDBLOCK)
		{
			//std::cout<<"没有收到服务器返回的数据！！"<<std::endl;  
			//Sleep(10);
			return;
		}
		else if (r == WSAENETDOWN)
		{
			std::cout << "数据接收失败！" << std::endl;
			return;
		}
	}
	else
	{
		std::cout << "接收成功！" << std::endl;

		std::cout << recvBuff << std::endl;
	}
}
