# PaloAtlo
PaloATLO: **A**re **T**he **L**ights **O**n?

A simple wireless communications project created out of forgetfulness.

## Purpose
My step dad's worst nightmare is a light being left on. He wakes in the middle of the night to ask me: "Are the lights on?". This was a quick project to show him that I care about the lights being on, to hopefully put his mind at ease.

## Description
### Hardware Requirements
1. Arduino UNO WiFi *
2. Arduino MKR1010 *
3. Analog Photoresistor Sensor **
4. Red LED
5. Green LED
6. 5 Male-to-male jumper wires
7. 3 Female-to-male jumper wires

* Any arduino board with WiFi functionality can work.
** Must be three pin (Vin, GND, AnalogOutput)
### Other Requirements
1. WPA2 Protected Network

### Functionality
The MKR1010 board is simply connected to a photoresistor. The photoresistor is given 5V and is wired into an analog input, where the value is then read every 0.5 seconds. Using MQTT protocols, the sensor reading is then sent to a broker that is hosted on port 1927. The sensor reading varies from 400 - 700 in high light, and 800 - 1023 in low light. The data is posted to a topic labeled "Light", which the UNO WiFi is also subscribed to. The UNO is connected to two LED lights as shown below. The green light is on when the board is connected to the WiFi, and the red light is on when the MKR1010 is sending sensor data within the high light range (<900). 

## Gallery
![alt text](https://raw.githubusercontent.com/RohitKochhar/PaloAtlo/master/Public/Photos/MKR1010.jpg)
![alt text](https://raw.githubusercontent.com/RohitKochhar/PaloAtlo/master/Public/Photos/MKR10102.jpg)
![alt text](https://raw.githubusercontent.com/RohitKochhar/PaloAtlo/master/Public/Photos/Photoresistor .jpg)
![alt text](https://raw.githubusercontent.com/RohitKochhar/PaloAtlo/master/Public/Photos/LightsOn.jpg)
The red light is activated in the above picture, signalling that the light is on.
![alt text](https://raw.githubusercontent.com/RohitKochhar/PaloAtlo/master/Public/Photos/LightsOff.jpg)
The red light is not activated in the above picture, signalling that the light is off. The green light is on, so we are connected to the internet.
This readme is in progress (as of 24/12/2018), check back in a bit and it will be completed.

