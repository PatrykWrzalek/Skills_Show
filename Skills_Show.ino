/*Some of this projects are not finished,*/
/*  but in short future it will be :D    */
#include <Servo.h>
#define LightNumber 3
#define ButtonNumber 1
#define LightStartsFromPin 5
#define ButtonStartsFromPin 8

uint8_t LightPin[LightNumber], ButtonPin[ButtonNumber];
uint8_t(*GreenLightStreet), (*YellowLightStreet), (*RedLightStreet);

void Light_init()
{
    for (uint8_t i = 0; i < LightNumber; i++)
    {
        LightPin[i] = i + LightStartsFromPin;
        pinMode(LightPin[i], OUTPUT);
        digitalWrite(LightPin[i], LOW);
    }
}
void init_LED_ladder() // Initialization LED_ladder programs
{
    pinMode(LED_BUILTIN, OUTPUT);
    for (uint8_t i = 0; i < ButtonNumber; i++)
    {
        ButtonPin[i] = i + ButtonStartsFromPin;
        pinMode(ButtonPin[i], INPUT_PULLUP);
    }
    Light_init();
}
void LED_3ladder_first_app() // First function
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
void LED_ladder_second_app() // Second function
{
    for (uint8_t i = 0; i < LightNumber; i++)
    {
        if (i == 0)
        {
            digitalWrite(LightPin[LightNumber - 1], LOW);
            digitalWrite(LightPin[i], HIGH);
        }
        else
        {
            digitalWrite(LightPin[i], HIGH);
            digitalWrite(LightPin[i - 1], LOW);
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
    if (window_status == HIGH)
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
    if (digitalRead(ButtonPin[0]) == HIGH)
        while (digitalRead(ButtonPin[0]) == HIGH)
            delay(5);
    else if (digitalRead(ButtonPin[0]) == LOW)
        while (digitalRead(ButtonPin[0]) == LOW)
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
    digitalWrite(LightStartsFromPin, HIGH);
    delay(int(voltage_mesure * 200));
    digitalWrite(LightStartsFromPin, LOW);
    delay(int(voltage_mesure * 200));
}
void battery_status_LED_ladder()
{
    uint16_t mesure_data = 0, scale_value = 0;
    mesure_data = analogRead(A5);
    scale_value = map(mesure_data, 0, 1023, 1, (LightNumber + 1));
    switch (scale_value)
    {
    case 1:
        digitalWrite(LightPin[0], LOW);
        break;
    case 2:
        digitalWrite(LightPin[0], HIGH);
        digitalWrite(LightPin[1], LOW);
        break;
    case 3:
        digitalWrite(LightPin[1], HIGH);
        digitalWrite(LightPin[2], LOW);
        break;
    case 4:
        digitalWrite(LightPin[2], HIGH);
        break;
    default:
        break;
    }
}
void walking_battery_status_LED_ladder()
{
    uint16_t mesure_data = 0, scale_value = 0;
    mesure_data = analogRead(A5);
    scale_value = map(mesure_data, 0, 1023, 1, (LightNumber + 1));
    if (scale_value != 1)
    {
        for (int i = 0; i < LightNumber; i++)
        {
            digitalWrite(LightPin[i], scale_value >= i + 2);
        }
    }
    else
        digitalWrite(LightPin[0], LOW);
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
            for (int i = 0; i < LightNumber; i++)
                digitalWrite(LightPin[i], HIGH);
            Serial.println("It's a night!");
        }
    }
    else
    {
        (*curr_state) = 0;
        if ((*prev_state) != (*curr_state))
        {
            for (int i = 0; i < LightNumber; i++)
                digitalWrite(LightPin[i], LOW);
            Serial.println("It's a day!");
        }
    }
    (*prev_state) = (*curr_state);
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////*Buzzer song test*//////////////////////////////////
void buzzer_test_init()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}
void buzzer_test()
{
    tiu_tiu();
    fast_piupiu();
    tiu_tiu();
    tiu_tiu();
    fast_bibibi();
    fast_piupiu();
    fast_piupiu();
    fast_piupiu();
    tiu_tiu();
    tiu_tiu();
    tiu_tiu();
    tiu_tiu();
}
void fast_bibibi()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(400);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}
void fast_piupiu()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
}
void tiu_tiu()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(900);
}
/////////////////////////////////////////////////////////////////////////////////
Servo serwomechanizm;
int change = 10;
int pos = 0;
void servo_move_init()
{
    UART_init();
    serwomechanizm.attach(10); // Servo.h supports only two pins: 9 and 10
}
void servo_move(int pos)
{
    for (pos = 0; pos < 180; pos = pos + change)
    {
        serwomechanizm.write(pos);
        Serial.println(String(pos));
        delay(500);
    }
}
void PWM_LED_init()
{
    UART_init();
    pinMode(11, OUTPUT);
    digitalWrite(11, LOW);
}
void PWM_LED()
{
    for (int i = 0; i < 255; i = i + 5)
    {
        analogWrite(11, i);
        Serial.println(String(i));
        delay(500);
    }
}

void setup()
{
    // Light_init();
    // UART_init();
    servo_move_init();
}

void loop()
{
    // NightLight_App(&prev_state, &curr_state);
    servo_move(pos);
}