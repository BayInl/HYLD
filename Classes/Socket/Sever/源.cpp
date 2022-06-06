#include<stdio.h>
#include"Socket_Sever.hpp"
int main()
{
	Serve myclass(1234,2);
	printf("%s\n%s", myclass.get_serve_name(), myclass.get_local_ip());
	myclass.set_status_listen();
	myclass.handshake();
	while (1) {
		char recv_mes[100];
		if (!myclass.accept_mes(recv_mes)) {
			printf("accept message error!");
			break;
		}
			
		if (!myclass.send_mes("test")) {
			printf("error!");
			break;
		}
			
	}
	return 0;
}