# arduinoIO

> Object oriented input/output abstraction layer for Arduino

This is a library for [Arduino](https://www.arduino.cc/en/Main/Products#entrylevel) devices. 
It provides an abstraction layer for general purpose input/output scenarios to read pin states,
detect pin changes, debounce buttons, switch relays, blink leds and more.

__Please make sure to read the [requirements](#requirements)__!

## Background
When working with arduino code, a lot of tasks repeat when it comes to GPIO. Pins have to be
defined, pinModes to be set, values to be read and interpreted. Most of the code repeats for 
each pin used in a project. Also this repeating code is usually defined in the global scope,
which causes huge blocks of constants, initialization lines and conditional checks.

arduinoIO fixes this by providing classes to control digital and analog pins with single line
declaration and single line usage. Furthermore it abstracts logic for digital inputs so they 
can be active LOW without code changes.

To handle the common standard scenarios, arduinoIO provides advanced classes to handle buttons,
debouncing, timed outputs, delay free intervals (blinking) and more.


## Requirements

- [Arduino](https://www.arduino.cc/en/Main/Products#entrylevel) 
  (Should also work on teensy and other arduino compatible platforms!)

## Installation
### Releases

No releases, you have to clone or download [From source](#from-source)

### From source

1. Get your favourite [Arduino IDE](https://www.arduino.cc/en/main/software)
2. Clone the repository into your library directory  
   ```
   git clone https://github.com/rampage128/arduinoIO.git
   ```
3. Start a new sketch and add the library to it

## Usage

After importing `#import <arduinoIO.h>`, you can use the following features:

### Basic Input

*AnalogInput*
provides a simple way to read analog pins.
Create a new analog input like so:
```
AnalogInput someInput(int pinNumber, int compareMin, int compareMax, unsigned int debounceDuration = 20, int mode = INPUT)
```
* `pinNumber`: specifies the pin you want to read
* `compareMin`: specifies the minimum value (voltage) the pin is considered active
* `compareMax`: specifies the maximum value (voltage) the pin is considered active
* `debounceDuration`: the time in ms to use for debouncing the pins signal (defaults to 20ms)
* `mode`: the pinmode to use (defaults to `INPUT`)

*DigitalInput*
provides a simple way to read digital pins.
Create a new digital input like so:
```
DigitalInput someInput(int pinNumber, unsigned int debounceDuration = 20, boolean compareMode = HIGH, int mode = INPUT)
```
* `pinNumber`: specifies the pin you want to read
* `debounceDuration`: the time in ms to use for debouncing the pins signal (defaults to 20ms)
* `compareMode`: specifies the mode the pin is considered active (defaults to `HIGH`)
  (set this to `LOW` to have an active low pin)
* `mode`: the pinmode to use (defaults to `INPUT`)

*Usage*

All inputs let you check if they are active by calling `boolean getState()` on them.
```
someInput.getState();
```

### Advanced Input

*Button*
Advanced class to emulate a button. Internally it uses a basic input.
Create a new button like so:
```
Button someButton(new DigitalInput(...), unsigned int pushDurationLimit = 300)
```

* input: has to be a pointer to an `Input` object. It does not matter if an `AnalogInput` or `DigitalInput` is used.
* pushDurationLimit: To emulate multi-clicks on a button, the code has to wait for further clicks by the user, before determining the total amount of clicks.
  Since not all hardware might allow to be pressed equally fast, you can set this time limit. It defaults to 300ms. It can be set to 0ms to disable multi clicks.

To use the button, it's state has to be updated continuously. You can do this by calling `update()` on a button before performing any checks on it:
```
someButton.update();
```
  
The button allows you to perform various checks on it:

* `isPressed()`: returns `true` if the button is being pressed (only once).
* `wasPressedFor(unsigned int duration)`: returns `true` if the button was pressed and is released after the given `duration`.
* `wasPressedTimes(unsigned int count)`: returns `true` if the button was pressed (and released) as many times as specified in `count`.
* `wasPressedTimesOrMore(unsigned int count)`: returns `true` if the button was pressed (and released) as many times as specified in `count` *or more*.
* `isHeld()`: returns `true` continuously while the button is held down.
* `wasHeldFor(int duration, int repeatTime = 0)`: returns `true` after the button was held down for given `duration`. If `repeatTime` is specified, this also returns `true` every time this interval passes.

Example:
```
someButton.update();

if (someButton.wasPressedTimes(1)) {
  Serial.println("Button was pressed once!");
}
else if (someButton.wasPressedTimes(2)) {
  Serial.println("Button was pressed twice!");
}

if (someButton.wasHeldFor(500, 200)) {
  Serial.println("Volume up!");
}
```

### Basic Output

*AnalogOutput*
provides a simple way to write analog pins.
Create a new analog output like so:
```
AnalogOutput someOutput(int pinNumber, int normally = LOW)
```
* `pinNumber`: specifies the pin you want to write to
* `normally`: specifies in which state the pin should be inactive (defaults to LOW)

An analog pin can be set to any value using `set(int value)` on it.
If you want to check if the pin is not set to any value (inactive), you can call `boolean isActive()`.
To read its value you can call `int getState()`.
The pin can also be deactivated (be put to its value previously defined in `normally`) by using `deactivate()`.

*DigitalOutput*
provides a simple way to write digital pins.
Create a new digital output like so:
```
DigitalOutput someOutput(int pinNumber, int active = HIGH)
```
* `pinNumber`: specifies the pin you want to write to
* `active`: specifies in which state the pin should be active (defaults to HIGH)

Digital outputs can use the same features as analog outputs (explained above).
Additionally the abstraction of the state can be fully used:

You can activate the pin using `activate()`. 
Also you can toggle the pin by using `toggle(boolean state)` specifying if the pin should be active or not with the `state` flag.

"activating" and "deactivating" does not equal `HIGH` or `LOW`! "active" can be `HIGH` or `LOW` depending on the specified `active` parameter when the output was created!

### Advanced Output

For more information, please refer to the [source](https://github.com/rampage128/arduinoIO).

## Contribute

Feel free to [open an issue](https://github.com/rampage128/arduinoIO/issues) or submit a PR

Also, if you like this or other of my projects, please feel free to support me using the Link below.

[![Buy me a beer](https://img.shields.io/badge/buy%20me%20a%20beer-PayPal-green.svg)](https://www.paypal.me/FrederikWolter/1)

## Dependencies

No external dependencies :-)