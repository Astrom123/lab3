#include <Servo.h>

int sensors_num = 3;
int echoPins[] = {2, 3, 5};
int trigPins[] = {1, 4, 6};

int angles[] = {0, 180, 90};
int dists[] = {0, 0, 0};

Servo servo;
int servoPin = 10;
int basePosition = 0;

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < sensors_num; i++)
  {
    pinMode(echoPins[i], INPUT);
    pinMode(trigPins[i], OUTPUT);
    digitalWrite(trigPins[i], LOW);
  }
  
  servo.attach(servoPin);
  servo.write(basePosition);

  for (int i = 0; i < sensors_num; i++)
  {
    dists[i] = readDist(trigPins[i], echoPins[i]);
    Serial.println(dists[i]);
  }
}

void loop() {
  int angle = getAngle();
  servo.write(angle);
  delay(300);
}

int getAngle(){
    int minDist = 2000;
    int angle = 0;
    for (int i = 0; i < sensors_num; i++)
    {
      int dist = readDist(trigPins[i], echoPins[i]);
      Serial.println(dist);
      if (dists[i] - dist > 20)
      {
        if (dist < minDist)
        {
          minDist = dist;
          angle = angles[i];
        }
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
