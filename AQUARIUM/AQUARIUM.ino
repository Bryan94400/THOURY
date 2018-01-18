 #include <LiquidCrystal_I2C.h>
  #include <Wire.h>
  #include "RTClib.h"

  RTC_DS1307 RTC;

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();                      // initialiser le lcd
  lcd.init();
  // Imprime un message sur l'écran LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("nous sommes le");

  
    Wire.begin();
    RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC n est pas en cours de fonctionnement!");
    // La ligne suivante fixe la date et l'heure du RTC avec les date et heur de compilation du sketch
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    }
}

void loop() {
  // placez le curseur sur la colonne 0, ligne 1
  // (note: la ligne 1 est la deuxième ligne, puisque le comptage commence par 0):
  lcd.setCursor(0, 1);
  // affiche le nombre de secondes écoulées depuis la réinitialisation:
  //lcd.print(millis()/1000);
  
    DateTime now = RTC.now();
    lcd.print(now.year()-2000, DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print(' ');
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.println(".");
}
