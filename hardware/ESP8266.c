/**
 ******************************************************************************
 * @file           : ESP8266.c
 * @brief          : ESP8266 version 01 wifi-module communicationhandler
 ******************************************************************************
 * @author  Tobias Mesch
 * @version 1.0
 * @date    2021-05-20
 * @brief   Functions and structures for handling Communication with ESP8266-01
 ******************************************************************************
 */

#include "ESP8266.h"

/*Handler*/
UART_HandleTypeDef huart5;
ITStatus UartReady = RESET;		//Flag to determine if uart was set/reset -> sending data -> completed

/*Static values used by class*/
#define BUFFERSIZE 4096	//Buffersize determines how many char should be in buffer (to be send/recieved)
static char Buffer[BUFFERSIZE];//Buffer -> filled with a sentence
static uint8_t RX_BUFFER_INDEX = 0;
static uint8_t rx_reciever;

/*Flags*/
static uint8_t error_flag = 0; //flag for errors
static uint8_t fail_flag = 0; //flag for fails
static uint8_t busy_flag = 0; //flag for fails

/**
 * @brief	INIT start first sequence of interupthandling
 * @note	Sets the rx_Callback ready to recieve data
 * @retval	None
 */
void init_uart_interrupt(void){
	HAL_UART_Receive_IT(&huart5, &rx_reciever, 1);
}

/**
 * @brief  Send command ESP8266
 * @param command	What command should be send to the module
 * @note   A command is issued and send over Tx/Rx UART to the wifi-module.
 *
 * Clear bufferarray
 * Transmit command over UART
 * Wait for buffer to fill out
 * When certain phrase are met issue this command (at best "OK")
 * OK means transmission was successful
 * See flags if error occurred
 * @retval 0 | 1 for success or not success
 */
int esp8266_sendCommand(const char* command){
	resetBuffer();//Reset buffer array -> causes issues otherwise?
	RX_BUFFER_INDEX = 0;//reset index for the buffer
	error_flag = 0;//reset flags for errorhandling
	fail_flag = 0;//reset flags for failhandling

	/*start sending out data*/
	if(HAL_UART_Transmit_IT(&huart5, (uint8_t *)command, strlen(command))!= HAL_OK)
	{
		Error_Handler();//something went wrong in data transfer
	}
	/* Wait for the end of the transfer */
	while (UartReady != SET)
	{
		//Do otherstuff
	}
	/* Reset transmission flag */
	UartReady = RESET;

	while((strstr(Buffer, ESP8266_AT_OK_TERMINATOR) == NULL)){ //wait for ok\r\n
		//Do nothing until ok is displayed
		if(strstr(Buffer, ESP8266_AT_ERROR)!=NULL){ //Something went wrong
			error_flag = 1;
			Error_Handler();
		}
		if(strstr(Buffer, ESP8266_AT_FAIL)!=NULL){ //Fail at connecting
			fail_flag = 1;
			return 1;
		}
		if(strstr(Buffer, ESP8266_AT_BUSY)!=NULL){ //When wifi is busy
			HAL_Delay(10);
			busy_flag=1;
			return 1;
		}
		if(strstr(Buffer, ESP8266_AT_CLOSE)!=NULL)//Closed connection call from wifi-module
		{
			return 0;
		}
	}
	return 0;
}

/**
 * @brief  Test to check ESP8266
 * @note   This sends AT command to make sure connection is established between hardware MCU + ESP8266
 * See flags if error occured
 * @retval none
 */
void esp8266_test()
{
	init_uart_interrupt();
	char test[] = "AT\r\n";
	esp8266_sendCommand(test);
}

/**
 * @brief  Buffer reset
 * @note   This clears the buffer for receiving msg
 * @retval none
 */
void resetBuffer()
{
	memset(Buffer, 0, BUFFERSIZE);//Set values in array to 0
}

/*CRASH? might occour @ hard resets :S 	=>> wait some time for module to reset?	*/
/**
 * @brief  INIT for ESP8266
 * @param  SSID	This is routers address
 * @param  sizeSSID	size of SSID
 * @param  PWD	This is the password to connect to the router
 * @param  sizePWD	size of PWD
 * @note   This initiates the ESP8266 communication with selected router
 *
 * Wait for ESP8266 to be ready to receive msg from MCU.
 * Optional reset
 * Set stationarymode
 * Optional read mode
 * Set loginvalues to router
 * Optional test login successful
 *
 * See flags if error occurred
 * Automation could be improved for smoother connection-phase
 *
 * @retval none
 */
