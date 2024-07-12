#pragma once
#include <stdint.h>

/*
 * Outputs Joystick direction.
 * 0: JoyStick has not moved enough.
 * 1: Up.
 * 2: Down.
 * 3: Right.
 * 4: Left.
 *
 * */
class JoyStick{
    public:
        // Outputs the direction: 0, 1, 2 ,3, 4
        uint8_t getDirection();
        // Update the x and y coordinates of the joystick.
        void updateXY(uint16_t x, uint16_t y);

    private:
        // Current coordinates.
        uint16_t x;
        uint16_t y;
};

