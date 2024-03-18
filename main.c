#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <stdbool.h>


volatile uint8_t sekunde = 0;
volatile uint8_t minute = 0;
volatile uint8_t stunde = 0;

void set_time(time_array[]);

void receive_time(volatile uint8_t minute, volatile uint8_t stunde){

bool bit;
bool receive_array[];
bool time_array[];

  for(uint8_t i = 0; i < 256; i++){

    bit = avr_receive();
    receive_array[i] = bit;
    PORTB |= (bit << PB0);

    if(receive_array[i-1]==receive_array[i]{
      for(uint8_t j = 0, j < 256){
      bit = avr_receive();
      time_array[j] = bit;
      PORTB |= (bit << PB0);
      }
    }

set_time(time_array[], minute, stunde);
}


void set_time(bool time_array[], volatile uint8_t minute, volatile uint8_t stunde){

sekunde = 5;
parity_minute = time_array[28];
minute =  if(time_array[21]==true)minute+1;
          if(time_array[22]==true)minute+2;
          if(time_array[23]==true)minute+4;
          if(time_array[24]==true)minute+8;
          if(time_array[25]==true)minute+10;
          if(time_array[26]==true)minute+20;
          if(time_array[27]==true)minute+40;

  if(parity_minute == time_array[21] | time_array[22] |time_array[23] | time_array[24] |time_array[25] | time_array[26]| time_array[27]){
    PORTB |= (1<<PB2);
  }

parity_stunde = time_array[35];
stunde =  if(time_array[29]==true)minute+1;
          if(time_array[30]==true)minute+2;
          if(time_array[31]==true)minute+4;
          if(time_array[32]==true)minute+8;
          if(time_array[33]==true)minute+10;
          if(time_array[34]==true)minute+20;


  if(parity_stunde == time_array[29] | time_array[30] |time_array[31] | time_array[32] |time_array[33] | time_array[34]){
    PORTB |= (1<<PB1);
  }

}




int main(void){

  //TIMER0 CTC for PWM
  TCCR0B |= (1 << CS01);
  OCR0A = 255;
  TCCR0A |= (1 << WGM00);
  TIMSK0 |= (1 << OCIE0A);

  //SET DDR and PULL-UP
    DDRB = 0b00000111;
    DDRC = 0b0011111;
    DDRD = 0b11111100;

    //WATCHDOG
    MCUSR &= ~(1 << WDRF); // Watchdog-Reset löschen
    wdt_disable();
    WDTCSR |= (1 << WDIE) | (1 << WDE) | (1 << WDP3) | (1 << WDP0); // WDT einstellen
    wdt_enable(WDTO_8S);

    //GLOBAL
    sei();  

    while(1){

    wdt_disable();
    receive_time();
    PORTC = stunde;
    PORTD = (2 << minute);


    }


}

ISR(TIMER0_COMPA_vect){

  sekunde++;
  if(sekunde==60){
    sekunde = 0;
    minute++;
        if(minute==60){
        minute= 0;
        stunde++;
            if(stunde==24){
            stunde = 0;
            }
        }   
  }

}