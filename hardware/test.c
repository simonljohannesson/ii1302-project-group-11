/*
 * test.c
 *
 *  Created on: May 3, 2021
 *      Author: Erik Almqvist
 */

#include "test.h"

/**
 *	Function tests
 */
void Test_program(void){
	//Test_uart5();
	//Test_esp8266();
	//Test_vl53l0x();
	//Test_espinit(SSID, PASSWORD);
	//Test_resetclk();
	//Test_standby();
}

/**
 *	Prints Hello to serial
 */
void Test_uart5(void){
	char *Hello = "Hello\n\r";
	HAL_UART_Transmit(&huart5, (uint8_t*)Hello, strlen(Hello), 10);
}

/**
 *	Test for response from the esp8266 mcu
 */
void Test_esp8266(void){
	HAL_Delay(5);

	char test[] = "AT\r\n";

	init_uart_interrupt();

	HAL_Delay(5);

	if(esp8266_sendCommand(test)!=0){
		Error_Handler();
	}
}

void Test_vl53l0x(void){
	VL53L0X.address=0x52;//0x29 IoT adress -> 8-bit i 0x?? format 7-bit requires move 1 bit;
	uint8_t tof_rev_id = VL53L0X_readReg(IDENTIFICATION_REVISION_ID);//Read the revision_ID of sensor, good first test for communication
	if(!VL53L0X_init(true)) Error_Handler();//run INIT - Check datasheet for all instances.
	VL53L0X_setTimeout(500);
	VL53L0X_startContinuous(0);//start reading sensor data -> set timeout period on 0ms
	while(1){
		distance = VL53L0X_readRangeContinuousMillimeters();
		//HAL_UART_Transmit(&huart5, (uint16_t*)distance, strlen(distance), 10);
	}
}

/**
 *	Test for communication with a access point
 */
void Test_espinit(const char* ssid,const char* psswrd){
	esp8266_init(ssid, psswrd);
}

/**
 *	Test for reseting the RTC after specified times
 */
void Test_resetclk(void){
	setclk0();
	HAL_UART_Transmit(&huart5, "Clk test start\r\n", 16, 5);

	while(1){
		if(getsec() >= ALIVE_SIGNAL){
			Print_time();
			setclk0();
			Print_time();
		}
	}
}

/**
 *	Tests for the main functions of the program
 */
void Test_standby(void){
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); // Ld
	VL53L0X.address=0x52;//0x29 IoT adress -> 8-bit i 0x?? format 7-bit requires move 1 bit;
	uint8_t tof_rev_id = VL53L0X_readReg(IDENTIFICATION_REVISION_ID);//Read the revision_ID of sensor, good first test for communication
	if(!VL53L0X_init(true)) Error_Handler();//run INIT - Check datasheet for all instances.
	VL53L0X_setTimeout(500);
	VL53L0X_startContinuous(0);//start reading sensor data -> set timeout period on 0ms

	uint8_t i = 0;

	HAL_Delay(5);

	//Start calibrate
	for(i=0; i < 10; i++){
		distance = VL53L0X_readRangeContinuousMillimeters();
		base_distance += distance/10;
	}
	//End calibrate
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); // Ld

	//Pseudo Standby state
	while(1){
		distance = VL53L0X_readRangeContinuousMillimeters();
		//HAL_UART_Transmit(&huart5, (uint16_t*)distance, strlen(distance), 10);
		if(distance > (base_distance + 50) || distance < (base_distance - 50)){
			Test_read(distance);
		}
	}
}

/**
 *	Test for passage past the sensor
 */
void Test_read(uint16_t first){
	uint16_t average[50];
	int value = 0;
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t k = 0;
	average[k] = first;
	k++;

	while(1){
		distance = VL53L0X_readRangeContinuousMillimeters();

		if(k == 50){
			for(i = 0; i < k-1; i++){
				value += average[i] - average[i+1];
				HAL_UART_Transmit(&huart5, "Working\r\n", 9, 5);
				k = 0;
				average[k] = distance;
				j=0;
			}
		}
		else if(distance < (base_distance + 30) && distance > (base_distance - 30)){
			j++;
			if(j >= 3){
				break;
			}
		}

		else if(distance > 5000);	//If an error is read it is to be ignored

		else{
			j=0;
			average[k] = distance;
			k++;
		}
	}

	//Evaluate
	for(i = 0; i < k-1; i++){
		value += average[i] - average[i+1];
	}
	if(value > 50){
		char buffer[15];
		sprintf(buffer, "-1, %d\r\n", value);
		HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 5);
		//HAL_UART_Transmit(&huart5, "-1\r\n", 4, 5);
	}
	else if(value < -50){
		char buffer[15];
		sprintf(buffer, "+1, %d\r\n", value);
		HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 5);
		//HAL_UART_Transmit(&huart5, "+1\r\n", 4, 5);
	}
	else{
		char buffer[15];
		sprintf(buffer, "0, %d\r\n", value);
		HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 5);
		//HAL_UART_Transmit(&huart5, "0\r\n", 3, 5);
	}
}

