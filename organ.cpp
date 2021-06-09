#include <iostream>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "led.hpp"
#include "i2c_cl.hpp"
#include "bmp180.hpp"
#include "spi_cl.hpp"
#include "n5110_lcd.hpp"


int main(){
		stdio_init_all();
		led l;

		l.flash(1000);

//************ init SPI ********************	
//init_SPI() ;
spi_link lcd_link(10,11,12,13,spi1);

//******* init ΝΟΚΙΑ 5110 LCD *************
nokia5110_lcd lcd(&lcd_link);

lcd.LcdClear();	
lcd.lcd_gotoXY(1,0);	 
std::string message="initializing ";
lcd.lcd_print_str(message);	
lcd.lcd_gotoXY(1,1);
message="pressure ";
lcd.lcd_print_str(message);	
lcd.lcd_gotoXY(1,2);
message="sensor";
lcd.lcd_print_str(message);	

l.flash(1000);

i2c_link  baro;	
BMP180 pres_sensor(&baro,0);

	 int i=0;
	while(1){
	  lcd.LcdClear();
	  lcd.lcd_gotoXY(1,0);	 	  
	  lcd.lcd_print_int(i);
	  lcd.lcd_gotoXY(1,1);	  
	  message="Press:";
	  lcd.lcd_print_str(message);	
	  lcd.lcd_print_double(pres_sensor.ret_pressure()/100.0,3);	  
	  lcd.lcd_gotoXY(1,2);	
	  message="Temp:"; 	  	
	  lcd.lcd_print_str(message);	
	  lcd.lcd_print_double(pres_sensor.ret_temp(),3);		  	
	  sleep_ms(10000);	  
	  ++i;
 }
}
