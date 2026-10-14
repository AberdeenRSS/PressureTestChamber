#include <chamber_state_machine.h>

// Current chamber state
ChamberStates chamberState = ChamberStates::Vent;

// Ascend rate in m/s
float ascendRate = 0;

ValveInstructions updateState(double pressure, double altitude){

    switch(chamberState){
        case ChamberStates::Vent:
            return { ValvePositions::Open, ValvePositions::Close };
        case ChamberStates::Hold:
            return { ValvePositions::Close, ValvePositions::Close };
        case ChamberStates::PumpDown:
            return { ValvePositions::Close, ValvePositions::Open };

        

        // Trigger venting by default
        default:
            return { ValvePositions::Open, ValvePositions::Close };
    }

}

void vent(){
    chamberState = ChamberStates::Vent;
}

void hold(){
    chamberState = ChamberStates::Hold;
}

void pumpDown(){
    chamberState = ChamberStates::PumpDown;
}

void ascendAtRate(float rate){
    chamberState = ChamberStates::AscendAtRate;
    ascendRate = rate;
}