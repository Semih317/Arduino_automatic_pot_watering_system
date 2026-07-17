#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 7  
#define DHTTYPE DHT11
#define BUTTON_PIN 6
#define LCD_BACKLIGHT_PIN 8
#define PUMP_PIN 3 
LiquidCrystal lcd(12, 11, 5, 4, 9, 10);
DHT dht(DHTPIN, DHTTYPE);
const int moistureSensorPowerPin = 2;
const int moistureSensorAnalogPin = A0;
const int dryValue = 985; //The value obtained by immersing the sensor in completely dry soil
const int wetValue = 230; //The value obtained by immersing the sensor in completely wet soil
const int maxMoisture = 75;
const int maxTrying = 10;
unsigned long lastMeasurementTime = 0;
const unsigned long measurementPeriod = 3600000;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(moistureSensorPowerPin, OUTPUT);
  digitalWrite(moistureSensorPowerPin, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);
  lcd.begin(16, 2);
}

int readSoilMoisture() {
  digitalWrite(moistureSensorPowerPin, HIGH);
  delay(50); //for sensor wake up

  long total = 0;
  const int exampleValue = 5;
  for (int i = 0; i < exampleValue; i++) {
    total += analogRead(moistureSensorAnalogPin);
    delay(20);
  }

  digitalWrite(moistureSensorPowerPin, LOW);
  return total / exampleValue;
}

int convertMoisturePercentage(int rawDeger) {
  rawDeger = constrain(rawDeger, wetValue, dryValue);
  int percentage = map(rawDeger, dryValue, wetValue, 0, 100);
  return percentage;
}

void irrigation(int percentage) {
  int trying = 0;

  while (percentage < maxMoisture && trying < maxTrying) {
    digitalWrite(PUMP_PIN, LOW);
    delay(700);
    digitalWrite(PUMP_PIN, HIGH);
    delay(3000);
    if (trying < 9){ //This is for prevent character distortion on the LCD
      int moistureRaw = readSoilMoisture();
      percentage = convertMoisturePercentage(moistureRaw);
    }
    trying++;
  }
}

void loop() {
  bool isButtonActive = (digitalRead(BUTTON_PIN) == LOW);
  unsigned long present = millis();

  if (present - lastMeasurementTime >= measurementPeriod) {
    lastMeasurementTime = present;

    int moistureRaw = readSoilMoisture();
    int moisturePercentage = convertMoisturePercentage(moistureRaw);
    
    if (moisturePercentage < maxMoisture) {
     irrigation(moisturePercentage);
    }
  }

  if (isButtonActive == false) {
    digitalWrite(LCD_BACKLIGHT_PIN, LOW);

    float airHumidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(airHumidity) || isnan(temperature)) {
      lcd.setCursor(0, 0);
      lcd.print("Sensor hatasi!  ");
    } else {
      int moistureRaw = readSoilMoisture();
      int moisturePercentage = convertMoisturePercentage(moistureRaw);
      lcd.setCursor(0, 0);
      lcd.print(temperature, 1);
      lcd.write(223);
      lcd.print("C ");
      lcd.print("Nem: ");
      lcd.print("%");
      lcd.print(airHumidity, 0);
      lcd.print("  "); //Added to prevent any residual characters from remaining

      lcd.setCursor(0, 1);
      lcd.print("Toprak Nemi:");
      lcd.print("%");
      lcd.print(moisturePercentage);
      lcd.print("   "); //Added to prevent any residual characters from remaining
    }
    delay(2000); //For DHT11
  } else { 
    digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
    lcd.clear();
    delay(50);
  }
}