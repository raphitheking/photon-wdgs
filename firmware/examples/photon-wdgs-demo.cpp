// This #include statement was automatically added by the Particle IDE.
#include "wdgs.h"



unsigned long lastmsg=millis();





void setup() {
    
    Particle.publish("watchdog_test", "Onlinev1");
    PhotonWdgs::begin(true,true,10000,TIMER7);
    

}




void loop() {

    //PhotonWdgs::tickle();
    if(lastmsg + 3000UL < millis()){
        Particle.publish("watchdog_test", "ALIVE!");
        lastmsg = millis();
    }

}

