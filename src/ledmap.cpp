/*
 * ledmap.cpp:
 *
 * This file assigns which function (from functions.cpp) is run on each LED.
 * Here we have two parallel arrays. One lists the pins in-order, and the
 * other sets the functions which run on those pins (in the same order).
 *
 *  Created on: Jan 26, 2019
 *      Author: lestarch
 */
#include <lily.h>

//Order of LEDs
int OUTPUT_LEDS[PIN_COUNT] = {PIN_2, PIN_12, PIN_7, PIN_9, HEALTH};

//Order of functions (same as above)
LedFunction& FUNC_LEDS[PIN_COUNT] = {BlinkFast(), BlinkBurst(), BlinkSlow(), BlinkBurst(), BlinkSlow()};


