#pragma once

enum ChamberStates {

    // Default state: venting the chamber ("in" valve open)
    Vent,

    // Don't do anything hold chamber at current pressure (both valves closed)
    Hold,

    // Pumping down chamber to lowest pressure
    PumpDown,

    // Go to the target pressure
    ReachSetPressureQuick,

    // Pump chamber up/down at a certain rate in m
    AscendAtRate,

};

enum ValvePositions {
    Open,
    Close
};

struct ValveInstructions {

    // This is a vacuum system the "in" valve will vent the system to atmosphere!
    ValvePositions inPosition;

    // This is a vacuum system the "out" valve will be to the pump and pump the system down!
    ValvePositions outPosition;

};

// Current chamber state
extern ChamberStates chamberState;

// Ascend rate in m/s
extern float ascendRate;

ValveInstructions updateState(double pressure, double altitude);

void vent();

void hold();

void pumpDown();

/**
 * @param rate Ascend rate in m/s
 */
void ascendAtRate(float rate);

