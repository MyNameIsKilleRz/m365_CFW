// Definitions for TM1637 segments
#define TM1637_SPEEDMODE_ECO          2   // 'Walk mode'
#define TM1637_SPEEDMODE_DRIVE        1
#define TM1637_SPEEDMODE_SPORT        4
#define TM1637_MODE_CHARGING     8
#define TM1637_MODE_OFF          16
#define TM1637_MODE_LOCK         32
#define TM1637_MODE
#define TM1637_OVERHEATING  128 // Add to eco, drive, sport, lock to display temp icon
#define TM1637_OFF 
#define TM1637_LOCKED
#define TM1637_LIGHT                  // Self-explanatory
#define TM1637_TEMP                   // BLE doesn't need to know temp, only if overheating or not
#define TM1637_ERR_CODE               // More info here: https://wiki.scooterhacking.org/doku.php?id=nberrorcodes
#define TM1637_BATT
#define TM1637_DISSABLE_CHARGING_MODE
#define TM1637_THROTTLE_VAL
#define TM1637_THROTTLE_IN //Raw throttle val 
#define TM1637_THROTTLE_CALIBRATION_LOW  40  //
#define TM1637_THROTTLE_CALIBRATION_HIGH 170 //Maybe i'll move this to user_config 
#define TM1637_BRAKE_VAL
#define TM1637_BRAKE_IN //Raw brake val
#define TM1637_BRAKE_CALIBRATION_LOW 40  //
#define TM1637_BRAKE_CALIBRATION_HIGH 180 //Maybe i'll move this to user_config 
#define TM1637_BUTTON_PRESSED
#define TM1637_BUTTON_PRESSCOUNTER


// Definitions for GPIO, thanks to https://github.com/Koxx3/SmartESC_STM32_v2/blob/vesc_comp/m365/Inc/main.h
#define PWR_BTN_Pin GPIO_PIN_14
#define PWR_BTN_GPIO_Port GPIOC
#define TPS_ENA_Pin GPIO_PIN_15
#define TPS_ENA_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOD
#define M1_TEMPERATURE_Pin GPIO_PIN_0
#define M1_TEMPERATURE_GPIO_Port GPIOA
#define M1_BUS_VOLTAGE_Pin GPIO_PIN_2
#define M1_BUS_VOLTAGE_GPIO_Port GPIOA
#define M1_CURR_AMPL_U_Pin GPIO_PIN_3
#define M1_CURR_AMPL_U_GPIO_Port GPIOA
#define M1_CURR_AMPL_V_Pin GPIO_PIN_4
#define M1_CURR_AMPL_V_GPIO_Port GPIOA
#define M1_CURR_AMPL_W_Pin GPIO_PIN_5
#define M1_CURR_AMPL_W_GPIO_Port GPIOA
#define PHASE_A_V_Pin GPIO_PIN_6
#define PHASE_A_V_GPIO_Port GPIOA
#define PHASE_B_V_Pin GPIO_PIN_7
#define PHASE_B_V_GPIO_Port GPIOA
#define M1_HALL_H3_Pin GPIO_PIN_0
#define M1_HALL_H3_GPIO_Port GPIOB
#define PHASE_C_V_Pin GPIO_PIN_1
#define PHASE_C_V_GPIO_Port GPIOB
#define UART_TX_Pin GPIO_PIN_10
#define UART_TX_GPIO_Port GPIOB
#define UART_RX_Pin GPIO_PIN_11
#define UART_RX_GPIO_Port GPIOB
#define M1_PWM_UL_Pin GPIO_PIN_13
#define M1_PWM_UL_GPIO_Port GPIOB
#define M1_PWM_VL_Pin GPIO_PIN_14
#define M1_PWM_VL_GPIO_Port GPIOB
#define M1_PWM_WL_Pin GPIO_PIN_15
#define M1_PWM_WL_GPIO_Port GPIOB
#define M1_PWM_UH_Pin GPIO_PIN_8
#define M1_PWM_UH_GPIO_Port GPIOA
#define M1_PWM_VH_Pin GPIO_PIN_9
#define M1_PWM_VH_GPIO_Port GPIOA
#define M1_PWM_WH_Pin GPIO_PIN_10
#define M1_PWM_WH_GPIO_Port GPIOA
#define BRAKE_LIGHT_Pin GPIO_PIN_15
#define BRAKE_LIGHT_GPIO_Port GPIOA
#define M1_HALL_H1_Pin GPIO_PIN_4
#define M1_HALL_H1_GPIO_Port GPIOB
#define M1_HALL_H2_Pin GPIO_PIN_5
#define M1_HALL_H2_GPIO_Port GPIOB
// gpio

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