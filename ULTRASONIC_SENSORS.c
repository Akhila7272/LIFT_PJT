/*
 * File:   ULTRASONIC_SENSORS.c
 * Author: aKhila
 *
 * Created on 17 September, 2024, 10:00 PM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
int time,distance,ones,tens,hnds;
void enable()
{
    RE0=1;
    __delay_us(10);
    RE0=0;
     __delay_us(10);
}
void lcd(char a,char b)
{
    RE1=a;
    PORTD=b;
    enable();
}
void string(char *ptr)
{
    while(*ptr)
        lcd(1,*ptr++);
}

void main() 
{
    PORTD=PORTE=0x00;
    TRISD=TRISE=0x00;
    PORTA=0x00;
    TRISA=0x01;
    ANSEL=ANSELH=0x00;
        
    T1CON=0x00;
            
    lcd(0,0x38);
    lcd(0,0x0E);
    lcd(0,0x80);
    lcd(1,'A');
    lcd(0,0xc0);
    
    while(1)
    {
        RA1=1; // triger 
        __delay_us(10);
        RA1=0;
        
        while(!RA0); //echo
        TMR1=0;
        TMR1ON=1;
        
        while(RA0);
        TMR1ON=0;
        
        time=TMR1;
        distance=time/58;  
        
        lcd(0, 0x80);
        ones=distance%10;   tens=((distance/10)%10);    hnds=distance/100;
        lcd(1,hnds+48);    lcd(1,tens+48);    lcd(1,ones+48);
        __delay_ms(100);
        
    }
}
