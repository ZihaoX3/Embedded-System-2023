# pragma once
#include <stdint.h>
#include <STM32FreeRTOS.h>
#include "knob.h"
#include "joyStick.h"
#include "keys.h"
#include <U8g2lib.h>

#ifndef GLOBAL_H
#define GLOBAL_H

extern volatile uint8_t keyArray[8];
// TODO: does this need to be volatile?
extern JoyStick joyStick;
extern SemaphoreHandle_t keyArrayMutex;
//extern const uint8_t knobID;
extern Knob::Rotation knobRotation3;
extern Knob::Rotation knobRotation2;
extern SelectButton selA;
extern SelectButton selB;
extern volatile uint32_t currentStepSize;
extern volatile bool pageNumber;
extern U8G2_SSD1305_128X32_NONAME_F_HW_I2C u8g2; //(U8G2_R0);

#endif
