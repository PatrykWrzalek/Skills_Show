// There was a registers program which do functions from Skills_Show for Arduino
/*
int main()
{
DDRD =0b00001100;   //Initialize PINs which we used from PORT D
DDRB =0b00000001;   //Initialize PINs which we used from PORT B
PORTB=1<<0;	        //Enable internal pullup resistor to INPUT PIN0

  while(1)
  {
    if(PINB&(~(1<<3))) {PORTD=(1<<3)|PORTD;}
    else blink_LED_PORTD(2, 500);
  }

}

void blink_LED_PORTD(uint8_t PIN, uint16_t time)    //Blinking LED's which are conected to PINs from PORT D
{
    PORTD=(1<<PIN)|PORTD;
    _delay_ms(time+1);
    PORTD=~(1<<PIN)&PORTD;
    _delay_ms(time+1);
}
*/