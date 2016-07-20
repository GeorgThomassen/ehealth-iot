var express = require('express');
var router = express.Router();

/*
 * AWAS
 */
var awsIot = require('aws-iot-device-sdk');
var response, reported;
var device = awsIot.device({
   keyPath: 'certs/4782034784-private.pem.key',
  certPath: 'certs/4782034784-certificate.pem.crt',
    caPath: 'certs/root-CA.crt',
  clientId: 'BloodPressureMonitor',
    region: 'eu-central-1' 
});

device.on('connect', function() {
  device.subscribe('$aws/things/BloodPressureMonitor/shadow/get/accepted');
  device.publish('$aws/things/BloodPressureMonitor/shadow/get', "");
});

device.on('message', function(topic, payload) {
    response = JSON.parse(payload.toString());
    reported = response.state.reported;
    console.log(JSON.stringify(reported));
});

/* GET home page. */
router.get('/', function(req, res, next) {

  device.publish('$aws/things/BloodPressureMonitor/shadow/get', "");
  
  res.render('index',
  	{
  		title: 'Blood Pressure Monitor',
  		systolic: reported.systolic,
  		diastolic: reported.diastolic,
  	 	pulse: reported.pulse,	
  	 });
});

module.exports = router;