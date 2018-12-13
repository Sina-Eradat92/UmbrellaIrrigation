/*
 * SPI transfer module (using spidev driver)
 *
 * Copyright (c) 2018  Umbrella Irrigation Software, Inc.
 * Copyright (c) 2018  Sina Eradat <sina.eradat.540@my.csun.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 */

#include <stdint.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include "SPI_Module.h"

// private var:
static int ret;
static int fd;
static uint8_t bits;
static uint32_t speed;
static uint16_t delay;

void spi_init(char *device, uint8_t mode, uint8_t num_bits, uint32_t num_speed, uint16_t num_delay){

	bits = num_bits;
	speed = num_speed;
	delay = num_delay;

	fd = open(device, O_RDWR);
	if (fd < 0){
		pabort("can't open device");
	}

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1){
		pabort("can't set spi mode");
	}

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1){
		pabort("can't get spi mode");
	}

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1){
		pabort("can't set bits per word");
	}

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1){
		pabort("can't get bits per word");
	}

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1){
		pabort("can't set max speed hz");
	}

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1){
		pabort("can't get max speed hz");
	}

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
	
	spi_transfer();
	close(fd);
}//end init 


void spi_transfer(){
		uint8_t tx[] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
		0xF0, 0x0D,
	};

	uint8_t rx[ARRAY_SIZE(tx)] = {0, };

	struct spi_ioc_transfer tr = {
	.tx_buf = (unsigned long)tx,
	.rx_buf = (unsigned long)rx,
	.len = ARRAY_SIZE(tx),
	.delay_usecs = delay,
	.speed_hz = speed,
	.bits_per_word = bits,
	.cs_change = 1,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1){
		pabort("can't send spi message");
	}//end if
	spi_print(rx);
}//end trans

void spi_print(uint8_t *data){
	int i;
	for(i = 0;i < ARRAY_SIZE(data);i++){
		if (!(i % 6)){
			puts("");
		}
		printf("%.2X ", data[i]);
	}//end for
	puts("");
}//end print

static void pabort(const char *s)
{
	perror(s);
	close(fd);
	abort();
}//end abort