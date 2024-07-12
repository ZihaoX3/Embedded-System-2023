#pragma once
#include <stdint.h>
#include <vector>


struct Key{
    Key(uint32_t step){
        this->stepSize = step;
    }
    void updateState(bool state_in){
        this->state = state_in;
    }
    bool state;
    bool prevState;
    uint32_t stepSize;
};

class PianoKeys{
    public:
        PianoKeys(const uint32_t stepSizes[12]);
        // Sums the phase of all the keys for polyphony.
        uint32_t getPhase();
        // Updates the states of all the keys using the keyArray.
        void updateKeyStates(uint16_t keys);

    private:
        std::vector<Key> pianoKeys;
};

/*
 * Reads the A or B piano keys.
 * Stores the state.
 * State can be read.
 * */
class SelectButton{
    public:
        // Constructor.
        // Input: 'A' or 'B' only.
        SelectButton(char ID);
        // Updates the pressed state of the object.
        // Input: keys = (keyArray[2] << 8) | (keyArray[1] << 4) | (keyArray[0]);
        void updateState(uint16_t keys);
        // Returns the "pressed" state of the object.
        bool getState();

    private:
        // The state of the key.
        bool pressed;
        // The ID of the button: 'A' or 'B' only.
        char ID;
};
