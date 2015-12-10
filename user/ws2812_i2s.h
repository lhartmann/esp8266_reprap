//Copyright 2015 <>< Charles Lohr, See LICENSE file.
//WS2812 sender that abuses the I2S interface on the WS2812.

#ifndef REPRAP_DMAIO_H
#define REPRAP_DMAIO_H

//Stuff that should be for the header:

#include <c_types.h>

//Parameters for the I2S DMA behaviour
#define I2SDMABUFCNT (    2) //Number of buffers in the I2S circular buffer
#define I2SDMABUFLEN (192*5) //Length of one buffer, in 32-bit words.
#define USE_REPRAP_DMAIO_INTERRUPTS

void ICACHE_FLASH_ATTR reprap_dmaio_init();

#endif

