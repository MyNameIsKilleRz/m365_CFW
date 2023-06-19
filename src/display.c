#include <include/defines.h>
#include <include/user_config.h>
#include <stdint.h>
#include <nrf_gpio.h>


void TM1637_Init() {
    
    //nrf_gpio_cfg_pin_input(TM1637_DIO, NRF_GPIO_PIN_PULLDOWN);
    //nrf_gpio_cfg_pin_input(TM1637_CLK, NRF_GPIO_PIN_PULLDOWN);
}
void TM1637_Change_Speed_Mode(int Mode, bool Force) {
    if (Force == false && BMS_CHARGING == 1 && TM1637_DISSABLE_CHARGING_MODE) {
        TM1637_MODE = TM1637_MODE_CHARGING;
    } else {
        if (Mode == 1) {
            // ECO
            TM1637_MODE = TM1637_SPEEDMODE_ECO;
        } else if (Mode == 2) {
            // Drive
            TM1637_MODE = TM1637_SPEEDMODE_DRIVE;
        } else if (Mode == 3) {
            // Sport
            TM1637_MODE = TM1637_SPEEDMODE_SPORT;
        }
    }
    TM1637_update();
}

void TM1637_readThrottleAndBrakeVal() {
    if (TM1637_MODE == 16) { // Check if TM1637 is off
        TM1637_THROTTLE_VAL = 0;
        TM1637_BRAKE_VAL = 0;
    } else {
        TM1637_THROTTLE_IN = 0; // Todo: Read UART bytes.
        TM1637_THROTTLE_VAL = (TM1637_THROTTLE_IN - TM1637_THROTTLE_CALIBRATION_LOW) / TM1637_THROTTLE_CALIBRATION_HIGH;
        TM1637_BRAKE_IN = 0; // Todo: Read UART bytes.
        TM1637_BRAKE_VAL = (TM1637_BRAKE_IN - TM1637_BRAKE_CALIBRATION_LOW) / TM1637_BRAKE_CALIBRATION_HIGH;
    }
}

void TM1637_update(){
    pkt = BuildPacket(ESC_POWER_MODE,TM1637_LIGHT,ESC_ERRORCODE,ESC_BEEP,ESC_MOTOR_SPEED,ESC_OVERHEATING)
    //todo send uart bytes
    return 0;
}
uint16_t* BuildPacket(int SpeedMode, bool light, bool charging, bool off, bool locked, int errorcode, bool beep, float speed, bool overheating) {
    // Packet 0x64
    // Mode explanation: 1=drive, 2=eco, 4=sport, 8=charge, 16=off, 32=lock, mode+128=overheating symbol
    uint16_t packet[14];
    uint16_t crc = 0;
    int SMode = SpeedMode;
    if (overheating == true) {
        SMode = SpeedMode + 128;
    }

    packet[0] = 0x55AA;
    packet[2] = 0x0821;
    packet[4] = 0x6400;
    packet[6] = SMode;
    // packet[7] = // Todo: Battery
    packet[8] = light;
    packet[9] = beep;
    packet[10] = static_cast<uint16_t>(speed * 3.6); // Convert float to uint16_t
    packet[11] = errorcode;
    // Calculating crc
    crc = 0;
    for (int i = 2; i <= 11; i++) { // Decreased the range to calculate the crc
        crc += packet[i];
    }
    packet[12] = static_cast<uint16_t>(crc ^ 0xFFFF); // Convert result to uint16_t
    packet[13] = static_cast<uint16_t>((crc ^ 0xFFFF) >> 8); // Convert result to uint16_t
    return packet;
}




//void TM1637_setBrightness(int brightness);//Would require custom ble firmware...
//void TM1637_setSegments(const int segments[]);
//void TM1637_showNumber(int number);
//void TM1637_clearScreen();

void TM1637_Button_Acction_Handler() {
    if (TM1637_OFF == true) {
        TM1637_OFF = false;
        TM1637_LOCKED = false;
        TM1637_update();
    } else if (TM1637_OFF == false) {
        if (TM1637_BUTTON_PRESSCOUNTER == 1) {
            // Turn on light
            TM1637_LIGHT = true;
        } else if (TM1637_BUTTON_PRESSCOUNTER == 2) {
            // Change mode
            if (TM1637_MODE == TM1637_MODE_ECO) {
                TM1637_MODE = TM1637_MODE_DRIVE;
            } else if (TM1637_MODE == TM1637_MODE_DRIVE) {
                TM1637_MODE = TM1637_MODE_SPORT;
            } else if (TM1637_MODE == TM1637_MODE_SPORT) {
                TM1637_MODE = TM1637_MODE_ECO;
            }
            TM1637_update();
        }
    }   
}
void TM1637_TurnOn() {
    if (STARTUP_MODE == 4) {
        TM1637_MODE = ESC_POWER_MODE;
    } else {
        TM1637_Change_Power_Mode(STARTUP_MODE, true);
    }
    TM1637_update();
}

void TM1637_TurnOff() {
    TM1637_MODE = TM1637_MODE_OFF;
    TM1637_update();
}
//void TM1637_clearScreen() {
//    int data[] = {0, 0, 0, 0};
//    TM1637_setSegments(data);
//}
