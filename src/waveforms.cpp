#include "waveforms.hpp"


// Piano sound: square waveform.
uint32_t Waveform::square(){

    static uint32_t localPhaseAcc = 0;
    // State = HIGH or LOW.
    static bool state = false;

    uint32_t phaseAccNext = localPhaseAcc + currentStepSize;
    // Overflow.
    if(phaseAccNext < localPhaseAcc){
        state = !state;
    }
    // Half way through flip.
    else if(phaseAccNext >= 0x7FFFFFFF && state == false){
        state = !state;
    }
    localPhaseAcc = phaseAccNext;

    return (state) ? 0xFFFFFFFF : 0x0;
}


// Piano sound: triangle waveform.
uint32_t Waveform::triangle(uint32_t phaseAcc){
    static int8_t gradient = +1;
    uint8_t frequencyScalar = 2;

    uint32_t phaseAccNext = (gradient == -1) ? phaseAcc - currentStepSize * frequencyScalar : phaseAcc + currentStepSize * frequencyScalar;

    // Overflow while positive gradient 
    if(gradient == +1 && phaseAccNext < phaseAcc){
        gradient = -1;
        return phaseAcc - currentStepSize * frequencyScalar;
    }
    else if(gradient == -1 && phaseAccNext > phaseAcc){
        gradient = +1;
        return phaseAcc + currentStepSize * frequencyScalar;
    }
    else{
        return phaseAccNext;
    }
}

// Piano sound: sawtooth waveform.
uint32_t Waveform::sawtooth(uint32_t phaseAcc){
    return phaseAcc + currentStepSize;
}
