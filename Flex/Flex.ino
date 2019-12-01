#define Bulb  3
#define Fan   4
#define Music 5
#define Lock  6 

//Constants:
const int flexPin[4] = {A0,A1,A2,A3}; //pin A0 to read analog input

//Variables:
int value; //save analog value
int check;
int Blue;

void setup()
{
  pinMode(Bulb, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Music, OUTPUT);
  pinMode(Lock, OUTPUT);
  digitalWrite(Bulb, LOW);
  digitalWrite(Fan, LOW);
  digitalWrite(Music, LOW);
  digitalWrite(Lock, LOW);
  Serial.begin(9600);       //Begin serial communication

}


void loop(){
  int value[4];
  int Values[4];
  for(int i=0; i<4; i++)
    Values[i]=0;
  for(int i=0;i<4;i++)
  {
    value[i] = analogRead(flexPin[i]);//Read and save analog value from potentiometer
  }
  if(value[0]>950)
    Values[0]=1;
  if(value[1]>900)
    Values[1]=1;
  if(value[2]>900)
    Values[2]=1;
  if(value[3]<1022)
    Values[3]=1;
  for(int i=0;i<4;i++)
  {
    Serial.print(value[i]);
    Serial.print("#");
  }//Print value
  Serial.println("");
  digitalWrite(Bulb, Values[0]);
  digitalWrite(Fan, Values[1]);
  digitalWrite(Music, Values[2]);
  digitalWrite(Lock, Values[3]);
  
  delay(1000);                          //Small delay
  
}
