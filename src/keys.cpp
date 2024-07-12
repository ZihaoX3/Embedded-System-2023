#include "keys.h"

PianoKeys::PianoKeys(const uint32_t stepSizes[12]){
    for(int i = 0; i < 12; i++){
        Key temp(stepSizes[i]);
        pianoKeys.push_back(temp);
    }
}

uint32_t PianoKeys::getPhase(){
    uint32_t phase = 0;
    uint8_t pressedCount = 0;

    for(auto key : pianoKeys){
        if(key.state == true){
            phase += key.stepSize;
            pressedCount++;
        }
    }

    // TODO: how to improve this?
    if(pressedCount > 0){
        phase /= pressedCount;
    }
    return phase;
}

void PianoKeys::updateKeyStates(uint16_t keys){
    for(size_t i = 0; i < 12; i++){
        uint8_t bitState = (keys >> i) & 0x1;
        if(bitState == 0){ // If asserted.
            this->pianoKeys[i].updateState(true);
        }
        else{ // If deasserted.
            this->pianoKeys[i].updateState(false);
        }
    }
}

// Input: 'A' or 'B' only.
SelectButton::SelectButton(char buttonID){
    this->ID = buttonID;
}

// TODO: make safe accesses to state variables.
bool SelectButton::getState(){
    return this->pressed;
}

// Updates the state of the Select button.
// Input: keys = (keyArray[2] << 8) | (keyArray[1] << 4) | (keyArray[0]);
void SelectButton::updateState(uint16_t keys){
    if(this->ID == 'A'){
        this->pressed = (keys >> 9) & 0x1;
    }
    else if(this->ID == 'B'){
        this->pressed = (keys >> 11) & 0x1;
    }
    // Key assert: 0 -> 1
    // Key deasserted: 1 -> 0
    this->pressed = !this->pressed;
}
