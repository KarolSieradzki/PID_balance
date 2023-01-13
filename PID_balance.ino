#include <Servo.h>

/*balancing the ball on the rail moved by servo, using PID*/

Servo myservo;  // create servo object to control a servo

int minservo = 65; 
int maxservo = 145;
int middleservo = 105;

int _delay = 50;
float distance, prev_distance;

float kp=3; 
float ki=0.1;
float kd=1000;
float r_p=0, r_i=0, r_d=0, degrees=0;

void setup() {
  myservo.attach(9);
  myservo.write(middleservo);
  Serial.begin(9600);
}

void loop() {
  //distance of the ball to middle of the rail in cm, 0cm is middle
  distance = getBallDistance();
  
  // Serial.print("distance = ");
  // Serial.println(distance);

  r_p = kp * distance; //calculate P value
  float diff = distance - prev_distance;
  r_d = kd*((diff)/_delay); //calculate D value

  //calculate I value
  if( -3 < distance && distance < 3)
     r_i = r_i + (ki * distance);
  else
     r_i = 0;
  
  //PID
  degrees = r_p + r_i + r_d;  
  //map the values to the angles used in the servo
  degrees = map(degrees, -150, 150, minservo, maxservo);

  if(degrees < minservo){degrees = minservo;}
  if(degrees > maxservo) {degrees = maxservo; } 

  myservo.write(degrees+10);  
  prev_distance = distance;

  delay(_delay);
}

int getBallDistance()
{
  float reading = 0.0;
  for (int i = 0 ; i< 16; i++){
    reading += analogRead(A0);
    delay(10);
  }
  
  reading = reading/16;

  float distance = 5*((float)reading/1023);
  distance = 34.25/distance - 30;

  return distance;
}
