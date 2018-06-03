// indigo6alpha's TM1637 demo for STM8SF103F3 MCU
// Project started 6/3/2018
// written by indigo6alpha (indigosixalpha164@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#include "gpio.h"
#include "clock.h"
#include "tm1637.h"

// DEPRECATED: This method is deprecated. Use tm1637Init to initialize the pins 
// Initialize GPIO pins for Clock and Data on TM1637
void init_gpio() {
	GPIO_Config_Pin(GPIO_PORT_C, GPIO_PIN_4, PIN_MODE_OUTPUT_PP);
	GPIO_Config_Pin(GPIO_PORT_B, GPIO_PIN_4, PIN_MODE_OUTPUT_PP);
}

int main() {
	int hours = 0, min = 0, secs = 0;
	char szTemp[8];
	
	CLK_Init(CLK_SRC_HSI, CLK_HSI_DIV_NONE, CLK_CPU_DIV_MASTER_NONE);
	// init_gpio();

	// Initialize clock, data pins
	tm1637Init(GPIO_PORT_C, GPIO_PIN_4, GPIO_PORT_B, GPIO_PIN_4); 
	tm1637SetBrightness(4);

	// The main loop
	while(1) {
		if(secs == 60) {
			secs = 0;
			min++;
			
		}
		if (min == 60) {
			min = 0;
			hours++;
		}
		if (hours == 24) {
			hours = 0;
		}
		if (secs & 1)
			sprintf(szTemp, "%02d:%02d", hours, min);
		else
			sprintf(szTemp, "%02d %02d", hours, min); 
		tm1637ShowDigits(szTemp);
		secs++;
		CLK_Delay_ms(1000);
	}
}
