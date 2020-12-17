char incoming_value = 0;
int LED_BL = 12;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BL,OUTPUT);
    digitalWrite(LED_BL, HIGH);
}

void BluetoothMethod()
{
        if(Serial.available() > 0)
        {
              incoming_value = Serial.read();
              switch(incoming_value)
              {
                case '0' : digitalWrite(LED_BL,HIGH);break;
                case '1' : digitalWrite(LED_BL,LOW);break;
              }
              Serial.println(incoming_value);
        }
        delay(50);
}

void loop() {
  BluetoothMethod();

}
