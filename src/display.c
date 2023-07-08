#include <include/defines.h>
#include <include/user_config.h>
#include <stdint.h>

#include <stdbool.h>

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
    pkt = BuildPacket(TM1637_MODE,TM1637_LIGHT,ESC_ERRORCODE,TM1637_BEEP,ESC_MOTOR_SPEED,ESC_OVERHEATING)
    //todo send uart bytes
    return 0;
}

int convertBoolToInt(bool value) {
    return value ? 1 : 0;
}

uint16_t* BuildX1Packet(int SpeedMode) {
    // Packet type 0x64
    // Sources: https://github.com/m365fw/vesc_m365_dash/blob/main/m365_dash.lisp
    //          https://github.com/camcamfresh/Xiaomi-M365-BLE-Controller-Replacement/tree/master
    // Speed modes can only be: 1=drive, 2=eco, 4=sport (others(off,lock,charge...) are handled differently) 
    // Mode explanation: 1=drive, 2=eco, 4=sport, 8=charge, 16=off, 32=lock, 128=overheating symbol
    packet[0] = 0x55; //fixed header
    packet[1] = 0xAA; //fixed header
    packet[2] = 0x08; //msg length (TODO)
    packet[3] = 0x21; //message destination: ,0x20 = BLE to motor controller ,0x21 = motor controller to BLE ,0x22 BLE to BMS ,0x23 motor controller to BLE ,0x25 BMS to motor controller
    packet[4] = 0x64; //message type: 0x01 = Read, and 0x03 = Write (Some messages use 0x64 & 0x65).
    packet[5] = 0x00; //command type
    
    if (TM1637_OFF == false){
       if (TM1637_LOCKED == false){
           if (ESC_OVERHEATING == true){ 
               packet[6] = TM1637_SPEEDMODE + TM1637_MODE_OVERHEATING; // Add's TM1637_MODE_OVERHEATING to speed mode (eco,drive,sport) to turn on the overheating symbol 
           }else{
               packet[6] = TM1637_SPEEDMODE;
           }
       }else{
          packet[6] = TM1637_MODE_LOCK; // lock display
       }
    }else{
      packet[6] = TM1637_MODE_OFF;
    }
    
      
    packet[7] = 100; // battery percentage
    packet[8] = 0x00;//light 0/1
    packet[9] = 0x00;//beep 0/1
    packet[10] = 654;// speed
    packet[11] = 0;// error code
    // Calculating crc
    int c_out = calc_crc(packet);
    packet[12] = c_out & 0xFF;
    packet[13] = c_out >> 8;

    // Packet type 0x64
    // Sources: https://github.com/m365fw/vesc_m365_dash/blob/main/m365_dash.lisp
    //          https://github.com/camcamfresh/Xiaomi-M365-BLE-Controller-Replacement/tree/master
    // Speed modes can only be: 1=drive, 2=eco, 4=sport (others(off,lock,charge...) are handled differently) 
    // Mode explanation: 1=drive, 2=eco, 4=sport, 8=charge, 16=off, 32=lock, 128=overheating symbol
    uint16_t packet[14];
    // uint16_t* packet = malloc(sizeof(uint16_t) * 14);
    uint16_t crc = 0;
    packet[0] = 0x55; //fixed header
    packet[1] = 0xAA; //fixed header
    packet[2] = 0x08; //msg length (TODO)
    packet[3] = 0x21; //message destination: ,0x20 = BLE to motor controller ,0x21 = motor controller to BLE ,0x22 BLE to BMS ,0x23 motor controller to BLE ,0x25 BMS to motor controller
    packet[4] = 0x64; //message type: 0x01 = Read, and 0x03 = Write (Some messages use 0x64 & 0x65).
    packet[5] = 0x00; //command type
    /*
    The X1 Structure: (source:https://github.com/camcamfresh/Xiaomi-M365-BLE-Controller-Replacement/tree/master)
    (Bit outdated but still works)
        Request: | 0x55 | 0xAA | 0x9 | 0x20 | 0x64 | L | 0x4 | T | B | S | ck0 | ck1 |
            L is the number of LED's the original controller should turn on.
            T is the throttle value.
            B is the brake value.
            S is the beep confirmation value.
        Response: | 0x55 | 0xAA | 0x06 | 0x21 | 0x64 | 0 | D | L | N | B | ck0 | ck1 |
            D is the drive mode: (this part is outdated)
                0x0 = Eco Disabled, Wheel Stationary
                0x01 = Eco Disabled, Wheel Moving
                0x02 = Eco Enabled, Wheel Stationary
                0x03 = Eco Enabled, Wheel Moving
            L is the amount of LED's that should be lit on the BLE dashboard.
            A value of 0 may indicate an error state.(i think this is also outdated)
            N is the night mode:
                0x0 = off
                0x64 = on
            B is the beep reqeuest (expects beep confirmation).
    */
    
    if (TM1637_OFF == false){
        if (TM1637_LOCKED == false){
            if (get_esc_temp() >= 60){ // temp icon will show up above 60 degree
                packet[6] = SpeedMode + TM1637_MODE_OVERHEATING; // Add's TM1637_MODE_OVERHEATING to speed mode (eco,drive,sport) to turn on the overheating symbol 
            }else{
                packet[6] = SpeedMode;
            }
        }else{
            packet[6] = convertBoolToInt(TM1637_MODE_LOCK); // lock display
        }
    }else{
        packet[6] = convertBoolToInt(TM1637_MODE_OFF);
    }

    if (TM1637_OFF == false && TM1637_LOCKED == false){
        if (TM1637_SHOW_CUSTOM_BATT == true && TM1637_SHOW_CUSTOM_BATT_ENABLED == true){
            packet[7] = TM1637_SHOW_CUSTOM_BATT;
        }else{
            packet[7] = BMS_CAPACITY * 3.6;
        }
    }
    packet[8] = convertBoolToInt(TM1637_LIGHT);
    packet[9] = convertBoolToInt(TM1637_BEEP); 
    if (TM1637_OFF == false && TM1637_LOCKED == false){
        if (TM1637_SHOW_CUSTOM_NUM == true && TM1637_SHOW_CUSTOM_NUM_ENABLED == true){
            packet[10] = TM1637_SHOW_CUSTOM_NUM;
        }else{
            packet[10] = ESC_MOTOR_SPEED * 3.6; // Convert float to uint16_t
        }
    }
    packet[11] = ESC_ERRORCODE;
    // Calculating crc
    crc = 0;
    for (int i = 2; i <= 11; i++) { // Decreased the range to calculate the crc
        crc += packet[i];
    }
    packet[12] = crc ^ 0xFFFF; // Convert result to uint16_t ck0 
    packet[13] = (crc ^ 0xFFFF) >> 8; // Convert result to uint16_t ck1 
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
bool TM1637_Button_Pressed_State(){
    return(TM1637_BUTTON_PRESSED);
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
