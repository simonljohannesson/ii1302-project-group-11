/*
 * program.c
 *
 *  Created on: 16 May 2021
 *      Author: Erik Almqvist
 */

#include "program.h"

typedef enum
{
	Standby,
	Read,
	Plus1,
	Minus1,
	Alive,
} states;

static states State, NextState;

void program(void){
	State = Standby;	//Initiate State to Standby
	NextState = Standby;

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); // Ld

	//Start Init VL53L0X
	VL53L0X.address=0x52;//0x29 IoT adress -> 8-bit i 0x?? format 7-bit requires move 1 bit;
	uint8_t tof_rev_id = VL53L0X_readReg(IDENTIFICATION_REVISION_ID);//Read the revision_ID of sensor, good first test for communication
	if(!VL53L0X_init(true)) Error_Handler();//run INIT - Check datasheet for all instances.
	VL53L0X_setTimeout(500);
	VL53L0X_startContinuous(0);//start reading sensor data -> set timeout period on 0ms
	//End Init VL53L0X

	//Start Init ESP8266
	#ifdef TEST
		HAL_UART_Transmit(&huart5, "Wifi disabled\r\n", 15, 5);
	#else
		esp8266_init(SSID, PASSWORD);
	#endif
	//End Init ESP8266

	uint16_t average[50];
	int value = 0;
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t k = 0;
	uint16_t dist=0;
	uint16_t base_dist=0;	//Calibrated dist while in standby

	HAL_Delay(5);

	//Start calibrate
	for(i=0; i < 10; i++){
		dist = VL53L0X_readRangeContinuousMillimeters();
		base_dist += dist/10;
	}
	//End calibrate

	//Set RTC
	setclk0();
	//End set RTC

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); // Ld

	while(1){
		State = NextState;
		switch(State){

		case Standby:
		{
			dist = VL53L0X_readRangeContinuousMillimeters();
			if(dist > (base_dist + 50) || dist < (base_dist - 50)){
				NextState = Read;
			}

			else if(getsec() >= ALIVE_SIGNAL){
				#ifdef TEST
				HAL_UART_Transmit(&huart5, "RTC set to 0\r\n", 14, 5);
				setclk0();
				#else
				NextState = Alive;
				#endif
			}
		}
		break;

		case Read:
		{
			average[50];
			value = 0;
			i = 0;
			j = 0;
			k = 0;
			average[k] = dist;
			k++;

			while(1){
				dist = VL53L0X_readRangeContinuousMillimeters();

				if(k == 50){
					for(i = 0; i < k-1; i++){
						value += average[i] - average[i+1];
						HAL_UART_Transmit(&huart5, "Working\r\n", 9, 5);
						k = 0;
						average[k] = dist;
						j=0;
					}
				}
				else if(dist < (base_dist + 30) && dist > (base_dist - 30)){
					j++;
					if(j >= 3){
						break;
					}
				}

				else if(dist > 5000);	//If an error is read it is to be ignored

				else{
					j=0;
					average[k] = dist;
					k++;
				}
			}

			//Evaluate
			for(i = 0; i < k-1; i++){
				value += average[i] - average[i+1];
			}
			if(value > 50){
				#ifdef TEST
				char buffer[15];
				sprintf(buffer, "-1, %d\r\n", value);
				HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 5);
				setclk0();
				NextState = Standby;
				#else
				NextState = Minus1;
				#endif
			}
			else if(value < -50){
				#ifdef TEST
				char buffer[15];
				sprintf(buffer, "+1, %d\r\n", value);
				HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 5);
				setclk0();
				NextState = Standby;
				#else
				NextState = Plus1;
				#endif
			}
			else{
				#ifdef TEST
				char buffer[15];
				sprintf(buffer, "0, %d\r\n", value);
				HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 5);
				setclk0();
				NextState = Standby;
				#else
				NextState = Standby;
				#endif
			}
			break;

		case Plus1:
		{
			//Insert Plus1 signal function code here
			setclk0();
			NextState = Standby;
		}
		break;

		case Minus1:
		{
			//Insert Minus1 signal function code here
			setclk0();
			NextState = Standby;
		}

		break;

		case Alive:
		{
			//Insert Alive signal function code here
			setclk0();
			NextState = Standby;
		}
		break;

		default:
			break;
		}
		}
	}
}
