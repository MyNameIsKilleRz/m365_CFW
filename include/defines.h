// Definitions for TM1637 segments
#define TM1637_MODE_ECO          2   // 'Walk mode'
#define TM1637_MODE_DRIVE        1
#define TM1637_MODE_SPORT        4
#define TM1637_MODE_CHARGING     8
#define TM1637_MODE_OFF          16
#define TM1637_MODE_LOCK         32
#define TM1637_MODE
#define TM1637_OVERHEATING  128 // Add to eco, drive, sport, lock to display temp icon
#define TM1637_LIGHT                  // Self-explanatory
#define TM1637_TEMP                   // BLE doesn't need to know temp, only if overheating or not
#define TM1637_ERR_CODE               // More info here: https://wiki.scooterhacking.org/doku.php?id=nberrorcodes
#define TM1637_BATT
#define TM1637_THROTTLE_VAL
#define TM1637_BRAKE_VAL

// Definitions for GPIO
#define TM1637_BAUDRATE     115200  // Half-duplex
#define TM1637_RX_PIN
#define TM1637_TX_PIN       // TODO Later
//#define TM1637_CLK        NRF_GPIO_PIN_MAP(PORT,PIN) // Not used
//#define TM1637_DIO        NRF_GPIO_PIN_MAP(PORT,PIN) // Not used
//#define UART_PARITY                  // Unused placeholder
//#define UART_FLOWCONTROL             // Unused placeholder
//#define BRAKE_PIN         NRF_GPIO_PIN_MAP(PORT,PIN) // Handled by BLE
//#define ACCELERATOR_PIN   NRF_GPIO_PIN_MAP(PORT,PIN) // Handled by BLE
//#define BUTTON_PIN        NRF_GPIO_PIN_MAP(PORT,PIN) // Handled by BLE

// Definitions for esc
#define ESC_POWER_MODE
#define ESC_ERRORCODE
#define ESC_BEEP
#define ESC_MOTOR_SPEED
#define ESC_OVERHEATING
#define ESC_TEMP
#define ESC_OVERHEATING_TEMP 60


#define BMS_CHARGING