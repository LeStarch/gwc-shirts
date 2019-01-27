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
 * This file defines the functors used to blink each LED.  It defines the code
 * which blink various LEDs.
 *
 * Each functor is called every millisecond, and thus for each millisecond the
 * functor determines if the LED is on or off. Think animation where each frame
 * is a millisecond long. Here each LED step (or frame) is 1-millisecond long.
 *
 * What is a functor? A functor is a class that wraps a named function.  This
 * allows us to treat functions like data, and store them in arrays etc.
 *
 * Here each class defines a "run" function, and that "run" function is called
 * to perform the action.  The "run" functions are the do different things but
 * are treated the same.  Thus we can get different behavior, but loop over the
 * functions.
 *
 *  Created on: Jan 26, 2019
 *      Author: lestarch
 */
#include <Arduino.h>

#define PIN_COUNT 5

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
extern LedFunction* FUNC_LEDS[PIN_COUNT];

/**
 * LedFunction:
 *
 * A base class. Shows what the custom functors below should look like.
 *
 * Specifically, they must override "virtual void run(int pin);"
 */
class LedFunction {
	//
	public:
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
	public:
		Intensity();
		void run(int pin);
		virtual ~Intensity();
	private:
		int m_count;
};
/**
 * Blink Fast:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * small count will blink fast.
 */
class BlinkFast : public LedFunction {
	public:
		BlinkFast();
		void run(int pin);
		virtual ~BlinkFast();
	private:
		//Static variables will persist across function calls
		int m_count;
		int m_state;
};

/**
 * Blink Slow:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, when the count expires the LED will switch state (ON -> OFF; OFF -> ON). This means a
 * large count will blink slow.
 */
class BlinkSlow : public LedFunction {
	public:
		BlinkSlow();
		void run(int pin);
		virtual ~BlinkSlow();
	private:
		//Static variables will persist across function calls
		int m_count;
		int m_state;
};
/**
 * Blink Burst:
 *
 * This function is called 1 time every millisecond. It is part of the 1MS "rate group". In this
 * function, there are 2 counters. One causes the LED to blink very fast, and the other stops these
 * "bursts" for a number of cycles.
 */
class BlinkBurst : public LedFunction {
	public:
		BlinkBurst();
    	void run(int pin);
    	virtual ~BlinkBurst();
	private:
    	int m_count; //50ms blink
    	int m_long_count; //1000ms envelope
    	int m_off_time; //For 400ms, remain off
    	int m_state;
};



#endif /* SRC_LILY_H_ */
