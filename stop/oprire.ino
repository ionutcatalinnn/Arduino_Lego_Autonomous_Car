#include <Servo.h> 

const int AIA = 3; //Define pin number for motor
const int AIB = 5; //Define pin number for motor
const int BIA = 6; //Define pin number for motor
const int BIB = 9; //Define pin number for motor

const int R = A5; //Line Sensor Right
const int M = A4; //Line Sensor Middle
const int L = A3; //Line Sensor Left

const int FD = A0; //Distance sensor front
const int MD = A1; //Distance sensor middle
const int BD = A2; //Distance sensor back

const int GROUND_COLOR = 100; // threshold for line sensor

int frontD = 0;

//int Vehicle_Direction = 1;

int z=0; //value for loop increment for steering
int VAL = 0; //received value from bluetooth converted to int
//int i;
int FromSerial; //received value from bluetooth
int servo_initial_position = 74; //initial position for servo from steering
Servo servo_direction; //define servomotor
int follow = 0;

void setup() {
  
Serial.begin(9600); //initialize comunication with arduino board
servo_direction.attach(10); //define pin number for servomotor / need to be a pwm pin
servo_direction.write(servo_initial_position); //set direction in initial position

 pinMode(FD, INPUT); //Configure the specified pin to behave as an input
 pinMode(MD, INPUT); //Configure the specified pin to behave as an input
 pinMode(BD, INPUT); //Configure the specified pin to behave as an input

 pinMode(R, INPUT); //Configure the specified pin to behave as an input
 pinMode(M, INPUT); //Configure the specified pin to behave as an input
 pinMode(L, INPUT); //Configure the specified pin to behave as an input

 pinMode(AIA, OUTPUT); //Configure the specified pin to behave as an output
 pinMode(AIB, OUTPUT); //Configure the specified pin to behave as an output
 pinMode(BIA, OUTPUT); //Configure the specified pin to behave as an output
 pinMode(BIB, OUTPUT); //Configure the specified pin to behave as an output
 
delay(2000); // delay time for a secure initialisation
}


void loop()
{

//Serial.print("Fata ");
//Serial.println(analogRead(FD));
//Serial.print(" Mijloc ");
//Serial.print(analogRead(MD));
//Serial.print(" Spate ");
//Serial.print(analogRead(BD));
//Serial.print(" Stanga ");
//Serial.print(analogRead(L));
//Serial.print(" Mijloc ");
//Serial.print(analogRead(M));
//Serial.print(" Dreapta ");
//Serial.println(analogRead(R));

if(Serial.available()) //Take the received value from serial in "VAL"
  {  
    FromSerial=Serial.read();
    if ( (FromSerial!=35) &&  (FromSerial!=98) &&  (FromSerial!=61))
    {
      VAL = FromSerial;
      Serial.println(VAL);
    }
  
if((analogRead(FD)>370)&&(analogRead(FD)<470))
{
  VAL=48;
}

if(analogRead(FD)>470)
{
VAL=50;
}

if((analogRead(FD)>200)&&(analogRead(FD)<370))
{
  VAL=49;
}



switch(VAL) //Drive by phone
  {
  case 49:// Front
    {
      Forward();
      break;
    }
  case 50:// Backward
    {
      Backward();
      break;
    }
  case 51: // Left
    {
      Left();
      break;
    }
  case 52: // Right
    {
      Right();
      break;
    }
  case 55:
    {
      //Line_Follow();
      break;
    } 
  case 48:
    {
      Stop();
      break;
    }
  case 0:
    {
      Stop();
      break;
    }
  }
}}
void Forward()
{
analogWrite(AIA, 255);
analogWrite(AIB, 0);
analogWrite(BIA, 255);
analogWrite(BIB, 0);
}

void Backward()
{
analogWrite(AIA, 0);
analogWrite(AIB, 255);
analogWrite(BIA, 0);
analogWrite(BIB, 255);
}

void Stop()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, 0);
 analogWrite(BIA, 0);
 analogWrite(BIB, 0);
}

void Left()
{
Serial.println(z);
z++;
if(z>7)
  {
    z=0;
    servo_direction.write(servo_initial_position --);
  if (servo_initial_position <= 54)
    {
    servo_initial_position = 54;
    }
  } 
}

void Right()
{
Serial.println(z);
z++;
if(z>7)
  {
    z=0;
    servo_direction.write(servo_initial_position ++);
  if (servo_initial_position >= 94)
    {
    servo_initial_position = 94;
    }
  } 
}
