#include <I2Cdev.h>
#include <MPU6050.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define SERIE_DELAY       25

#define UNO       1
#define DOS       2
#define TRES      3
#define CUATRO    4
#define CINCO     5
#define SEIS      6
#define OTRO      15
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;



/*    Array   */


/*struct takePos {
  int posX;
  int posY;
  int posZ;
  };

  takePos meanPos [longArray];*/

/*    Captacion de posicion     */
int i = 0;

/*         Timer         */
void Count(void);
int cntShow = 0;
#define    timeTimer   50000


/*    Posicion    */
#define  iteration 20

int16_t averageX = 0;
int16_t averageY = 0;
int16_t averageZ = 0;

int chooseFace();

int changeFace = 0;
int posDice;


#define LED_PIN 13
bool blinkState = false;

void setup() {

  lcd.begin(16, 2);              // Inicializar el LCD
  Serial.begin(38400);

  Timer1.initialize(timeTimer); // 50ms.
  Timer1.attachInterrupt(Count);


  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();


  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (changeFace == posDice)
  {
  }
  else {

    switch (posDice) {
      case UNO:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("La UNO '1'");

        changeFace = posDice;
        break;

      case DOS:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("La DOS '2'");

        changeFace = posDice;
        break;

      case TRES:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("La TRES '3'");

        changeFace = posDice;
        break;

      case CUATRO:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("La CUATRO '4'");

        changeFace = posDice;
        break;

      case CINCO:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("La CINCO '5'");

        changeFace = posDice;
        break;

      case SEIS:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("La SEIS '6'");

        changeFace = posDice;
        break;

      case OTRO:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("La cara es:");
        lcd.setCursor(2, 1);
        lcd.print("Ta borracho");

        changeFace = posDice;
        break;

      default:
        // statements
        break;
    }
  }







  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

int chooseFace()
{

  //1: X : 17 Y : -3  Z : 172
  if (averageX >= 0 && averageY <= 0 && averageZ >= 100)
  {
    return UNO;
  }

  //2: X : -127 Y : 0 Z : 1
  else if (averageX <= -100 && averageY <= 0 && averageZ >= 0)
  {
    return DOS;
  }

  //3: X : 15 Y : -154  Z : 4
  else if (averageX >= 0 && averageY <= -100 && averageZ >= 0)
  {
    return TRES;
  }

  //4: X : 18  Y : 160 Z : 5
  else if (averageX >= 0 && averageY >= 100 && averageZ >= 0)
  {
    return CUATRO;
  }

  //5: x: 183 Y : -3  Z : 4
  else if (averageX >= 100 && averageY <= 0 && averageZ >= 0)
  {
    return CINCO;
  }

  //6: X : 13  Y : 0 Z : -142
  else if (averageX >= 0 && averageY <= 0 && averageZ <= -100)
  {
    return SEIS;
  }

  else
  {
    return OTRO;
  }

}  


/*                Count Timer             */
void Count(void)
{

  cntShow++;
  //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //meanPos[i].posX = ax / 100;
  //meanPos[i].posY = ay / 100;
  //meanPos[i].posZ = az / 100;
  averageX = ((averageX * i + (ax / 100)) / (i + 1));
  averageY = ((averageY * i + (ay / 100)) / (i + 1));
  averageZ = ((averageZ * i + (az / 100)) / (i + 1));

  if (i <= iteration - 1)
  {
    i++;
  }
  else
  {
    i = 0;
  }



  if (cntShow >= iteration)
  {
    /*for (int index = 0; index <= longArray - 1; index++)
      {
      averageX = averageX + meanPos[index].posX;
      averageY = averageY + meanPos[index].posY;
      averageZ = averageZ + meanPos[index].posZ;
      meanPos[index].posX = 0;
      meanPos[index].posY = 0;
      meanPos[index].posZ = 0;
      }

      /*averageX = averageX / longArray;
      averageY = averageY / longArray;
      averageZ = averageZ / longArray;*/

    Serial.print("Prueba 5: \t");
    Serial.print("X : ");
    Serial.print(averageX); Serial.print("\t");
    Serial.print("Y : ");
    Serial.print(averageY); Serial.print("\t");
    Serial.print("Z : ");
    Serial.println(averageZ);
    Serial.println(cntShow);
    posDice = chooseFace();
    averageX = 0;
    averageY = 0;
    averageZ = 0;

    cntShow = 0;
  }



}
