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

}
