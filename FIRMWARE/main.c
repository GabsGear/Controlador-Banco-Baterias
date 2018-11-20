#include <main.h>

int t_up = 0;
int menu = 0;
float v1_dc, v2_dc, v3_dc, v4_dc = 0 ;
float temp, umd = 30;

#int_ext
void trataExt(){
      while(!input(PIN_B0)){
         clear;
         /* porcentagem de carga = somatorio das cargas *100/1020*/
         readVoltages();
         setupSwitches();
         bateryStatus();
 
         float carga = v1_dc + v2_dc + v3_dc + v4_dc;
         carga = carga*100/1020;
         printf(LCD_PUTC,"**** FALTA ****");
         printf(LCD_PUTC,"\n  CARGA %.2f %%",  carga);
         delay_ms(2000);
      }
}


// timer checkagem temperatura
#int_timer1
void trata_t1() 
{
        set_timer1(65536 - 65200);
        if (temp > 40){
              printf(LCD_PUTC,"*****ALERTA*****");
              printf(LCD_PUTC,"\nTEMPERATURA");              
        }
}

void setup(){
   lcd_init();
   
   // enable interrupts
   enable_interrupts(global | int_ext | int_timer0);
   ext_int_edge(H_TO_L);
   
   // Enable timer

   //enable_interrupts(GLOBAL | INT_TIMER1);
   //set_timer1(65536 - 65200);

   // lcd
   lcd_init();
   Port_b_pullups(true);
   
   // adc
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(V1);
   setup_wdt(WDT_2304MS);

   // inicialisa reles
   output_low(S1);
   output_low(S2);
   output_low(S3);
}

void main()
{
     setup();
     
     while (True){
         restart_wdt();
         selectMenu();
         checkChargeMode();
         showMenu(); 
         readVoltages();
         bateryStatus();
         delay_ms(400);  
      }
}

// Le as tensoes analogicas da bateria 
void readVoltages(){ // AQUI TA ZUADO

      delay_adc;
      set_adc_channel(0);
      delay_adc;
      v1_dc = read_adc();
      delay_adc;
     /* set_adc_channel(1);
      delay_adc;
      v2_dc = read_adc();
      delay_adc;
      set_adc_channel(2);
      delay_adc;
      v3_dc = read_adc();
      delay_adc;
      set_adc_channel(3);
      delay_adc;
      v4_dc = read_adc();*/
      
      v2_dc = 255;
      v3_dc = 255;
      v4_dc = 255;
}

// informações do LCD
void showMenu(){
  switch(menu){
       case 1:          
             clear;
             printf(LCD_PUTC,"Bateria 1");
             printf(LCD_PUTC,"\nT: %.2f V", v1_dc);
             break;                                    
       case 2:   
             clear;
             printf(LCD_PUTC,"Bateria 2");
             printf(LCD_PUTC,"\nTensao 2: %f V",  v2_dc);
             break;                                     
       case 3:    
             clear;
             printf(LCD_PUTC,"Bateria 3");
             printf(LCD_PUTC,"\nTensao: %f V", v3_dc);
             break;     
       case 4:   
             clear;
             printf(LCD_PUTC,"Bateria 4");
             printf(LCD_PUTC,"\nTensao: %f V",  v4_dc);
             break; 
       case 5:
             clear;
             printf(LCD_PUTC,"\T: %f C",  temp);
             printf(LCD_PUTC,"\nU: %f %%",  umd);
             break; 
    } 
}

// logica dos menus
void selectMenu(){
  if(input(up))  t_up = 1;
  if(!input(up) && t_up){
    t_up = 0;
    menu++;
    if(menu > 5) menu = 1;
  }
}

// converte para o lcd o valor da tensao
float convertVoltage(int digital_value){
      return (15*digital_value)/255.0 ;
}

// Gerencia os switches para a melhor descarga da bateria. 
void setupSwitches(){
   if ((v1_dc < v_min) || (v2_dc < v_min)) { output_high(S1);}
   else {output_low(S1);}
   
   if ((v2_dc < v_min) || (v3_dc < v_min)) { output_high(S2);}
   else  {output_low(S2);}
   
   if ((v3_dc < v_min) || (v4_dc < v_min)) {output_high(S3);}
   else  {output_low(S3);}
   
}

// verifica a tensao das baterias
void bateryStatus(){
    if (v1_dc < v_min) output_high(LB1);
    else  output_low(LB1);
    
    if (v2_dc < v_min)output_high(LB2);
    else  output_low(LB2);
    
    if (v3_dc < v_min) output_high(LB3);
    else  output_low(LB3);
    
    if (v4_dc < v_min) output_high(LB4);
    else  output_low(LB4);
}

// modos de carga
void checkChargeMode(){
     if(input(CHARGE_MODE)) {   //modo flutuacao liga todas as baterias em paralelo e a fonte alimenta no modo flutuação
         output_low(CHARGE_LED);
         output_low(S1);
         output_low(S2);
         output_low(S3);
         
     }
     else {    // modo equalização Remove o curto circuito entre as baterias e se carrega até que a voltagem de cada uma chegue a tensão da fonte repois religa 
         if ((v1_dc >= v_equal) || (v2_dc > v_equal)) { output_high(S1);}
         else {output_low(S1);}
         
         if ((v2_dc > v_equal) || (v3_dc > v_equal)) { output_high(S2);}
         else  {output_low(S2);}
         
         if ((v3_dc < v_equal) || (v4_dc < v_equal)) {output_high(S3);}
         else  {output_low(S3);} 
     }
}



