# Mikrokontrolery - Laboratoria (AVR)

Repozytorium zawiera kod z zajęć laboratoryjnych z przedmiotu Mikrokontrolery. Projekty zostały napisane w języku C z myślą o mikrokontrolerach z rodziny AVR i skupiają się na obsłudze 4-cyfrowego, 7-segmentowego wyświetlacza LED przy użyciu techniki multipleksowania.

## Opis sprzętowy i konfiguracja
- **Taktowanie (F_CPU):** 16 MHz
- **Segmenty wyświetlacza (katody):** `PORTA` (rejestr kierunku `DDRA`)
- **Wybór cyfry (anody):** `PORTD` (piny `PD0` - `PD3`)
- **Odświeżanie:** Realizowane za pomocą `Timer0` w trybie CTC. Przerwania od zrównania (Compare Match) odświeżają cyklicznie kolejne anody wyświetlacza.

## Struktura projektu

### Biblioteka wyświetlacza
* **`d_led.h` / `d_led.c`**: Biblioteka (autorstwa Mirosława Kardasia) inicjalizująca porty GPIO oraz `Timer0`. Udostępnia interfejs w postaci zmiennych globalnych (`cy1`, `cy2`, `cy3`, `cy4`), do których można bezpośrednio wpisywać wartości (od 0 do 9, lub wartość `NIC` oznaczającą wygaszenie cyfry).

### Zadania

#### 1. Prosty licznik (`MULTI_LED.c`)
Realizacja prostego licznika jednocyfrowego.
* Wyświetla cyfry od 0 do 9 na pierwszej pozycji wyświetlacza, wygaszając pozostałe.
* Wartość zwiększa się co 1 sekundę (użycie `_delay_ms(1000)`).
* Po osiągnięciu wartości 9, licznik zeruje się.

#### 2. Licznik kaskadowy (`MULTI_LED2.c`)
Realizacja 4-cyfrowego licznika kaskadowego o zakresie od 0000 do 9999.
* Początkowa wartość wszystkich cyfr to 0.
* Inkrementacja najmłodszej cyfry (jedności) następuje co 100 ms (`_delay_ms(100)`).
* Program posiada logiczną kaskadę: przepełnienie cyfry jedności (>9) powoduje inkrementację dziesiątek, przepełnienie dziesiątek powoduje inkrementację setek itd. Po przekroczeniu 9999, licznik powraca do wartości 0000.

## Wymagania i kompilacja
Aby poprawnie skompilować ten kod, potrzebujesz środowiska obsługującego łańcuch narzędzi `avr-gcc` (np. Atmel Studio/Microchip Studio).
Ze względu na użyte rejestry (`PORTA`, `PORTD`, `TCCR0`), kod jest przeznaczony dla mikrokontrolerów posiadających ten układ portów (np. popularna `ATmega32` lub `ATmega16`). Przed kompilacją upewnij się, że ustawiony jest poprawny model procesora. W każdym programie głównym wymagane jest wywołanie `sei()` przed główną pętlą `while(1)`, aby uaktywnić przerwania niezbędne do działania multipleksowania.
