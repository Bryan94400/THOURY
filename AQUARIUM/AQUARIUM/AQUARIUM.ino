// AQUARIUM V0.0.1
// BY Jérémy Cheynet et Bryan Thoury
//

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"

// Create object RTC
RTC_DS1307 RTC;

// Create object lcd (I2C)
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // Init serial and print message
  Serial.begin(9600);
  Serial.println("Start program");
  Serial.println("V0.0.1");

  // Init I2C
  Wire.begin();

  // Init RTC
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC n est pas en cours de fonctionnement!");
  }

  // Init lcd and print message
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Start program");
  lcd.setCursor(1,1);
  lcd.print("V.0.0.1");
  delay(5000);
  lcd.setCursor(1,0);
  lcd.print("nous sommes le");
}

void loop() {
  // Get DateTime
  DateTime now = RTC.now();

  // Transformation de la date et de l'heure en chaine de caractère
  char buffer[200] = {0, };
  snprintf(buffer, 199, "%02d/%02d/%02d %02d:%02d   ", now.year()-2000,
      now.month(), now.day(), now.hour(), now.minute(), now.second());

  // Display DateTime
  lcd.setCursor(0, 1);  
  lcd.print(buffer);

  // Print DateTime on serial
  Serial.println(buffer);

  // Wait 100ms
  delay(100);
}
