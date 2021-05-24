/*
 * settings.h
 *
 *  Created on: 20 May 2021
 *      Author: Erik Almqvist
 */

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#define TEST		//For testing purposes in program.c without the esp8266 module
//#undef TEST

#define RUN_TEST_PROGRAM	//For testing purposes in Test.c
#undef RUN_TEST_PROGRAM

static const char SSID[]     	= "";			//SSID for the network
static const char PASSWORD[] 	= "";			//Password for the specified network
static const uint8_t ALIVE_SIGNAL = 45;			//Time the program awaits to send an alive signal in seconds


#endif /* INC_SETTINGS_H_ */
