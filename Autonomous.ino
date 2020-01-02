#include <Maneuver.h>
#include <Servo.h>

Servo servo; // create servo object to control servo
Maneuver maneuver;
Sensor frontSensor;
Sensor rearSensor;

int rightDistance = 0, leftDistance = 0, frontDistance = 0, rearDistance = 0;

void scan(Sensor sensor){
  maneuver.Turn('L',90);
  delay(200);
  leftDistance = maneuver.Distance(sensor);  
  delay(800);
  
  maneuver.Turn('R',180);
  delay(200);
  rightDistance = maneuver.Distance(sensor);
  delay(800);
  
  maneuver.Turn('L',90);
  delay(200);
  frontDistance = maneuver.Distance(sensor);
  delay(800);
}

void setDirection(){
  if((rightDistance <= 50) && (leftDistance <= 50) && (frontDistance <= 50)){
    maneuver.Backward();
    delay(400);
    scan(frontSensor);
    setDirection();    
  }
  
  if(rightDistance == leftDistance){
    maneuver.Backward();
    delay(400);
    scan(frontSensor);
    setDirection();
  }

  if(leftDistance > rightDistance){
    maneuver.Turn('L',90);
  }else if (rightDistance > leftDistance){
    maneuver.Turn('R', 90);
  }else if ((frontDistance > leftDistance) && (frontDistance > rightDistance)) {
    maneuver.Forward();
  }else {
    // write a function to randomly determine a direction here
    maneuver.Turn('L',90);
  }
}

void configureSensor(Sensor &sensor, int echo, int trig){
  sensor.Echo = echo;
  sensor.Trig = trig;
  
  pinMode(sensor.Echo, INPUT);    
  pinMode(sensor.Trig, OUTPUT);
}

void setup() {
  Serial.begin(9600); 

  //servo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  maneuver.Configure({5, 6, 7, 8, 9, 11, false});
  maneuver.SetSpeed(250);
  
  configureSensor(frontSensor, A4, A5); 
    
  maneuver.Stop();
}

void loop() {
  frontDistance = maneuver.Distance(frontSensor);
  
  if(frontDistance > 50){
    maneuver.Forward();
  }else {
    scan(frontSensor);
    setDirection();
  } 
}
