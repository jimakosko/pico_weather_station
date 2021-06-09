//*******************************************************************
//*************** pico led        ****************************************
//*************** 09/06/2021 *****************************************

class led{
uint LED_PIN ;	
uint delay;
public:
led(uint l_p=25,uint de=100){
	LED_PIN = l_p;	
	delay=de;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 0);				
}	
	void flash(uint de){
		gpio_put(LED_PIN, 1);
		sleep_ms(de);	
		gpio_put(LED_PIN, 0);				
	}
	void flash(){
		gpio_put(LED_PIN, 1);
		sleep_ms(delay);	
		gpio_put(LED_PIN, 0);						
	}	
	
};
