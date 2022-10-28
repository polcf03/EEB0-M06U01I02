#include <I2Cdev.h>
#include <MPU6050.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define SERIE_DELAY       25

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;





#define LED_PIN 13
bool blinkState = false;

void setup() {

  lcd.begin(16, 2);              // Inicializar el LCD
  Serial.begin(38400);


  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();


  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);



  if (ax < -1500)
  {
    // Derecha
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Derecha");
  }

  else if (az > 1600)
  {
    // Arriba
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Arriba");
  }

  else if (az < -1500)
  {
    // Abajo
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Abajo");
  }

  else if (ax > 1600)
  {
    // Izquierda
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Izquierda");
  }

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
