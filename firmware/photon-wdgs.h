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
#ifndef _PHOTON_WDGS_LIB
#define _PHOTON_WDGS_LIB

#include "application.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"
namespace PhotonWdgs{
  
    extern IntervalTimer _wdgTimer;
    extern unsigned long _aliveCount;
    extern unsigned long _timeoutval;
    extern bool _wwdgRunning;
    extern bool _iwdgRunning;
    
    void _tickleWDGs();

    
    //_timeout = timout for calling tickle in msec (percision = 10ms)
    /* @brief Starts one or both watchdogs. The first two parameters are
     * flags to start the watchdogs, the timeout is specified in milliseconds
     * and tells the watchdog(s) when to reset if tickle() is not called. Last
     * the HW timer is specified using the TIMER constants from SparkIntervalTimer
     * library. We recommend using TIMER7.
     */
    void begin(bool _enableWwdg,bool _enableIwdg,unsigned long _timeout, TIMid id);
    /* @brief When having activated one or both watchdogs you need to call this
     * function regularly from your program. If you don't call it during or before
     * the specified timeout is reached, the watchdog(s) will reset.
     */
    void tickle();
      
      



}
#endif
