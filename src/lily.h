/*
 * lily.h
 *
 * Pins and header definitions specifically for the lilypad version of the microcontroller.
 *
 *  Created on: Oct 26, 2018
 *      Author: starchmd
 */

#ifndef SRC_LILY_H_
#define SRC_LILY_H_

/*
 * functions.cpp:
 *
 * This file defines the functions used to blink each LED.  It defines the code
 * which blink various LEDs.
 *
 * Each function is called every millisecond, and thus for each millisecond the
 * function determines if the LED is on or off. Think animation where each frame
 * is a millisecond long. Here each LED step (or frame) is 1-millisecond long.
 *
 *  Created on: Jan 26, 2019
 *      Author: lestarch
 */
#include <Arduino.h>

#define PIN_COUNT 4

// Pin assignments. For the shirts we use, pins 2, 12, 7, 9 as LED pins.
#define PIN_2 2
#define PIN_12 12
#define PIN_7 7
#define PIN_9 9
#define HEALTH 13

class LedFunction;

//An array to hold the LEDs
extern int OUTPUT_LEDS[PIN_COUNT];
//An array to hold the functions on those LEDs
extern LedFunction& FUNC_LEDS[PIN_COUNT];


/**
 * LedFunction:
 *
 * A class
 */
class LedFunction {
	//
	virtual void run(int pin);
	virtual ~LedFunction();
};

/**
 * Intensity:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, the count is used as an intensity. We use analogWrite to do a PWM signal which
 * dims the LED
 */
class Intensity : public LedFunction {
    void run(int pin);
};
/**
 * Blink Fast:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * small count will blink fast.
 */
class BlinkFast : public LedFunction {
    void run(int pin);
};

/**
 * Blink Slow:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * large count will blink slow.
 */
class BlinkSlow : public LedFunction {
    void run(int pin);
};
/**
 * Blink Burst:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, there are 2 counters. One causes the LED to blink very fast, and the other stops these
 * "bursts" for a number of cycles.
 */
class BlinkBurst : public LedFunction {
    void run(int pin);
};



#endif /* SRC_LILY_H_ */
