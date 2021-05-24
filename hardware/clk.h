/*
 * clk.h
 *
 *  Created on: 17 May 2021
 *      Author: Erik Almqvist
 */

#ifndef INC_CLK_H_
#define INC_CLK_H_

#include "rtc.h"
#include "usart.h"
#include "string.h"

char* gettime(void);
int getsec(void);
void setclk0(void);
void Print_time(void);


#endif /* INC_CLK_H_ */
