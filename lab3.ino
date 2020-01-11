#include <Servo.h>

int sensors_num = 3;
int echoPins[] = {1, 3, 5};
int trigPins[] = {2, 4, 6};
int angles[] = {0, 90, 180};

Servo servo;
int basePosition = 0;

void setup()
{
  for (int i = 0; i < sensors_num; i++)
  {
    pinMode(echoPins[i], INPUT);
    pinMode(trigPins[i], OUTPUT);
    digitalWrite(trigPins[i], LOW);
  }
  
  servo.attach(10);
  servo.write(basePosition);
}

void loop() {
  int angle = getAngle();
  servo.write(angle);
}

int getAngle(){
    int angle = angles[0];
    float minDist = readDist(trigPins[0], echoPins[0]);

    for (int i = 1; i < sensors_num; i++)
    {
      int dist = readDist(trigPins[i], echoPins[i]);
      if (dist < minDist)
      {
        minDist = dist;
        angle = angles[i];
      }
    }

    return angle;
}

float readDist(int trigPin, int echoPin)
{
  const float speedOfSoundMPerSec = 340.0;
  const float speedOfSoundCmPerUs = speedOfSoundMPerSec / 10000.0;
  return readPulse(trigPin, echoPin) * speedOfSoundCmPerUs / 2.0;
}

float readPulse(int trigPin, int echoPin)
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration;
}
