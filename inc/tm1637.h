// indigo6alpha's TM1637 library for STM8SF103F3 MCU
// Project started 3/17/2018
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

#include <stdio.h>
#include <time.h>
#include "gpio.h"

/// <summary>
/// Sleep for the specified time (in ms). It internally just calls the CLK delay function defined in clock.h
/// </summary>
void usleep(int milliseconds);

/// <summary>
/// Initialize tm1637 with the clock and data pins
/// </summary>
int tm1637Init(gpio_port_t bClock, gpio_pin_t bClockP, gpio_port_t bData, gpio_pin_t bDataP);

/// <summary>
/// Start wire transaction
/// </summary>
static void tm1637Start(void);

/// <summary>
/// Stop wire transaction
/// </summary>
static void tm1637Stop(void);

/// <summary>
/// Get data acknowledgement
/// </summary>
static unsigned char tm1637GetAck(void);

/// <summary>
/// Write a unsigned char to the controller
/// </summary>
static void tm1637WriteByte(unsigned char b);

/// <summary>
/// Write a sequence of unsigned chars to the controller
/// </summary>
static void tm1637Write(unsigned char *pData, unsigned char bLen);

/// <summary>
/// Set brightness (0-8)
/// </summary>
void tm1637SetBrightness(unsigned char b);

/// <summary>
/// Display a string of 4 digits and optional colon
/// by passing a string such as "12:34" or "45 67"
/// </summary>
void tm1637ShowDigits(char *pString);