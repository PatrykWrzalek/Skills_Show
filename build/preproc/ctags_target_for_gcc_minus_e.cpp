# 1 "c:\\Users\\Patryk\\Desktop\\App\\Arduino XH-Conector_Tester\\StreetLight.ino"
/*#define GHz 1000000000

#define MHz 1000000

#define kHz 1000*/
//uint32_t MCU_Freguancy = 16 * MHz; //Max MCU_Freguancy 4 294 967 296 Hz
uint8_t LightPin[3];

void streetlight_first_app() /*First program*/
{
    digitalWrite(LightPin[2], 0x1);
    digitalWrite(LightPin[1], 0x0);
    digitalWrite(LightPin[0], 0x0);
    digitalWrite(13, 0x0);
    delay(1000);
    digitalWrite(LightPin[2], 0x0);
    digitalWrite(LightPin[1], 0x1);
    digitalWrite(LightPin[0], 0x0);
    digitalWrite(13, 0x1);
    delay(1000);
    digitalWrite(LightPin[2], 0x0);
    digitalWrite(LightPin[1], 0x0);
    digitalWrite(LightPin[0], 0x1);
    digitalWrite(13, 0x0);
    delay(1000);
}
void streetlight_second_app() /*Second program*/
{
for (uint8_t i = 0; i < 3; i++)
    {
        if(i==0)
        {
            digitalWrite(LightPin[3 -1], 0x0);
            digitalWrite(LightPin[i], 0x1);
        }
        else
        {
            digitalWrite(LightPin[i], 0x1);
            digitalWrite(LightPin[i-1], 0x0);
        }
        digitalWrite(13, bool(i/2));
        delay(1000);
    }
}

void setup()
{
    pinMode(13, 0x1);
    for (uint8_t i = 0; i < 3; i++)
    {
        LightPin[i]=i;
        pinMode(LightPin[i], 0x1);
        //digitalWrite(LightPin[i], LOW);
    }
}

void loop()
{
    streetlight_second_app();
}
