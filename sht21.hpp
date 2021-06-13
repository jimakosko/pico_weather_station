#ifndef sht21_GUARD
#define sht21_GUARD 

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c_cl.hpp"

//*******************************************************************
//*************** sht21 SENSOR *************************************
//*************** 09/06/2021 *****************************************

// command codes
#define MEASURE_R_H_HOLD 0xE5 
#define MEASURE_R_H_NO_HOLD 0xF5 
#define MEASURE_TEMP_HOLD 0xE3
#define MEASURE_TEMP_NO_HOLD 0xF3
#define READ_TEMP_PREV 0xE0
#define RESET 0xFE
#define WRITE_RH_T_REG1 0xE6
#define READ_RH_T_REG1 0xE7
#define WRITE_HEATER_C_REG 0x51
#define READ_HEATER_C_REG 0x11
#define READ_ID11 0xFA 
#define READ_ID12 0x0F 
#define READ_ID21 0xFC
#define READ_ID22 0xC9 
#define READ_FIRMWARE_VER1 0x84
#define READ_FIRMWARE_VER2 0xB8


//*******************************************************************
//*******************************************************************
class sht21{
int addr = 0x40; //sensor address
i2c_link  * link;   
float temperature;
float humidity;
uint32_t s_num_1; 
uint32_t s_num_2;
uint8_t _revision;


//*******************************************************************
// GET CHIP ID AND CHECK COMMUNICATION 
bool sensor_id(void);

//*******************************************************************
void reset(void);

//*******************************************************************

void read_temp(void);

void read_hum(void);


public:

//*******************************************************************
// CONSTRUCTOR
sht21(i2c_link  * ln);

float ret_temp(void);
float ret_hum(void);
};
#endif 
