#include <Arduino.h>
#include "lily.h"

#define NUM_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))
/**
 * Loop:
 *
 * Loop function runs after setup and just keeps going forever and ever and ever and ever.
 * This function delays (waits) at the end to ensure that each function is called 1 time
 * every millisecond.
 */
void loop() {
	//Grab the start time in microseconds
	unsigned long start = micros();
	//Run all the functions
	for (unsigned int i = 0; i < NUM_ELEMENTS(OUTPUT_LEDS); i++)
	{
		FUNC_LEDS[i](OUTPUT_LEDS[i]);
	}
	//Calculate the time elapsed and if less than 1ms (1000 microseconds)
	//then wait, otherwise loop immediately
	unsigned long elapsed = (micros() - start);
	if (elapsed < 1000)
	{
		delayMicroseconds(1000 - elapsed);
	}
}

/**
 * Setup:
 *
 * Sets up the arduino functions needed during the loop. This basically amounts to setting  pin
 * modes, setting up the I2C device etc.
 */
void setup() {
	//Loop through all pins defined as output (in array OUTPUT_PINS) and set mode to be "OUTPUT"
	for (unsigned int i = 0; i < NUM_ELEMENTS(OUTPUT_LEDS); i++)
	{
		pinMode(OUTPUT_LEDS[i], OUTPUT);
	}

}
#if 0
/**
 * Main function:
 *
 * Some potential boards do not use the arduino compiler so this
 * mimics what the arduino compiler does.
 */
int main(int argc, char** argv) {
    setup();
    while(1) {
        loop();
    }
}
#endif
