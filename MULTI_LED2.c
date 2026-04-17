/*
 * Multi_LED.c - Zadanie 2
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

    // Wyzerowanie wszystkich wyświetlaczy na start (wartość 0000)
    cy1 = 0; // Tysiące
    cy2 = 0; // Setki
    cy3 = 0; // Dziesiątki
    cy4 = 0; // Jedności

    // Włączenie globalnego zezwolenia na przerwania
    sei();			

    // Pętla główna
    while(1)
    {
        _delay_ms(100); // Odczekaj 0,1 sekundy (100 ms)

        // Logika kaskadowego licznika
        cy4++; // Zawsze inkrementujemy jedności
        
        if (cy4 > 9) 
        {
            cy4 = 0;     // Przepełnienie jedności, wyzeruj
            cy3++;       // Przenieś bit na dziesiątki
            
            if (cy3 > 9) 
            {
                cy3 = 0; // Przepełnienie dziesiątek, wyzeruj
                cy2++;   // Przenieś bit na setki
                
                if (cy2 > 9) 
                {
                    cy2 = 0; // Przepełnienie setek, wyzeruj
                    cy1++;   // Przenieś bit na tysiące
                    
                    if (cy1 > 9) 
                    {
                        cy1 = 0; // Przepełnienie tysięcy - po 9999 wracamy do 0000
                    }
                }
            }
        }
    }
}
