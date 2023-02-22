# 1 "c:\\Users\\Patryk\\Desktop\\App\\Arduino XH-Conector_Tester\\sketch.ino"


int LED_PIN[8];

void setup()
{
    for(int i=0; i<8; i++)
    {
        LED_PIN[i]=i;
        pinMode(LED_PIN[i], 0x0);
    }
}

void loop()
{
    digitalWrite(LED_PIN[1], 0x1);
    delay(5000);
    digitalWrite(LED_PIN[1], 0x0);
    digitalWrite(LED_PIN[2], 0x1);
    delay(5000);
    digitalWrite(LED_PIN[2], 0x0);
    digitalWrite(LED_PIN[3], 0x1);
    delay(5000);
    digitalWrite(LED_PIN[3], 0x0);
    digitalWrite(LED_PIN[4], 0x1);
    delay(5000);
}
