//#include<WINSOCK2.H>  
//#include<STDIO.H>  
//#include<iostream>  
//#include<cstring>  
//using namespace std;
//#pragma comment(lib, "ws2_32.lib")  
//
//int main()
//{
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA data;
//	if (WSAStartup(sockVersion, &data) != 0)
//	{
//		return 0;
//	}
//	while (true) {
//		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (sclient == INVALID_SOCKET)
//		{
//			printf("invalid socket!");
//			return 0;
//		}
//
//		sockaddr_in serAddr;
//		serAddr.sin_family = AF_INET;
//		serAddr.sin_port = htons(8888);
//		serAddr.sin_addr.S_un.S_addr = inet_addr("168.168.127.21");
//
//		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
//		{  //����ʧ��   
//			printf("connect error !");
//			closesocket(sclient);
//			return 0;
//		}
//
//		string data = "�ͻ�������abc";
//		const char * sendData;
//		sendData = data.c_str();   //stringתconst char*   
//								   //char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";  
//		send(sclient, sendData, strlen(sendData), 0);
//		//send()������������ָ����socket�����Է�����  
//		//int send(int s, const void * msg, int len, unsigned int flags)  
//		//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0  
//		//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error   
//
//		char recData[255];
//		int ret = recv(sclient, recData, 255, 0);
//		if (ret>0) {
//			recData[ret] = 0x00;
//			printf(recData);
//		}
//		closesocket(sclient);
//	}
//
//
//	WSACleanup();
//	return 0;
//
//}



//-------------------------------------------------------------������ģʽ------------------------------------------------------------------------------
//��Դ��http://blog.csdn.net/ithzhang/article/details/8274596

//#include<iostream>  
//#include"windows.h"  
//#pragma  comment (lib,"wsock32.lib")  
//SOCKET clientSocket;
//HANDLE hRecvThread;
//HANDLE hSendThread;
//bool IsConnected;
//char sendBuff[1024];
//char recvBuff[1024];
//HANDLE hEvent;
//HANDLE hSendEvent;
//bool InitMember();
//bool InitSocket();
//bool startConnect();
//DWORD WINAPI recvThread(void*param);
//DWORD WINAPI sendThread(void*param);
//
//
//int main(int argc, char**argv)
//{
//	InitMember();
//	InitSocket();
//	startConnect();
//	char buff[256];
//	while (IsConnected)
//	{
//		memset(buff, 0, 256);
//		std::cout << "��������ʽ��";
//		std::cin >> sendBuff;
//		if (!strcmp(buff, "exit"))
//		{
//			std::cout << "�����Ƴ���" << std::endl;
//			IsConnected = false;
//			HANDLE hHandleArray[2];
//			hHandleArray[0] = hRecvThread;
//			hHandleArray[1] = hSendThread;
//			SetEvent(hEvent);
//			WaitForMultipleObjects(2, hHandleArray, true, INFINITE);
//			getchar();
//			return 0;
//		}
//		else
//		{
//			SetEvent(hEvent);
//		}
//	}
//
//
//	return 0;
//}
////��ʼ���׽��֡�  
//bool InitSocket()
//{
//	WSAData wsadata;
//	WSAStartup(MAKEWORD(2, 2), &wsadata);
//	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSocket == INVALID_SOCKET)
//	{
//		return false;
//	}
//	unsigned long ul = 1;
//	ioctlsocket(clientSocket, FIONBIO, &ul);
//
//	sockaddr_in addr;
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(8888);
//	addr.sin_addr.S_un.S_addr = inet_addr("168.168.127.21");
//
//	while (true)
//	{
//		int ret = connect(clientSocket, (sockaddr*)&addr, sizeof(addr));
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (r == WSAEWOULDBLOCK || r == WSAEINVAL)
//			{
//				Sleep(20);
//				continue;
//			}
//			else if (r == WSAEISCONN)//�׽���ԭ���Ѿ����ӣ���  
//			{
//				break;
//			}
//			else
//			{
//				std::cout << "��������" << std::endl;
//				return false;
//			}
//		}
//		if (ret == 0)
//		{
//			break;
//		}
//	}
//	IsConnected = true;
//	return true;
//}
//
//bool InitMember()
//{
//	hSendThread = NULL;
//	hRecvThread = NULL;
//	hEvent = CreateEvent(NULL, true, false, NULL);
//	hSendEvent = CreateEvent(NULL, true, false, NULL);
//	IsConnected = false;
//	memset(recvBuff, 0, 1024);
//	memset(sendBuff, 0, 1024);
//	return true;
//}
////�������պͷ��������̡߳�  
//bool startConnect()
//{
//	hRecvThread = CreateThread(NULL, 0, recvThread, NULL, 0, NULL);
//	if (hRecvThread == NULL)
//	{
//		return false;
//	}
//	hSendThread = CreateThread(NULL, 0, sendThread, NULL, 0, NULL);
//	if (hSendThread == NULL)
//	{
//		return false;
//	}
//	return 0;
//}
////���������߳���ں�����  
//DWORD WINAPI recvThread(void*param)
//{
//	std::cout << "���ݽ����߳��ѿ�ʼ���У�" << std::endl;
//	while (IsConnected)
//	{
//		WaitForSingleObject(hSendEvent, INFINITE);
//		//ResetEvent(hSendEvent);  
//		int ret = recv(clientSocket, recvBuff, 1024, 0);
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (r == WSAEWOULDBLOCK)
//			{
//				//std::cout<<"û���յ����������ص����ݣ���"<<std::endl;  
//				Sleep(10);
//				continue;
//			}
//			else if (r == WSAENETDOWN)
//			{
//				std::cout << "���ݷ���ʧ�ܣ�" << std::endl;
//				return false;
//			}
//		}
//		else
//		{
//			std::cout << "���ճɹ���" << std::endl;
//
//			std::cout << recvBuff << std::endl;
//		}
//	}
//	return true;
//}
////���������߳���ں�����  
//DWORD WINAPI sendThread(void*param)
//{
//	std::cout << "���ݷ����߳��ѿ�ʼ���У���" << std::endl;
//
//	while (IsConnected)//�Ƿ������������  
//	{
//		WaitForSingleObject(hEvent, INFINITE);//�ȴ����������߳�֪ͨ��  
//		ResetEvent(hEvent);
//		int ret = send(clientSocket, sendBuff, 256, 0);
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (r == WSAEWOULDBLOCK)
//			{
//				std::cout << "���ݷ���ʧ�ܣ�" << std::endl;
//				Sleep(20);
//				continue;
//			}
//			else
//			{
//				std::cout << "���ݷ���ʧ�ܣ�" << std::endl;
//				break;
//			}
//		}
//		else
//		{
//			std::cout << "���ͳɹ�����" << std::endl;
//			SetEvent(hSendEvent);
//		}
//	}
//	return true;
//}


//-------------------------------------------------------------������ģʽ2���߳�------------------------------------------------------------------------------
#include<iostream>  
#include "WinSocketClient.h"
#include"windows.h"  

WinSocketClient socketClient;

int main(int argc, char**argv)
{
	bool result = socketClient.Connect("192.168.1.103",8888);

	if (!result)
		return 1;

	int id = 0;
	while (true)
	{
		std::string msg = "��Ϣ" + std::to_string(id++);

		socketClient.Send(msg);

		socketClient.TryReceiveData();

		Sleep(1000);
	}


	return 0;
}