/*
 * Bluetoth transfer module (using blueZ driver)
 *
 * Copyright (c) 2018  Umbrella Irrigation Software, Inc.
 * Copyright (c) 2018  Sina Eradat <sina.eradat.540@my.csun.edu>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include "Bluetooth_Module.h"

//private var:
inquiry_info *ii = NULL;
int dev_id;
int socket;
int max_rsp;
int num_rsp;

int bt_init(){

    int len;
    int flags;

    len  = 8;
    max_rsp = 255;

    //retrieve the resource number of the first available Bluetooth adapter
    dev_id = hci_get_route(NULL);

    //opens a Bluetooth socket with the specified resource number
    socket = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
       pabort("opening socket faild");
    }//end if

    //the cache of previously detected devices is flushed before performing the current inquiry
    //performs a Bluetooth device discovery and returns a list of detected devices and some basic information about them in the variable ii
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ){
        perror("hci_inquiry faild");
    }
    
    return 0;
}//end init

int bt_readData(){
    // read data from the client

}//end read

void deviseScan(){

    int i;
    char addr[19] = { 0 }; 
    char name[248] = { 0 };
  
    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(socket, &(ii+i)->bdaddr, sizeof(name),name, 0) < 0){
        strcpy(name, "[unknown]");
	}
        printf("%s  %s\n", addr, name);
    }

}//end device scan

int bt_clear(){
    free( ii );
    close( sock );
    return 0;
}

static void pabort(const char *s)
{
	perror(s);
	exit(1);
}//end abort

