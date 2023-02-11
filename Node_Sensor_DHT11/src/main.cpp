#include <Arduino.h>
#define but_adc 14
#define pin_adc 33
#define led_1 25
#define led_2 26
#define led_3 27
int val_adc;

hw_timer_t *timer = NULL;
volatile bool flag = false;
void off_led()
{
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
}
void IRAM_ATTR read_adc_pin()
{
  flag = true;
}
void IRAM_ATTR timer_adc()
{
  Serial.println("All Led off");
  off_led();
  timerStop(timer);
  //   timer = NULL;
  
}
void start_timer()
{
  // config timer
  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  /* Attach timer_adc function to our timer */
  timerAttachInterrupt(timer, &timer_adc, true);
  /* Set alarm to call timer_adc function every second 1 tick is 1us
  => 3 second is 3000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 3000000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}
void check_value()
{
      if (val_adc < 3158)
    {
      Serial.println("HIGH Pin");
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, HIGH);
    }
    if (val_adc > 3158 && val_adc < 3846)
    {
      Serial.println("Nomal Pin");
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, HIGH);
    }
    if (val_adc > 3846)
    {
      Serial.println("Full Pin");
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);
    }
}
void setup() {
    Serial.begin(9600);
  Serial.setTimeout(500);
    // config read adc pin
  pinMode(but_adc, INPUT_PULLUP);
  attachInterrupt(but_adc, read_adc_pin, CHANGE);
  // init timer
  start_timer();
  // config led display
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  off_led();
  // put your setup code here, to run once:
}

void loop() {
    if (flag)
  {
    val_adc = analogRead(pin_adc);
    Serial.println(val_adc);
    check_value();
    flag = false;
    Serial.println("Start timer");
    timerStart(timer);
  }
  // put your main code here, to run repeatedly:
}