void esp8266_init(char* SSID, uint8_t sizeSSID, char* PWD, uint8_t sizePWD)
{
	init_uart_interrupt();

	while(esp8266_sendCommand(ESP8266_AT)!=0)/*To many resets might make wifi not wanna go to work, chill for some time, try again*/
	{
		HAL_Delay(1);
	}

	//esp8266_sendCommand(ESP8266_AT_RST);//restart wifi-module
	//HAL_Delay(5);//wait for stabalizing wifi

	esp8266_sendCommand(set_ESP8266_mode);//station-mode is online

	esp8266_sendCommand("AT+CWMODE?\r\n");//Check what mode wifi is on

	//esp8266_sendCommand("AT+CWLAP\r\n");//see surrounding wifi connections

	/*	Note	*/
	/*choosing size of connection array might depend on several parts*/
	/*SSID maximum 32 char*/
	/*PWD encryption -> WEP::16, WPA::63*/
	char connect_wifi[30];
	//combine all into one string
	sprintf(connect_wifi, "%s\"%s\",\"%s\"\r\n", ESP8266_AT_CWJAP_SET, SSID, PWD);
	//send message AT+CWJAP=\"SSID\\"PWD\"
	while(esp8266_sendCommand(connect_wifi)!=0)//send command
	{
		HAL_Delay(10);//wait and try connecting again
	}

	esp8266_sendCommand(ESP8266_AT_CWJAP_TEST);//Did we establish a connection?
}

/*Module is operating*/
/*Connect to local wifi-hotspot*/
/*Connect TCP link to server*/
/*Transmit message to topic*/
/*Terminate TCP*/
/*Check still connected? redo*/

/**
 * @brief  Connect to this Broker
 * @param  hostIP	This is the brokers IP-adress
 * @note   Connect to broker at IP adress on this port.
 *
 * Ping to host begins, if not successful read flag
 * Next start up a TCP link to broker
 *
 * @retval none
 */
void esp8266_connect(char* hostIP, uint16_t hostPort)
{
	//Start pinging host -> does he exist
	char ping_connect[100];//not dynamic, be aware
	memset(ping_connect, 0, 100);//Set values in array to 0
	sprintf(ping_connect, "%s\"%s\"\r\n",ESP8266_AT_PING,hostIP);//AT+PING="host.ip"\r\n
	//161.156.96.82 f35rw3.messaging.internetofthings.ibmcloud.com	-> Hardcode IP / WEB
	esp8266_sendCommand(ping_connect);//error here would mean a timeout occoured

	//Start TCP connection to IBM-Host
	char tcp_connect[100];//not dynamic, be aware
	memset(tcp_connect, 0, 100);//Set values in array to 0
	/*"AT+CIPSTART="(optional=ID)","TCP","192.0.0.1","8001",*/
	sprintf(tcp_connect, "%s\"%s\",\"%s\",%hu\r\n", ESP8266_AT_START, "TCP", hostIP, hostPort);
	//HAL_UART_Transmit(&huart2, (uint8_t *) tcp_connect, strlen(tcp_connect), 100); //For testing
	esp8266_sendCommand(tcp_connect);

	//Debug connection
	//esp8266_sendCommand(ESP8266_AT_CIPSTATUS);//Check tcp link -> 0 ESP8266 runs as client
}

/**
 * @brief  Transmit data from ESP8266 to Broker
 * @param  mqttName This should be the username for AUTH
 * @param  sizemqttName	Size of mqttName
 * @param  mqttPWD	This should be the password for AUTH
 * @param  sizemqttPWD Size of mqttPWD
 * @param  mqttPublish This is the topic where data is published to
 * @param  sizemqttPublish Size of mqttPublish
 * @note   Ideally this would be fully operating transmission of data to broker.
 *
 * For now ping to host works
 * TCP link to host seems to work
 * MQTT msg is not properly made, msg does not deliver to broker
 * Automation for UTF-8 encoding needs to implement
 * Functional rec of ack-packet does not exist
 * Errorhandling needs improvement
 *
 * @retval OK | Error - Operationalflag successful or not
 */
