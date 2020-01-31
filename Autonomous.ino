#include <Maneuver.h>

Maneuver maneuver;

int forwardDistance = 0;
int minimumDistance = 12;

void setup() {
  Serial.begin(9600); 

  Settings settings = {5, 6, 7, 8, 9, 11, true, minimumDistance, {A4, A5}};
  
  maneuver.Configure(settings);
  maneuver.SetSpeed(250);
  
  maneuver.Stop();
}

void loop() {
  forwardDistance = maneuver.GetDistance();
    
  if(forwardDistance >= minimumDistance){
    maneuver.Forward();
  }else {
    maneuver.Scan();
  }
}
