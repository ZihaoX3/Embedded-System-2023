#include "matrix.h"

// ===============================================================================================
// Matrix Namespace definitions
// -----------------------------------------------------------------------------------------------

// Select a given row.
void Matrix::setRow(uint8_t rowIdx){
    digitalWrite(REN_PIN, LOW);
    digitalWrite(RA0_PIN, rowIdx & 0x01);
    digitalWrite(RA1_PIN, rowIdx & 0x02);
    digitalWrite(RA2_PIN, rowIdx & 0x04);
    digitalWrite(REN_PIN, HIGH);
}
    
// Read columns.
uint8_t Matrix::readCols(){
    uint8_t byte;
    byte = digitalRead(C3_PIN) << 3;
    byte |= digitalRead(C2_PIN) << 2;
    byte |= digitalRead(C1_PIN) << 1;
    byte |= digitalRead(C0_PIN) << 0;
    return byte;
}

void Matrix::setOutMuxBit(const uint8_t bitIdx, const bool value){
      digitalWrite(REN_PIN,LOW);
      digitalWrite(RA0_PIN, bitIdx & 0x01);
      digitalWrite(RA1_PIN, bitIdx & 0x02);
      digitalWrite(RA2_PIN, bitIdx & 0x04);
      digitalWrite(OUT_PIN,value);
      digitalWrite(REN_PIN,HIGH);
      delayMicroseconds(2);
      digitalWrite(REN_PIN,LOW);
}

void Matrix::readJoyStick(){
    uint16_t x = analogRead(JOYX_PIN);
    uint16_t y = analogRead(JOYY_PIN);
    joyStick.updateXY(x, y);
}
