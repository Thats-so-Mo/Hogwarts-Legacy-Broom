# Hogwarts Legacy Broom

The basic idea behind this project is to control the in-game broomstick in Hogwarts Legacy via a $800 Harry Potter's Nimbus 2000 movie prop replica. This done by the combination of a Adafruit LSM6DS3TR-C (Accelerometer), HC-SR04 Ultrasonic Module (Distance Measuring) Sensor and a Arduino Pro Micro. I essentially turn the broom movie prop replica into a GIANT XBOX 360/One controller by utilising the Arduino Xinput library (created by David Madison). The Arduino connects to the PC as a XBOX 360/One Controller. The Arduino utilises the sensors as a way to input data, to determine which buttons are needed to be pressed to send the PC with Hogwarts Legacy running on it via USB.

## Check out the video for a demonstration

[![Thumbnail of Youtube Video based upon this fantastic and brilliant project](https://i.ibb.co/Q8b7BfG/thumbnailv2.png)](https://youtu.be/3N-Sf7CjN4E)

## Ingredients

Items needed:
1. Arduino based Pro Micro (eBay/electronics site)
2. HC-SR04 Ultrasonic Module Distance Measuring Sensor (I got mine here: https://core-electronics.com.au/hc-sr04-ultrasonic-module-distance-measuring-sensor.html)
3. Adafruit LSM6DS3TR-C (I got mine here: https://core-electronics.com.au/adafruit-lsm6ds3tr-c-6-dof-accel-gyro-imu-stemma-qt-qwiic.html)
4. a push button (for reseting the Arduino - to reset the mount state just incase)

Three required libraries:

Dave Madison's Arduino Xinput - https://www.partsnotincluded.com/how-to-emulate-an-xbox-controller-with-arduino-xinput/

Tim Eckel's NewPing

Adafruit LSM6DS3: https://github.com/adafruit/Adafruit_LSM6DS

Special Thanks to the creators of those libraries, without them - I would not have been able to complete this project. :)

## Wiring Diagram

## Explaination


My code is based off of the example code that was provided by Adafruit for the LSM6DS3TR-C sensor.  I removed certain elements that were deemed useless to my goal for example, serial printing temperature, acceleration, gyro. I also added in the setup required for the ultrasonic sensor and Arduino xinput. Three different libraries are required for my code: Arduino Xinput, Adafruit_ accelerator, newping (ulstrasonic). 


![Acc data](https://i.ibb.co/Sx92kC7/2-1.png)

This section essentially converts the accelerometer data from reading the acceleration data into angle data, from radians to degrees.


![data](https://i.ibb.co/hMJB7M2/2-2.png)

Now in the first if statement, you can see that i added in three conditions:

 1. The mountstate - the mountstate essentially tells the arduino if your either mounted or not, 0 being not and 1 being yes your mounted. This state changes in relation to whether you are mounted or not so in this case this line of code will be triggerable if you are NOT mounted.
 2. This bit of code actually relates to the angle of the broom, essentially the pitch axis (this may be different to how you mount your sensor which in my case x axis become my pitch axis). The broom must be angled between 80 to 100 degrees to satisfy this condition. Because in the harry potter movies and in game, its roughly the angle a person keeps their broom at when they are mounting it.
 3. the third one is that the ultra sonic sensor must detect my torso within a 40cm range of the sensor.

Once all three conditions are satisfied, the Arduino sends out a xinput command to essentially mount the broom in game. It will Hold LB for 1 second, press B for ¾ of a second and then release the hold of the two buttons and change the mountstate to 1. So at this point you should be in person mounted on your broom while your character is doing the same.


![data](https://i.ibb.co/BqRywRv/2-3.png)

Now in this section of the code, the six lines of code become activated once the mountstate becomes 1. The first three lines of code relate to the pitch and roll movement of the nimbus 2000 and associating it with the ingame broom. The xinput joysticks is essentially mapped directly to the x axis (pitch) and the z axis (roll).

I have also set a range for the joysticks of only reading between 60 to 115 degrees to smooth out the controlling. Tinkering may need to occur for this section, to calibrate to the rider to their broom and to the game.

The next two relate to the propulsion, the first one determines that if the ultrasonic sensor detects my torso between 2cm to 20cm of the sensor, it will activate normal propulsion, normal flight speed - which will trigger RT.

The next line considers that if my torso is in between 2cm to 10cm of the sensor to activate  the speed boost, by sending out the LT command.

Now the last chunk of the relates to the demounting of the broom, so if the broom is pitched at an angle over 170 degrees or below 10 degrees, and if the distance of the rider is greater than 35cm or equals to 0cm - it will conside the rider is not on the broom, having to be demounted in which will trigger send the B button press command for 2 seconds, to ensure the mc demounts the broom. It will also change the mount state back to 0.

Thats pretty much it… simple and sufficient. Calibration may be required for certain elements for example the distance measuring element.

