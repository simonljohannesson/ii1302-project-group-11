/*
 * clk.c
 *
 *  Created on: 17 May 2021
 *      Author: Erik Almqvist
 */

#include "clk.h"

volatile char time[8];

/**
 *	Return the current time in the RTC peripheral
 */
char* gettime(void){

	RTC_DateTypeDef currDate;
	RTC_TimeTypeDef currTime;

	uint8_t hour;
	uint8_t min;
	uint8_t sec;

	HAL_RTC_GetTime(&hrtc, &currTime, RTC_FORMAT_BIN); // Get Time
	HAL_RTC_GetDate(&hrtc, &currDate, RTC_FORMAT_BIN); // Get Date

	hour = currTime.Hours;
	min = currTime.Minutes;
	sec = currTime.Seconds;

	time[0]	= (hour / 10) + 0x30;
	time[1] = (hour % 10) + 0x30;

	time[2] = 0x3A;

	time[3]	= (min / 10) + 0x30;
	time[4] = (min % 10) + 0x30;

	time[5] = 0x3A;

	time[6]	= (sec / 10) + 0x30;
	time[7] = (sec % 10) + 0x30;

	return time;
}
/**
 *	Return the current time from the RTC peripheral in seconds
 */
int getsec(void){
	RTC_DateTypeDef currDate;
	RTC_TimeTypeDef currTime;

	uint8_t hour;
	uint8_t min;
	uint32_t sec;

	HAL_RTC_GetTime(&hrtc, &currTime, RTC_FORMAT_BIN); // Get Time
	HAL_RTC_GetDate(&hrtc, &currDate, RTC_FORMAT_BIN); // Get Date

	hour = currTime.Hours;
	min = currTime.Minutes;
	sec = currTime.Seconds;

	sec += hour*60*60 + min*60;

	return sec;
}

/**
 *	Set the RTC to 00:00:00
 */
void setclk0(void){

	RTC_DateTypeDef currDate;
	RTC_TimeTypeDef currTime;

	currTime.Hours 		= 0;
	currTime.Minutes	= 0;
	currTime.Seconds 	= 0;

	HAL_RTC_SetTime(&hrtc,&currTime,RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc,&currDate,RTC_FORMAT_BIN);
}

/**
 *	Prints the current time to UART
 */
void Print_time(void){
	char *msg = gettime();
	HAL_UART_Transmit(&huart5, (uint8_t*)msg, strlen(msg), 5);
	HAL_UART_Transmit(&huart5, "\r\n", 2, 5);
}

