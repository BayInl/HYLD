#pragma once
#include<winsock.h>
#include<cstdio>
#pragma comment(lib,"ws2_32.lib")
#pragma error(disable:4996)
using namespace std;
class Serve {
private:
	char m_serve_name[155];//������������
	char* m_serve_localip;//����������IP

	/*
	����ֵ��int��
			-1��ʾ��ʼ���׽��ֿ�ʧ��
			0��ʾ�׽��ֿ�汾�Ų���
			1��ʾ�����ɹ�
	���ܣ������׽���
	*/
	int initialization() {
		int i = -1;
		WORD w_req = MAKEWORD(2, 2);//�汾��
		WSADATA wsadata;
		
		//��ȡ������������IP��ַ(����)
		PHOSTENT hostinfo;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		gethostname(m_serve_name, sizeof(m_serve_name));
		hostinfo = gethostbyname(m_serve_name);
		m_serve_localip = inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[0]);
		
		int err;
		err = WSAStartup(w_req, &wsadata);
		if (err != 0) 
			return i; //��ʼ���׽��ֿ�ʧ�ܣ�
		
		else 
			++i;//��ʼ���׽��ֿ�ɹ���

		//���汾��
		if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
			WSACleanup();
			return i;//�׽��ֿ�汾�Ų�����
		}
		else 
			++i;//�׽��ֿ�汾�ŷ��ϣ�
		return i;
		
	}
	
	SOCKET s_server;
	SOCKET s_accept;
	SOCKADDR_IN server_addr;
	SOCKADDR_IN *accept_addr;

	char m_local_ip[100];
	char *m_return_mes;
	int m_number_client = 0;
	
public:
	Serve(const int& local_port, const int& number_client):m_number_client(number_client) {
		initialization();
		accept_addr = new SOCKADDR_IN[m_number_client];
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr(m_serve_localip);
		server_addr.sin_port = htons(local_port);
		s_server = socket(AF_INET, SOCK_STREAM, 0);
	}
	~Serve() {
		//�ر��׽���
		closesocket(s_server);
		closesocket(s_accept);

		//�ͷ�DLL��Դ
		WSACleanup();

		delete[]accept_addr;
	}
	bool set_status_listen() {//���ü���״̬
		if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			printf("�׽��ְ�ʧ�ܣ�");
			WSACleanup();
			return false;
		}
		else {}//�׽��ְ󶨳ɹ���
		char s[50];
		strcat(s, "1");
		if (listen(s_server, SOMAXCONN) < 0) {
			printf("���ü���״̬ʧ�ܣ�");
			WSACleanup();
			return false;
		}
		else {
			printf("��������ڼ������ӣ����Ժ�....\n");//���ü���״̬�ɹ���
			return true;
		}
	}
	bool handshake() {
		//������������
		for (int i = 0; i < m_number_client; i++) {
			int len = sizeof(SOCKADDR);
			s_accept = accept(s_server, (SOCKADDR*)&accept_addr[i], &len);
			if (s_accept == SOCKET_ERROR) {
				printf("%d������ʧ�ܣ�",i+1);
				WSACleanup();
				return false;
			}
			else {
				send_mes("Wait for other ");
				printf("%d�����ӳɹ���IP: %s,Port: %d\n", i + 1, inet_ntoa(accept_addr[i].sin_addr), ntohs(accept_addr[i].sin_port));
			}//���ӳɹ���
		}
		printf("�������ӽ�����׼����������");
		return true;
	}
	//����Ϊchar*����
	template <typename T>
	bool accept_mes(T& recv_buf) {//��������
		int recv_len = recv(s_accept, recv_buf, sizeof(T) / sizeof(*recv_buf), 0);
		if (recv_len < 0) 
			return false;//����ʧ�ܣ�
		return true;
		
	}
	
	//����Ϊchar*����
	template <typename T>
	bool send_mes(T &send_buf) {
		//sendto(s_accept, send_buf, sizeof(T) / sizeof(*send_buf),);
		int send_len = send(s_accept, send_buf, sizeof(T) / sizeof(*send_buf), 0);
		if (send_len < 0) {
			printf( "����ʧ�ܣ�");
			return false;
		}
		return true;
	}
	const char* get_serve_name() {
		return m_serve_name;
	}
	const char* get_local_ip() {
		return m_serve_localip;
	}
};
