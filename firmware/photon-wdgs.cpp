#include "photon-wdgs.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"
IntervalTimer PhotonWdgs::_wdgTimer;
unsigned long PhotonWdgs::_aliveCount;
unsigned long PhotonWdgs::_timeoutval;
bool PhotonWdgs::_wwdg_running;
bool PhotonWdgs::_iwdg_running;



void PhotonWdgs::_tickleWDGs() {
    if(PhotonWdgs::_iwdg_running) {
        IWDG_ReloadCounter();
    }
    if(PhotonWdgs::_wwdg_running) {
        if(_aliveCount < PhotonWdgs::_timeoutval) {
            WWDG_SetCounter(0x7F);
            PhotonWdgs::_aliveCount++;
        }
    }
    // deactivate WWDG if OTA updates pending
    if(System.updatesPending()) {
        if(PhotonWdgs::_wwdg_running) {
            WWDG_DeInit();
        }
        System.enableUpdates();
        PhotonWdgs::_wdgTimer.end();
    }
}

void PhotonWdgs::begin(bool _enable_wwdg,bool _enable_iwdg,unsigned long _timeout, TIMid id) {
    if(!_enable_wwdg && !_enable_iwdg) {
        // nothing to do ...
        return;
    }
    PhotonWdgs::_aliveCount = 0;
    PhotonWdgs::_timeoutval = _timeout / 10;
    
    RCC_LSICmd(ENABLE); //LSI is needed for Watchdogs

    PhotonWdgs::_wdgTimer.begin(PhotonWdgs::_tickleWDGs, 20, hmSec, id);
    // OTA updates won't work with watchdog enabled
    System.disableUpdates();
    PhotonWdgs::_wwdg_running = _enable_wwdg;
    if(_enable_wwdg) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
        WWDG_SetPrescaler(WWDG_Prescaler_8);
        WWDG_SetWindowValue(0x7F);
        WWDG_Enable(0x7F);
    }
    PhotonWdgs::_iwdg_running = _enable_iwdg;
    if(_enable_iwdg) {
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetPrescaler(IWDG_Prescaler_256);
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetReload(0xFFF);
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_Enable();
    }
}

void PhotonWdgs::tickle() {
    PhotonWdgs::_aliveCount = 0;
}

