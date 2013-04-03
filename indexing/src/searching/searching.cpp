#include<iostream>

#include "searching_algorim.h"
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
using namespace std;


int main(int argc,char** argv)
{

	
	//cout<<query.size()<<endl;
	//start a http server 
	int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    char recvBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9998); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    cout<<"start searching service...listen to 9998"<<endl;
    // while(1)
    // {
    //     connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
    //    	//if((numbytes = recv(connfd,recvBuff,sizeof(recvBuff),0))!=-1)
    //    	{
    //    		//cout<<"recv:"<<recvBuff<<endl;
    //    		ticks = time(NULL);
	   //      snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
	   //      write(connfd, sendBuff, strlen(sendBuff)); 
    //    	}
        

    //     close(connfd);
    //     sleep(1);
    //  }
	SearchingAlgorim demo;
	demo.do_searching("the");
	return 0;
}
