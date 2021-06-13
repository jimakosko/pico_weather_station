
#include "bmp180.hpp"



//*******************************************************************
// GET CHIP ID AND CHECK COMMUNICATION 
bool BMP180::sensor_id(void) {
    uint8_t sensor_id_reg = bmp180_id_reg;
    uint8_t sensor_id_val[1];

		link->write(&sensor_id_reg,addr,1);
		link->read(sensor_id_val,addr,1);
    if (sensor_id_val[0] != bmp180_id) {
		
		std::cout << "Returned Chip ID: "<< (int)sensor_id_val[0]<< "\n";
        std::cout << "Check your I2C configuration and connection.\n";   
          
        return false;
    }
    else   
     
        std::cout << "sensor ok\n";	
    return true;
} 


//*******************************************************************
// GET CALLIBRATION COEFFICIENTS FROM CHIP
bool BMP180::get_calib(void) {
    uint8_t calib_reg = calibration_reg;
    uint8_t calib_val[calibration_len];

		link->write(&calib_reg,addr,1);
		link->read(calib_val,addr,calibration_len);

    for (int i = 0; i < calibration_len ; i+=2) {
		int16_t tmp=(int16_t)((calib_val[i]<<8) | calib_val[i+1]);
		 if ((tmp == 0) | (tmp== -1)) {
			 std::cout << "Calibation data invalid.\n";
			  return false;
		 }
	 }

	AC1=(int16_t)((calib_val[0]<<8) | calib_val[1]);
	AC2=(int16_t)((calib_val[2]<<8) | calib_val[3]);
	AC3=(int16_t)((calib_val[4]<<8) | calib_val[5]);
	AC4=(uint16_t)((calib_val[6]<<8) | calib_val[7]);	
	AC5=(uint16_t)((calib_val[8]<<8) | calib_val[9]);
	AC6=(uint16_t)((calib_val[10]<<8) | calib_val[11]);	
	B1=(int16_t)((calib_val[12]<<8) | calib_val[13]);
	B2=(int16_t)((calib_val[14]<<8) | calib_val[15]);	
	MB=(int16_t)((calib_val[16]<<8) | calib_val[17]);
	MC=(int16_t)((calib_val[18]<<8) | calib_val[19]);	
	MD=(int16_t)((calib_val[20]<<8) | calib_val[21]);	
			

    return true;
}

//*******************************************************************
bool BMP180::get_temperature(void){
    uint8_t temp_reg_start[] = {
        control_reg,
        temp_select
    };
   link->write(temp_reg_start,addr,2);       

    sleep_ms(5);    
        
    uint8_t temp_reg = result_reg;
    uint8_t temp_val[2];
    
    link->write(&temp_reg,addr,1);
     sleep_ms(5);       
    link->read(temp_val,addr,2);  
 
    int16_t UT = (int16_t)(temp_val[0] << 8) + (int16_t)temp_val[1];

    if (UT == (int16_t)0x8000) {
        	 std::cout << "Non-initialized register detected.\n";
      return false;
    }

    int32_t X1 = (((int32_t)UT - AC6) * AC5) >> 15;
    int32_t X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    temperature = ((B5 + 8) >> 4) * 0.1f;

    if ((temperature >= max_temp)  || (temperature <= min_temp)) {
       	 std::cout << "temp out of limits: " <<  temperature << "\n";;
        return false;
	}

    return true;	
}

//*******************************************************************
bool BMP180::get_pressure(void){
    uint8_t pres_reg_start[] = {
        control_reg,
        (uint8_t)(press_select +(oversampling <<6))
    };
    link->write(pres_reg_start,addr,2);          

     sleep_ms(oversampling_time[oversampling]);		

    uint8_t pres_reg = result_reg;
    uint8_t pres_val[3];
    
    link->write(&pres_reg,addr,1); 
     sleep_ms(oversampling_time[oversampling]);	   
    link->read(pres_val,addr,3);  
     

    int32_t UP = ((pres_val[0] << 16) + (pres_val[1] << 8) + pres_val[2]) >> (8 - oversampling);

    int32_t X1, X2, X3, B3, B6, p = 0;
	uint32_t B4, B7 = 0;

    B6 = B5 - 4000;
    X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
    X2 = (AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((AC1 * 4 + X3) << oversampling) + 2) / 4;
    X1 = (AC3 * B6) >> 13;
    X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (AC4 * (uint32_t)(X3 + 32768)) >> 15;
    B7 = ((uint32_t)(UP) - B3) * (50000 >> oversampling);

    if (B7 < 0x80000000) {
        p = (B7 * 2) / B4;
    } else {
        p = (B7 / B4) * 2;
    }

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;

    pressure = p + ((X1 + X2 + 3791) >> 4);

    return true;	
}

//*******************************************************************
//constructor
BMP180::BMP180(i2c_link  * ins,uint8_t os){
	link=ins;	
	oversampling=os;	
    std::cout << "check baro sensor \n";	    
	sensor_id();	
    std::cout << "get calib coeficients \n";		
	while(!get_calib()){}
	}

//*******************************************************************
float BMP180::ret_temp(void){
	get_temperature();	
	return temperature;
}

//*******************************************************************
float BMP180::ret_pressure(void){	
	get_temperature();		
	get_pressure();
	return pressure;
}
