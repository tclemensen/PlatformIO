#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_PCD8544.h>

Adafruit_BME280 bme;
Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);

unsigned long delayInterval = 10000;
unsigned long previousMillis = 0;

void displayDataLCD()
{
  // Reading data from sensor and displaying data on the LCD

  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = (bme.readPressure() / 100);

  display.clearDisplay();
  display.println("Tmp:  " + String(temp) + " C");
  display.println("Hum:  " + String(humidity) + " %");
  display.println("Bar: " + String(pressure) + "hPa");

  if (pressure > 1014)
  {
    display.println("High");
  }
  else if (pressure < 1014 and pressure > 1012)
  {
    display.println("Normal");
  }
  else if (pressure < 1012)
  {
    display.println("Low");
  }

  display.display();
}

void displayDataSerial()
{
  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = (bme.readPressure() / 100);

  Serial.println("Tmp: " + String(temp) + " C");
  Serial.println("Hum: " + String(humidity) + " %");
  Serial.println("Bar: " + String(pressure) + "hPa");
}

void setup()
{
  Wire.begin(D6, D5); // Initialising I2C on digital pins D6 and D5

  Serial.begin(115200); // Starting serial monitor communication
  display.begin();      // Starting Nokia 5110 Display
  bme.begin(0x76);      // Starting BME280 Sensor

  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setContrast(5);
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.print("Initialising");
  display.display();

  Serial.print("Initialising . . .");
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= delayInterval)
  {
    displayDataLCD();
    displayDataSerial();
    previousMillis = millis();
  }
}