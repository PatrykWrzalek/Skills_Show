/*#define GHz 1000000000
#define MHz 1000000
#define kHz 1000*/
#define LightNumber 3

//uint32_t MCU_Freguancy = 16 * MHz; //Max MCU_Freguancy 4 294 967 296 Hz
uint8_t LightPin[LightNumber];

void streetlight_first_app()        /*First program*/
{
    digitalWrite(LightPin[2], HIGH);
    digitalWrite(LightPin[1], LOW);
    digitalWrite(LightPin[0], LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LightPin[2], LOW);
    digitalWrite(LightPin[1], HIGH);
    digitalWrite(LightPin[0], LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LightPin[2], LOW);
    digitalWrite(LightPin[1], LOW);
    digitalWrite(LightPin[0], HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
void streetlight_second_app()       /*Second program*/
{
for (uint8_t i = 0; i < LightNumber; i++)
    {
        if(i==0) 
        {
            digitalWrite(LightPin[LightNumber-1], LOW);
            digitalWrite(LightPin[i], HIGH);
        }
        else
        {
            digitalWrite(LightPin[i], HIGH);
            digitalWrite(LightPin[i-1], LOW);
        }
        digitalWrite(LED_BUILTIN, bool(i/2));
        delay(1000);
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); 
    for (uint8_t i = 0; i < LightNumber; i++)
    {
        LightPin[i]=i;
        pinMode(LightPin[i], OUTPUT); 
        //digitalWrite(LightPin[i], LOW);
    }
}

void loop()
{
    streetlight_second_app();
}