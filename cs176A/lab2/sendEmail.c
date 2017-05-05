/*
* CS 176A Programming Assignment 3
*
* The command line arguments should be:
* ./EmailSender <recipient address>
*
* NOTE:
* 1- I would like you to hardcode the following:
*	a- Sender address: "MAIL FROM".
*	b- Message you are sending.
* 2- Pass the recipient address "RCPT TO" as a command line argument.
* 3- INCLUDE comments in the code to show what is going on (not too detailed).
* 4- INCLUDE a README file if something did not run properly. That will help you receive partial credit.
*
*/

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

#define SMTP_PORT 25
#define MAXLINE 1024 			// NOTE: Can be modified to any size you want.

char *Server_IP = "128.111.53.4"; 	// NOTE: IP of the mail server after running "nslookup -type=MX cs.ucsb.edu".  Hence you will need to change this value.

void main (int argc, char ** argv)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	char recipient_address[MAXLINE]; // "RCPT TO" address.
	char sender_address[MAXLINE];	 // "MAIL FROM" adress.
	char *temp;
	int n;
	
	if (argc != 2)
	{
		printf("usage: ./EmailSender <recipient address,\"RCPT TO\">\n");
		exit(0);
	}
	strcpy(recipient_address, argv[1]);
			
	/* Establish a TCP connection with the main server */
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serveraddr;

	bzero(&serveraddr,sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr(Server_IP);
	serveraddr.sin_port=htons(SMTP_PORT);
	
	connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	
	/* Read greeting from the server */
	read(sockfd, recvline, MAXLINE);
	printf("%s\n", recvline);	
	temp = strtok(recvline, " ");
	if (strcmp(temp, "220")!=0)
	{
		printf("220 reply ont received from server.\n");
		exit(0);
	}
	
	/* Send HELO command and get server response */
	strcpy(sendline, "HELO sxh19911230\r\n");
	printf("%s\n", sendline);
	write(sockfd, sendline, strlen(sendline));
	
	read(sockfd, recvline, MAXLINE);
	printf("%s\n", recvline);
	temp = strtok(recvline, " ");
	if (strcmp(temp, "250")!=0)
	{
		printf("250 reply not received from server.\n");
		exit(0);
	}
	
	// Send MAIL FROM command.
	strcpy(sender_address, "MAIL FROM: <sxh19911230@engineering.ucsb.edu>\r\n"); 	// NOTE: replace address with your own.
	write(sockfd, sender_address, strlen(sender_address));
	printf("%s\n", sender_address);
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = 0;
	printf("%s\n", recvline);
	// Send RCPT TO command.
	strcpy(sender_address, "RCPT TO: <");
	strcpy(&(sender_address[strlen(sender_address)]),recipient_address);
	strcpy(&(sender_address[strlen(sender_address)]),">\r\n"); 
	write(sockfd, sender_address, strlen(sender_address));
	printf("%s\n", sender_address);
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = 0;
	printf("%s\n", recvline);
	// Send DATA command.
	write(sockfd, "DATA\r\n", 7);
	printf("DATA\n\n");
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = 0;
	printf("%s\n", recvline);
	// Send message data.
	strcpy(sendline, "SUBJECT: Great To Meet You\r\nHi, Great to meet you.\r\n.\r\n");
	write(sockfd, sendline, strlen(sendline));
	printf("SUBJECT: Great To Meet You\nHi, Great to meet you.\n.\n");
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = 0;
	printf("%s\n", recvline);
	// Send QUIT command.
	strcpy(sendline, "QUIT\n");
	write(sockfd, sendline, strlen(sendline));
	printf("QUIT\n");
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = 0;
	printf("%s\n", recvline);
	exit(0);	
} 
 
