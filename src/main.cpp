#include <STM32FreeRTOS.h>
#include "display.h"
#include "global.h"
#include "matrix.h"
#include "knob.h"
#include "waveforms.hpp"
#include "keys.h"

// ===============================================================================================
// Global Variables
// -----------------------------------------------------------------------------------------------
U8G2_SSD1305_128X32_NONAME_F_HW_I2C u8g2(U8G2_R0);

volatile uint8_t keyArray[8];
volatile uint16_t joyStickByteX;
volatile uint16_t joyStickByteY;
JoyStick joyStick;
SemaphoreHandle_t keyArrayMutex;
volatile uint32_t currentStepSize = 0;
// Knob rotation detection.
Knob::Rotation knobRotation3(0, 8, 0);
Knob::Rotation knobRotation2(1, 4, 1);

// Set the page number;
volatile bool pageNumber = 0;

SelectButton selA('A');
SelectButton selB('B');
//lolxd 
// ===============================================================================================
// Constants
// -----------------------------------------------------------------------------------------------
const uint32_t interval = 100; //Display update interval

//Audio analogue out
const int OUTL_PIN = A4;
const int OUTR_PIN = A3;

//Output multiplexer bits
const int DEN_BIT = 3;
const int DRST_BIT = 4;
const int HKOW_BIT = 5;
const int HKOE_BIT = 6;

// Piano notes frequencies
const uint32_t stepSizes[12] = {51076922, 54112683, 57330004, 60740599, 64352276, 68178701, 72231589, 76528508, 81077269, 85899345, 91006452, 96418111};
PianoKeys pianoKeys(stepSizes);

// =============================================================================================== // Intermidiate Functions
// -----------------------------------------------------------------------------------------------

void sampleISR(){
    static uint32_t phaseAcc = 0;

    // Disables sound depending on the page number.
    if(pageNumber == 1){
        return;
    }

    switch(knobRotation2.getRotation()){
        case 1:
            phaseAcc = Waveform::sawtooth(phaseAcc);
            break;
        case 2:
            phaseAcc = Waveform::triangle(phaseAcc);
            break;
        case 3:
            phaseAcc = Waveform::square();
            break;
        case 4:
            break;
        default:;
    }

    int32_t Vout = (phaseAcc >> 24) - 128;
    // Volume control.
    if(knobRotation3.getRotation() == 0){
        Vout = 0;
    }
    else{
        Vout = Vout >> (8 - knobRotation3.getRotation());
    }

    analogWrite(OUTR_PIN, Vout + 128);
}

void scanKeysTask(void * pvParameters){
    const TickType_t xFrequency = 20 / portTICK_PERIOD_MS;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint8_t previousAB;
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // Read all the piano keys.
        for(uint8_t i = 0; i < 5; i++){
            Matrix::setRow(i);
            delayMicroseconds(3);
            xSemaphoreTake(keyArrayMutex, portMAX_DELAY);
            keyArray[i] = Matrix::readCols();
            xSemaphoreGive(keyArrayMutex);
            Matrix::readJoyStick();
        }

        if(pageNumber == 0){
            // Set the increment.
            xSemaphoreTake(keyArrayMutex, portMAX_DELAY);

            // Update knob 3 position.
            uint8_t index = (knobRotation3.ID() > 1) ? 3 : 4;
            knobRotation3.updateRotation(keyArray[index]);
            // Update knob 2 position.
            index = (knobRotation2.ID() > 1) ? 3 : 4;
            knobRotation2.updateRotation(keyArray[index]);

            // Update the piano keys states.
            uint16_t keys = (keyArray[2] << 8) | (keyArray[1] << 4) | (keyArray[0]);
            pianoKeys.updateKeyStates(keys);

            // Select buttons.
            selA.updateState(keys);
            selB.updateState(keys);

            xSemaphoreGive(keyArrayMutex);

            // Set the step size for sound.
            __atomic_store_n(&currentStepSize, pianoKeys.getPhase(), __ATOMIC_RELAXED);
        }
        else{
            xSemaphoreTake(keyArrayMutex, portMAX_DELAY);
            // Update the select buttons.
            uint16_t keys = (keyArray[2] << 8) | (keyArray[1] << 4) | (keyArray[0]);
            xSemaphoreGive(keyArrayMutex);
            // Select buttons.
            selA.updateState(keys);
            selB.updateState(keys);

        }

    }
}

// ===============================================================================================
// Main
// -----------------------------------------------------------------------------------------------

void setup() {
    // put your setup code here, to run once:

    //Set pin directions
    pinMode(RA0_PIN, OUTPUT);
    pinMode(RA1_PIN, OUTPUT);
    pinMode(RA2_PIN, OUTPUT);
    pinMode(REN_PIN, OUTPUT);
    pinMode(OUT_PIN, OUTPUT);
    pinMode(OUTL_PIN, OUTPUT);
    pinMode(OUTR_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(C0_PIN, INPUT);
    pinMode(C1_PIN, INPUT);
    pinMode(C2_PIN, INPUT);
    pinMode(C3_PIN, INPUT);
    pinMode(JOYX_PIN, INPUT);
    pinMode(JOYY_PIN, INPUT);

    //Initialise display
    Matrix::setOutMuxBit(DRST_BIT, LOW);  //Assert display logic reset
    delayMicroseconds(2);
    Matrix::setOutMuxBit(DRST_BIT, HIGH);  //Release display logic reset
    //u8g2.begin();
    Display::Initialise();
    Matrix::setOutMuxBit(DEN_BIT, HIGH);  //Enable display power supply

    //Initialise UART
    Serial.begin(9600);
 
    // Initialise Timer.
    TIM_TypeDef *Instance = TIM1;
    HardwareTimer *sampleTimer = new HardwareTimer(Instance);
    sampleTimer->setOverflow(22000, HERTZ_FORMAT);
    sampleTimer->attachInterrupt(sampleISR);
    sampleTimer->resume();

    // Initialise scanKeysTask thread.
    TaskHandle_t scanKeysHandle = NULL;
    xTaskCreate(scanKeysTask, "scanKeys", 128, NULL, 2, &scanKeysHandle);

    // Initialise displayUpdateTask() thread.
    TaskHandle_t displayUpdateHandle = NULL;
    xTaskCreate(Display::updateTask, "displayUpdate", 256, NULL, 1, &displayUpdateHandle);

    // Lock the keyArray.
    keyArrayMutex = xSemaphoreCreateMutex();
    // Start all threads.
    vTaskStartScheduler();
}

void loop(){}
