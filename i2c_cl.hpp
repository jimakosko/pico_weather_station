#ifndef i2c_GUARD
#define i2c_GUARD 

#include "pico/stdlib.h"
#include "hardware/i2c.h"

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

i2c_link(int rat=400000,int sc=PICO_DEFAULT_I2C_SCL_PIN,int sd=PICO_DEFAULT_I2C_SDA_PIN,i2c_inst_t* ins=i2c_default);

int ret_rate(void);
int ret_scl(void);
int ret_sda(void);
i2c_inst_t*	ret_inst(void);
bool write(uint8_t * buf, int addr,int len);
bool read(uint8_t *buf,int addr ,int len);

};
#endif 
