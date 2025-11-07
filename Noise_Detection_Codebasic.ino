// include the library code:
#include <LiquidCrystal.h>

//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  LiquidCrystal lcd(13, 12, 11, 10,  9,  8);
 
const int SENSOR_PIN = 2;
const int BUZZER_PIN = 7;
const int LED_PIN = 6;
 
void setup ()  
{   
  pinMode (SENSOR_PIN, INPUT); // Set the Sensor pin as INPUT  
  pinMode(BUZZER_PIN, OUTPUT);  // Set the BUZZER pin as OUTPUT 
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as OUTPUT 

  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.setCursor(0,0); // set the cursor position:
  lcd.print("  THE BRIGHT LIGHT    ");
  lcd.setCursor(0,1);
  lcd.print("NOISE MONITORING SYS             ");
  lcd.setCursor(0, 3);
  lcd.print("      NO SOUND             ");
}  
void loop ()  
{
  int Sensor_Val = digitalRead(SENSOR_PIN);  //get reading from microphone
  if (Sensor_Val == HIGH) //If Sound Sensor Detected the Sound
  {
    lcd.setCursor(0, 3);
    lcd.print("   SOUND DETECTED             ");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    lcd.setCursor(0, 3);
    lcd.print("      NO SOUND             ");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
  }
}
