#include "lib/Subsystem.h"

Subsystem::Subsystem(){
    getController()->kP = 0;
    getController()->kI = 0;
    getController()->kD = 0;
}

Subsystem::Subsystem(float kP, float kI, float kD){
    getController()->kP = kP;
    getController()->kI = kI;
    getController()->kD = kD;
}