void setup() {
    Serial.begin(9600);
    pinMode(13,OUTPUT);
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
                digitalWrite(13, LOW);
            }
            else if(incoming_value == '0')
            {
                digitalWrite(13, HIGH);
            }
      }
}

void loop() {
  BluetoothMethod();

}
