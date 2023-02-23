# 1 "c:\\Users\\Patryk\\Desktop\\App\\Arduino XH-Conector_Tester\\StreetLight.ino"
/*#define GHz 1000000000

#define MHz 1000000

#define kHz 1000*/



//uint32_t MCU_Freguancy = 16 * MHz; //Max MCU_Freguancy 4 294 967 296 Hz
uint8_t LightPin[3], ButtonPin[1];
uint8_t (*GreenLightStreet), (*YellowLightStreet), (*RedLightStreet);

void init_LED_ladder() //Initialization LED_ladder programs
{
    pinMode(13, 0x1);
    for (uint8_t i = 0; i < 1; i++)
        {
        ButtonPin[i]=i+8;
        pinMode(ButtonPin[i], 0x2);
        }
    for (uint8_t i = 0; i < 3; i++)
        {
        LightPin[i]=i+0;
        pinMode(LightPin[i], 0x1);
        digitalWrite(LightPin[i], 0x0);
        }
}
void LED_3ladder_first_app() //First program
{
    digitalWrite(LightPin[2], 0x1);
    digitalWrite(LightPin[1], 0x0);
    digitalWrite(LightPin[0], 0x0);
    delay(1000);
    digitalWrite(LightPin[2], 0x0);
    digitalWrite(LightPin[1], 0x1);
    digitalWrite(LightPin[0], 0x0);
    delay(1000);
    digitalWrite(LightPin[2], 0x0);
    digitalWrite(LightPin[1], 0x0);
    digitalWrite(LightPin[0], 0x1);
    delay(1000);
}
void LED_ladder_second_app() //Second program
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
        delay(1000);
        }
}
void streetlight_init () //Assigning meaning to the streetlight_app
{
    GreenLightStreet=&LightPin[2];
    YellowLightStreet=&LightPin[1];
    RedLightStreet=&LightPin[0];
}
void streetlight_app(bool crosswalk_open) //Streetlight_app (street lights control)
{
    if(crosswalk_open==0x1)
        {
        digitalWrite((*RedLightStreet), 0x0);
        digitalWrite((*GreenLightStreet), 0x1);
        }
    else
        {
        digitalWrite((*RedLightStreet), 0x1);
        digitalWrite((*GreenLightStreet), 0x0);
        }
}

void setup()
{
    init_LED_ladder();
    streetlight_init();
}

void loop()
{
    streetlight_app(digitalRead(ButtonPin[0]));
}
