#include <Maneuver.h>
#include <Servo.h>

Servo servo; // create servo object to control servo
Maneuver maneuver;
Sensor frontSensor;
Sensor rearSensor;

int rightDistance = 0, leftDistance = 0, frontDistance = 0, rearDistance = 0;

void scan(){
  maneuver.Turn('L',90);
  leftDistance = maneuver.Distance(frontSensor);  
  delay(1000);
  
  maneuver.Turn('R',180);
  rightDistance = maneuver.Distance(frontSensor);
  delay(1000);
  
  maneuver.Turn('L',90);
  frontDistance = maneuver.Distance(frontSensor);
  delay(1000);
}

void setDirection(){
  if((rightDistance <= 50) && (leftDistance <= 50) && (frontDistance <= 50)){
    maneuver.Backward();
    delay(400);
    scan();
    setDirection();    
  }else if(rightDistance == leftDistance){
    maneuver.Backward();
    delay(400);
    scan();
    setDirection();
  }else if((leftDistance > 50) && (leftDistance > rightDistance)){
    maneuver.Turn('L',90);
  }else if ((rightDistance > 50) && (rightDistance > leftDistance)){
    maneuver.Turn('R', 90);
  }else if((frontDistance > 50) && ((frontDistance > leftDistance) && (frontDistance > rightDistance))) {
    maneuver.Forward();
  }else {
    // write a function to randomly determine a direction here
    maneuver.Turn('L',90);
  }
}

void setup() {
  Serial.begin(9600); 

  //servo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  maneuver.Configure({5, 6, 7, 8, 9, 11, false});
  maneuver.SetSpeed(250);

  frontSensor.Echo = A4;
  frontSensor.Trig = A5;
  
  pinMode(frontSensor.Echo, INPUT);    
  pinMode(frontSensor.Trig, OUTPUT);
    
  maneuver.Stop();
}

void loop() {
  frontDistance = maneuver.Distance(frontSensor);
  
  if(frontDistance > 50){
    maneuver.Forward();
  }else {
    scan();
    setDirection();
  } 
}
