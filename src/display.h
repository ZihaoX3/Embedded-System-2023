#pragma once
#include <Arduino.h>
#include <U8g2lib.h>
#include <stdint.h>
#include "global.h"
#include <STM32FreeRTOS.h>
#include "knob.h"

namespace Display{
    // Piano notes
    const char notes[12] = {'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'G', 'A', 'A', 'B'};
    // Display driver object
    void pianoNotes();
    void updateTask(void * pvParameters);
    void Initialise();
};
