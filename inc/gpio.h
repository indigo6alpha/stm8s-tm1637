// indigo6alpha's GPIO library for STM8SF103F3 MCU
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

#ifndef GPIO_H
#define GPIO_H

/* ------------------- TYPES  ------------------- */
typedef unsigned char* 	gpio_port_t;
typedef unsigned char	gpio_pin_t;

/* ------------------- REGISTERS -------------- */
#define GPIO_OFST_ODR			0x0000
#define GPIO_OFST_IDR			0x0001
#define GPIO_OFST_DDR			0x0002
#define GPIO_OFST_CR1			0x0003
#define GPIO_OFST_CR2			0x0004

#define GPIO_PORT_A			(gpio_port_t)0x5000

#define GPIO_PORT_B			(gpio_port_t)0x5005

#define GPIO_PORT_C			(gpio_port_t)0x500A

#define GPIO_PORT_D			(gpio_port_t)0x500F

#define GPIO_PORT_E 			(gpio_port_t)0x5014

#define GPIO_PORT_F 			(gpio_port_t)0x5019

/* ------------------- PINS ------------------- */
#define GPIO_PIN_0		1
#define GPIO_PIN_1		2
#define GPIO_PIN_2		4
#define GPIO_PIN_3		8
#define GPIO_PIN_4		16
#define GPIO_PIN_5		32
#define GPIO_PIN_6		64
#define GPIO_PIN_7		128
#define GPIO_PIN_ALL		255

/* ------------------- DIRECTOIN -------------- */
#define PIN_DIR_IN	0
#define PIN_DIR_OUT	1

/* ------------------- MODES -------------- */
#define PIN_MODE_INPUT_FL_NO_INT	0x00
#define PIN_MODE_INPUT_FL_INT		0x01
#define PIN_MODE_INPUT_PU_NO_INT	0x02
#define PIN_MODE_INPUT_PU_INT		0x03
#define PIN_MODE_OUTPUT_OD		0x04
#define PIN_MODE_OUTPUT_OD_FAST		0x05
#define PIN_MODE_OUTPUT_PP		0x06
#define PIN_MODE_OUTPUT_PP_FAST		0x07
#define PIN_MODE_OUTPUT_TRUE_OD		0x08


/** CR1 OpenDrain Output Normal */
#define PIN_MODE_OD			0
/** CR1 PushPull Output Normal */
#define PIN_MODE_PP			1
/** CR2 OpenDrain Output FastMode */
#define PIN_MODE_ODF 			1


/* ---------- FUNCTION PROTO TYPES -------------- */

/// <summary>
/// Configures the pin according to the provided mode
/// </summary>
void GPIO_Config_Pin(gpio_port_t port, gpio_pin_t pins,
	unsigned char pin_mode);

/// <summary>
/// Set pin(s) to output HIGH
/// </summary>
/// <param name="port">
/// The port to be configured.
/// </param>
/// <param name="pins">
/// Pin(s) to be configured. This can be a single pin or a group of pins
/// For example: Send (GPIO_PIN_0 | GPIO_PIN_1) to set pin 0 and 1 together.
/// </param>
void GPIO_Set_Pin_High(gpio_port_t port, gpio_pin_t pins);

/// <summary>
/// Set pin(s) to output LOW
/// </summary>
/// <param name="port">
/// The port to be configured.
/// </param>
/// <param name="pins">
/// Pin(s) to be configured. This can be a single pin or a group of pins
/// For example: Send (GPIO_PIN_0 | GPIO_PIN_1) to set pin 0 and 1 together.
/// </param>
void GPIO_Set_Pin_Low(gpio_port_t port, gpio_pin_t pins);

/// <summary>
/// Reverses the pin(s) output level
/// </summary>
/// <param name="port">
/// The port to be toggled.
/// </param>
/// <param name="pins">
/// Pin(s) to be configured. This can be a single pin or a group of pins
/// For example: Send (GPIO_PIN_0 | GPIO_PIN_1) to set pin 0 and 1 together.
/// </param>
void GPIO_Toggle_Pin(gpio_port_t port, gpio_pin_t pins);

/// <summary>
/// Read pin(s) input level
/// </summary>
unsigned char GPIO_Read_Pin(gpio_port_t port, gpio_pin_t pin);
 
/// <summary>
/// Read entire input state of pins of a port
/// </summary>
unsigned char GPIO_Read_Port(gpio_port_t port);


#endif
