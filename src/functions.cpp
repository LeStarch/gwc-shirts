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
#include "lily.h"
/**
 * Intensity:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, the count is used as an intensity. We use analogWrite to do a PWM signal which
 * dims the LED
 */
void Intensity :: run(int pin) {
	//Static variables will persist across function calls
	static int count = 1024; //Roughly a 1S dimming, but a multiple of 256
	analogWrite(pin, (1024 - count) >> 2); //Reversed to start low and grow in intensity;
	count -= 1;
	//Wrap count back to the begining if the count expires
	if (count == 0) {
		count = 1024;
	}
}

/**
 * Blink Fast:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * small count will blink fast.
 */
void BlinkFast :: run(int pin) {
	//Static variables will persist across function calls
	static int count = 200;
	static int state = HIGH;
	//If the 200 ms count expires, toggle the
	if (count == 0) {
		//Toggle state
		state = !state;
		digitalWrite(pin, state);
		count = 200;
	}
	count -= 1;
}

/**
 * Blink Slow:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * large count will blink slow.
 */
void BlinkSlow :: run(int pin) {
	//Static variables will persist across function calls
	static int count = 1000;
	static int state = HIGH;
	//If the 1000 ms count expires, toggle the
	if (count == 0) {
		//Toggle state
		state = !state;
		digitalWrite(pin, state);
		count = 1000;
	}
	count -= 1;
}

/**
 * Blink Burst:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, there are 2 counters. One causes the LED to blink very fast, and the other stops these
 * "bursts" for a number of cycles.
 */
void BlinkBurst :: run(int pin) {
	//Static variables will persist across function calls
	static int count = 50; //50ms blink
	static int long_count = 1000; //1000ms envelope
	static int off_time = 400; //For 400ms, remain off
	static int state = HIGH;
	//If the 10 ms count expires, blink the led unless long count is too low
	if (count == 0) {
		//Toggle state
		state = !state;
		digitalWrite(pin, state && (long_count > off_time));
		count = 50;
	}
	//Loop long count
	if (long_count == 0) {
		long_count = 1000;
	}
	long_count -= 1;
	count -= 1;
}
