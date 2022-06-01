#pragma once
#include<winsock.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
class Client {
private:
	
	char m_client_name[155];//客户端主机名
	char* m_client_localip;//客户端本地IP
	/*
	返回值：int型
	-1表示初始化套接字库失败
	0表示套接字库版本号不符
	1表示创建成功
	功能：创建套接字
	*/
	int initialization() {
		int i = -1;
		WORD w_req = MAKEWORD(2, 2);//版本号
		WSADATA wsadata;

		//获取主机名与客户端IP地址(本地)
		PHOSTENT hostinfo;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		gethostname(m_client_name, sizeof(m_client_name));
		hostinfo = gethostbyname(m_client_name);
		m_client_localip = inet_ntoa(*(struct in_addr*)hostinfo->h_addr_list[0]);

		int err;
		err = WSAStartup(w_req, &wsadata);
		if (err != 0)
			return i; //初始化套接字库失败！

		else
			++i;//初始化套接字库成功！

		//检测版本号
		if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
			WSACleanup();
			return i;//套接字库版本号不符！
		}
		else
			++i;//套接字库版本号符合！
		return i;

	}
	
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;

public:
	Client(const char* serve_ip, const int& serve_port) {
		initialization();
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr(serve_ip);
		server_addr.sin_port = htons(serve_port);
		//创建套接字
		s_server = socket(AF_INET, SOCK_STREAM, 0);
	}
	~Client() {
		//关闭套接字
		closesocket(s_server);
		//释放DLL资源
		WSACleanup();
	}
	//与服务端建立握手
	bool handshake() {
		if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			WSACleanup();
			return false;//服务器连接失败！
		}
		return true; //服务器连接成功！
	}
	//必须为char*类型
	template <typename T>
	bool send_mes(T &send_buf) {//发送信息
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
	//必须为char*类型
	template <typename T>
	bool accept_mes(T &recv_buf) {//接收数据
		int recv_len = recv(s_server, recv_buf, sizeof(T) / sizeof(*recv_buf), 0);
		if (recv_len < 0)
			return false;
		return true;
	}
};
