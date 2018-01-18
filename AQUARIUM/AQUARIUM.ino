/**
 * AQUARIUM
 * @version 0.0.3
 * @author Bryan Thoury
 * @author Jérémy Cheynet
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <DallasTemperature.h>
#include <DHT.h>

#define VERSION "version 0.0.3"

//DS18B20
OneWire oneWire(3); //Bus One Wire sur la pin 3 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie

// DHT22
// @todo : 
#define DHT_PIN 2
#define DHTTYPE DHT22

DHT dht(DHT_PIN, DHTTYPE);

// Create RTC object
RTC_DS1307 RTC;

// Init liquid crystal (I2C)
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    // Init serial
    Serial.begin(9600);
    Serial.println("Aquarium start");
    Serial.println(VERSION);

    // Init lcd
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Aquarium start");
    lcd.setCursor(0,1);
    lcd.print(VERSION);

    // Wait 5s before continue programme
    delay(5000);

    // Init I2C
    Wire.begin();

    // Init RTC (DS3132)
    RTC.begin();
    if (! RTC.isrunning()) {
        Serial.println("Can't init RTC");
        lcd.setCursor(0,0);
        lcd.print("Can't init RTC");
        delay(2000);
    }

    lcd.setCursor(0,0);
    lcd.print("nous sommes le");

    // Init dht
    dht.begin();
}

void loop() {
    // Get time and display (lcd and serial)
    displayTime();

    // Get temperature
    getTemperature();

    // attend 100ms
    delay(100);
}

void displayTime()
{
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
}

void getTemperature()
{
    sensors.requestTemperatures(); //Demande la température aux capteurs
    Serial.print("La température est: ");
    Serial.print(sensors.getTempCByIndex(0)); //Récupération de la température en celsius du capteur n°0
    Serial.println(" C°");
}

void getHumidityAndTemperature()
{
    // Get humidity
    float humidity = dht.readHumidity();

    // Get temperature (in Celsius)
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature) ) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    char buffer[200] = {0, };
    snprintf(buffer, 199, "Humidity : %d \% -- Temperature : %d°C", 
           humidity, temperature);

    Serial.println(buffer);
}