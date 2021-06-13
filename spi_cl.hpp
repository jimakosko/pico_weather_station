#ifndef SPI_GUARD
#define SPI_GUARD 

//*******************************************************************
//*************** pico spi port *********** ****************************
//*************** 09/06/2021 *****************************************
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/binary_info.h"


class spi_link{
//*****************************************
//      SPI PINS
//*****************************************
uint32_t PIN_SCK;      //CLOCK
uint32_t PIN_MOSI;   //MOSI
uint32_t PIN_MISO;        //NOT CONNECTED
uint32_t PIN_CS;        //CHIP SELECT || SELECTED 0
uint32_t repeated_tx_data;
//*****************************************
//      SPI PORT
//*****************************************
spi_inst_t * SPI_PORT;       //SPI PORT 1

//*****************************************	
void init_SPI();

public:
//*****************************************	
//******** constructor **********************
spi_link(uint8_t sck=6,uint8_t mosi=7,uint8_t miso=4,uint8_t cs=5, spi_inst_t * port=spi0, uint8_t r_tx_data=0);
//*****************************************	
void spi_write(uint8_t *data,int size) ;
//*****************************************	
void spi_read(uint8_t *data,int size);
//*****************************************	
void select_dev();
 //*****************************************	
 void deselect_dev();
};
#endif 
