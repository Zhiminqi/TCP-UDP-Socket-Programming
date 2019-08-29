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

#define PORT 18333
#define MAX_DATA_SIZE 1024
#define MAX_CLIENTS 5
#define IP_ADDRESS "127.0.0.1"

main()
{

	struct sockaddr_in server, client;
	unsigned int sockaddr_len = sizeof(struct sockaddr_in);
	int sock;
	int new_sockfd;
	int data[MAX_DATA_SIZE];
	int data_len;
	int count1;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}


	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	bzero(&server.sin_zero, 8);

	
	if((bind(sock, (struct sockaddr *)&server, sockaddr_len)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if((listen(sock, MAX_CLIENTS)) == -1)
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		printf("Server is running and ready to receive connections on port %d...\n",PORT);
		
		if((new_sockfd = accept(sock, (struct sockaddr *)&client, &sockaddr_len)) == -1)
		{
			perror("accept");
			continue;
		}
		
		data_len = 1;

		while(data_len)
		{
			data_len = recv(new_sockfd, data, MAX_DATA_SIZE, 0);

			if(data_len)
			{
				printf("Received number of %d from some client.\n", *data);
				printf("Computing the number of '1's in the binary representation...\n");
				count1 = 0;
				while(*data){
					(*data % 2 == 0)?:count1++;
					*data /= 2;					
				}
				printf("The number of '1's in the binary representation of %d is: %d\n",*data, count1);	

				if(send(new_sockfd, &count1, sizeof(count1), 0)==-1)
					perror("send");
				printf("Sent result back to that client.\n");
			}
			
		}
		close(new_sockfd);

	}
	
	
	close(sock);

}		

