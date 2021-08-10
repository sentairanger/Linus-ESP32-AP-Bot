# Linus-ESP32-AP-Bot

## Introduction

This time I decided to move away from python and Raspberry Pis towards the ESP32. I will show you how I built and ran my own ESP32 bot using my existing robot Linus and how you can do it on your own. 

## Getting Started

To get started here is the hardware and software I used.

### Hardware

* My robot Linus fitted with an ESP32. You can use any ESP32 including the ESP32 CAM.
Materials used:
1. Generic robot chassis
2. CamJam Edukit 3 motors and Wheels
3. L298N H bridge motor controller
4. cardboard for Linus's face and servo arm
5. 2 SG90 servo motors
6. Dupont connectors
7. breadboard for ESP32
8. ESP32
9. cable ties for wiring
10. Power LED cables for Eyes including bezels
11. 6V battery packs for motors and servos

### Software

* Arduino IDE (You can download from [here](https://www.arduino.cc/en/software))
* ESP32 Library (Follow [this](https://dronebotworkshop.com/esp32-intro/) link for more details)

## Code Explanation

`robot_esp32_complete.ino`: Here we import the WiFi, WiFi Client, WiFiAP, and the ESP32Servo libraries. We define the two servos, the variables for the servos, the pins and then we define the PWM properties. Here, I am using channel 4 but you can use any channel from 0-15 as long as it does not interfere with the Servos as they operate in their own PWM channels. Then we define the AP and the password which can be anything. Then in the void setup, we allow the servo timers to be allocated, then set a period hertz for each and then attach the servo pins. Then we set the rest of the pins to output and then set up the PWM channels for the enable lines. Then the serial console is set up at a baud rate of 115200 and then the WiFi AP is setup. In void loop, the server begins and then the server displays the HTML page. Each button has its own onmousedown and onmouseup function where it invokes the commands from below. To run this on your own, be sure to upload it, then go to your WiFi settings and find your AP. Once you do enter the password and go to 192.168.4.1 where the page will be displayed. Then you can control the robot from anywhere. Move it around to test the motors and move the arm around. 

## Pictures

`Linus`
* ![Linus](https://github.com/sentairanger/Linus-ESP32-AP-Bot/blob/main/IMG_20210808_205054407.jpg)

`App Screenshot`
![Screenshot](https://github.com/sentairanger/Linus-ESP32-AP-Bot/blob/main/Screenshot%20from%202021-08-08%2020-14-42.png)
