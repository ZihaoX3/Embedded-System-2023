#pragma once

// ===============================================================================================
// Libraries
// -----------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <stdint.h>
#include "global.h"

// ===============================================================================================
// Constants
// -----------------------------------------------------------------------------------------------

// Pin definitions
// Row select and enable
const int RA0_PIN = D3;
const int RA1_PIN = D6;
const int RA2_PIN = D12;
const int REN_PIN = A5;

// Matrix input and output
const int C0_PIN = A2;
const int C1_PIN = D9;
const int C2_PIN = A6;
const int C3_PIN = D1;
const int OUT_PIN = D11;

//Joystick analogue in
const int JOYY_PIN = A0;
const int JOYX_PIN = A1;

// ===============================================================================================
// Matrix
// -----------------------------------------------------------------------------------------------

namespace Matrix{
    void setRow(uint8_t rowIdx);
    uint8_t readCols();
    void setOutMuxBit(const uint8_t bitIdx, const bool value);
    void readJoyStick();
};
