#include <I2Cdev.h>
#include <MPU6050.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
MPU6050 accelgyro;
#define btnRIGHT  4
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 0
#define btnNONE   10
int16_t ax, ay, az;
float degreeX, degreeY, degreeZ;
float offsetX = 0, offsetY = 0, offsetZ = 0;
int offs = 0;
int adcKeyIn;
bool btPressed;
/*         Timer         */
void Count(void);
int cnt = 0;

void setup() {
  lcd.begin(16, 2);              // Inicializar el LCD
  Serial.begin(38400);
  accelgyro.initialize();
  Wire.begin();
  Timer1.initialize(100000); // 50ms.
  Timer1.attachInterrupt(Count);
  Serial.println("Initializing I2C devices...");
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  // Leer las aceleraciones
  accelgyro.getAcceleration(&ax, &ay, &az);
  //Calcular los angulos de inclinacion:
  degreeX = (atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * (180.0 / 3.14)) + 3 - offsetX;
  degreeY = (atan(ax / sqrt(pow(ay, 2) + pow(az, 2))) * (180.0 / 3.14)) + 1.5 - offsetY;
  degreeZ = (atan(ay / sqrt(pow(az, 2) + pow(ax, 2))) * (180.0 / 3.14)) + 3- offsetZ;

  switch (read_LCD_buttons()) {
    case btnSELECT:
      offsetX = degreeX;
      offsetY = degreeY;
      offsetZ = degreeZ;
      break;
    case btnLEFT:
      offsetX = 0;
      offsetY = 0;
      offsetZ = 0;
      break;
    default:
      break;
  }
}
int read_LCD_buttons() {
  adcKeyIn = analogRead(0);      // Leemos A0
  //Serial.println (adcKeyIn);
  if (!btPressed)
  {
    if (adcKeyIn < 10)
    {
      btPressed = true;
      return btnRIGHT;
    }
    if (adcKeyIn < 150)
    {
      btPressed = true;
      return btnUP;
    }
    if (adcKeyIn < 300)
    {
      btPressed = true;
      return btnDOWN;
    }
    if (adcKeyIn < 450)
    {
      btPressed = true;
      return btnLEFT;
    }
    if (adcKeyIn < 700)
    {
      btPressed = true;
      return btnSELECT;
    }
  }

  else if (adcKeyIn > 1000)
  {
    btPressed = false;

  }

  return btnNONE;  // in any other case
}
void Count(void) {
  if (cnt >= 1 )
  {
    //Mostrar los angulos separadas por un [tab]
    Serial.print("Degree X: ");
    Serial.print(degreeX);
    Serial.print("Degree Y:");
    Serial.print(degreeY);
    Serial.print("Degree Z:");
    Serial.println(degreeZ);
    cnt = 0;
  }
  else {
    cnt++;
  }
}
