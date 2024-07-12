#pragma once
#include <stdint.h>
#include <stdexcept>

namespace Knob
{
/*
 * Knob::Rotation
 * Decodes information from the A and B parts of the knob specified by 
 * the knobID and updates the current rotation of the knob.
 * The knob rotation is set within the limits specified by the user.
 * */
class Rotation{
    public:
        // Constructor: sets the knob ID and the rotation limits.
        Rotation(uint8_t knobID, int8_t upperLimit, int8_t lowerLimit);

        /*
         * Public Functions
         * */

        // Returns the current rotation.
        int32_t getRotation();
        // Updates the current rotation.
        void updateRotation(uint8_t currentAB);
        // Returns the knobID.
        uint8_t ID();

    private:
        /*
         * Private Variables
         * */

        // Limits for the rotation.
        int8_t upperLimit;
        int8_t lowerLimit;
        // ID for the knob.
        uint8_t knobID;
        // Previous increment.
        uint8_t prevIncrement = 0;
        // Previous knob AB information.
        uint8_t previousAB = 0;
        // Current rotation of knob.
        int32_t rotation = 0;

        /*
         * Private Functions
         * */

        // UPdates the increment depending on the state of rotation.
        int8_t limitIncrement(int8_t increment);
        // Decodes the knob signals.
        int8_t decode(uint8_t previousAB, uint8_t currentAB);
};
};

