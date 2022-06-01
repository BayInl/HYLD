#include"Socket_Client.hpp"
#include<cstdio>
int main() {
	Client myclass("192.168.101.32",1234);
	if(myclass.handshake())
		printf("Handshake Successful\n");
	else
		printf("Handshake Failed\n");
	while (1) {
		//std::string str="Hello!";
		char recv_mes[100];
		if (myclass.accept_mes(recv_mes)) {
			printf("%s", recv_mes);
			myclass.send_mes("Hello!");
		}
		 else {
			printf("error");
			 break;
		 }	 
	}
	return 0;
}