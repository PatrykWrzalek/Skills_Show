// There was a registers program which do functions from Skills_Show for Arduino
/*
int main()
{
DDRB =0x0C;   		//Initialize PINs which we used from PORT B
DDRD =0b00000100;   //Initialize PINs which we used from PORT D
PORTD=1<<2;			//Enable internal pullup resistor to INPUT PIN0
PORTB=(1<<3)|PORTB;	//Set High state on PIN3 of PORT B

TCCR1A=0x00;	//Set WGM bits to CTC (mode 4)
TCCR1B=0x0D;	//Set CS bits to prescaler of 1024
OCR1A=15264;	//Set output compare for interrupt period of 1sec
TIMSK1=0x02;	//Enable output compare match interrupt A

EICRA =0x01;	//The falling edge of INT0 generates an interrupt request
EIMSK =0x01;	//Enable INT0
sei();			//Enable interrupts globally
  while(1)
  {
    //blink_LED_PORTB(2, 500);
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
ISR(TIMER1_COMPA_vect)	//Interrupt for timer 1 output compare match A
{
  PORTB^=(1<<2)|PORTB;  //Toggle PIN2
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
//Broken stopwatch because it count MAX to 4sec//

#include <LiquidCrystal.h> 			//Libraries attached
#define CPU_Freq	16000000		//Arduino work frequancy
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);//PINs LCD are connected
volatile uint16_t time;
volatile uint8_t state=0;

int main()
{
DDRB =~(1<<4);	//Initialize PINs which we used as INPUT from PORT B
PORTB =(1<<4);  //Enable internal pullup resistor to INPUT PIN12

PCICR =(1<<0);	//Enable PIN change interrupt for PINs from PCINT0..7
PCMSK0 =(1<<4);	//Select PIN change mask register for PCINT4 - PIN12
sei();	//Enable interrupts

lcd.begin(16, 2); //Settings for LCD
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" Hello unknown! ");
for (long int i=0; i<(CPU_Freq/16);i++) asm("");

Serial.begin(115200);

TCCR1A =0x00;		//Normal timer mode
TCCR1B =0x05;		//Prescaler set to 1024

  while(1)
  {
    if (state==3){
      lcd.setCursor(0,0);
    lcd.print(" Measured time: ");
        if(time>4000)
        {
        lcd.setCursor(0,1);
    lcd.print("time > than 4sec");
        }
        else
        {
    lcd.setCursor(0,1);
    lcd.print(time);
        lcd.setCursor(4,1);
        lcd.print(" miliseconds");
        }
    }
    else if (state==2){
      for (uint8_t i=0; i<=16;i++)
      {
        lcd.setCursor(i,0);
    lcd.print(" ");
        lcd.setCursor(i,1);
    lcd.print(" ");
      }
      state=3;
    }
    else{
        lcd.setCursor(0,0);
    lcd.print(" Push button to ");
    lcd.setCursor(0,1);
    lcd.print("  start count!  ");
    }
    //Serial.println(TCNT1);
  }
}

ISR(PCINT0_vect)
{
  if(PINB&0x10)
  {
  if (state!=3) state++;		//Turn on measure time state=3
  else if (state==3) 			//Clearing LCD Display state=2
  {
  time=abs(TCNT1/16); //Convert clock ticks to milisec 1 tick is 64us that if we have 16 ticks it will be 1,024ms
  state=2;
  }
  }
  else TCNT1=0;	//Reset timer to 0
}*/