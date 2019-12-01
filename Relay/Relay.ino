#include<Servo.h>

#define I1 4
#define I2 5
#define I3 6
#define I4 7
#define Bulb  8
#define Fan   9
#define Music 10
#define Lock  11


int data[4];
int angle=0;
boolean check[4]={false,false,false,false};
Servo Door;

void setup() 
{
  pinMode(I1,INPUT);
  pinMode(I2,INPUT);
  pinMode(I3,INPUT);
  pinMode(I4,INPUT);
  pinMode(Bulb, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Music, OUTPUT);
  Door.attach(Lock);
  digitalWrite(Bulb, LOW);
  digitalWrite(Fan, LOW);
  digitalWrite(Music, LOW);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() 
{
  // Checks whether data is comming from the serial port
  data[0]=digitalRead(I1);
  data[1]=digitalRead(I2);
  data[2]=digitalRead(I3);
  data[3]=digitalRead(I4);
  Serial.print(data[0]);
  Serial.print("#");
  Serial.print(data[1]);
  Serial.print("#");
  Serial.print(data[2]);
  Serial.print("#");
  Serial.print(data[3]);  
  Serial.println("");
  if(check[2])
  {
    if(data[0]==1 && data[1]==0)
      check[2]=false;
  }
  else
  {
    if(data[0]==1 && data[1]==0)
    {
      if(check[0])
      {
        digitalWrite(Bulb, LOW);
      }      
      else
      {
        digitalWrite(Bulb, HIGH);  
      }  
      check[0]=!check[0]; 
      for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
      {                                  
        Door.write(angle);                 //command to rotate the servo to the specified angle
        delay(10);                       
      }
    }
    else if(data[0]==0 && data[1]==1)
    {
      if(check[1])
      {
        digitalWrite(Fan, HIGH);
      }      
      else
      {
        digitalWrite(Fan, LOW);
      } 
      check[1]=!check[1]; 
    }
    else if(data[0]==1 && data[1]==1)
    {
      if(check[2])
      {
        digitalWrite(Music, HIGH);
      }      
      else
      {
        digitalWrite(Music, LOW);
      } 
      check[2]=!check[2]; 
    }
    
  }
  delay(1000);
}
