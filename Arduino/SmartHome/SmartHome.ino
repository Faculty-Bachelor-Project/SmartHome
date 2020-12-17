char incoming_value = 0;
int LED_BL = 12;
int LED_PIR = 11;
int INP_PIR = 4;


void setup() {
    Serial.begin(9600);
    pinMode(LED_BL,OUTPUT);
    pinMode(LED_PIR, OUTPUT);
    pinMode(INP_PIR, INPUT);
    digitalWrite(LED_BL, HIGH);
    digitalWrite(LED_PIR, HIGH);

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
  BluetoothMethod();
  SensorPIR();
}
