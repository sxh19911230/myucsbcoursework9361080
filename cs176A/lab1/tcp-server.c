//Originally from http://www.cs.ucsb.edu/~almeroth/classes/W01.176B/hw2/examples/tcp-server.c
//Edited by Xianghong Sun

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv)
{
   int listenfd,connfd,n,i,sum,computable,temp;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   pid_t     childpid;
   char mesg[1000];

   if (argc != 2)
   {
      printf("usage:  server <Port Number>\n");
      exit(1);
   }

   listenfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(atoi(argv[1]));
   bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   listen(listenfd,1024);

   clilen=sizeof(cliaddr);
   connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

   close (listenfd);

   n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
   sum = 0;
   computable = 1;
   for (i = 0; i < n; i++) {
      if (mesg[i] == 10) break;
      else if (mesg[i] - 48 >= 0 && mesg[i] - 48 < 10) sum += (mesg[i] - 48);
      else {
        //printf("%i\n",mesg[i]);
        computable = 0;
        break;
      }
   }

   if (computable) {
     i = 0;
     while (sum >= 10) {
       sprintf(&mesg[i], "%d", sum);
       i = strlen(mesg);
       mesg[i] = ' ';
       i += 1;
       temp = 0;
       while (sum) {
         temp += sum % 10;
         sum /=10;
       }
       sum = temp;
     }
     sprintf(&mesg[i], "%d", sum);
     i = strlen(mesg);
     mesg[i] = '\n';
     mesg[i+1] = '\0';
     sendto(connfd,mesg,i+1,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   }
   else sendto(connfd,"Sorry, cannot compute!\n",24,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   //printf("-------------------------------------------------------\n");
   //mesg[n] = 0;
   //printf("Received the following:\n");
   //printf("%s",mesg);
   //printf("-------------------------------------------------------\n");
         
      close(connfd);
}
