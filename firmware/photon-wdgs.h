#ifndef _PHOTON_WDGS_LIB
#define _PHOTON_WDGS_LIB

#include "application.h"
#include "SparkIntervalTimer/SparkIntervalTimer.h"
namespace PhotonWdgs{
  
    extern IntervalTimer _wdgTimer;
    extern unsigned long _aliveCount;
    extern unsigned long _timeoutval;
    extern bool _wwdg_running;
    extern bool _iwdg_running;
    
    void _tickleWDGs();

    
    //_timeout = timout for calling tickle in msec (percision = 10ms)
    void begin(bool _enable_wwdg,bool _enable_iwdg,unsigned long _timeout, TIMid id);
    void tickle();
      
      



}
#endif
