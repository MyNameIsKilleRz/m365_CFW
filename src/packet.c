#include <include/defines.h>
#include <include/user_config.h>
#include <stdint.h>
#include <stdbool.h>


uint16_t* Packet(bCmd,) {
    // Sources: https://github.com/m365fw/vesc_m365_dash/blob/main/m365_dash.lisp
    //          https://github.com/camcamfresh/Xiaomi-M365-BLE-Controller-Replacement/tree/master
    //          https://github.com/etransport/ninebot-docs/wiki/protocol
    //          
    // Speed modes can only be: 1=drive, 2=eco, 4=sport (others(off,lock,charge...) are handled differently) 
    // Mode explanation: 1=drive, 2=eco, 4=sport, 8=charge, 16=off, 32=lock, 128=overheating symbol
    uint16_t packet[14];
    uint16_t crc = 0;
    bool PRO_DISPLAY
    packet[0] = 0x55; //fixed header
    packet[1] = 0xAA; //fixed header
    
    switch (bCmd)
    ​{
        case 65:
          // statements
          break;
    
        case 64:
          if (PRO_DISPLAY == true)
          
        default:
          // default statements
    }
    packet[2] = 0x08; //msg length (TODO)


}