char* esp8266_transmit(char* mqttName, uint8_t sizemqttName, char* mqttPWD, uint8_t sizemqttPWD, char* mqttPublish, uint8_t sizemqttPublish)
{
	static uint8_t error_flag = 0; //flag for errors
	static uint8_t fail_flag = 0; //flag for fails
	static uint8_t busy_flag = 0; //flag for fails

	//Check flags for error handling, if flag is set -> Issue
	if(error_flag || fail_flag || busy_flag)
	{
		return "Error";
	}

	/*	Default MQTT communication 		*/
	/*	Connect Package send to broker 	*/
	/*	Connect Acknowledge from broker */
	/*	Publish to topic 				*/
	/*	Publish acknowledge 			*/

	//Fixed		0x10	- CONNECT MQTT packet type	|| 0x30 PUBLISH
	//Fixed		0x0A	- Remaining lenght -> Variable + Payload
	//Variable	0x00	- Lenght MSB(0)
	//Variable	0x04	- Lenght LSB(4)
	//Variable 	0x4d	- "M"
	//Variable	0x51	- "Q"
	//Variable	0x54	- "T"
	//Variable	0x54	- "T"
	//Protocol	0x04	- Protocol version 5 -> change to 4 or 3 for downgrade	-> Connack return code 0x01 (unacceptable protocol level according to server)
	//ConnectF	0xC0	- UserName, Password, WillRetain, QoS, Will, Clean, Reserved	-> Specify Username & Password in payload
	//KeepAlive	0x00	- Server does not need to keep client alive
	//KeepAlive 0x3C	- LSB, set to 60 then timeout

	//Package send
	//char con[12]={0x10,0x13,0x00,0x04,0x4d,0x51,0x54,0x54,0x04,0x02,0x00,0x3C};//simple connect
	//char con[12]={0x10,0x32,0x00,0x04,0x4d,0x51,0x54,0x54,0x04,0x00,0x00,0x00};//Package for uname + pwd
	//char con[12]={0x10,0x32,0x00,0x04,0x4d,0x51,0x54,0x54,0x04,0x00,0x00,0x00};//Package for uname + pwd + topic + payload

	/* UTF-8 encoded msg */
	//char clientID[10] = {0x00,0x08,0x73,0x65,0x6E,0x73,0x6F,0x72,0x2D,0x31};//lenght[msb|lsb] + sensor-1		-> Connack return code 0x02 (identifier rejected)
	//char uname[14] = {0x75,0x73,0x65,0x2D,0x74,0x6F,0x6B,0x65,0x6E,0x2D,0x61,0x75,0x74,0x68};//use-token-auth
	//char pwd[18] = {0x55,0x77,0x59,0x4C,0x29,0x42,0x70,0x44,0x21,0x4F,0x37,0x59,0x26,0x2D,0x41,0x68,0x3F,0x75};//UwYL)BpD!O7Y&-Ah?u

	char package[22]={0x10,0x13,0x00,0x04,0x4d,0x51,0x54,0x54,0x04,0x02,0x00,0x3C,0x00,0x08,0x73,0x65,0x6E,0x73,0x6F,0x72,0x2D,0x31};
	/* ISSUES DUE TO 0x00 BEING NULL TERMINATE -> find solution*/
	//char package[100];//buffer to fill with MQTT header information
	//memset(package, 0, 100);//Set values in array to 0
	//sprintf(package, "%s%s",con,clientID);

	/*Prepare wifi-module to transmit -> Send transmission data*/
	char sendBuf[20];
	memset(sendBuf, 0, 20);//Set values in array to 0
	sprintf(sendBuf, "%s%d\r\n",ESP8266_AT_SEND,sizeof(package));//AT+CIPSEND = # (size of message to send)
	esp8266_sendCommand(sendBuf);//Set wifi-module to transmit data []


	/*start sending out data*/
	if(HAL_UART_Transmit_IT(&huart5, (uint8_t*)package, sizeof(package))!= HAL_OK)
	{
		Error_Handler();//something went wrong in data transfer
	}
	/* Wait for the end of the transfer */
	while (UartReady != SET)
	{
		//Do otherstuff
	}
	/* Reset transmission flag */
	UartReady = RESET;

	//Wait for transmission flag complete
	while((strstr(Buffer, ESP8266_AT_SEND_OK) == NULL)){ //wait for send ok\r\n
		/*Find error codes for better while loop handler*/
		/*ERROR 	-> connection not established, or disruption on line*/
		/*SEND FAIL -> if transmitted msg was not successful*/
	}
	//Wait for response
	while(1){
		//If return msg is CLOSED a disconnection was made from host
		if(strstr(Buffer, ESP8266_AT_CLOSED) != NULL){
			return "CLOSED CONNECTION FROM HOST";
		}
	}
	return "OK";//return Ok
}

/**
 * @brief  Disconnection
 * @note   Send AT msg close, this terminates TCP link to host.
 * @retval None
 */
void esp8266_disconnect()
{
	esp8266_sendCommand(ESP8266_AT_STOP);
}

/**
 * @brief  Tx Transfer completed callback
 * @param  UartHandle: UART handle.
 * @note   Set UartReady as transfer completed
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	/* Set transmission flag: transfer complete*/
	UartReady = SET;
}

/**
 * @brief  Rx Transfer completed callback
 * @param  UartHandle: UART handle
 * @note   When message arrives put it into BufferArray and increase pointer. Clear flag and resume listening
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	//UartReady = SET;
	/* Set transmission flag: transfer complete*/
	//UartReady = SET;
	if(UartHandle->Instance == UART5) {
		Buffer[RX_BUFFER_INDEX++] = rx_reciever;//place recived message into buff.array, 1 byte. Increase index of array by 1.
	}
	if(HAL_UART_Receive_IT(&huart5, &rx_reciever,1)!=HAL_OK)//Clear flag, read next byte
	{
		Error_Handler();
	}
}
