#include "display.h"


void Display::pianoNotes(){
    xSemaphoreTake(keyArrayMutex, portMAX_DELAY);
    // Concatenate all the keys together.
    const uint16_t keys = (keyArray[2] << 8) | (keyArray[1] << 4) | (keyArray[0]);
    xSemaphoreGive(keyArrayMutex);

    for(uint8_t i = 0; i < 12; i++){
        // Check each bit is asserted and print it.
        const uint8_t bitState = ((keys >> i) & 0x0001);
        u8g2.print((bitState == 0) ? notes[i] : '_');
        // Check if it is a sharp note and print it.
        if((bitState == 0) && (i != 0) && (notes[i - 1] == notes[i])){
            u8g2.print('#');
        }
    }
}

void Display::Initialise(){
    u8g2.begin();
}

void Display::updateTask(void * pvParameters){
    const TickType_t xFrequency = 100 / portTICK_PERIOD_MS;
    TickType_t xLastWakeTime = xTaskGetTickCount();

//start page
start:    
    while(1){
        pageNumber=1;
        u8g2.clearBuffer();         
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.setCursor(5,15);
        u8g2.print("Start?");
        u8g2.sendBuffer();  

        if(joyStick.getDirection() == 1){
            goto main;
        }

      }

//main-dashboard page 
main:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
        pageNumber=0;
       
           u8g2.setCursor(5,15);
            Display::pianoNotes();
            u8g2.setCursor(5, 30);
            u8g2.print("Vol ");
            u8g2.print(knobRotation3.getRotation());
            u8g2.print(" Wave ");
            u8g2.print(knobRotation2.getRotation());
            u8g2.print(" Joy ");
            u8g2.print(joyStick.getDirection());
            u8g2.sendBuffer();

        if(joyStick.getDirection() == 2){
            goto start;
        }

        if(joyStick.getDirection() == 3){
            goto Setting1;
        }    
    }



Setting1:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;

        u8g2.setCursor(15,15);
        u8g2.drawCircle(10, 10, 2, U8G2_DRAW_ALL);
        u8g2.print("Setting 1");    
        u8g2.setCursor(75, 15);
        u8g2.print("Setting 2");
        u8g2.setCursor(15,30);
        u8g2.print("Setting 3");    
        u8g2.setCursor(75, 30);
        u8g2.print("Setting 4");    

        u8g2.sendBuffer();

        if(selB.getState() == 1){
            goto main;
        }

        if(selA.getState() == 1){
            goto Setting1sel;
        }

        if(joyStick.getDirection()==3){
            goto Setting2;
        }

        if(joyStick.getDirection()==2){
            goto Setting3;
        }
        
    }

Setting1sel:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;
        u8g2.setCursor(15,15);
        u8g2.print("Setting 1 Selected!");
        u8g2.sendBuffer();
        //here call the method corresponding to the setting
        //knobs and other may also be configure each time depending on the setting selected
        
        
        if(selB.getState() == 1){
            goto Setting1;
        }
        
    }    
Setting2:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;

        u8g2.setCursor(15,15);
        u8g2.print("Setting 1");    
        u8g2.setCursor(75, 15);
        u8g2.drawCircle(70, 10, 2, U8G2_DRAW_ALL);
        u8g2.print("Setting 2");
        u8g2.setCursor(15,30);
        u8g2.print("Setting 3");    
        u8g2.setCursor(75, 30);
        u8g2.print("Setting 4");    

        u8g2.sendBuffer();

        if(selB.getState() == 1){
            goto main;
        }

        if(selA.getState() == 1){
            goto Setting2sel;
        }

        if(joyStick.getDirection()==4){
            goto Setting1;
        }

        if(joyStick.getDirection()==2){
            goto Setting4;
        }

    }
Setting2sel:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;
        u8g2.setCursor(15,15);
        u8g2.print("Setting 2 Selected!");
        u8g2.sendBuffer();

        if(selB.getState() == 1){
            goto Setting2;
        }
        
    }        

Setting3:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;

        u8g2.setCursor(15,15);
        u8g2.print("Setting 1");    
        u8g2.setCursor(75, 15);
        u8g2.print("Setting 2");
        u8g2.setCursor(15,30);
        u8g2.drawCircle(10,25, 2, U8G2_DRAW_ALL);
        u8g2.print("Setting 3");    
        u8g2.setCursor(75, 30);
        u8g2.print("Setting 4");    

        u8g2.sendBuffer();

        if(selB.getState() == 1){
            goto main;
        }

        if(selA.getState() == 1){
            goto Setting3sel;
        }

        if(joyStick.getDirection()==1){
            goto Setting1;
        }

        if(joyStick.getDirection()==3){
            goto Setting4;
        }

    }

Setting3sel:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;
        u8g2.setCursor(15,15);
        u8g2.print("Setting 3 Selected!");
        u8g2.sendBuffer();

        if(selB.getState() == 1){
            goto Setting3;
        }
        
    }        
Setting4:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;

        u8g2.setCursor(15,15);
        u8g2.print("Setting 1");    
        u8g2.setCursor(75, 15);
        u8g2.print("Setting 2");
        u8g2.setCursor(15,30);
        u8g2.print("Setting 3");    
        u8g2.setCursor(75, 30);
        u8g2.drawCircle(70,25, 2, U8G2_DRAW_ALL);
        u8g2.print("Setting 4");    

        u8g2.sendBuffer();

        

        if(selB.getState() == 1){
            goto main;
        }

        if(selA.getState() == 1){
            goto Setting4sel;
        }

        if(joyStick.getDirection()==4){
            goto Setting3;
        }
        if(joyStick.getDirection()==1){
            goto Setting2;
        }

    }                  

Setting4sel:
    while(1){
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        //Update display
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

        pageNumber=1;
        u8g2.setCursor(15,15);
        u8g2.print("Setting 4 Selected!");
        u8g2.sendBuffer();

        if(selB.getState() == 1){
            goto Setting4;
        }
        
    }    

}
