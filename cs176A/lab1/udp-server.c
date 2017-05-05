
/* Sample UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv)
{
   int sockfd,n,i,sum,computable,temp;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[1000];

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(atoi(argv[1]));
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   len = sizeof(cliaddr);
   n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
   sum = 0;
   computable = 1;
   for (i = 0; i < n; i++) {
      if (mesg[i] == 10) break;
      else if (mesg[i] - 48 >= 0 && mesg[i] - 48 < 10) sum += (mesg[i] - 48);
      else {
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
     sendto(sockfd,mesg,i+1,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
   }

   else sendto(sockfd,"Sorry, cannot compute!\n",24,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

}
