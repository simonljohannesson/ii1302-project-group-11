/**
 ******************************************************************************
 * @file           : ESP8266.h
 * @brief          : Header file for ESP8266.c file
 ******************************************************************************
 * @author  Tobias Mesch
 * @version 1.0
 * @date    2021-05-20
 * @brief   Contains support libraries and variables used by ESP8266.c
 ******************************************************************************
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_



#endif /* INC_ESP8266_H_ */

#include "main.h"
#include <string.h>
#include <stdbool.h> //include boolean values
#include <stdio.h>

/*Msg return by ESP8266-01*/
static const char ESP8266_AT_OK_TERMINATOR[]  		= "OK\r\n";
static const char ESP8266_AT_ERROR[] 				= "ERROR";
static const char ESP8266_AT_FAIL[] 				= "FAIL";
static const char ESP8266_AT_BUSY[] 				= "busy";
static const char ESP8266_AT_CLOSED[] 				= "CLOSED";
static const char ESP8266_AT_CLOSE[]				= "CLOSE";
static const char ESP8266_AT_SEND_OK[] 			 	= "SEND OK";
/*AT - commands for msg handling with module*/
static const char ESP8266_AT_CWJAP_SET[]			= "AT+CWJAP="; // add "ssid","pwd" + CRLF
static const char ESP8266_AT_CWJAP_TEST[]			= "AT+CWJAP?\r\n";//Did we actually connect to the wifiArea?
static const char ESP8266_AT_RST[]					= "AT+RST\r\n";//Reset wifi-module
static const char ESP8266_AT[]						= "AT\r\n";//AT, established working wifi-module
static const char set_ESP8266_mode[] 				= "AT+CWMODE=1\r\n";//initialize station mode¨
static const char ESP8266_AT_SEND[]					= "AT+CIPSEND=";//Send data
static const char ESP8266_AT_START[]				= "AT+CIPSTART=";//Start a connection
static const char ESP8266_AT_STOP[]					= "AT+CIPCLOSE";//Disconnect from connection , ='id' (optional)
static const char ESP8266_AT_CIPSTATUS[]			= "AT+CIPSTATUS\r\n";//Check status on TCP link
static const char ESP8266_AT_PING[]					= "AT+PING=";//Ping this host


/*Functions inside class*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle);

void init_uart_interrupt(void);

void esp8266_test(void);

void resetBuffer(void);

int esp8266_sendCommand(const char* command);

void esp8266_init(char* SSID, uint8_t sizeSSID, char* PWD, uint8_t sizePWD);

void esp8266_connect(char* hostIP, uint16_t hostPort);

char* esp8266_transmit(char* mqttName, uint8_t sizemqttName, char* mqttPWD, uint8_t sizemqttPWD, char* mqttPublish, uint8_t sizemqttPublish);

void esp8266_disconnect(void);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
