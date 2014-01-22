/**
 * This example demonstrates how to write PWM signals
 * It assumes there are LEDs+resistors with the positive lead of the LEDs
 * connected to the 16 channels of the 74HC4067 mux/demux, respectively
 * 
 * For more about the interface of the library go to
 * https://github.com/pAIgn10/MUX74HC4067
 */

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-5th arguments are the Arduino PINs to which the S0-S3 pins connect
MUX74HC4067 mux(7, 8, 9, 10, 11);

void setup()
{
	// Configures how the SIG pin will be interfaced
	// e.g. The SIG pin connects to PIN 3 on the Arduino,
	//      and PIN 3 is a Analog (PWM) Output
	mux.signalPin(3, OUTPUT, ANALOG);
}

// Writes to the 16 channels a PWM output, one after the other
// At each next channel, the duty cycle of the PWM increases
void loop()
{
	for (byte i = 0; i < 16; ++i)
	{
		// Connects to channel i and outputs a PWM signal
		mux.write(i, i * 16 + 1);
		delay(200);
	}
	
	mux.disable();  // Disconnects the SIG pin from any channel
	delay(1000);
}
