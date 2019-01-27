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
 * These functions are various implementations of the "run" function of the
 * LedFunction class.  Which is a functor, or class wrapping a function that
 * can vary in subclasses. This allows a class tree to perform different functions
 * but still look like a class tree.
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
	analogWrite(pin, (1024 - m_count) >> 2); //Reversed to start low and grow in intensity;
	m_count -= 1;
	//Wrap count back to the begining if the count expires
	if (m_count == 0) {
		m_count = 1024;
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
	//If the 200 ms count expires, toggle the
	if (m_count == 0) {
		//Toggle state
		m_state = !m_state;
		digitalWrite(pin, m_state);
		m_count = 200;
	}
	m_count -= 1;
}
/**
 * Blink Slow:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * large count will blink slow.
 */
void BlinkSlow :: run(int pin) {
	//If the 1000 ms count expires, toggle the
	if (m_count == 0) {
		//Toggle state
		m_state = !m_state;
		digitalWrite(pin, m_state);
		m_count = 1000;
	}
	m_count -= 1;
}
/**
 * Blink Burst:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, there are 2 counters. One causes the LED to blink very fast, and the other stops these
 * "bursts" for a number of cycles.
 */
void BlinkBurst :: run(int pin) {
	//If the 10 ms count expires, blink the led unless long count is too low
	if (m_count == 0) {
		//Toggle state
		m_state = !m_state;
		digitalWrite(pin, m_state && (m_long_count > m_off_time));
		m_count = 50;
	}
	//Loop long count
	if (m_long_count == 0) {
		m_long_count = 1000;
	}
	m_long_count -= 1;
	m_count -= 1;
}

/**
 * Constructors and Destructors for every class. These setup and tear down the
 * classes, setup member variables etc. They are needed for the code to work
 * but shouldn't need to be changed.
 */
Intensity :: Intensity() {
	//Member variables will persist across function calls
	m_count = 1024; //Roughly a 1S dimming, but a multiple of 256
}
BlinkFast::BlinkFast() {
	//Member variables will persist across function calls
	m_count = 200;
	m_state = HIGH;
}

BlinkSlow :: BlinkSlow() {
	//Member variables will persist across function calls
	m_count = 1000;
	m_state = HIGH;
}
BlinkBurst :: BlinkBurst() {
	m_count = 50; //50ms blink
	m_long_count = 1000; //1000ms envelope
	m_off_time = 400; //For 400ms, remain off
	m_state = HIGH;
}
//Destructors, no custom work needed
LedFunction :: ~LedFunction() {};
Intensity :: ~Intensity() {};
BlinkSlow :: ~BlinkSlow() {};
BlinkFast :: ~BlinkFast() {};
BlinkBurst :: ~BlinkBurst() {};
