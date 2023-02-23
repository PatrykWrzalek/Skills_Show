# 1 "c:\\Users\\Patryk\\Desktop\\App\\Arduino XH-Conector_Tester\\StreetLight.ino"
/*#define GHz 1000000000

#define MHz 1000000

#define kHz 1000*/
# 4 "c:\\Users\\Patryk\\Desktop\\App\\Arduino XH-Conector_Tester\\StreetLight.ino"
//#include <XH_ConnectorTester.ino>





//uint32_t MCU_Freguancy = 16 * MHz; //Max MCU_Freguancy 4 294 967 296 Hz
uint8_t LightPin[3], ButtonPin[1];
uint8_t (*GreenLightStreet), (*YellowLightStreet), (*RedLightStreet);
uint8_t (*GreenLightWindow), (*RedLightWindow);

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
        LightPin[i]=i+5;
        pinMode(LightPin[i], 0x1);
        digitalWrite(LightPin[i], 0x0);
        }
}
void LED_3ladder_first_app() //First function
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
void LED_ladder_second_app() //Second function
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
void streetlight_app() //Streetlight_app (street lights control)
{

}

void setup()
{
    init_LED_ladder();
    windowlight_init();
    UART_init();
}

void loop()
{
    is_window_open(digitalRead(ButtonPin[0]));
    wait_till_next_action_window();
}
/////////////////////////////////////////////
void UART_init() //Initialization UART
{
    Serial.begin(115200);
    Serial.println("Hello Unknown :D");
}
void windowlight_init () //Assigning meaning to the is_window_open
{
    GreenLightWindow=&LightPin[2];
    RedLightWindow=&LightPin[0];
}
void is_window_open(bool window_status)
{
    if(window_status==0x1)
        {
        digitalWrite((*RedLightWindow), 0x0);
        digitalWrite((*GreenLightWindow), 0x1);
        Serial.println("Window is close!");
        }
    else
        {
        digitalWrite((*RedLightWindow), 0x1);
        digitalWrite((*GreenLightWindow), 0x0);
        Serial.println("Alarm! Window is open!");
        }
}
void wait_till_next_action_window()
{
    if (digitalRead(ButtonPin[0])==0x1) while (digitalRead(ButtonPin[0])==0x1) delay(5);
    else if (digitalRead(ButtonPin[0])==0x0) while (digitalRead(ButtonPin[0])==0x0) delay(5);
}
