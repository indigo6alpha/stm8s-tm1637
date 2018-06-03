// indigo6alpha's TM1637 library for STM8SF103F3 MCU
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
#include "tm1637.h"
#include "clock.h"

#define CLOCK_DELAY 0

#define LOW 0
#define HIGH 1


// Table which translates a digit into the segments
const unsigned char cDigit2Seg[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

static gpio_pin_t bClockPin, bDataPin;
static gpio_port_t bClockPort, bDataPort;


/// <summary>
/// Sleep for the specified time (in ms). It internally just calls the CLK delay function defined in clock.h
/// </summary>
void usleep(int milliseconds)
{
	CLK_Delay_ms(milliseconds);
}

/// <summary>
/// Initialize tm1637 with the clock and data pins
/// </summary>
int tm1637Init(gpio_port_t bClock, gpio_pin_t bClockP, gpio_port_t bData, gpio_pin_t bDataP)
{
	bClockPort = bClock;
	bDataPort = bData;
	bClockPin = bClockP;
	bDataPin = bDataP;
	GPIO_Config_Pin(bClockPort, bClockPin, PIN_MODE_OUTPUT_PP);
	GPIO_Config_Pin(bDataPort, bDataPin, PIN_MODE_OUTPUT_PP);
	GPIO_Set_Pin_Low(bClockPort, bClockPin);
	GPIO_Set_Pin_Low(bDataPort, bDataPin);
	return 0;
}

/// <summary>
/// Start wire transaction
/// </summary>
static void tm1637Start(void)
{
	GPIO_Set_Pin_High(bDataPort, bDataPin);
	GPIO_Set_Pin_High(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	GPIO_Set_Pin_Low(bDataPort, bDataPin);
}

/// <summary>
/// Stop wire transaction
/// </summary>
static void tm1637Stop(void)
{
	// clock low
	GPIO_Set_Pin_Low(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	// data low
	GPIO_Set_Pin_Low(bDataPort, bDataPin);
	usleep(CLOCK_DELAY);
	// clock high
	GPIO_Set_Pin_High(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	// data high
	GPIO_Set_Pin_High(bDataPort, bDataPin);
} 

/// <summary>
/// Get data ack
/// </summary>
static unsigned char tm1637GetAck(void)
{
	unsigned char bAck = 1;

	// read ack
	// clock to low
	GPIO_Set_Pin_Low(bClockPort, bClockPin);
	// data as input
	
	usleep(CLOCK_DELAY);

	// clock high
	GPIO_Set_Pin_High(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	// clock to low
	GPIO_Set_Pin_Low(bClockPort, bClockPin);
	return bAck;
}


/// <summary>
/// Write a unsigned char to the controller
/// </summary>
static void tm1637WriteByte(unsigned char b)
{
	unsigned char i;

	for (i=0; i<8; i++)
	{
		// clock low
		GPIO_Set_Pin_Low(bClockPort, bClockPin);
		// LSB to MSB
		if (b & 1) 
			GPIO_Set_Pin_High(bDataPort, bDataPin);
		else
			GPIO_Set_Pin_Low(bDataPort, bDataPin);
		usleep(CLOCK_DELAY);
		// clock high
		GPIO_Set_Pin_High(bClockPort, bClockPin);
		usleep(CLOCK_DELAY);
		b >>= 1;
	}
}

/// <summary>
/// Write a sequence of unsigned chars to the controller
/// </summary>
static void tm1637Write(unsigned char *pData, unsigned char bLen)
{
	unsigned char b, bAck;
	bAck = 1;
	tm1637Start();
	for (b=0; b<bLen; b++)
	{
		tm1637WriteByte(pData[b]);
		bAck &= tm1637GetAck();
	}
	tm1637Stop();
} 

/// <summary>
/// Set brightness (0-8)
/// </summary>
void tm1637SetBrightness(unsigned char b)
{
	unsigned char bControl;
	if (b == 0) 
		// display off
		bControl = 0x80; 
	else
	{
		if (b > 8) b = 8;
		bControl = 0x88 | (b - 1);
	}
	tm1637Write(&bControl, 1);
} 

/// <summary>
/// Display a string of 4 digits and optional colon
/// by passing a string such as "12:34" or "45 67"
/// </summary>
void tm1637ShowDigits(char *pString)
{
	// commands and data to transmit
	unsigned char b, bTemp[16]; 
	unsigned char i, j;

	j = 0;
	// memory write command (auto increment mode)
	bTemp[0] = 0x40;
	tm1637Write(bTemp, 1);

	// set display address to first digit command
	bTemp[j++] = 0xc0;
	for (i=0; i<5; i++)
	{
   	// position of the colon
		if (i == 2) 
		{
	  	// turn on correct bit
			if (pString[i] == ':')
			{
		 	// second digit high bit controls colon LEDs
				bTemp[2] |= 0x80;
			}
		}
		else
		{
			b = 0;
			if (pString[i] >= '0' && pString[i] <= '9')
			{
			// segment data
				b = cDigit2Seg[pString[i] & 0xf]; 
			}
			bTemp[j++] = b;
		}
	}
	// send to the display
	tm1637Write(bTemp, j); 
}