// inlcuding  libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// setting pins
const int soilMoisturePin = A0;
const int waterPumpPin = 3;
const int DHTPin = 2;
const int lcdColumns = 16;
const int lcdRows = 2;
const int moistureThreshold = 700;  // Dry Soil Moisture Threshold

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
DHT dht(DHTPin, DHT11);

int pumpStatus = 0;

// setup code

void setup() {
  pinMode(soilMoisturePin, INPUT);
  pinMode(waterPumpPin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(lcdColumns, lcdRows);
  dht.begin();
}

// loop code
void loop() {
  int soilMoisture = analogRead(soilMoisturePin); // reading soil moisture
  // reading temperature and humidity
  float humidity = dht.readHumidity();        
  float temperature = dht.readTemperature();

  // lcd code
  // printing soil moisture
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.setCursor(2, 0);
  lcd.print(soilMoisture);

  // printing temperature and humidity on lcd
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.setCursor(2, 1);
  lcd.print(temperature);
  lcd.setCursor(4, 1);
  lcd.print("C");
  lcd.setCursor(6, 1);
  lcd.print("H:");
  lcd.setCursor(8, 1);
  lcd.print(humidity);
  lcd.print("%");

  // Displaying all information on the serial monitor
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(", Temperature: ");
  Serial.print(temperature);
  Serial.print(", Humidity: ");
  Serial.print(humidity);
  Serial.print(", Pump Status: ");
  Serial.println(pumpStatus == 1 ? "On" : "Off");

  // Activate and deactivate pump based on soil moisture
  if (soilMoisture > moistureThreshold && pumpStatus == 0) {
    activatePump();
  } else if (soilMoisture <= moistureThreshold && pumpStatus == 1) {
    deactivatePump();
  }

  // delaying 5s
  delay(5000);
}

// pump activating logic
void activatePump() {
  digitalWrite(waterPumpPin, HIGH);
  pumpStatus = 1;
  lcd.setCursor(0, 1);
  lcd.print("Soil Dry! Pump On");
  Serial.println("Pump activated");
}

// pump deactivate logiv
void deactivatePump() {
  digitalWrite(waterPumpPin, LOW);
  pumpStatus = 0;
  lcd.setCursor(0, 1);
  lcd.print("Soil Moist. OK");
  Serial.println("Pump deactivated");
}