#include <SparkFunTSL2561.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define Type DHT11

LiquidCrystal_I2C lcd(0x27, 20, 4);

SFE_TSL2561 light;

boolean gain;
unsigned int ms = 1500;

int LED_B_BL = 6;
int LED_G_BL = 5;
int LED_BL = 12;
int LED_PIR = 11;
int INP_PIR = 4;
int LED_TSL = 3;
int LED_B_TSL = 10;
int LED_G_TSL = 9;
int DHT_PIN = 8;
int COOLER_PIN = 13;
int MQ7_analog_IN = A0;
int MQ2_analog_IN = A1;
float humidity;
float tempC;
float tempF;

DHT dht(DHT_PIN,Type);

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Which sensor do");
    lcd.setCursor(0,1);
    lcd.print("you want to use?");
    Serial.begin(9600);
    pinMode(LED_BL,OUTPUT);
    pinMode(LED_PIR, OUTPUT);
    pinMode(INP_PIR, INPUT);
    pinMode(COOLER_PIN, OUTPUT);
    pinMode(MQ7_analog_IN, INPUT);
    pinMode(MQ2_analog_IN, INPUT);
    digitalWrite(LED_BL, HIGH);
    digitalWrite(LED_PIR, HIGH);
    analogWrite(LED_TSL, 255);

    dht.begin();
    delay(500);
    light.begin();

    gain = 1;
    unsigned char time = 2;

    // setTiming() will set the third parameter (ms) to the
    // requested integration time in ms (this will be useful later):
    light.setTiming(gain,time,ms);

    // To start taking measurements, power up the sensor:
    light.setPowerUp();

}

void MonoxideSensorPrint()
{
  int Value = analogRead(MQ7_analog_IN);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CO value:   ");
  lcd.print(Value);
  //delay(1500);   
}

void GasSensorPrint()
{
  int Value = analogRead(MQ2_analog_IN);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gas value:  ");
  lcd.print(Value);
  //delay(1500);   
}

void CoSensor()
{
  int Value = analogRead(MQ7_analog_IN);
  Serial.print("Monoxid value: ");
  Serial.println(Value);
  
  if(Value >= 100)
  {
    digitalWrite(COOLER_PIN, HIGH);
  }
  else
  {
    digitalWrite(COOLER_PIN, LOW);
  }
}
//  delay(1500);


void GazSensor()
{
  int Value = analogRead(MQ2_analog_IN);
  Serial.print("Gsz value: ");
  Serial.println(Value);
  
  if(Value >= 170)
  {
    digitalWrite(COOLER_PIN, HIGH);
  }
  else
  {
    digitalWrite(COOLER_PIN, LOW);
  }
 // delay(1500);
}

void DHTSensor()
{
    humidity = dht.readHumidity();
    tempC = dht.readTemperature();
    tempF = dht.readTemperature(true);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TempC:");
    lcd.print(tempC);
    lcd.print(" C ");
    lcd.setCursor(0,1);
    lcd.print("Humidity:");
    lcd.print(humidity);
    lcd.print(" %");
  //  delay(500);
    
}

void SensorTSL()
{
  //  delay(ms);
    unsigned int visible, infrared;
  
    if (light.getData(visible,infrared))
    {
      Serial.print("Visible: ");
      Serial.print(visible);
      Serial.print("\n");
      
      if (visible > 20000)
      {
      analogWrite(LED_TSL, 255);
      analogWrite(LED_B_TSL, 255);
      analogWrite(LED_G_TSL, 255);
      }
      else
      {
      analogWrite(LED_TSL, visible/3);
      delay(500);
      analogWrite(LED_B_TSL, visible/3);
      delay(500);
      analogWrite(LED_G_TSL, visible/3);
      delay(500);
      }

    }
    else
    {
      byte error = light.getError();
      Serial.println(error);
    }
}

void SensorPIR(){
   if(digitalRead(INP_PIR) == HIGH)
   {
    Serial.println("Motion Detected");
      digitalWrite(LED_PIR,LOW);
     // delay(2000);
   }
  else{
    Serial.println("Motion not detected");
      digitalWrite(LED_PIR,HIGH);
     // delay(2000);
  }
}

void BluetoothMethod()
{
      if(Serial.available() > 0)
      {
            char incoming_value = Serial.read();
            Serial.print(incoming_value);
            Serial.print("\n");

            switch(incoming_value)
            {
              case 'a':
                DHTSensor();
                break;
              case 'b':
                GasSensorPrint();
                break;
              case 'c':
                MonoxideSensorPrint();
                break;
              default:
                DHTSensor();
                break;
            }

            switch (incoming_value)
            {
            case '1':
               digitalWrite(LED_BL, LOW);
               delay(500);
               digitalWrite(LED_BL, HIGH);
               delay(500);
               analogWrite(LED_B_BL, 0);
               delay(500);
               analogWrite(LED_B_BL, 255);
               delay(500);
               analogWrite(LED_G_BL, 0);
               delay(500);
               analogWrite(LED_G_BL, 255);
               delay(500);
               digitalWrite(LED_BL, LOW);
               analogWrite(LED_B_BL, 0);
               delay(500);
               digitalWrite(LED_BL, HIGH);
               analogWrite(LED_B_BL, 255);
               delay(500);
               digitalWrite(LED_BL, LOW);
               analogWrite(LED_G_BL, 0);
               delay(500);
               digitalWrite(LED_BL, HIGH);
               analogWrite(LED_G_BL, 255);
               delay(500);
               break;
            case '0':
                digitalWrite(LED_BL, HIGH);
                analogWrite(LED_B_BL, 255);
                analogWrite(LED_G_BL, 255);
                break;
            default:
                digitalWrite(LED_BL, HIGH);
                analogWrite(LED_B_BL, 255);
                analogWrite(LED_G_BL, 255);
                break;  
           }
      }
}

void loop() {
  SensorTSL();
  BluetoothMethod();
  SensorPIR();
  CoSensor();
  GazSensor();

  Serial.print("\n");
  delay(1500);
}
