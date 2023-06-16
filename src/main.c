#include <include/user_config.h>
#include <include/commands.h>
#include <include/defines.h>
#include <include/display.h>
#include <include/strings.h>

#include <stdbool.h>
#include <stdint.h>
// todo use MCSDK to control the bldc(foc) motor... And that's final
#include "FreeRTOS.h"
#include "task.h"

typedef enum {false, true} bool;

bool isStopped = true;

void handleButton(){

}

void handleFWupd(){
    //check if firmware update is needed
    //later add fw ver. spoofing
}

void handleLocking(){

}

void handleShutdown(){

}

void handleCommands(){

}

float getSpeed(){
    float speed;

    return speed;
}

void handleSpeedometer(){

}

void handleHandles(){

}

void updateDisplay(){

}

static void display_update_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        

        
    }
}

static void command_handler_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        

        
    }
}

static void button_handler_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        

        
    }
}

static void input_handler_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        

        
    }
}

static void mi_setup_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);

    //Mi one-time stuff


    //Mi data loop
    while (true)
    {
        

        
    }
}

static void locking_handler_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        

        
    }
}

int main() {
    

    //Check if factory reset combo
    
    TM1637_Init();
    //Setup stuff
    //Setup bluetooth
    //Connection stuff
    //Setup serial

    while (1){
        if (isStopped) {
            handleFWupd();
            handleLocking();
            handleShutdown();
        }

        //Check if stopped, then
            //Firmware update?
            //Shutdown?
        
        handleCommands();
        updateSpeedometer();
        handleButton();
        handleHandles();
        updateDisplay();
        //Check incoming command
        //Process command
            //Serial
        //Update speedometer
        //Handle button presses
            //Timer
                //switch
                    //LED
                    //Mode
                    //Cruise control
        //Handle handles
        //Cruise control update
        //Check battery state
        //Handle Display

        if (floor(getSpeed()) <= 1){
            isStopped = true;
        }
    }
}