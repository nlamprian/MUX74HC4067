MUX74HC4067
===========

This is an Arduino library for interfacing the 74HC4067 multiplexers/demultiplexers.

![project](https://github.com/nlamprian/MUX74HC4067/wiki/assets/project.png)

Interface
---------

```cpp
MUX74HC4067(uint8_t en, int8_t s0, int8_t s1 = -1, int8_t s2 = -1, int8_t s3 = -1);
```
Class `constructor`. `en` is the Arduino pin to which the `EN` pin connects. `s0`-`s3` are the Ardunio pins to which the `S1`-`S3` pin connects. The use of `S1`-`S3` is optional. If not used, they should connect to either `VCC` or `GND` depending on what range of channels is used.
```cpp
void setChannel(int8_t pin, uint8_t set = ENABLED);
```
It selects a channel and connects it to the `SIG` pin by default. The second argument is optional. If the `DISABLED` constant is given as a 2nd argument, it selects the requested channel, but it doesn't enable the connection to the `SIG` pin.
```cpp
void enable();
```
It enables the connection of the `SIG` pin with a channel that was set earlier by calling either `setChannel` or `write`.
```cpp
void disable();
```
It disables the connection of the `SIG` pin with a channel that was set earlier by calling either `setChannel` or `write`.
```cpp
void signalPin(uint8_t sig, uint8_t mode, uint8_t type = DIGITAL);
```
It configures how the `SIG` pin is going to be regarded. Where will it connect to? Will it be an `INPUT` or an `OUTPUT` to the Arduino? Is it going to communicate `ANALOG` or `DIGITAL` signals? In the argument list, one should specify the Arduino pin to which the `SIG` pin connects, the mode of that pin, either `INPUT`, or `OUTPUT`, or `INPUT_PULLUP`, and the type of the signals to handle, either `ANALOG` or `DIGITAL`.
```cpp
int16_t read(int8_t chan_pin = -1);
```
It reads from a channel. It's always used after a call to `signalPin`. It has an optional argument. To use it without an argument, the `setChannel` method has to have been called earlier (it will read from that specified channel). If the signal pin was set to `DIGITAL`, `read` returns `HIGH` or `LOW`. If the signal pin was set to `ANALOG`, `read` returns the value read by the A/D converter. If `read` is called with argument the channel from which to read and `setChannel` was called earlier, `read` won't make any changes on that configuration (#channel and ENABLED/DISABLED).
```cpp
uint8_t write(int8_t chan_pin, uint8_t data, int8_t type = -1);
```
It writes to the requested channel. If the signal pin was set to `DIGITAL`, `data` should be `HIGH` or `LOW`. If the signal pin was set to `ANALOG`, `write` outputs a `PWM` signal, and `data` should be the signal's `duty cycle`. There is an optional argument, it's either `ANALOG` or `DIGITAL`, that overrides the configuration set for the signal pin... e.g. if the signal pin was set to `DIGITAL OUTPUT`, it can still output a `PWM` signal by providing to `write` as a 3rd argument, the constant `ANALOG`.

Examples
--------

There are five accompanying examples with the library that demonstrate some basic functionality.