#include <Maneuver.h>
#include <Servo.h>

Servo frontServo; // create servo object to control servo
Maneuver maneuver;

struct Sensor {
  int Echo;
  int Trig;
} frontSensor, rearSensor;

int rightDistance = 0, leftDistance = 0, frontDistance = 0, rearDistance = 0;

//Ultrasonic distance measurement Sub function
int getDistance(Sensor sensor) {
  digitalWrite(sensor.Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(sensor.Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(sensor.Trig, LOW);   
  float Fdistance = pulseIn(sensor.Echo, HIGH);  
  Fdistance = Fdistance / 58;
  
  return (int)Fdistance;
}  

void scan(Sensor sensor){
  maneuver.Turn('L',90);
  leftDistance = getDistance(sensor);  
  delay(1000);
  
  maneuver.Turn('R',180);
  rightDistance = getDistance(sensor);
  delay(1000);
  
  maneuver.Turn('L',90);
  frontDistance = getDistance(sensor);
  delay(1000);
}

void setDirection(){
  if((rightDistance <= 50) && (leftDistance <= 50)){
    maneuver.Reverse();
    delay(400);
    scan(frontSensor);
    setDirection();    
  }else if(rightDistance == leftDistance){
    maneuver.Reverse();
    delay(400);
    scan(frontSensor);
    setDirection();
  }else if(leftDistance > rightDistance){
    maneuver.Turn('L',90);
  }else if (rightDistance > leftDistance){
    maneuver.Turn('R', 90);
  }else {
    // write a function to randomly determine a direction here
    maneuver.Turn('L',90);
  }
}

void setup() { 
  Serial.begin(9600); 

  //frontServo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  maneuver.Configure({5, 6, 7, 8, 9, 11, false});

  frontSensor.Echo = A4;
  frontSensor.Trig = A5;
  
  pinMode(frontSensor.Echo, INPUT);    
  pinMode(frontSensor.Trig, OUTPUT);  
    
  maneuver.Stop();
}

void loop() {
  frontDistance = getDistance(frontSensor);
  
  if(frontDistance > 50){
    maneuver.Forward();
  }else {
    scan(frontSensor);
    setDirection();
  } 
}
