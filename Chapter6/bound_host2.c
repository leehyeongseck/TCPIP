#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char msg1[]="Hi!";
	char msg2[]="I'm another UDP host!";
	char msg3[]="Nice to meet you";

	struct sockaddr_in your_adr; // 목적지 주소 정보 
	socklen_t your_adr_sz;
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_DGRAM, 0);   // 비연결 지향형 소켓 생성 
	if(sock==-1)
		error_handling("socket() error");
	
	// 프로그램 실행 인자로 전달받은 목적지 주소정보로 할당 
	// 전달할 목적지 정보를 매 호출 시 마다 지정한다.
	memset(&your_adr, 0, sizeof(your_adr));
	your_adr.sin_family=AF_INET;
	your_adr.sin_addr.s_addr=inet_addr(argv[1]);
	your_adr.sin_port=htons(atoi(argv[2]));
	
	// sendto() 함수 3번 호출 
	// 프로그램 실행 때 마다 같은 목적지로 보낸다는 보장이 없기 때문에 위에서 목적지 주소정보를 할당받는다.
	sendto(sock, msg1, sizeof(msg1), 0, 
					(struct sockaddr*)&your_adr, sizeof(your_adr));
	sendto(sock, msg2, sizeof(msg2), 0, 
					(struct sockaddr*)&your_adr, sizeof(your_adr));
	sendto(sock, msg3, sizeof(msg3), 0, 
					(struct sockaddr*)&your_adr, sizeof(your_adr));
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

/*
root@my_linux:/home/swyoon/tcpip# gcc bound_host2.c -o host2
root@my_linux:/home/swyoon/tcpip# ./host2
Usage : ./host2 <IP> <port>
root@my_linux:/home/swyoon/tcpip# ./host2 127.0.0.1 9190
root@my_linux:/home/swyoon/tcpip# 
*/
