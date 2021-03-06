/*
 * ledmap.cpp:
 *
 * This file assigns which functor (from functions.cpp) is run on each LED.
 * Here we have two parallel arrays. One lists the pins in-order, and the
 * other sets the functors which run on those pins (in the same order).
 *
 *  Created on: Jan 26, 2019
 *      Author: lestarch
 */
#include <lily.h>

//Order of LEDs
int OUTPUT_LEDS[PIN_COUNT] = {PIN_2, PIN_12, PIN_7, PIN_9, HEALTH};

//Order of functions (same as above).
//CHANGE ME: to assign different behavior to the above pins.
LedFunction* FUNC_LEDS[PIN_COUNT] = {new BlinkFast(), new BlinkBurst(), new BlinkSlow(), new BlinkBurst(), new BlinkSlow()};


