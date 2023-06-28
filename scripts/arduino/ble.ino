/*
  This example program can be used to test the "SoftwareSerialWithHalfDuplex" library, adapted from the SoftwareSerial library.
  The value of half-duplex is that one pin can be used for both transmitting and receiving data.
  Also many devices can be daisy-chained to the same line. RS485 still commonly uses half-duplex.
  
  By default the library works the same as the SoftwareSerial library, but by adding a couple of additional arguments
  it can be configured for half-duplex. In that case, the transmit pin is set by default to an input, with the pull-up set. 
  When transmitting the pin temporarily switches to an output until the byte is sent, then flips back to input. When a module is 
  receiving it should not be able to transmit, and vice-versa. This library probably won't work as is if you need inverted-logic.
  
  To use this test example, upload SoftwareSerialWithHalfDuplex_test_partA to as many arduinos as you like. Be sure to change 
  "myID" for each arduino loaded with partA. Upload SoftwareSerialWithHalfDuplex_test_partB to a different arduino. All arduinos
  should be connected to each other by the same communications pin, and by ground. Open up the serial monitor pointing to partB.
  When you type in the id number of one of the devices it should respond.
  
  This is a first draft of the library and test programs. It appears to work, but has only been tested on a limited basis,
  and hasn't yet been tested with any native half-duplex devices (like the bioloid ax12 robot servo). 
  Seems fairly reliable up to 57600 baud. As with all serial neither error checking, nor addressing are implemented, 
  so it is likely that you will need to do this yourself. Also, you can make use of other protocols such as i2c. 
  I am looking for any feedback, advice and help at this stage. 
  Contact me at n.stedman@steddyrobots.com or on the arduino forums.
*/


#include <SoftwareSerialWithHalfDuplex.h>

#define comPin 3

SoftwareSerialWithHalfDuplex TM1637(comPin,comPin,false,false);


void setup(){
  TM1637.begin(115200);
    uint8_t packet[14];
    // uint16_t* packet = malloc(sizeof(uint16_t) * 14);
    uint8_t crc = 0;
    packet[0] = 0x55; //fixed header
    packet[1] = 0xAA; //fixed header
    packet[2] = 0x08; //msg length (TODO)
    packet[3] = 0x21; //message destination: ,0x20 = BLE to motor controller ,0x21 = motor controller to BLE ,0x22 BLE to BMS ,0x23 motor controller to BLE ,0x25 BMS to motor controller
    packet[4] = 0x64; //message type: 0x01 = Read, and 0x03 = Write (Some messages use 0x64 & 0x65).
    packet[5] = 0x00; //command type
    packet[6] = 4
    packet[7] = 100
    packet[8] = 0
    packet[9] = 0
    packet[10] = 22
    packet[11] = 0
    // Calculating crc
    crc = 0;
    for (int i = 2; i <= 11; i++) { // Decreased the range to calculate the crc
        crc += packet[i];
    }
    packet[12] = crc ^ 0xFFFF; // Convert result to uint16_t ck0 
    packet[13] = (crc ^ 0xFFFF) >> 8; // Convert result to uint16_t ck1 

}

void loop(){
  if(TM1637.available()){
    for (int i = 0; i < sizeof(data); i++) {
      TM1637.write(data[i])
  
    
  }
}

