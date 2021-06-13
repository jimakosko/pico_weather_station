#include "led.hpp"


led::led(uint l_p,uint de){
	LED_PIN = l_p;	
	delay=de;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 0);				
}	
void led::flash(uint de){
		gpio_put(LED_PIN, 1);
		sleep_ms(de);	
		gpio_put(LED_PIN, 0);				
	}
	
void led::flash(){
		gpio_put(LED_PIN, 1);
		sleep_ms(delay);	
		gpio_put(LED_PIN, 0);						
	}	
