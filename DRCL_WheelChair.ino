// I2Cdev and MPU6050 must be installed as libraries , or else the . cpp /.h files
// for both classes must be in the include path of your project
# include "I2Cdev.h"
# include "MPU6050.h"
# include "Wire.h"
#include "HX711.h"


// Create object to read accelerometer data
MPU6050 accelgyro ;

// Create variables to hold acceleration values
int16_t ax, ay, az ;
int16_t gx, gy, gz ;
//HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
long firstReading;
long reading;
long initial;
HX711 scale;

void setup () {
// Initialize communication with accelerometer .
// The Wire library requires special communication via
// pins A4 ( connected to SDA ) and A5 ( connected to SCL).
Wire.begin ();

// initialize serial communication
Serial.begin (9600);
scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

// initialize accelerometer
accelgyro.initialize () ;

// verify connection

Serial.println (" Testing device connections ...");

if(accelgyro.testConnection () ) {
  Serial.println (" MPU6050 connection successful ");
  } else {
  Serial.println (" MPU6050 connection failed ");
}

if (scale.is_ready()){
  
  while(firstReading < 250000){
    firstReading = scale.read();
  } 
  initial = firstReading;
  Serial.print(initial);
  
}

}

void loop () {
  reading = scale.read();
  // read raw accel / gyro measurements from device
  accelgyro.getMotion6 (& ax , & ay , &az , &gx , &gy , & gz );

  if(reading >= initial-10000 && ay>-500 && ay <2500){
    Serial.print("HX711 reading: ");
    Serial.println(reading);
    Serial.print ( ay ); 
    Serial.print ( '\n' );
    Serial.print ("\t"); // Print acceleration in y
    delay(50);
  } else if (reading < initial-10000 || ay< -450){
    Serial.print("Accelerate forward");
  } else if (ay > 2500){
    Serial.print("Accelerate backwards");

  }
  Serial.print('\n');
  delay(50);
}