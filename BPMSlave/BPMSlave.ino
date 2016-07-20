#include <aws_iot_mqtt.h>
#include <aws_iot_version.h>
#include "aws_iot_config.h"
#include <ArduinoJson.h>
#include <Wire.h>

char systo[4];                                                // Buffer for systolic reading
char diast[4];                                                // Buffer for diastolic reading
char pulse[4];                                                // Buffer for pulse reading

aws_iot_mqtt_client myClient;                                 // init iot_mqtt_client
char msg[32];                                                 // read-write buffer
int rc = -100;                                                // return value placeholder
bool success_connect = false;                                 // whether it is connected
StaticJsonBuffer<70> jsonBuffer;                              // JSON buffer

JsonObject& root = jsonBuffer.createObject();                 // Create empty JSON object
JsonObject& state = root.createNestedObject("state");         // Add 'state' object
JsonObject& reported = state.createNestedObject("reported");  // Add 'reported' object

void setup() {
  Serial.begin(9600);                                         // Start serial for output
  Wire.begin(1);                                              // Join i2c bus with adress #1
  Wire.onReceive(receiveEvent);                               // Register event

  while(!Serial);                                             // Waiting for Serial
  Serial.println(F("Connecting..."));                         // Print status

  rc = myClient.setup(AWS_IOT_CLIENT_ID);                     // Setup AWS
  rc = myClient.config(AWS_IOT_MQTT_HOST,
                       AWS_IOT_MQTT_PORT,
                       AWS_IOT_ROOT_CA_PATH,
                       AWS_IOT_PRIVATE_KEY_PATH,
                       AWS_IOT_CERTIFICATE_PATH);             // Config AWS
  rc = myClient.connect();                                    // Connect to AWS
  
  if (rc == 0) {                                              // See if connected succesful
    success_connect = true;
    Serial.println(F("AWS succeeded!"));
  } else {
    Serial.println(F("AWS failed!"));
  }
  
  delay(2000);  // Delay to make sure SUBACK is received
}

void loop() {

  char buffer[70];                            // Buffer for JSON-string
  
  if(success_connect) {
  
    reported.set("systolic" , atoi(systo));   // Set key-value pair for systolic
    reported.set("diastolic", atoi(diast));   // Set key-value pair for diastolic
    reported.set("pulse"    , atoi(pulse));   // Set key-value pair for pulse
  
    root.printTo(buffer, sizeof(buffer));     // Printing JSON object to string
    
    if((rc = myClient.publish("$aws/things/BloodPressureMonitor/shadow/update",
                               buffer,
                               strlen(buffer),
                               1,
                               false)) != 0)
    {
        Serial.println(F("Publish failed!"));
    }                                         // Publish JSON string to AWS Shadow
  }
  
  delay(1000);                                // 1 Second delay
}

void receiveEvent(int howMany) {
  if(Wire.available()) {
    
    for(int i = 0; i < 3; i++) {  // Get three bytes
      char c = Wire.read();       // Receive byte as a character
      systo[i] = c;               // Add char to variable
    }
    
    for(int i = 0; i < 3; i++) {  // Get three bytes
      char c = Wire.read();       // Receive byte as a character
      diast[i] = c;               // Add char to variable
    }
    
    for(int i = 0; i < 3; i++) {  // Get three bytes
      char c = Wire.read();       // Receive byte as a character
      pulse[i] = c;               // Add char to variable
    }

    while(Wire.available()) {
      Wire.read();                // Clear input if any bytes left
    }
  }
}
