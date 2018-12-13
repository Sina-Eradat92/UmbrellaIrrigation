/*
 * main module (using spi_module, bluetooth_module drivers)
 *
 * Copyright (c) 2018  Umbrella Irrigation Software, Inc.
 * Copyright (c) 2018  Sina Eradat <sina.eradat.540@my.csun.edu>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "SPI_Module.h"
#include "Bluetooth_Module.h"
#include "UmbrellaIrrigation.h"

int main(){
	printMenue();

	printf("Testing SPI...");
	init(SPI_DIVICE, SPI_DEF , UNUM_BITS_8, NUM_SPEED_MAX, NUM_DELAY_HALFSEC);
	
	

	return 0;
}//end main

void printMenue(){
	printf("\t\tUmbrella Irrigation(Inc)\n\t\t ver:0.1\n");
}//end print