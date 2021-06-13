#include "sht21.hpp"

//*******************************************************************
// GET CHIP ID AND CHECK COMMUNICATION 
bool sht21::sensor_id(void) {
	
	
	return true;
}

//*******************************************************************
void sht21::reset(void) {
  uint8_t buf = RESET;
  link->write(&buf,addr,1);
       sleep_ms(50);  
}
//*******************************************************************

void sht21::read_temp(void){
   uint8_t buf[4];   	
   uint8_t buf_w=MEASURE_TEMP_NO_HOLD;	
   link->write(&buf_w,addr,1); 	
   sleep_ms(100);   

    link->read(buf,addr,3);   
          
	uint16_t  temp = (buf [0] << 8 | buf [1]);
	temp&= ~0x0003; 
	
	temperature = temp*175.72 / 65536.0;
	temperature-=46.85;
	
}

void sht21::read_hum(void){
   uint8_t buf[4];   	
   uint8_t buf_w=MEASURE_R_H_NO_HOLD;	
   link->write(&buf_w,addr,1); 	
   sleep_ms(100);   

    link->read(buf,addr,3);   
	
  	uint16_t humid = (buf [0] << 8 | buf [1]) ;
  	humid &= ~0x0003; 

	humidity = humid * 125.0 / 65536.0;
	humidity-=6.0 ;
}

sht21::sht21(i2c_link  * ln){
	link=ln;
	std::cout << "check humidity sensor \n";	 
	sensor_id();
	//read_SN_frmw();
	
}

float sht21::ret_temp(void){
	read_temp();
	return temperature;
}
float sht21::ret_hum(void){
	read_hum();
	return humidity;
}
