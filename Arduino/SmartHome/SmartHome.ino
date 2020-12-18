#include <SparkFunTSL2561.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define Type DHT11

// Set the LCD address to 0x27 or 0x3f for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Create an SFE_TSL2561 object, here called "light":
SFE_TSL2561 light;

// Global variables:
boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms = 1500;  // Integration ("shutter") time in milliseconds

char incoming_value = 0;
int LED_BL = 12;
int LED_PIR = 11;
int INP_PIR = 4;
int LED_TSL = 3;
int DHT_PIN = 8;
float humidity;
float tempC;
float tempF;

DHT dht(DHT_PIN,Type);

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    pinMode(LED_BL,OUTPUT);
    pinMode(LED_PIR, OUTPUT);
    pinMode(INP_PIR, INPUT);
    digitalWrite(LED_BL, HIGH);
    digitalWrite(LED_PIR, HIGH);
    analogWrite(LED_TSL, 255);

    dht.begin();
    delay(500);
    light.begin();

    // If gain = false (0), device is set to low gain (1X)
    // If gain = high (1), device is set to high gain (16X)
    gain = 1;

    // If time = 0, integration will be 13.7ms
    // If time = 1, integration will be 101ms
    // If time = 2, integration will be 402ms
    // If time = 3, use manual start / stop to perform your own integration
    unsigned char time = 2;

    // setTiming() will set the third parameter (ms) to the
    // requested integration time in ms (this will be useful later):
    light.setTiming(gain,time,ms);

    // To start taking measurements, power up the sensor:
    light.setPowerUp();

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
    delay(500);
    
}

void SensorTSL()
{
    delay(ms);
    unsigned int visible, infrared;
  
    if (light.getData(visible,infrared))
    {
      Serial.print("Visible: ");
      Serial.print(visible);
      Serial.print("\n");

      analogWrite(LED_TSL, visible/3);

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
      delay(2000);
   }
  else{
    Serial.println("Motion not detected");
      digitalWrite(LED_PIR,HIGH);
      delay(2000);
  }
}

void BluetoothMethod()
{
      if(Serial.available() > 0)
      {
            incoming_value = Serial.read();
            Serial.print(incoming_value);
            Serial.print("\n");

            if(incoming_value == '1')
            {
                digitalWrite(LED_BL, LOW);
            }
            else if(incoming_value == '0')
            {
                digitalWrite(LED_BL, HIGH);
            }
      }
}

void loop() {
  SensorTSL();
  BluetoothMethod();
  SensorPIR();
  DHTSensor();
}
