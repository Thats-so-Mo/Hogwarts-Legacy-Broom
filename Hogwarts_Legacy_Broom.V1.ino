//  _   _                                _         _                                  ______ _       _              ______
// | | | |                              | |       | |                                 |  ___| |     (_)             | ___ \                          
// | |_| | ___   __ ___      ____ _ _ __| |_ ___  | |     ___  __ _  __ _  ___ _   _  | |_  | |_   _ _ _ __   __ _  | |_/ /_ __ ___   ___  _ __ ___
// |  _  |/ _ \ / _` \ \ /\ / / _` | '__| __/ __| | |    / _ \/ _` |/ _` |/ __| | | | |  _| | | | | | | '_ \ / _` | | ___ \ '__/ _ \ / _ \| '_ ` _ \ 
// | | | | (_) | (_| |\ V  V / (_| | |  | |_\__ \ | |___|  __/ (_| | (_| | (__| |_| | | |   | | |_| | | | | | (_| | | |_/ / | | (_) | (_) | | | | | |
// \_| |_/\___/ \__, | \_/\_/ \__,_|_|   \__|___/ \_____/\___|\__, |\__,_|\___|\__, | \_|   |_|\__, |_|_| |_|\__, | \____/|_|  \___/ \___/|_| |_| |_|
//               __/ |                                         __/ |            __/ |           __/ |         __/ |
//              |___/                                         |___/            |___/           |___/         |___/
//
// Turn a movie prop/broom/mop/sweeper into a controller to fly the in-game broom of Hogwarts Legacy (PC Only).
// This code is created/modified by 'That's So Mo' or 'Mo', the code itself utilises the ArduinoXInput library (created by Dave Madison - https://github.com/dmadison/ArduinoXInput). This bit of cheeky code essentially turns the broom/mop/sweeper into a giant Xbox 360 controller
// This code is open-source/free to use and modify etc.
// Thanks to Dave Madison for his ArduinoXinput Library and I followed this tutorial to set myself up: https://www.partsnotincluded.com/how-to-emulate-an-xbox-controller-with-arduino-xinput/
// Check out and subscribe to my YouTube Channel!: https://www.youtube.com/thatssomo1

#include <Adafruit_LSM6DS3TRC.h>
#include <NewPing.h>
#include <XInput.h>
#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 500
// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int minVal = 265;
int maxVal = 402;
int mountState = 0;
double x;
double y;
double z;

Adafruit_LSM6DS3TRC lsm6ds3trc;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit LSM6DS3TR-C test!");

  //if (!lsm6ds3trc.begin_I2C()) {
  if (!lsm6ds3trc.begin_SPI(LSM_CS)) {
    Serial.println("Failed to find LSM6DS3TR-C chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DS3TR-C Found!");

  // lsm6ds3trc.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (lsm6ds3trc.getAccelRange()) {
    case LSM6DS_ACCEL_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case LSM6DS_ACCEL_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case LSM6DS_ACCEL_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case LSM6DS_ACCEL_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }

  // lsm6ds3trc.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Accelerometer data rate set to: ");
  switch (lsm6ds3trc.getAccelDataRate()) {
    case LSM6DS_RATE_SHUTDOWN:
      Serial.println("0 Hz");
      break;
    case LSM6DS_RATE_12_5_HZ:
      Serial.println("12.5 Hz");
      break;
    case LSM6DS_RATE_26_HZ:
      Serial.println("26 Hz");
      break;
    case LSM6DS_RATE_52_HZ:
      Serial.println("52 Hz");
      break;
    case LSM6DS_RATE_104_HZ:
      Serial.println("104 Hz");
      break;
    case LSM6DS_RATE_208_HZ:
      Serial.println("208 Hz");
      break;
    case LSM6DS_RATE_416_HZ:
      Serial.println("416 Hz");
      break;
    case LSM6DS_RATE_833_HZ:
      Serial.println("833 Hz");
      break;
    case LSM6DS_RATE_1_66K_HZ:
      Serial.println("1.66 KHz");
      break;
    case LSM6DS_RATE_3_33K_HZ:
      Serial.println("3.33 KHz");
      break;
    case LSM6DS_RATE_6_66K_HZ:
      Serial.println("6.66 KHz");
      break;
  }

  lsm6ds3trc.configInt1(false, false, true);
  XInput.setRange(JOY_LEFT, 60, 115);
  XInput.setRange(JOY_RIGHT, 60, 115);
  XInput.begin();
}

void loop() {
  // Get a new normalized sensor event
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds3trc.getEvent(&accel, &gyro, &temp);


  int xAng = map(accel.acceleration.x, minVal, maxVal, -90, 90);
  int yAng = map(accel.acceleration.y, minVal, maxVal, -90, 90);
  int zAng = map(accel.acceleration.z, minVal, maxVal, -90, 90);

  z = RAD_TO_DEG * (atan2(-accel.acceleration.y, -accel.acceleration.x) + PI);
  x = RAD_TO_DEG * (atan2(-accel.acceleration.y, -accel.acceleration.z) + PI);
  y = RAD_TO_DEG * (atan2(-accel.acceleration.x, -accel.acceleration.z) + PI);


  if (mountState == 0 && ((x >= 80) && (x <= 100)) && (sonar.ping_cm() <= 40)) //to mount the broom, initial mounting needs calibration for person and positioning of sensors on broom - etc.
  {
    XInput.press(BUTTON_LB);
    delay(1002);
    XInput.press(BUTTON_B);
    delay(750);
    XInput.release(BUTTON_LB);
    XInput.release(BUTTON_B);
    mountState = 1;
    delay(100);
  }
  if (mountState == 1) //default stuff that should be running once mounted on broom
  {
    XInput.setJoystickY(JOY_RIGHT, x, false);
    XInput.setJoystickX(JOY_RIGHT, (x) , false);    
    XInput.setJoystickX(JOY_LEFT, z, false);
    XInput.setButton(TRIGGER_RIGHT, ((sonar.ping_cm() >= 2) && (sonar.ping_cm() <= 20))); //normal flight speed
    XInput.setButton(TRIGGER_LEFT, ((sonar.ping_cm() >= 2) && (sonar.ping_cm() <= 10)));  //turbo flight speed
    if ((x >= 170) || (x <= 10) && (sonar.ping_cm() >= 35 || sonar.ping_cm() == 0))
    {
      XInput.press(BUTTON_B);
      delay(2000);
      XInput.release(BUTTON_B);
      mountState = 0;
      delay(3000);
    }
  }

  delay(100);

}
