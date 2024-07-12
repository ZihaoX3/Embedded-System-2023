#include "joyStick.h"

// Faster than calculating angles.
// Computes the direction.
uint8_t JoyStick::getDirection(){
    uint8_t dy;
    // 1: Up
    if(this->y < 250){
        dy = 1;
    }
    // 2: Down
    else if(this->y > 750){
        dy = 2;
    }
    // 0: Origin.
    else{
        dy = 0;
    }
    uint8_t dx;
    // 3: Right
    if(this->x < 250){
        dx = 3;
    }
    // 4: Left
    else if(this->x > 750){
        dx = 4;
    }
    // 0: Origin
    else{
        dx = 0;
    }

    // Up if y is smaller otherwise Right.
    if(dx == 3 && dy == 1){
        return (x > y) ? 1 : 3;
    }
    // Up if 1024-y is smaller otherwise Left.
    else if(dx == 4 && dy == 1){
        return (x > (1024 - y)) ? 1 : 4;
    }
    // Down if y is smaller otherwise Right.
    else if(dx == 3 && dy == 2){
        return ((1024 - x) > y) ? 2 : 3;
    }
    // Down if y is smaller otherwise Left.
    else if(dx == 4 && dy == 2){
        return (x > y) ? 4 : 2;
    }
    // If dx at origin return dy.
    else if(dx == 0){
        return dy;
    }
    // If dy at origin return dx.
    else if(dy == 0){
        return dx;
    }
    // Origin
    else{
        return 0;
    }
}

// Update the current coordinates.
void JoyStick::updateXY(uint16_t x, uint16_t y){
    this->x = x;
    this->y = y;
}
