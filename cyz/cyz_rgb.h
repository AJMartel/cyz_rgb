#ifndef _CYZ_RGB_H_
#define _CYZ_RGB_H_

/*****************************************************************************
 *	Codalyze PWM RGB: A very basic implementation of pulse-width modulation (PWM) on an AVR controller with
 *  three leds of different color(R,G,B): display any 24-bit color using three leds.
 *
 *	PWM in Plain English:
 *	 PROBLEM:	We have three leds, each led has two positions (on/off): we can only get 8 colors.
 *				We fancy displaying 24-bit rgb colors.
 *
 *	 SOLUTION:	We turn leds on and off very fast and trick the eye. ex: we want to display
 *				RGB{255, 165, 0} (orange): overy 255 ticks
 *				- red led is always on
 *				- green led is on for the first 165 ticks and then is off
 *				- blue led is always off
 *	 Much more detail on wikipedia.
 *
 *	This code has been implemented for and tested on ATtiny45 with 3 leds connected on PB3, PB4, PB1.
 *	It should work on all avr chips, just remember to update definitions of
 *	PWM_PORT,PWM_DDR, PINRED, PINGRN, PINBLU according to your setup.
 *
 *	Compiler: AVR-GCC
 *
 *	Usage:
 *		1. invoke CYZ_RGB_setup(); in global space
 *		2. invoke CYZ_RGB_init(); in main
 *		3. invoke CYZ_RGB_pulse(); at fixed intervals;
 *		   putting it in SIGNAL(SIG_OVERFLOW0) {} works good (initialize timers and signals, if you do)
 *		4. every time CYZ_RGB_set_color(red, green, blue) is called, the perceived color will change
 *		   if CYZ_RGB_set_color(red, green, blue) is called, the color fades from one color to the other
 *
 *	Links:
 *	ATtiny45 - http://www.atmel.com/dyn/products/Product_card.asp?part_id=3618
 *
 *	Author: Matteo Caprari <matteo.caprari@gmail.com>
 *	Thanks to: Lorenzo Grespan, Todd E. Kurt, AVR Application note 136: Low-jitter Multi-channel Software PWM
 *
 *	License: new BSD license
 *******************************************************************************/

/* select port and data direction register on which pin leds are */
#include <stdlib.h>
#include "color.h"
#include "io.h"

void CYZ_RGB_init();
void _CYZ_RGB_fade_step_component(uint8_t*, uint8_t*);

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))


#endif

/* BlinkM Original */
#if defined( __AVR_ATtiny45__ ) | \
    defined( __AVR_ATtiny85__ )
#define BLINKM_TYPE_BLINKM
#endif

/* BlinkM MaxM */
#if defined( __AVR_ATtiny44__ ) | \
    defined( __AVR_ATtiny84__ )
#define BLINKM_TYPE_MAXM
#endif


