/*
 * test.h
 *
 *  Created on: May 3, 2021
 *      Author: Erik Almqvist
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include "VL53L0X.h"
#include "clk.h"
#include "gpio.h"
#include "usart.h"
#include "string.h"
#include "settings.h"

volatile uint16_t distance=0;
volatile uint16_t base_distance=0;	//Calibrated distance while in standby

void Test_program(void);
void Test_uart5(void);
void Test_esp8266(void);
void Test_espinit(const char* ssid,const char* psswrd);
void Test_resetclk(void);
void Test_standby(void);
void Test_read(uint16_t first);

#endif /* INC_TEST_H_ */
