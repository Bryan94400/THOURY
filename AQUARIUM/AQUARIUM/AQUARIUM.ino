// AQUARIUM V0.0.2 TEST
// BY Jérémy Cheynet et Bryan Thoury
//

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <DallasTemperature.h> //Librairie du capteur

           //DS18B20
OneWire oneWire(3); //Bus One Wire sur la pin 3 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie

// Créz l'objet RTC
RTC_DS1307 RTC;

// Crée l'objet lcd (I2C)
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // Init le message série et imprimer
  Serial.begin(9600);
  Serial.println("Start program");
  Serial.println("V0.0.2 TEST");

  // Init I2C
  Wire.begin();

  // Init RTC
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC n est pas en cours de fonctionnement!");
  }

  // Init lcd et imprime le message
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Start program");
  lcd.setCursor(1,1);
  lcd.print("V.0.0.1");
  delay(5000);
  lcd.setCursor(1,0);
  lcd.print("nous sommes le");

            //DS18B20

Serial.begin(9600); //Permet la communication en serial
 sensors.begin(); //Activation des capteurs
 sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du bus
 sensors.setResolution(sensorDeviceAddress, 12); //Résolutions possibles: 9,10,11,12

}

void loop() {
  // Get DateTime
  DateTime now = RTC.now();

  // Transformation de la date et de l'heure en chaine de caractère
  char buffer[200] = {0, };
  snprintf(buffer, 199, "%02d/%02d/%02d %02d:%02d   ", now.year()-2000,
      now.month(), now.day(), now.hour(), now.minute(), now.second());

  // Afficher DateTime
  lcd.setCursor(0, 1);  
  lcd.print(buffer);

  // Imprimer DateTime en série
  Serial.println(buffer);

  // attend 100ms
  delay(100);

            //DS18B20

void loop()  {
 sensors.requestTemperatures(); //Demande la température aux capteurs
 Serial.print("La température est: ");
 Serial.print(sensors.getTempCByIndex(0)); //Récupération de la température en celsius du capteur n°0
 Serial.println(" C°");
}
