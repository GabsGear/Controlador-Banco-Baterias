#include <16F877A.h>

#FUSES WDT                    //Watch Dog Timer
#FUSES XT                       //Crystal osc <= 4mhz
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected

#define BASE_TEMPO  (65536-625)



#define clear lcd_putc('\f');
#define delay_adc delay_us(1000); 
// lcd pins
#define LCD_ENABLE_PIN  PIN_E0                                    
#define LCD_RS_PIN      PIN_E1                                    
#define LCD_RW_PIN      PIN_E2                                    
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                   
#define LCD_DATA7       PIN_D7

// fator divisor de tensao
#define relac 3

// voltage pins
#device ADC=8
#define V1 AN0
#define V2 AN1
#define V3 AN2
#define V4 AN3

// relays
#define S1 PIN_D0
#define S2 PIN_D1
#define S3 PIN_D2

// output leds
#define LB1 PIN_C0
#define LB2 PIN_C1
#define LB3 PIN_C2
#define LB4 PIN_C3
#DEFINE CHARGE_LED PIN_C4


// menu pins 
#define up PIN_B1
#define CHARGE_MODE PIN_B2


#use delay(clock=4000000)
#include <lcd.c>

// constantes
const float v_equal = 80;
const float v_min = 10;


// Funções
float convertVoltage(unsigned int digitalRead);
void selectMenu();
void showMenu();
void readVoltages();
void setupSwitches();
void bateryStatus();
void checkChargeMode();
