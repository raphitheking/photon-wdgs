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
// This #include statement was automatically added by the Particle IDE.
#include "photon-wdgs/photon-wdgs.h"



unsigned long lastmsg=millis();





void setup() {
    
    Particle.publish("watchdog_test", "Onlinev1");
/* Start both watchdogs: the WWDG and IWDG.
 * It is recommended to use both watchdogs. They run on different
 * HW clocks (the WWDG same as your code, IWDG on its own).
 * 
 * This library depends on SparkIntervalTimer (see https://github.com/pkourany/SparkIntervalTimer)
 * To decide which HW timer to use for the WWDGs see here: https://github.com/pkourany/SparkIntervalTimer#1-using-hardware-timers-
 */
    PhotonWdgs::begin(true,true,10000,TIMER7);
    

}




void loop() {
    // call tickle regularly from your code, to ensure the watchdogs do not reset
    PhotonWdgs::tickle();
    if(lastmsg + 3000UL < millis()){
        Particle.publish("watchdog_test", "ALIVE!");
        lastmsg = millis();
    }

}

