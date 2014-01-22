/**
 * This example demonstrates how to combine reading inputs and writing
 * outputs, whether they are digital or analog
 * It assumes there are 2 push buttons with pullup resistors connected
 * to channels C0 and C1, 2 potentiometers connected to channels C2
 * and C3, and 4 LEDs+resistors with the positive lead of the LEDs 
 * connected to channels C4 to C7
 * PIN A0 is used for reading the inputs and should connect to the SIG pin
 * PIN 3 is used for writing the outputs and should connect to the SIG pin
 * Connecting both PIN A0 and PIN 3 to the SIG pin won't create a problem
 * because when the pins are not used, they are declared as inputs which 
 * puts them in a high impedance state
 * 
 * For more about the interface of the library go to
 * https://github.com/pAIgn10/MUX74HC4067
 */

#include "MUX74HC4067.h"

// Creates a MUX74HC4067 instance
// 1st argument is the Arduino PIN to which the EN pin connects
// 2nd-4th arguments are the Arduino PINs to which the S0-S2 pins connect
// Only channels C0-C7 are used, so pin S3 should connect to GND
MUX74HC4067 mux(7, 8, 9, 10);

void setup()
{

}

// Reads the state of the push buttons and the potentiometers
// and outputs to the LEDs a corresponding value:
// * HIGH is the buttons are pressed, LOW otherwise
// * A PWM signal with duty cycle that depends on the pots' position
void loop()
{
	int data[4];

	// Reads the 2 push buttons at channels C0 and C1
	mux.signalPin(A0, INPUT);
	for (byte i = 0; i < 2; ++i) data[i] = mux.read(i);

	// Reads the 2 potentiometers at channels C2 and C3
	mux.signalPin(A0, INPUT, ANALOG);
	for (byte i = 2; i < 4; ++i) data[i] = mux.read(i);

	pinMode(A0, INPUT);  // Puts PIN A0 in a high impedance state

	// Writes to the 2 LEDs at channels C4 and C5 HIGH
	// or LOW according to the state of the push buttons
	mux.signalPin(3, OUTPUT);
	for (byte i = 0; i < 2; ++i) { mux.write(i+4, !data[i]);
								   delay(300); }

	// Outputs a PWM signal to the 2 LEDs at channels C6 and C7
	// according to the position of the potentiometers
	mux.signalPin(3, OUTPUT, ANALOG);
	for (byte i = 2; i < 4; ++i) { mux.write(i+4, data[i]);
								   delay(300); }
	
	// Puts PIN 3 in a high impedance state
	digitalWrite(3, LOW);
	pinMode(3, INPUT);
	
	mux.disable();
}
