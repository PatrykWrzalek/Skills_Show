#define XH_Lenght 8

int LED_PIN[XH_Lenght];

void setup()
{
    for(int i=0; i<XH_Lenght; i++)
    {
        LED_PIN[i]=i;
        pinMode(LED_PIN[i], INPUT);
    }
}

void loop()
{
    digitalWrite(LED_PIN[1], HIGH);
    delay(5000);
    digitalWrite(LED_PIN[1], LOW);
    digitalWrite(LED_PIN[2], HIGH);
    delay(5000);
    digitalWrite(LED_PIN[2], LOW);
    digitalWrite(LED_PIN[3], HIGH);
    delay(5000);
    digitalWrite(LED_PIN[3], LOW);
    digitalWrite(LED_PIN[4], HIGH);
    delay(5000);
}
