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
#include "photon-wdgs.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"
IntervalTimer PhotonWdgs::_wdgTimer;
unsigned long PhotonWdgs::_aliveCount;
unsigned long PhotonWdgs::_timeoutval;
bool PhotonWdgs::_wwdgRunning;
bool PhotonWdgs::_iwdgRunning;



void PhotonWdgs::_tickleWDGs() 
{
    if(_aliveCount < PhotonWdgs::_timeoutval) {
        if(PhotonWdgs::_wwdgRunning) {
            WWDG_SetCounter(0x7F);
        }
        if(PhotonWdgs::_iwdgRunning) {
            IWDG_ReloadCounter();
        }
        PhotonWdgs::_aliveCount++;
    }
    // deactivate WWDG if OTA updates pending
    if(System.updatesPending()) {
        if(PhotonWdgs::_wwdgRunning) {
            WWDG_DeInit();
        }
        System.enableUpdates();
        PhotonWdgs::_wdgTimer.end();
    }
}

void PhotonWdgs::begin(bool _enableWwdg,bool _enableIwdg,unsigned long _timeout, TIMid id) 
{
    if(!_enableWwdg && !_enableIwdg) {
        // nothing to do ...
        return;
    }
    PhotonWdgs::_aliveCount = 0;
    PhotonWdgs::_timeoutval = _timeout / 10;
    
    RCC_LSICmd(ENABLE); //LSI is needed for Watchdogs

    PhotonWdgs::_wdgTimer.begin(PhotonWdgs::_tickleWDGs, 20, hmSec, id);
    // OTA updates won't work with watchdog enabled
    System.disableUpdates();
    PhotonWdgs::_wwdgRunning = _enableWwdg;
    if(_enableWwdg) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
        WWDG_SetPrescaler(WWDG_Prescaler_8);
        WWDG_SetWindowValue(0x7F);
        WWDG_Enable(0x7F);
    }
    PhotonWdgs::_iwdgRunning = _enableIwdg;
    if(_enableIwdg) {
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetPrescaler(IWDG_Prescaler_256);
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetReload(0xFFF);
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_Enable();
    }
}

void PhotonWdgs::tickle() 
{
    PhotonWdgs::_aliveCount = 0;
}

void PhotonWdgs::stopWwdg()
{
    WWDG_DeInit();
}
