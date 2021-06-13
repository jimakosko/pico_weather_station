#include "spi_cl.hpp"

//*****************************************	
void spi_link::init_SPI() {
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
//******** constructor **********************
spi_link::spi_link(uint8_t sck,uint8_t mosi,uint8_t miso,uint8_t cs, spi_inst_t * port, uint8_t r_tx_data){
	PIN_SCK=sck;
	PIN_MOSI=mosi;
	PIN_MISO=miso;
	SPI_PORT=port;
	PIN_CS=cs;	
	repeated_tx_data=	r_tx_data;
	init_SPI();
}

//*****************************************
void spi_link::spi_write(uint8_t *data,int size) {
	select_dev();	
	spi_write_blocking(SPI_PORT, data, size);
	//sleep_ms(10);
	deselect_dev();
  }	
 
//*****************************************
void spi_link::spi_read(uint8_t *data,int size) {
	select_dev();		
	spi_read_blocking(SPI_PORT, repeated_tx_data,data, size);
	//sleep_ms(10);
	deselect_dev();	
  }	
  
 void spi_link::select_dev() {
	gpio_put(PIN_CS, 0);
// Active low
 }

void spi_link::deselect_dev() {
	gpio_put(PIN_CS, 1);
 }	
	
