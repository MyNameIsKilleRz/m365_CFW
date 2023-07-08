#include <Arduino.h>
#include <XDash.h>
#include <SoftwareSerialWithHalfDuplex.h>

int Speed = 0;
int BattLevel = 0;
int ButtonState = 0;
int SpeedMode = 0;
int Locked = 0;
int Charging = 0;
int IgnoreChargingMode = 0;
int Overheating = 0;
bool IgnoreErrorCodes = false;
int ErrorCode = 0;
int HeadlightState = 0;
//int ThrottleVal // TODO
//int BrakeVal  //   -//-
int BaudRate = 115200;
//int SpeedUnit = 0; // kmh or mph todo
//int Color = 0; // Red = 0,Pink = 1,White = 2 also todo (seen someone do it so i know it's possible)

unsigned int calc_crc(unsigned char* tx_frame) {
    unsigned int crc = 0;
    for (int i = 2; i <= 12; i++) {
        crc += tx_frame[i];
    }
    unsigned int c_out = crc ^ 0xFFFF;
    return(c_out);
    
}


XDash::XDash(uint8_t uartPin,uint8_t buttonPin){
  SoftwareSerialWithHalfDuplex DASH(uartPin,uartPin,false,false);
  pinMode(buttonPin,INPUT_PULLUP);
  DASH.begin(BaudRate);
}
XDash::SetSpeed(int num){
  Speed = num;
}
XDash::SetBatteryPercentage(int Percentage){
  :BattLevel = Percentage;
}
XDash::SetSpeedMode(int Smode,lock,charge,){
  SpeedMode = Percentage;

}

XDash::update(){
  uint8_t packet[14];
  packet[0] = 0x55; //fixed header
  packet[1] = 0xAA; //fixed header
  packet[2] = 0x08; //msg length (TODO)
  packet[3] = 0x21; //message destination: ,0x20 = BLE to motor controller ,0x21 = motor controller to BLE ,0x22 BLE to BMS ,0x23 motor controller to BLE ,0x25 BMS to motor controller
  packet[4] = 0x64; //message type: 0x01 = Read, and 0x03 = Write (Some messages use 0x64 & 0x65).
  packet[5] = 0x00; //command type
  if (off == 0){
    if (Locked == 0){
      if (Charging == 1){
          if (IgnoreChargingMode == 1){
            if (Overheating == 0){
              packet[6] = SpeedMode 
            }else{
              packet[6] = SpeedMode + 128
            }
          }else{
            packet[6] = 8
          }
      }else{
        if (Overheating == 0){
          packet[6] = SpeedMode 
        }else{
          packet[6] = SpeedMode + 128
        }
      }    
    }else{
      packet[6] = 32
    }
  }else{
    packet[6] = 16
  }


  packet[7] = BattLevel; // battery percentage
  packet[8] = HeadlightState;//light 0/1
  packet[9] = 0x00;//beep 0/1
  packet[10] = Speed;// speed
  if (IgnoreErrorCodes == true){
    packet[11] = 0x00;// error code
  }else{
    packet[11] = ErrorCode;
  }
  
  // Calculating crc
  int crc = calc_crc(packet);
  packet[12] = crc & 0xFF;
  packet[13] = crc >> 8;
  
  for (int i = 0; i < sizeof(packet); i++) {
    BLE.write(packet[i]);
    }
}