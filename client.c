#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  /* netdb is necessary for struct hostent */

#define PORT 5000  /* server port */

#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
	char str[50];
    int sockfd, num;    /* files descriptors */
    char buf[MAXDATASIZE];    /* buf will store received text */
    struct hostent *he;    /* structure that will get information about remote host */
    struct sockaddr_in server;
    
    if (argc < 2)
    {
        printf("Usage: %s execte error\n",argv[0]);
        exit(1);
    }
    
    if((he=gethostbyname(argv[1]))==NULL)
    {
        printf("gethostbyname() error\n");
        exit(1);
    }
	printf("argv[2]:%s\n",argv[2]); 
    sprintf(str,"%s",argv[2]);
	if((sockfd=socket(AF_INET,SOCK_STREAM, 0))==-1)
    {
        printf("socket() error\n");
        exit(1);
    }
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server))==-1)
    {
        printf("connect() error\n");
        exit(1);
    }
	
	if((num=send(sockfd,str,strlen(str),0))==-1){
		printf("send() error\n");
		exit(1);
	}
	if((num=recv(sockfd,buf,MAXDATASIZE,0))==-1)
	{
		printf("recv() error\n");
		exit(1);
	}
	buf[num-1]='\0';
	printf("recv server message: %s\n",buf);
	close(sockfd);
	return 0;
}
