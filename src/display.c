#include <include/defines.h>
#include <include/user_config.h>
#include <stdint.h>
#include <nrf_gpio.h>


void TM1637_Init() {
    
    //nrf_gpio_cfg_pin_input(TM1637_DIO, NRF_GPIO_PIN_PULLDOWN);
    //nrf_gpio_cfg_pin_input(TM1637_CLK, NRF_GPIO_PIN_PULLDOWN);
}
void TM1637_Change_Power_Mode(int Mode,bool Force) {
    if (Force == false, BMS_CHARGING == 1){
        TM1637_MODE = TM1637_MODE_CHARGING
    }
    else
    {
        if (Mode == 1) {
            // ECO
            TM1637_MODE = TM1637_MODE_ECO 
        }
        else if (Mode == 2)
        {
            // Drive
            TM1637_MODE = TM1637_MODE_DRIVE
        }
        else if (Mode == 3)
        {
            //Sport
            TM1637_MODE = TM1637_MODE_SPORT
        }
    }
    TM1637_update()
}

void TM1637_update(){
    pkt = BuildPacket(ESC_POWER_MODE,TM1637_LIGHT,ESC_ERRORCODE,ESC_BEEP,ESC_MOTOR_SPEED,ESC_OVERHEATING)
   
}
uint16_t* BuildPacket(int Mode, int light, int errorcode, int beep, float speed, bool overheating)
{
    // packet 0x64
    // mode explanation 1=drive, 2=eco, 4=sport, 8=charge, 16=off, 32=lock, mode+128=overheating symbol
    uint16_t packet[14];
    uint16_t crc = 0;
    int SMode = Mode;
    if (overheating == true)
    {
        SMode = Mode + 128;
    }
    packet[0] = 0x55AA;
    packet[2] = 0x0821;
    packet[4] = 0x6400;
    packet[6] = SMode;
    //packet[7] = // todo battery 
    packet[8] = light;
    packet[9] = beep;
    packet[10] = static_cast<uint16_t>(speed * 3.6); // Convert float to uint16_t
    packet[11] = errorcode;
    //Calculating crc
    crc = 0;
    for (int i = 2; i <= 11; i++) // Decreased the range to calculate the crc
    {
        crc += packet[i];
    }
    packet[12] = static_cast<uint16_t>(crc ^ 0xFFFF); // Convert result to uint16_t
    packet[13] = static_cast<uint16_t>((crc ^ 0xFFFF) >> 8); // Convert result to uint16_t
    return packet;
}

void TM1637_clearScreen(){

}

void TM1637_setBrightness(int brightness){

}

void TM1637_setSegments(const int segments[]){
    
}

void TM1637_showNumber(int number){

}

void TM1637_on(){
    if (STARTUP_MODE == 4) {
        TM1637_MODE = ESC_POWER_MODE
    }
    else {
        TM1637_Change_Power_Mode(STARTUP_MODE,true)
    }    
    TM1637_update()
}

void TM1637_TurnOff() {
    TM1637_MODE = TM1637_MODE_OFF
    TM1637_update()
}

//void TM1637_clearScreen() {
//    int data[] = {0, 0, 0, 0};
//    TM1637_setSegments(data);
//}
