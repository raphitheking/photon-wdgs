/*
The MIT License (MIT)

Copyright (c) 2015 Kevin Kasal, Alexander Partsch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
# photon-wdgs
Library to employ independent and window watchdogs of STM32F205 for the Particle Photon with the help of hardware timers.
See: http://stasheddragon.com/2015/watchdog-library-for-particle-photon/

# Why?
Sometimes faults can happen. Maybe its a bit in your code that gets flipped in ram, or a simple programming bug in your software. Electronic devices can get stuck and when this happens a watchdog is able to detect the problem and reset your device. This is especially helpful when you want to use your photon 24/7 or in hard to reach places.  

## Importing the Library
Normally you should use the Particle WebIDE to include this Project, but you could also manually add the .cpp and .h file to your particle project.

## Usage
Simply call `PhotonWdgs::begin` to start the watchdog, and reset it regularly by calling `PhotonWdgs::tickle()`
** IMPORTANT:
This library depends on the library [SparkIntervalTimer|https://github.com/pkourany/SparkIntervalTimer], so you must include it in your project as well **

** IMPORTANT:
The current status of the library does _not_ support sleeping once you started the watchdog(s) this will change in a future version, however please consider this if you are trying to run your project from batteries **

### begin(bool \_enable\_wwdg,bool \_enable\_iwdg,unsigned long \_timeout, TIMid id)
Starts one or both watchdogs. The first two parameters are
flags to start the watchdogs, the timeout is specified in milliseconds
and tells the watchdog(s) when to reset if tickle() is not called. Last
the HW timer is specified using the TIMER constants from SparkIntervalTimer
library. We recommend using TIMER7 if not otherwhise used in one of Projects.

 * \_enable\_wwdg:
	Enable this to use the Window Watchdog.
	This watchdog *can* be disabled during runtime in a future version of the library, however it uses the same clock source as the CPU itself so it is not as reliable as the independent watchdog.
 * \_enable\_iwdg:
	Enable this to use the independent watchdog.
	This watchdog *cannot* be disabled during runtime. It uses an independent clock source (LSI) and can trigger an reset even if the main clock goes down. * It is not possible to use this watchdog if you want to use low power modes (sleep) because the only option to deactivate it is a reset(hardware) *
 * \_timeout (in ms):
	Sets the maximum amount of time between calling tickle() in ms ( percision: 10ms, so avoid setting it lower ). Set this as low as possible. 
* id:
	Selects the hardware timer to use. We recommend *TIMER7*.



### tickle()

Call this function to reset the watchdog.

## If something goes wrong

If you accidently started the watchdog in your code and you do not call tickle somewhere within the given timout, your photon will reset. That could mean that you are unable to flash your photon OTA. There is a simple method to restore access to your photon by entering safe mode:

1. Hold down BOTH buttons
2. Release only the RESET button, while holding down the SETUP button.
3. Wait for the LED to start flashing magenta
4. Release the SETUP button
5. Flash another piece of software

