#include "n5110_lcd.hpp"

void n5110_lcd::lcd_command() {
	gpio_put(PIN_DC, 0);
 }
 
void n5110_lcd::lcd_data() {
	gpio_put(PIN_DC, 1);
 } 
 
void n5110_lcd::lcd_reset() {
	gpio_put(PIN_RST, 0);
	gpio_put(PIN_RST, 1);	
}	


void  n5110_lcd::init_LCD() {
	lcd_reset();	
	lcd_command();
	uint8_t comm;	
	comm=0x21;
	link->spi_write(&comm,1);	
	comm=0xB1;	
	link->spi_write(&comm,1);	
	comm=0x04;	
	link->spi_write(&comm,1);	
	comm=0x14;
	link->spi_write(&comm,1);
	comm=0x20;
	link->spi_write(&comm,1);	
	comm=0x0C;
	link->spi_write(&comm,1);	
	
}

void n5110_lcd::writeComm(uint8_t *data,int size){
	lcd_command();
	link->spi_write(data,size);	
}	

//******************************************
//******************************************
//******************************************
//******************************************
n5110_lcd::n5110_lcd(spi_link * lnk,uint8_t rst,uint8_t dc){
	PIN_RST=rst;
	PIN_DC=dc;
	link=lnk;
	//INIT RST AND DC PINS
	gpio_init(PIN_RST);
	gpio_set_dir(PIN_RST, GPIO_OUT);	
	gpio_put(PIN_RST, 1);		

	gpio_init(PIN_DC);
	gpio_set_dir(PIN_DC, GPIO_OUT);	
	
	init_LCD();		
}	

void n5110_lcd::writeChar(uint8_t *data,int size){
	lcd_data();
	link->spi_write(data,size);	
}
	


void n5110_lcd::LcdClear(void){
	uint8_t message;	
	message=0x00;
	lcd_gotoXY(0,0);
    for (int index = 0; index < LCD_X * LCD_Y / 8; index++)  writeChar(&message,1);
}	
	
void n5110_lcd::lcd_gotoXY(int x, int y){
  uint8_t x_pos=0x80 | x;
  uint8_t y_pos=0x40 | y; 
  writeComm( &x_pos,1);  // Column.
  writeComm( &y_pos,1);  // Row.  
}	

void n5110_lcd::lcd_print_char(char mes){
	uint8_t message[5];	
	for (int j=0;j<5;++j) message[j]=ASCII[mes-32][j]; 
	writeChar(message,5);
	message[0]=0x00;
	writeChar(message,1);		
}	

void n5110_lcd::lcd_print_int(int num){
		uint8_t message[5];	
		if (num<0) 	lcd_print_char('-');
		num=abs(num);
		if (num<10){
			for (int j=0;j<5;++j) message[j]=ASCII[num+16][j]; //m
			writeChar(message,5);	
			return;						
		}
		
		int dig=0;
		int num_tmp=num;
		while(num_tmp!=0){
			num_tmp/=10;
			++dig;
		}

		for (int i=0;i<dig;++i){
			num_tmp=num/pow(10,(dig-1-i));
			for (int j=0;j<5;++j) message[j]=ASCII[num_tmp+16][j]; //m
			writeChar(message,5);	
			num-=num_tmp*pow(10,(dig-1-i));			
		}
}	

void n5110_lcd::lcd_print_double(double num,int digits){
	if (num<0) 	lcd_print_char('-');
	num=fabs(num);
	int int_part;
	double dec_part;
	//int part	
	int_part=(int)num;
	// decimal part
	dec_part=num-(int)num;
	dec_part*=pow(10,digits);
	lcd_print_int(int_part);	
	lcd_print_char('.');	
	lcd_print_int((int)dec_part);	
}

void n5110_lcd::lcd_print_str(char *data){
	int i=0;
	while(data[i]) {
		lcd_print_char(data[i]);	
		++i;
	}
}

//*******************************************************************
void n5110_lcd::lcd_print_str(std::string data){
	for (int i=0;i<data.size();++i) 	lcd_print_char(data[i]);
}
