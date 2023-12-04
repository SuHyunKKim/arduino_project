void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = (sensorValue/1024*5.0)*1000;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.print("        sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" mV");
  delay(1000);
}

