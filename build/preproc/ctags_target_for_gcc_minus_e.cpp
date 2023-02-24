# 1 "c:\\Users\\Patryk\\Desktop\\App\\Skills_Show\\Skills_Show.ino"
/*Some of this projects are not finished,*/
/*  but in short future it will be :D    */





uint8_t LightPin[3], ButtonPin[1];
uint8_t(*GreenLightStreet), (*YellowLightStreet), (*RedLightStreet);

void Light_init()
{
    for (uint8_t i = 0; i < 3; i++)
    {
        LightPin[i] = i + 5;
        pinMode(LightPin[i], 0x1);
        digitalWrite(LightPin[i], 0x0);
    }
}
void init_LED_ladder() // Initialization LED_ladder programs
{
    pinMode(13, 0x1);
    for (uint8_t i = 0; i < 1; i++)
    {
        ButtonPin[i] = i + 8;
        pinMode(ButtonPin[i], 0x2);
    }
    Light_init();
}
void LED_3ladder_first_app() // First function
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
void LED_ladder_second_app() // Second function
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            digitalWrite(LightPin[3 - 1], 0x0);
            digitalWrite(LightPin[i], 0x1);
        }
        else
        {
            digitalWrite(LightPin[i], 0x1);
            digitalWrite(LightPin[i - 1], 0x0);
        }
        delay(1000);
    }
}

void streetlight_init() // Assigning meaning to the streetlight_app
{
    GreenLightStreet = &LightPin[2];
    YellowLightStreet = &LightPin[1];
    RedLightStreet = &LightPin[0];
}
void streetlight_app() // Streetlight_app (street lights control)
{
}

/////////////////////////////////////////////////////////////////////////////////
//////////*Window alarm application with the ability to arm the alarm*///////////
uint8_t(*GreenLightWindow), (*RedLightWindow);
String read_data = "";
String user_login = "admin";

void UART_init() // Initialization UART
{
    Serial.begin(115200);
    Serial.println("Hello Unknown :D");
}
void windowlight_init() // Assigning meaning to the is_window_open
{
    GreenLightWindow = &LightPin[2];
    RedLightWindow = &LightPin[0];
}
void is_window_open(bool window_status)
{
    if (window_status == 0x1)
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
    if (digitalRead(ButtonPin[0]) == 0x1)
        while (digitalRead(ButtonPin[0]) == 0x1)
            delay(5);
    else if (digitalRead(ButtonPin[0]) == 0x0)
        while (digitalRead(ButtonPin[0]) == 0x0)
            delay(5);
}
void window_alarm_init()
{
    init_LED_ladder();
    windowlight_init();
    UART_init();
}
void window_alarm()
{
    Serial.println("Login:");
    while (Serial.available() == 0)
    {
        if (Serial.available() > 0)
        {
            read_data = Serial.readStringUntil('\n');
            if (read_data == user_login)
            {
                while (read_data == user_login)
                {
                    is_window_open(digitalRead(ButtonPin[0]));
                    wait_till_next_action_window();
                }
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////
//////////*Flashing application depending on the potentiometer turning*//////////
void voltage_mesure_init()
{
    UART_init();
    Light_init();
}
void voltage_mesure()
{
    float voltage_mesure = 0.0;
    voltage_mesure = analogRead(A5) * 5.0 / 1023.0;
    Serial.println(String(voltage_mesure) + " V");
    digitalWrite(5, 0x1);
    delay(int(voltage_mesure * 200));
    digitalWrite(5, 0x0);
    delay(int(voltage_mesure * 200));
}
void battery_status_LED_ladder()
{
    uint16_t mesure_data = 0, scale_value = 0;
    mesure_data = analogRead(A5);
    scale_value = map(mesure_data, 0, 1023, 1, (3 + 1));
    switch (scale_value)
    {
    case 1:
        digitalWrite(LightPin[0], 0x0);
        break;
    case 2:
        digitalWrite(LightPin[0], 0x1);
        digitalWrite(LightPin[1], 0x0);
        break;
    case 3:
        digitalWrite(LightPin[1], 0x1);
        digitalWrite(LightPin[2], 0x0);
        break;
    case 4:
        digitalWrite(LightPin[2], 0x1);
        break;
    default:
        break;
    }
}

/////////////////////////////WORKING_PROJECTS////////////////////////////////////
///*Light which turn on when it's come night (with potentiometer calibration)*///
uint8_t prev_state = 0, curr_state = 0;
void NightLight_App(uint8_t *prev_state, uint8_t *curr_state)
{
    uint16_t light_sensitiv = analogRead(A5);
    if (uint16_t(analogRead(A4)) > light_sensitiv)
    {
        (*curr_state) = 1;
        if ((*prev_state) != (*curr_state))
        {
            for (int i = 0; i < 3; i++)
                digitalWrite(LightPin[i], 0x1);
            Serial.println("It's a night!");
        }
    }
    else
    {
        (*curr_state) = 0;
        if ((*prev_state) != (*curr_state))
        {
            for (int i = 0; i < 3; i++)
                digitalWrite(LightPin[i], 0x0);
            Serial.println("It's a day!");
        }
    }
    (*prev_state) = (*curr_state);
}
/////////////////////////////////////////////////////////////////////////////////
void setup()
{
    Light_init();
    UART_init();
}

void loop()
{
    NightLight_App(&prev_state, &curr_state);
}
