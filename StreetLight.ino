/*#define GHz 1000000000
#define MHz 1000000
#define kHz 1000*/
//#include <XH_ConnectorTester.ino>
#define LightNumber 3
#define ButtonNumber 1
#define LightStartsFromPin  5
#define ButtonStartsFromPin 8

//uint32_t MCU_Freguancy = 16 * MHz; //Max MCU_Freguancy 4 294 967 296 Hz
uint8_t LightPin[LightNumber], ButtonPin[ButtonNumber];
uint8_t (*GreenLightStreet), (*YellowLightStreet), (*RedLightStreet);
uint8_t (*GreenLightWindow), (*RedLightWindow);

void init_LED_ladder()             //Initialization LED_ladder programs
{
    pinMode(LED_BUILTIN, OUTPUT); 
    for (uint8_t i = 0; i < ButtonNumber; i++)
        {
        ButtonPin[i]=i+ButtonStartsFromPin;
        pinMode(ButtonPin[i], INPUT_PULLUP); 
        }
    for (uint8_t i = 0; i < LightNumber; i++)
        {
        LightPin[i]=i+LightStartsFromPin;
        pinMode(LightPin[i], OUTPUT); 
        digitalWrite(LightPin[i], LOW);
        }
}
void LED_3ladder_first_app()       //First function
{
    digitalWrite(LightPin[2], HIGH);
    digitalWrite(LightPin[1], LOW);
    digitalWrite(LightPin[0], LOW);
    delay(1000);
    digitalWrite(LightPin[2], LOW);
    digitalWrite(LightPin[1], HIGH);
    digitalWrite(LightPin[0], LOW);
    delay(1000);
    digitalWrite(LightPin[2], LOW);
    digitalWrite(LightPin[1], LOW);
    digitalWrite(LightPin[0], HIGH);
    delay(1000);
}
void LED_ladder_second_app()       //Second function
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
        delay(1000);
        }
}

void streetlight_init ()           //Assigning meaning to the streetlight_app
{
    GreenLightStreet=&LightPin[2];        
    YellowLightStreet=&LightPin[1];
    RedLightStreet=&LightPin[0];
}
void streetlight_app()   //Streetlight_app (street lights control)
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
void UART_init()        //Initialization UART
{
    Serial.begin(115200);
    Serial.println("Hello Unknown :D");
}
void windowlight_init ()           //Assigning meaning to the is_window_open
{
    GreenLightWindow=&LightPin[2];        
    RedLightWindow=&LightPin[0];
}
void is_window_open(bool window_status)
{
    if(window_status==HIGH) 
        {
        digitalWrite((*RedLightWindow), LOW);
        digitalWrite((*GreenLightWindow), HIGH);
        Serial.println("Window is close!");
        }
    else 
        {
        digitalWrite((*RedLightWindow), HIGH);
        digitalWrite((*GreenLightWindow), LOW);
        Serial.println("Alarm! Window is open!");
        }
}
void wait_till_next_action_window()
{
    if (digitalRead(ButtonPin[0])==HIGH) while (digitalRead(ButtonPin[0])==HIGH) delay(5);
    else if (digitalRead(ButtonPin[0])==LOW) while (digitalRead(ButtonPin[0])==LOW) delay(5);
}