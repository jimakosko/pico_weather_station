//*******************************************************************
//*************** pico i2c port *********** ****************************
//*************** 09/06/2021 *****************************************

class i2c_link{
	int addr;
	int rate;
	int scl;
	int sda;
	i2c_inst_t* inst;	
public:

	i2c_link(int rat=400000,int sc=PICO_DEFAULT_I2C_SCL_PIN,int sd=PICO_DEFAULT_I2C_SDA_PIN,i2c_inst_t* ins=i2c_default){
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
	int ret_rate(void) {
		return rate;				
	}
//*************************************	
	int ret_scl(void) {
		return scl;				
	}	
//*************************************
	int ret_sda(void) {
		return sda;				
	}	
//*************************************	
	i2c_inst_t*	ret_inst(void){
		return inst;		
	}	
//*************************************	
	bool write(uint8_t * buf, int addr,int len){
		i2c_write_blocking(inst, addr, buf, len, true);		
		return true;
	}
//*************************************	
	bool read(uint8_t *buf,int addr ,int len){
		i2c_read_blocking(inst, addr, buf, len, false);		
		return true;			 
	}
	
};
