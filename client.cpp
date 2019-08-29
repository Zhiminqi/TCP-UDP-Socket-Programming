#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 18333
#define MAX_DATA_SIZE 1024
#define IP_ADDRESS "127.0.0.1"

using namespace std;

int main()
{
	struct sockaddr_in client_addr;
	int sock;
	int num;
	int buf[MAX_DATA_SIZE];

	cout << "please provide an integer in the range [0,2147483647]:\n";
	cin >> num;
	

	if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	client_addr.sin_family =AF_INET;
	client_addr.sin_port = htons(PORT);
	client_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	bzero(&(client_addr.sin_zero), 8);

	if(connect(sock,(struct sockaddr *)&client_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect");
		exit(1);	
	}

	if(send(sock, &num, sizeof(num), 0) ==-1)
	{
		perror("send");
		exit(1);
	}

	printf("Sent %d to Server on port: %d\n", num, PORT);

	if((recv(sock, buf, MAX_DATA_SIZE, 0)) == -1)
	{
		perror("recv");
		exit(1);
	}

	printf("Received the following result from server:%d \n", *buf);	
	printf("Done!\n");
	
	close(sock);
	return 0;

}

























