#include <iostream>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "led.hpp"
#include "i2c_cl.hpp"
#include "bmp180.hpp"
#include  "sht21.hpp"
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
n5110_lcd lcd(&lcd_link);

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

i2c_link  i2c_l;	
BMP180 pres_sensor(&i2c_l,0);

sht21 hum_sensor(&i2c_l);

float press,temp1,temp2,hum;


	 int i=0;
	while(1){
	  press=pres_sensor.ret_pressure()/100.0;
	  temp1=pres_sensor.ret_temp();
	  temp2=hum_sensor.ret_temp();
	  hum=hum_sensor.ret_hum();
	  
	  lcd.LcdClear();
	  lcd.lcd_gotoXY(1,0);	 	  
	  lcd.lcd_print_int(i);
	  
	  lcd.lcd_gotoXY(1,1);	  
	  message="Press:";
	  lcd.lcd_print_str(message);	
	  lcd.lcd_print_double(press,3);	 
	   
	  lcd.lcd_gotoXY(1,2);	
	  message="Temp:"; 	  	
	  lcd.lcd_print_str(message);	
	  lcd.lcd_print_double(temp1,3);	
	  	
	  lcd.lcd_gotoXY(1,3);		  
	  message="Temp2:"; 	  	
	  lcd.lcd_print_str(message);	
	  lcd.lcd_print_double(temp2,3);
	  	
	  lcd.lcd_gotoXY(1,4);		  
	  message="Humid%:"; 	  	
	  lcd.lcd_print_str(message);	
	  lcd.lcd_print_double(hum,3);		  
	  	    	
	  sleep_ms(1000);	  
	  ++i;
 }
}
