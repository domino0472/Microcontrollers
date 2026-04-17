/*
 * Multi_LED.c - Zadanie 1
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL // Ustawienie szybkości zegara 16 MHz
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "d_led.h"

int main(void)
{
    // Inicjalizacja wyświetlacza multipleksowanego
    d_led_init();   		

    // Ustawienie początkowe: na pierwszym wyświetlaczu 0, reszta wygaszona
    cy1 = 0;
    cy2 = NIC; // Wyświetla pustkę
    cy3 = NIC; // Wyświetla pustkę
    cy4 = NIC; // Wyświetla pustkę

    // Włączenie globalnego zezwolenia na przerwania (niezbędne do odświeżania LED)
    sei();			

    // Pętla główna
    while(1)
    {
        _delay_ms(1000); // Odczekaj 1 sekundę

        cy1++;           // Zwiększ wartość na wyświetlaczu o 1
        
        if(cy1 > 9)      // Jeśli przekroczymy 9, wróć do 0
        {
            cy1 = 0;
        }
    }
}
