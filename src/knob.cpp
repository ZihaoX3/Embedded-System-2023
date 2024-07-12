#include "knob.h"

// Set the ID and this->rotation limits.
Knob::Rotation::Rotation(uint8_t ID, int8_t upper, int8_t lower){
    this->knobID = ID;
    this->upperLimit = upper;
    this->lowerLimit = lower;
    this->rotation = lower;
}

// Returns the knobID.
uint8_t Knob::Rotation::ID(){
    return this->knobID;
}

// Getter for this->rotation.
int32_t Knob::Rotation::getRotation(){
    return this->rotation;
}

// Update the rotation.
void Knob::Rotation::updateRotation(uint8_t currentAB){
    int8_t increment = this->decode(this->previousAB, currentAB);
    increment = limitIncrement(increment);
    __atomic_store_n(&this->rotation, this->rotation+increment, __ATOMIC_RELAXED);
    this->previousAB = currentAB;
}

// Limits the increment based on the state of the rotation.
int8_t Knob::Rotation::limitIncrement(int8_t increment){
    if(increment == 1 && this->rotation == this->upperLimit)
        increment = 0;
    else if(increment == -1 && this->rotation == this->lowerLimit)
        increment = 0;
    return increment;
}

// Decode the rotation of the knob.
int8_t Knob::Rotation::decode(uint8_t previousAB, uint8_t currentAB){
    // Odd knobNumber then AB stored in 2 LSB bits.
    // Even knobNumber then AB stored in 2 MSB bits.
    uint8_t mask = (this->knobID % 2 == 0) ? 0b1100 : 0b0011;
    uint8_t shiftAmount = (this->knobID % 2 == 0) ? 2 : 0;
    // Combine both numbers.
    uint8_t transitionState = ((previousAB & mask) >> shiftAmount) << 2;
    transitionState |= (currentAB & mask) >> shiftAmount;

    // Moving +1.
    if(transitionState == 0x1 || transitionState == 0xE)
        this->prevIncrement = +1;
    // Moving -1.
    else if(transitionState == 0x4 || transitionState == 0xB)
        this->prevIncrement = -1;
    // Impossible transitions.
    else if(transitionState == 0x3 || transitionState == 0x6 || transitionState == 0x9 || transitionState == 0xC)
        return this->prevIncrement;
    // No change + Intermediate states.
    else
        this->prevIncrement = 0;

    return this->prevIncrement;
}

