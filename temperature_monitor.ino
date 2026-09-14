#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int tempPin = A1;
const int potPin = A0;

const int redLED = 8;
const int greenLED = 7;
const int yellowLED = 6;
const int buzzer = 5;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Temperature");
}

void loop() {
  int tempValue = analogRead(tempPin);
  int potValue = analogRead(potPin);

  float voltage = tempValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  int level = map(potValue, 0, 1023, 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  if (temperature < 20) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 1);
    lcd.print("Status: COLD   ");
  }
  else if (temperature >= 20 && temperature < 30) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL ");
  }
  else if (temperature >= 30 && temperature < 40) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 1);
    lcd.print("Status: WARM   ");
  }
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    tone(buzzer, 1000);

    lcd.setCursor(0, 1);
    lcd.print("Status: HOT!   ");
  }

  delay(500);
}
