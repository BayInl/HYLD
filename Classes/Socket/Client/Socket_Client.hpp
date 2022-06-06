#pragma once
#include<winsock.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
class Client {
private:
	
	char m_client_name[155];//�ͻ���������
	char* m_client_localip;//�ͻ��˱���IP
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

		//��ȡ��������ͻ���IP��ַ(����)
		PHOSTENT hostinfo;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		gethostname(m_client_name, sizeof(m_client_name));
		hostinfo = gethostbyname(m_client_name);
		m_client_localip = inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[0]);

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
	
	//���������׽��֣����������׽���
	SOCKET s_server;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;

public:
	Client(const char* serve_ip, const int& serve_port) {
		initialization();
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr(serve_ip);
		server_addr.sin_port = htons(serve_port);
		//�����׽���
		s_server = socket(AF_INET, SOCK_STREAM, 0);
	}
	~Client() {
		//�ر��׽���
		closesocket(s_server);
		//�ͷ�DLL��Դ
		WSACleanup();
	}
	//�����˽�������
	bool handshake() {
		if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			WSACleanup();
			return false;//����������ʧ�ܣ�
		}
		return true; //���������ӳɹ���
	}
	//����Ϊchar*����
	template <typename T>
	bool send_mes(T &send_buf) {//������Ϣ
		/*
		std::string &send_buf
		char* tem = new char[send_buf.size()];
		int send_len = send(s_server, tem, send_buf.size(), 0);
		send_buf = tem;
		*/
		int send_len = send(s_server, send_buf, sizeof(T) / sizeof(*send_buf), 0);
		if (send_len < 0) 
			return false;
		return true;
	}
	//����Ϊchar*����
	template <typename T>
	bool accept_mes(T &recv_buf) {//��������
		int recv_len = recv(s_server, recv_buf, sizeof(T) / sizeof(*recv_buf), 0);
		if (recv_len < 0)
			return false;
		return true;
	}
};
