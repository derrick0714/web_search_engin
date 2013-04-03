#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char sendBuff[1024];
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    
    int offset = 0;
    char c=' ';
    cout<<argv[0]<<endl;
    for( int i = 1 ; i < argc; i++)
    {
        memcpy(sendBuff+offset, argv[i], strlen(argv[i]));
        offset+=strlen(argv[i]);
        if(i != argc- 1)
        {
             memcpy(sendBuff+offset, &c, 1);
             offset+=1;
        }
    }
    sendBuff[offset]='\0';
    //cout<<sendBuff<<endl;
    

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9888); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    write(sockfd, sendBuff, strlen(recvBuff));
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}