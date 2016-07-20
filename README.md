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
2. Upload BPMMaster sketch to Arduino Uno
3. Upload BPMSlave sketch to Arduino Yun
4. Connect blood pressure monitor to the Arduino Uno
5. Copy `certs` folder from AWS-SDK to website folder
6. Change `/website/routes/index.js` to match `certs` folder
7. Run `npm install` and `bower install` in `website` folder
8. Run `npm start` in website folder to start website at `localhost:3000`