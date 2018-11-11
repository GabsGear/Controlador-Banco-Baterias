#include <main.h>

int t_up = 0;
int menu = 0;

void setup(){
   lcd_init();
   enable_interrupts(global);
   enable_interrupts(int_ext);
   ext_int_edge(H_TO_L);
   lcd_init();
   Port_b_pullups(true);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(V1); 
   
}


void main()
{
     setup();
     
     while (1){
         selectMenu();
         showMenu();
         delay_ms(200);
      }
}




/**
      int digital_value;
      int valor;
      WHILE (1){
         delay_us(20); 
         set_adc_channel(0);
         digital_value = read_adc();
         printf(LCD_PUTC,"ADC : %i", digital_value);
         float valor = convertVoltage(digital_value);
       
         printf(LCD_PUTC,"\nReal: %.2f", valor);
         delay_ms(2000);
         clear;
      }


**/

void showMenu(){
  switch(menu){
       case 1:          
             clear;
             printf(LCD_PUTC,"Menu1");
             break;                                    
       case 2:   
             clear;
             printf(LCD_PUTC,"Menu2");                                       
             break;                                     
       case 3:    
             clear;
             printf(LCD_PUTC,"Menu3");                                      
             break;       
       case 4:   
             clear;
             printf(LCD_PUTC,"Menu4");                                    
             break;   
    } 
}


void selectMenu(){
  if(input(up))  t_up = 1;
  if(!input(up) && t_up){
    t_up = 0;
    menu++;
    if(menu > 4) menu = 1;
  }
}

float convertVoltage(int digital_value){
      float analogic_value = (5*digital_value)/255.0;
      return 3 * analogic_value;
}
