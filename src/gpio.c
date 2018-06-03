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

#include "gpio.h"

/// <summary>
/// Configures the pin according to the provided mode
/// </summary>
void GPIO_Config_Pin(gpio_port_t port, gpio_pin_t pins,
	unsigned char pin_mode) {

	if(pin_mode > 0x07) {
		//TODO figure out to implement PIN_MODE_OUTPUT_TRUE_OD
		return; //for now, supported modes are 0 to 7
	}

	//set DDR, CR1 and CR2 registers
	//DDR is the 3rd bit of pin_mode
	((pin_mode & ( 1 << 2)) >> 2) == 1 ? 
	*(port + GPIO_OFST_DDR) = pins & 0xFF :
	pins & 0x00;

	//CR1 is the 2nd bit of pin_mode
	((pin_mode & ( 1 << 1)) >> 1) == 1 ? 
	*(port + GPIO_OFST_CR1) = pins & 0xFF :
	pins & 0x00;

	//CR2 is the 1st bit of pin_mode
	((pin_mode & ( 1 << 0)) >> 0) == 1 ? 
	*(port + GPIO_OFST_CR2) = pins & 0xFF :
	pins & 0x00;
}


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
void GPIO_Set_Pin_High(gpio_port_t port, gpio_pin_t pins) {
	*port |= pins;
}

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
void GPIO_Set_Pin_Low(gpio_port_t port, gpio_pin_t pins) {
	*port &= ~(pins);
}

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
void GPIO_Toggle_Pin(gpio_port_t port, gpio_pin_t pins) {
	*port ^= pins;
}

/// <summary>
/// Read pin(s) input level
/// </summary>
unsigned char GPIO_Read_Pin(gpio_port_t port, gpio_pin_t pin) {
	return *(port + GPIO_OFST_IDR) & pin;
}

/// <summary>
/// Read entire input state of pins of a port
/// </summary>
unsigned char GPIO_Read_Port(gpio_port_t port) {
	return *(port + GPIO_OFST_IDR);
}
