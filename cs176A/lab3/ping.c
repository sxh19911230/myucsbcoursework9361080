#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>

#define MAXLINE 1024

int main(int arg, char** argv) {
	
	char buffer[MAXLINE], server_addr[MAXLINE];
	int port, i, nBytes, nSent, nReceived;
	double elapsedTime;
	double max=0., min=3., sum=0.;
	struct timeval t1, t2;
	struct timeval timeout={3,0};
	
	if (arg != 3) {
		printf("Usage: %s <ip address> <port num>\n",argv[0]);
		exit(0);
	}
	
	
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serveraddr;

	bzero(&serveraddr,sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	serveraddr.sin_port=htons(atoi(argv[2]));
	
	setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
	
	nSent=0;nReceived=0;
	for(i=0; i<10; ++i) {
		++nSent;
		gettimeofday(&t1, NULL);
		sendto(sockfd,"a",2,0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		nBytes = recvfrom(sockfd,buffer,1024,0,NULL, NULL);
		gettimeofday(&t2, NULL);
		
		if (nBytes >= 0) {
			elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
			elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
			sum+=elapsedTime;
			if (max < elapsedTime) max = elapsedTime;
			if (min > elapsedTime) min = elapsedTime;
			
			++nReceived;
			
			printf("PING received from machine_name: seq#=%i time=%.2f ms\n", i, elapsedTime);
			sleep(1); 
		}
			
		else {
			printf("Timeout\n");
		}	
	}
	
	printf("--- %s ping statistics ---\n %i packets transmitted, %i received,\
	%i packet loss rtt min/avg/max = %.2f %.2f %.2f ms\n",argv[1], nSent,nReceived,
	100 - 100 * nReceived / nSent, min, sum/nReceived, max);
	
	return 0;
}
