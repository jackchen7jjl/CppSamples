#include "CClient.h"

CClient::CClient(void)
{
}

CClient::CClient(SOCKET s, sockaddr_in addr)
{//��ʼ������Ա������  
	m_socket = s;
	m_addr = addr;
	m_hRecvThread = NULL;
	m_hSendThread = NULL;
	m_IsConnected = true;
	m_IsSendData = true;
	m_hEvent = CreateEvent(NULL, true, false, NULL);
	m_pRecvData = new char[1024];
	m_pSendData = new char[1024];
	memset(m_pSendData, 0, 1024);
	memset(m_pRecvData, 0, 1024);
}


CClient::~CClient(void)
{
	delete[]m_pRecvData;
	delete[]m_pSendData;
}

bool CClient::IsConnected()
{
	return m_IsConnected;
}


bool CClient::calc()
{
	time_t t;
	struct tm *local;
	char T[256];
	memset(T, 0, 256);
	t = time(NULL);
	local = localtime(&t);
	sprintf(T, "%d/%d/%d %d:%d:%d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	strcpy(m_pSendData, T);
	return true;
}

DWORD WINAPI CClient::sendThread(void*param)//�����߳���ں�����  
{
	std::cout << "���������߳̿�ʼ���У���" << std::endl;
	CClient *pClient = static_cast<CClient*>(param);//���CClient����ָ�롣�Ա���ݳ�Ա������  
	WaitForSingleObject(pClient->m_hEvent, INFINITE);//�ȴ����������߳�֪ͨ��</span><span style="font-size:18px;">  
	while (pClient->m_IsConnected)
	{
		while (pClient->m_IsSendData)//���Է������ݡ�  
		{
			std::cout << "�ȴ����������߳�֪ͨ����" << std::endl;
			//  
			//ResetEvent(pClient->m_hEvent);  
			int ret = send(pClient->m_socket, pClient->m_pSendData, 1024, 0);
			if (ret == SOCKET_ERROR)
			{
				int r = WSAGetLastError();
				if (r == WSAEWOULDBLOCK)
				{
					continue;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				std::cout << "������ͳɹ�����" << std::endl;
				pClient->m_IsSendData = false;
				break;
			}

		}
		Sleep(1000);//δ�յ�����֪ͨ��˯��1�롣  

	}
}

DWORD WINAPI CClient::recvThread(void*param)//���������߳���ں�����</span><span style="font-size:18px;">  
{
	std::cout << "���������߳̿�ʼ���У���" << std::endl;
	CClient *pClient = static_cast<CClient*>(param);
	while (pClient->m_IsConnected)
	{
		memset(pClient->m_pRecvData, 0, 1024);
		int ret = recv(pClient->m_socket, pClient->m_pRecvData, 1024, 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (r == WSAEWOULDBLOCK)
			{
				//std::cout<<"û���յ����Կͻ��˵����ݣ���"<<std::endl;  
				Sleep(20);
				continue;
			}
			else if (r == WSAENETDOWN)
			{
				std::cout << "���������̳߳��ִ���,�����жϣ�" << std::endl;
				break;
			}
			else
			{
				std::cout << "���������̳߳��ִ���" << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "��ϲ���յ����Կͻ��˵�����:" << pClient->m_pRecvData << std::endl;
			pClient->calc();
			std::cout << "֪ͨ�����̷߳��ͽ������" << std::endl;
			SetEvent(pClient->m_hEvent);
			pClient->m_IsSendData = true;
		}
	}
	return 0;
}
bool CClient::startRunning()//��ʼΪ���Ӵ������ͺͽ����̡߳�  
{
	m_hRecvThread = CreateThread(NULL, 0, recvThread, (void*)this, 0, NULL);//����static��Ա�������޷��������Ա����˴���thisָ�롣  
	if (m_hRecvThread == NULL)
	{
		return false;
	}
	m_hSendThread = CreateThread(NULL, 0, sendThread, (void*)this, 0, NULL);
	if (m_hSendThread == NULL)
	{
		return false;
	}
	return true;

}

bool CClient::DisConnect()
{
	m_IsConnected = false;//���պͷ����߳��˳�����Դ�ͷŽ�����Դ�ͷ��̡߳�  
	return true;
}