# eHealth-IoT
Healthcare Internet of Things device

![screenshot](https://georgthomassen.github.io/images/ehealth-iot/website.png)

# Used units
- Arduino Yún
- Arduino Uno
- Amazon AWS IoT
- [Cooking Hacks eHealth pack](https://www.cooking-hacks.com/documentation/tutorials/ehealth-biometric-sensor-platform-arduino-raspberry-pi-medical)

# Usage
1. Setup [AWS IoT SDK](https://github.com/aws/aws-iot-device-sdk-arduino-yun#installation) on the Arduino Yún
2. Add [eHealth](https://www.cooking-hacks.com/documentation/tutorials/ehealth-biometric-sensor-platform-arduino-raspberry-pi-medical#step3_1), [ArduinoJson](https://github.com/bblanchon/ArduinoJson) and the AWS libraries to the Arduino IDE
3. Upload BPMMaster sketch to Arduino Uno
4. Upload BPMSlave sketch to Arduino Yun
5. Connect blood pressure monitor to the Arduino Uno
6. Copy `certs` folder from AWS-SDK to website folder
7. Change `/website/routes/index.js` to match `certs` folder
8. Run `npm install` and `bower install` in `website` folder
9. Run `npm start` in website folder to start website at `localhost:3000`

# Circuit
![circuit](https://georgthomassen.github.io/images/ehealth-iot/wires.png)