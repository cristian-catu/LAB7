/* 
 * File:   main.c
 * Author: CATU
 *
 * Created on 4 de abril de 2022, 12:15 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "setup.h"

#define _XTAL_FREQ 4000000
int8_t i = 1; //se establecen todas las variables a utilizar
int8_t unidades = 0;
int8_t decenas = 0;
int8_t centenas = 0;
int8_t display_unidades = 0;
int8_t display_decenas = 0;
int8_t display_centenas = 0;
uint8_t valor = 0;
int8_t remainder = 0;

void __interrupt() isr (void){
    if(INTCONbits.RBIF){  
        if(!PORTBbits.RB0){ //si se presionó RB0 entonces incrementamos
            PORTA++;
            valor++;
        }
        if(!PORTBbits.RB1){ //si se presionó RB1 entonces decrementamos               
            PORTA--;
            valor--;
        }
        INTCONbits.RBIF = 0; //se limpia la bandera del puerto B
    }
    if(INTCONbits.T0IF){  //interrupción cada 2ms
        switch(i)         //se hacen los estados para el multiplexado
        {        
            case 1:  //mostramos centenas en display 1
                PORTD = 0b00000001;
                PORTC = display_centenas;
                i = 2;
                break;
            case 2: //mostramos decenas en display 2
                PORTD = 0b00000010;
                PORTC = display_decenas;
                i = 3;
                break;
            case 3:  //mostramos unidades en display 2
                PORTD = 0b00000100;
                PORTC = display_unidades;
                i = 1;
                break;
        }
        INTCONbits.T0IF = 0; //se limpia la bandera del TMR0
        TMR0 = 248; //se pone el valor inicial del TMR0
    }
    return;
}

void main(void) {
    setup();
    int tabla[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111}; //Tabla para mostrar el valor en el display
    while(1){
        centenas = valor/100; //Se obtienen las centenas al divir dentro de 100
        remainder = valor%100;
        decenas = remainder/10; //Se obtienen las decenas al divir el remainder dentro de 10
        unidades = remainder%10;  //Se obtienen las unidades al sacar el remainder del remainder
        display_unidades = tabla[unidades]; //llamamos a la tabla para obener los valores a poner en el display de 7-seg
        display_decenas = tabla[decenas];
        display_centenas = tabla[centenas];
    }
    return;
}