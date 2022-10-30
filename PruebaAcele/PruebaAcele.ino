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


/*    Array   */
#define longArray       20

struct takePos {
  int posX;
  int posY;
  int posZ;
};

takePos meanPos [longArray];

/*    Captacion de posicion     */
int i = 0;

/*         Timer         */
void Count(void);
int cntTake = 0;
int cntShow = 0;

/*    Posicion    */

int averageX = 0;
int averageY = 0;
int averageZ = 0;

#define LED_PIN 13
bool blinkState = false;

void setup() {

  lcd.begin(16, 2);              // Inicializar el LCD
  Serial.begin(38400);

  Timer1.initialize(50000); // 50ms.
  Timer1.attachInterrupt(Count);


  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();


  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("CNT");
  lcd.setCursor(0, 0);
  lcd.print(cntShow);



  /*Serial.print("Prueba 0: \t");
    Serial.print("x"); Serial.print(" : ");
    Serial.print(ax); Serial.print("\t");
    Serial.print("Y"); Serial.print(" : ");
    Serial.print(ay); Serial.print("\t");
    Serial.print("Z"); Serial.print(" : ");
    Serial.println(az);*/
  /*Serial.print(az); Serial.print("\t");º
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.println(gz);*/



  /*if (averageX < -1500)
    {
    // Derecha
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Derecha");
    averageX = 0;
    averageY = 0;
    averageZ = 0;
    }

    else if (averageZ > 1600)
    {
    // Arriba
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Arriba");
    averageX = 0;
    averageY = 0;
    averageZ = 0;
    }

    else if (averageZ < -1500)
    {
    // Abajo
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Abajo");
    averageX = 0;
    averageY = 0;
    averageZ = 0;
    }

    else if (averageX > 1600)
    {
    // Izquierda
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Izquierda");
    averageX = 0;
    averageY = 0;
    averageZ = 0;
    }*/

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

/*void takeInfo()
  {



  meanPos[i].posX = ax;
  meanPos[i].posY = ay;
  meanPos[i].posZ = az;
  Serial.print("Hola/");
  }*/

/*                Count Timer             */
void Count(void)
{
  cntShow++;

  //Serial.println("Toy aqui");
  //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  meanPos[i].posX = ax;
  meanPos[i].posY = ay;
  meanPos[i].posZ = az;
  Serial.print("Prueba 1: \t");
    Serial.print("x"); Serial.print(" : ");
    Serial.print(ax); Serial.print("\t");
    Serial.print("Y"); Serial.print(" : ");
    Serial.print(ay); Serial.print("\t");
    Serial.print("Z"); Serial.print(" : ");
    Serial.println(az);
    Serial.print("Prueba 2: \t");
    Serial.print("x"); Serial.print(" : ");
    Serial.print(meanPos[i].posX); Serial.print("\t");
    Serial.print("Y"); Serial.print(" : ");
    Serial.print(meanPos[i].posY); Serial.print("\t");
    Serial.print("Z"); Serial.print(" : ");
    Serial.println(meanPos[i].posZ); 

  if (i <= longArray - 1)
  {
    i++;
    //Serial.println("++");
  }
  else
  {
    i = 0;
    //Serial.println("0");
  }

  //Serial.print("Hola/");

  if (cntShow >= longArray)
  {
    //Serial.print("if");
    for (int index = 0; index <= longArray - 1; index++)
    {

      averageX = averageX + meanPos[index].posX;
      averageY = averageY + meanPos[index].posY;
      averageZ = averageZ + meanPos[index].posZ;
      meanPos[index].posX = 0;
      meanPos[index].posY = 0;
      meanPos[index].posZ = 0;
      Serial.print("Prueba 5: \t");
    Serial.print("X : ");
    Serial.print(averageX); Serial.print("\t");
    Serial.print("Y : ");
    Serial.print(averageY); Serial.print("\t");
    Serial.print("Z : ");
    Serial.println(averageZ);
    Serial.println(cntShow);

      //Serial.println("Array");

    }
    averageX = averageX / longArray;
    averageY = averageY / longArray;
    averageZ = averageZ / longArray;

    /*Serial.print("Prueba 5: \t");
    Serial.print("X : ");
    Serial.print(averageX); Serial.print("\t");
    Serial.print("Y : ");
    Serial.print(averageY); Serial.print("\t");
    Serial.print("Z : ");
    Serial.println(averageZ);
    Serial.println(cntShow);*/
    averageX = 0;
    averageY = 0;
    averageZ = 0;



    cntShow = 0;
  }



}
