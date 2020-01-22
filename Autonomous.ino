#include <Maneuver.h>

Maneuver maneuver;
Sensor frontSensor;
Sensor rearSensor;

int forwardDistance = 0;

void setup() {
  Serial.begin(9600); 

  maneuver.Configure({5, 6, 7, 8, 9, 11, true});
  maneuver.SetSpeed(250);

  frontSensor.Echo = A4;
  frontSensor.Trig = A5;
  
  pinMode(frontSensor.Echo, INPUT);    
  pinMode(frontSensor.Trig, OUTPUT);
    
  maneuver.Stop();
}

void loop() {
  forwardDistance = maneuver.GetDistance(frontSensor);
  
  if(forwardDistance > 50){
    maneuver.Forward();
  }else {
    maneuver.Scan(frontSensor);
  } 
}
