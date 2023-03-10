// There was a registers program which do functions from Skills_Show for Arduino
/*
int main()
{
DDRB =0x0C;   		//Initialize PINs which we used from PORT B
DDRD =0b00000100;   //Initialize PINs which we used from PORT D
PORTD=1<<2;			//Enable internal pullup resistor to INPUT PIN0
PORTB=(1<<3)|PORTB;	//Set High state on PIN3 of PORT B

EICRA =0x01;	//The falling edge of INT0 generates an interrupt request
EIMSK =0x01;	//Enable INT0
sei();			//Enable interrupts globally
  while(1)
  {
    blink_LED_PORTB(2, 500);
  }

}

void blink_LED_PORTB(uint8_t PIN, uint16_t time)    //Blinking LED's which are conected to PINs from PORT B
{
    PORTB=(1<<PIN)|PORTB;	//High state setting
    _delay_ms(time+1);
    PORTB=~(1<<PIN)&PORTB;	//Low state setting
    _delay_ms(time+1);
}

ISR(INT0_vect)	//External interrupt
{
  if(PIND&(1<<2)) 	//Check if is High state on PIN2 (Button not press)
    {PORTB^=(1<<3)|PORTB;}	//Toggle PIN 3
}
*/