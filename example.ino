#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int soilMoisturePin = A0;
const int waterPumpPin = 3;
const int DHTPin = 2;
const int lcdColumns = 16;
const int lcdRows = 2;
const int moistureThreshold = 700;  // Adjust as needed

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
DHT dht(DHTPin, DHT11);

int pumpStatus = 0;

void setup() {
  pinMode(soilMoisturePin, INPUT);
  pinMode(waterPumpPin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(lcdColumns, lcdRows);
  dht.begin();
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil:");
  lcd.setCursor(6, 0);
  lcd.print(soilMoisture);

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(6, 1);
  lcd.print(temperature);
  lcd.setCursor(10, 1);
  lcd.print("C");
  lcd.setCursor(12, 1);
  lcd.print("Hum:");
  lcd.setCursor(15, 1);
  lcd.print(humidity);
  lcd.print("%");

  // Display information on the serial monitor
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(", Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Pump Status: ");
  Serial.println(pumpStatus == 1 ? "On" : "Off");

  // Adjust pump based on soil moisture
  if (soilMoisture > moistureThreshold && pumpStatus == 0) {
    activatePump();
  } else if (soilMoisture <= moistureThreshold && pumpStatus == 1) {
    deactivatePump();
  }

  delay(5000);
}

void activatePump() {
  digitalWrite(waterPumpPin, HIGH);
  pumpStatus = 1;
  lcd.setCursor(0, 1);
  lcd.print("Soil Dry! Pump On");
  Serial.println("Pump activated");
}

void deactivatePump() {
  digitalWrite(waterPumpPin, LOW);
  pumpStatus = 0;
  lcd.setCursor(0, 1);
  lcd.print("Soil Moist. OK");
  Serial.println("Pump deactivated");
}
