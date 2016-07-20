#include <eHealth.h>
#include <Wire.h>

char tmp[4];
char msg[10];

void setup() {
  pinMode(13,OUTPUT);                 // Set PIN mode
  digitalWrite(13, HIGH);             // Power on BPM
  delay(1000);                        // Wait for power on
  eHealth.readBloodPressureSensor();  // Read data
  delay(100);                         // Wait
  Wire.begin();                       // Join i2c bus
  Serial.begin(9600);                 // Start serial for output
}

void loop() {
  
  msg[0] = (char) 0;                                                    // Clear msg
  uint8_t i = eHealth.getBloodPressureLength()-1;                       // Get last reading index
  
  sprintf(tmp,"%03d", 30+eHealth.bloodPressureDataVector[i].systolic);  // Get Systolic reading and convert to 3 bytes char*
  sprintf(msg,"%s%s", msg, tmp);                                        // Add to msg char*

  sprintf(tmp,"%03d", eHealth.bloodPressureDataVector[i].diastolic);    // Get Diastolic reading and convert to 3 bytes char*
  sprintf(msg,"%s%s", msg, tmp);                                        // Add to msg char*

  sprintf(tmp,"%03d", eHealth.bloodPressureDataVector[i].pulse);        // Get Pulse reading and convert to 3 bytes char*
  sprintf(msg,"%s%s", msg, tmp);                                        // Add to msg char*

  Wire.beginTransmission(1);  // Begin i2c transmission
  Wire.write(msg);            // Send msg to Yun
  Wire.endTransmission();     // End i2c transmission

  delay(500);
}
