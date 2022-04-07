#include <xc.h>

void setup(void){
    ANSEL = 0;
    ANSELH = 0;               // I/O digitales
    
    OSCCONbits.IRCF = 0b110; // 4MHz
    OSCCONbits.SCS = 1;       // Oscilador interno
    TRISC = 0b0000000;
    PORTC = 0b0000000;
    
    TRISA = 0b0000000;
    PORTA = 0b0000000;
    
    TRISD = 0b0000000;
    PORTD = 0b0000000;
    
    TRISBbits.TRISB0 = 1;       // RB0 como entrada (configurada con control de bits)
    TRISBbits.TRISB1 = 1;       // RB0 como entrada (configurada con control de bits)
    
    OPTION_REGbits.nRBPU = 0;   // Habilitamos resistencias de pull-up del PORTB
    WPUBbits.WPUB0 = 1;         // Habilitamos resistencia de pull-up de RB0
    WPUBbits.WPUB1 = 1;         // Habilitamos resistencia de pull-up de RB1
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones globales
    INTCONbits.RBIE = 1;        // Habilitamos interrupciones del PORTB
    INTCONbits.T0IE = 1;        // Habilitamos interrupciones del TMR0
    IOCBbits.IOCB0 = 1;         // Habilitamos interrupción por cambio de estado para RB0
    IOCBbits.IOCB1 = 1;         // Habilitamos interrupción por cambio de estado para RB1
    INTCONbits.RBIF = 0;        // Limpiamos bandera de interrupción
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    TMR0 = 248;
    INTCONbits.T0IF = 0;
}