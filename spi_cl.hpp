//*******************************************************************
//*************** pico spi port *********** ****************************
//*************** 09/06/2021 *****************************************


#include "pico/binary_info.h"
#include "hardware/spi.h"

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
void init_SPI() {
//spi
	spi_init(SPI_PORT, 480 * 1000);
	gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
	gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
	gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
// Make the SPI pins available to picotool
	bi_decl(bi_3pins_with_func(PIN_MISO, PIN_MOSI,PIN_SCK, GPIO_FUNC_SPI));	
// Chip select is active-low, so we'll initialise it to a driven-high state
	gpio_init(PIN_CS);
	gpio_set_dir(PIN_CS, GPIO_OUT);
	gpio_put(PIN_CS, 1);
// Make the CS pin available to picotool
	bi_decl(bi_1pin_with_name(PIN_CS, "SPI CS"));	
		
}	
//*****************************************		
public:
//*****************************************	
//******** constructor **********************
spi_link(uint8_t sck=6,uint8_t mosi=7,uint8_t miso=4,uint8_t cs=5, spi_inst_t * port=spi0, uint8_t r_tx_data=0){
	PIN_SCK=sck;
	PIN_MOSI=mosi;
	PIN_MISO=miso;
	SPI_PORT=port;
	PIN_CS=cs;	
	repeated_tx_data=	r_tx_data;
	init_SPI();
}

//*****************************************
void spi_write(uint8_t *data,int size) {
	select_dev();	
	spi_write_blocking(SPI_PORT, data, size);
	//sleep_ms(10);
	deselect_dev();
  }	
 
//*****************************************
void spi_read(uint8_t *data,int size) {
	select_dev();		
	spi_read_blocking(SPI_PORT, repeated_tx_data,data, size);
	//sleep_ms(10);
	deselect_dev();	
  }	
  
 void select_dev() {
	gpio_put(PIN_CS, 0);
// Active low
 }

void deselect_dev() {
	gpio_put(PIN_CS, 1);
 }	
	
};
