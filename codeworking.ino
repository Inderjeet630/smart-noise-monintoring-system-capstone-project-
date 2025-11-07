#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
SoftwareSerial esp(3, 4); // RX, TX for ESP8266

const int SENSOR_PIN = 2;
const int BUZZER_PIN = 7;
const int LED_PIN = 6;

String apiKey = "ZPKS99CD0VKND6B6";  // Replace with your ThingSpeak key
String ssid = "Galaxy A21s2F1E";       // Replace with your WiFi name
String pass = "12345678";   // Replace with your WiFi password

void setup ()  
{   
  pinMode(SENSOR_PIN, INPUT);  
  pinMode(BUZZER_PIN, OUTPUT);  
  pinMode(LED_PIN, OUTPUT);  

  lcd.begin(20, 4); 
  lcd.setCursor(0,0);
  lcd.print("  THE BRIGHT LIGHT    ");
  lcd.setCursor(0,1);
  lcd.print("NOISE MONITORING SYS  ");
  lcd.setCursor(0, 3);
  lcd.print("      NO SOUND        ");

  Serial.begin(9600);
  esp.begin(9600); // Use 9600 in Proteus

  // Connect to WiFi
  esp.println("AT");
  delay(2000);
  esp.println("AT+CWMODE=1");
  delay(2000);
  esp.println("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"");
  delay(8000);
}

void loop ()  
{
  int Sensor_Val = digitalRead(SENSOR_PIN);  //get reading from microphone

  if (Sensor_Val == HIGH) // Sound detected
  {
    lcd.setCursor(0, 3);
    lcd.print("   SOUND DETECTED             ");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);

    // Send 1 to ThingSpeak
    esp.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
    delay(2000);
    String cmd = "GET /update?api_key=" + apiKey + "&field1=1\r\n";
    esp.print("AT+CIPSEND=");
    esp.println(cmd.length());
    delay(2000);
    esp.print(cmd);
  }
  else // No sound
  {
    lcd.setCursor(0, 3);
    lcd.print("      NO SOUND             ");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);

    // Send 0 to ThingSpeak
    esp.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
    delay(2000);
    String cmd = "GET /update?api_key=" + apiKey + "&field1=0\r\n";
    esp.print("AT+CIPSEND=");
    esp.println(cmd.length());
    delay(2000);
    esp.print(cmd);
  }

  delay(15000); // ThingSpeak limit: 15 sec between uploads
}
