import processing.serial.*;
import processing.sound.*;

Serial myPort;  // The serial port
String Sval="0#0#0#0#";
int Data[]={0,0,0,0};
int fan=0;
boolean Check[]={false,false,false,false};
boolean Pause=true;
PImage BulbOff;
PImage BulbOn;
PImage FanOn;
PImage FanOff;
PImage LockOn;
PImage LockOff;
PImage Radio;
PImage Play;
SoundFile file;

void setup() 
{
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  size(1000,1000);
  Play=loadImage("Play.png");
  BulbOff=loadImage("Bulb_OFF.png");
  BulbOn=loadImage("Bulb_ON.png");
  FanOff=loadImage("Fan_Off.png");
  FanOn=loadImage("Fan_ON.png");
  LockOff=loadImage("Lock_Off.png");
  LockOn=loadImage("Lock_On.png");
  Radio=loadImage("Radio.png");
  file = new SoundFile(this, "Thunder.mp3");
}
void draw() 
{
  background(255,0,0);
  while (myPort.available() > 0) 
  {
    if(myPort.available()>0) 
      {  
        Sval=myPort.readStringUntil('\n');
      }
      if(Sval!=null)
      {  
        for(int i=0;i<4;i++)
        {
          Data[i]=int(Sval.substring(2*i,(2*i)+1));
        }
      }
      
  }
  
  if(Check[2])
  {
    background(0,255,255);
    image(Radio,50,0);
    image(Play,400,750,200,200);
    if(Pause)
    {
      file.play();
      Pause=false;
    }
    if(Data[0]==1 && Data[1]==0)
    {
      Pause=true;  
      file.pause();
    }
    else if(Data[0]==0 && Data[1]==1)
    {
      file.stop();
      Check[2]=false;
    }
  }
  else
  {
    if(Data[0]==1 && Data[1]==0)
    {
      Check[2]=true;    
    }
    else if(Data[0]==1 && Data[1]==1)
    {
      Check[0]=!Check[0];
    }
    else if(Data[0]==0 && Data[1]==1)
    {
      Check[1]=!Check[1];
    }
    
    fill(255,150,200);
    rect(0,0,500,500);
    fill(0,255,255);
    rect(0,500,500,500);
    fill(255,0,255);
    rect(500,0,500,500);
    fill(0,0,255);
    rect(500,500,500,500);
    
    //For Bulb
    if(Check[0])
      image(BulbOn,120,70);
    else
      image(BulbOff,120,70);
      
    
    
    //For Fan
    if(Check[1])
    {
      image(FanOn,550,50,500,400);  
    }
    else
    {
      image(FanOff,550,50,250,400);
    }
    
    //For Lock
    if(Check[3])
    {
      image(LockOn,120,600,250,300);
    }
    else
    {
      image(LockOff,120,600,250,300);
    }
    
    //For Radio
    image(Radio,600,600,300,300);
  }
  delay(1000);
}
