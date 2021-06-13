#ifndef BMP180_GUARD
#define BMP180_GUARD 

#include <iostream>
#include "pico/stdlib.h"
#include "i2c_cl.hpp"

//*******************************************************************
//*************** BOSCH BMP180 SENSOR ****************************
//*************** 09/06/2021 *****************************************


class BMP180{
int addr = 0x77; //sensor address
i2c_link  * link;   
uint8_t oversampling;
uint8_t oversampling_time[4]={5,8,14,26} ;
float temperature;
int32_t pressure;

//calibration parameters from chip	
int16_t  AC1;
int16_t  AC2;
int16_t  AC3;
uint16_t AC4;
uint16_t AC5;
uint16_t AC6;
int16_t  B1;
int16_t  B2;
int16_t  MB;
int16_t  MC;
int16_t  MD;	

//registers	
uint8_t calibration_reg=0xAA;
uint8_t calibration_len=0x16;
uint8_t bmp180_id_reg=0xD0;
uint8_t bmp180_id= 0x55;
uint8_t control_reg=0xF4; 
uint8_t result_reg=0xF6;
uint8_t temp_select=0x2E;
uint8_t press_select=0x34;

int min_temp=-40;
int max_temp=+85;

int32_t B5;


//*******************************************************************
// GET CHIP ID AND CHECK COMMUNICATION 
bool sensor_id(void);


//*******************************************************************
// GET CALLIBRATION COEFFICIENTS FROM CHIP
bool get_calib(void) ;

//*******************************************************************
bool get_temperature(void);
//*******************************************************************
bool get_pressure(void);

public:
//*******************************************************************
//constructor
BMP180(i2c_link  * ins,uint8_t os=0);

//*******************************************************************
float ret_temp(void);

//*******************************************************************
float ret_pressure(void);

};
#endif 
