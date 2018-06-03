// indigo6alpha's CLK library for STM8SF103F3 MCU
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

#include "clock.h"

/// <summary>
/// Initialize CLK on the MCU
/// </summary>
void CLK_Init(unsigned char clk_src, unsigned char ps
	, unsigned char cpu_div) {

	//return if settings are already what user wants
	if(CLK_SWCR == clk_src) {
		//TODO simplify this for less instructions!
		//check if CPU_DIV is bigger than Fmaster/8
		//check if 2nd but if CPU_CLKDIVR is 1 it means Fcpu is 
		//divided by bigger than 8
		return;
	}

	if(clk_src == CLK_SRC_HSI) {
		//set dividers
		CLK_CKDIVR = (ps << 3) | (cpu_div << 0);
		return;
	}

	if(clk_src == CLK_SRC_HSE) {

		CLK_ECKRR |= 0x1 >> 0;
		CLK_SWCR |= 1 << 1;
		CLK_SWR = clk_src;
	}
	//wait for clock source to change
	while(CLK_SWR != CLK_CMSR) { /* DO NOTHING */};
}


/// <summary>
/// Delay routine for milliseconds for 16MHz clock
/// </summary>
void CLK_Delay_ms(unsigned long ms) {
	unsigned long cycles = CLK_DELAY_CYCLES_MS_16 * ms;
	volatile unsigned long int i = 0;
	for(i = 0; i < cycles; i++) {
		/* DO NOTHING BUT WASTE CYCLES */
	}
}


