#include <Servo.h>

#define triggerPin 8
#define echoPin 9
#define motorPin 11
#define motorPin2 10
#define avgCount 5


Servo myservo;
void setup() {
  Serial.begin(9600);
  myservo.attach(5);
  pinMode(triggerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  analogWrite(motorPin, 200);
  int duracao, distancia, sum, media[avgCount], i = 0, j, invalid = 0;
  while (i<avgCount)
  {
    sum = 0;
    j = 0;
    while (j<avgCount)
    {
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(triggerPin, LOW);
      
      duracao = pulseIn(echoPin, HIGH);  
      distancia = (duracao/2) /29.1;
      if (distancia > 4 && distancia < 400)
      {
        sum += distancia;
      }
      else
      {
        invalid++;
      }
      j++;
    }
    media[i] = sum / j;
    i++;
  }
  
  Serial.println(invalid);
  double realAvg = avg(media);
  Serial.println(realAvg);
  
  if (invalid > 30)
  {
    analogWrite(motorPin, 0);
    analogWrite(motorPin2, 175);
  }
  else if(realAvg < 15)
  {
    analogWrite(motorPin, 125);
    myservo.write(0);
    
  }
  else if(realAvg < 45)
  {
        analogWrite(motorPin, 125);
    myservo.write(45);

  }
  else
  {
    myservo.write(90);
    analogWrite(motorPin, 210);
  }
  
  
  //if (invalid < avgCount * avgCount / 4 && realAvg >0 && realAvg <31)
  //{
  //  turn(realAvg);
  //}
  //else{
  //  myservo.write(90);
  //}
}

double avg(int * arr){
  int i, sum = 0;
  for (i = 0; i<avgCount; i++)
    sum += arr[i];
  return sum / avgCount;
}

void turn(double avg){
  if (avg<=10){
    myservo.write(180);
  }
  else{
    myservo.write(135);
  }
  delay(50);
}
