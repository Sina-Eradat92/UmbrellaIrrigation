/*
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <linux/spi/spidev.h>
#include <stdint.h>


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define SPI_DIVICE  "/dev/spidev0.0"
#define SPI_DEF  SPI_MODE_0 
#define UNUM_BITS_8 (uint8_t)8
#define NUM_SPEED_MAX  (uint32_t)50000 
#define NUM_DELAY_HALFSEC  (uint16_t)500


static void pabort(const char *s);

void init(char *device, uint8_t mode, uint8_t num_bits, uint32_t num_speed, uint16_t num_delay);
void spi_transfer();
void spi_print(uint8_t *data);