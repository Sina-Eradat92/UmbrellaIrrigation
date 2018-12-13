 /* TCP IP transfer module (using sys/socket driver)
 *
 * Copyright (c) 2018  Umbrella Irrigation Software, Inc.
 * Copyright (c) 2018  Sina Eradat <sina.eradat.540@my.csun.edu>
 */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "TCP_Module.h"

//private var:
struct sockaddr_in address;
struct sockaddr_in serv_addr;
int sock = 0, valread;



int tcp_init(int port,char *ipadr){

	//check conection befor creating socket
	if((sock = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Socket creation error \n");
        	return -1;
    	}//end if

    //set up client protocall type and port 
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET6;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET6, ipadr, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  	
  	//Connect the client to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    return 0;
}//end 

int tcp_read(char *data){
	while(recv(sock,data,sizeof(data),0) <= 0){
		printf("Waiting for server\n");
	}
	return 0;
}

int tcp_write(char *data){
	if(send(sock,data,sizeof(data),0) < 0){
		printf("Faild to send\n");
		return -1;
	}
	return 0;
}

int tcp_xfer(char *data_Tx, char *data_RX){
	while(send(sock,data_Tx,sizeof(data_Tx),0) < 0){

	}
	while(recv(sock,data_RX,sizeof(data_RX),0) < 0){

	}
	return 0;
}//end xfer

