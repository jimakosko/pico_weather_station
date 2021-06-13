#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c_cl.hpp"

//*************************************
i2c_link::i2c_link(int rat,int sc,int sd,i2c_inst_t* ins){
	rate=rat;
	scl=sc;
	sda=sd;
	inst=ins;

	i2c_init(inst, rate);
	
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_pull_up(scl);
    gpio_pull_up(sda);	
	
    sleep_ms(100);	

	}
//*************************************
	int i2c_link::ret_rate(void) {
		return rate;				
	}
//*************************************	
	int i2c_link::ret_scl(void) {
		return scl;				
	}	
//*************************************
	int i2c_link::ret_sda(void) {
		return sda;				
	}	
//*************************************	
	i2c_inst_t *	i2c_link::ret_inst(void){
		return inst;		
	}	
//*************************************	
	bool i2c_link::write(uint8_t * buf, int addr,int len){
		i2c_write_blocking(inst, addr, buf, len, true);		
		return true;
	}
//*************************************	
	bool i2c_link::read(uint8_t *buf,int addr ,int len){
		i2c_read_blocking(inst, addr, buf, len, false);		
		return true;			 
	}
	
