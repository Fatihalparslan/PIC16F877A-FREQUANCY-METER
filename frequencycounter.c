#include <16f877A.h>    
#include<stdbool.h>
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD 
#use delay (clock=4MHz)
#include <lcd.c>
unsigned int32 f = 0;   
unsigned int16 count1=0;
volatile int8 i=0;
void _1snbekle(void);
#INT_TIMER0
void  Timer0_kesme() 
{
   count1++;
}
#INT_TIMER1
void  Timer1_kesme() 
{ 
   set_timer1(40536);
  i=i+1;
}
void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_2(T2_DISABLED,0,1); 
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_ccp1(CCP_OFF);
   setup_ccp2(CCP_OFF);
   lcd_init();
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8 );
   setup_timer_0(T0_EXT_H_TO_L | RTCC_DIV_1);
   enable_interrupts(INT_TIMER0); 
   enable_interrupts(INT_TIMER1);
  
   while(TRUE)
   {      
      f = 0;
      count1 = 0;
      clear_interrupt(INT_TIMER0);
      clear_interrupt(INT_TIMER1);  
      _1snbekle();    
      f= get_timer0();      
      f =f+count1 * 256;
      printf(lcd_putc,"\fFREKANS %luHz",f);  
      delay_ms(1000);
   }
}
void _1snbekle(void)
{
   enable_interrupts(GLOBAL);      
   set_timer1(40536);//65536-40536=25.000*1/125000=0.2sn 
   set_timer0(0);
   while(i<5);
   i=0;
   disable_interrupts(GLOBAL);
}



