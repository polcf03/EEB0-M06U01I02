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

void chooseFace(int posDice);


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


  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("CNT");
  lcd.setCursor(0, 0);
  lcd.print(cntShow);




  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

void chooseFace()
{
  if ()
  {

  }
  else if ()
  {

  }
  else if ()
  {

  }
  else if ()
  {

  }
  else if ()
  {

  }
  else if ()
  {

  }

  Serial.print("Hola/");
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
    chooseFace();
    averageX = 0;
    averageY = 0;
    averageZ = 0;

    cntShow = 0;
  }



}
