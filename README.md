# Overview
The project aims to build an embedded system to detect hazards like fires, smoke, and intrusions. Also, a communication system is implemented
between two microcontrollers using Li-Fi communication

# Basic operation
A microcontroller is connected to the sensors (in our case a Tiva c board is used) and keeps on monitoring their readings until a reading exceeds its threshold, After pressing
a start button, the microcontroller starts monitoring the sensors, 
if an abnormal reading happens
the microcontroller sends a light signal to the receiver microcontroller (in our case an atmega32 was used) to decode the type of hazard then acts accordingly and displays a warning message on
an LCD, while activating a buzzer and a blinking light which operate until a mute button is pressed, Also a warning message is sent to the mobile phone using Bluetooth
If a stop button is pressed the first microcontroller doesn't monitor the sensors

# Sender Side Tools
* Tiva-C Board
* HC-SR04 ultrasonic sensor (to detect intrusions)
* MQ-2 Smoke Sensor
* A Switch
* Start and Stop Buttons (on the tiva-c board)
* HC-05 Bluetooth Module (to send warnings to mobile phone)
* Red LED (Used for Li-Fi communication)

# Reciever Side Tools
* Atmega32 IC
* LCD 16x2
* Buzzer
* Mute Button
* LED (flashes for every warning)
* LDR (For detecting light in Li-Fi communication)

# Li-Fi Communication Protocol
Each time a hazard is detected, the sender microcontroller flashes A certain number of light pulses in one second.
On the receiver side, each time a pulse is detected using the LDR a one-second timer is started, and after the timer elapses, 
the microcontroller counts the number of pulses received in this one second and acts according to the type of hazard
* 1 Pulse ---------------> Hazard detected by Ultrasonic Sensor
* 2 Pulses --------------> Hazard detected by Smoke Sensor
* 3 Pulses --------------> Switch was switched ON

# Collaborators

This project wasn't going to be possible if it weren't for:
[Yehia Hassan](https://github.com/DevYehia)
<br>
[Mohammed Ayman](https://github.com/M0hAyman)
<br>
[Ismail Seddik](https://github.com/Ismailseddik)
<br>
[Tarek Khaled](https://github.com/tito360x)
<br>
[Mohammed Hesham](https://github.com/MHZDN)https://github.com/MHZDN


