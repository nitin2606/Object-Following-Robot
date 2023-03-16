#include<HID.h>
#include<SoftwareSerial.h>


int ENA = 5;
int ENB = 6;
int IN_1 = 7;
int IN_2 = 8;
int IN_3 = 9;
int IN_4 = 10;

int RX = 2;
int TX = 3;

SoftwareSerial softwareSerial(RX, TX);

int buzzer = 4;
char data;
int speedCar = 1023;
int speed_Coeff = 3;

//const int echoPin = 13;
//const int trigPin = 12;

//long duration, cm;




void setup() {
  // put your setup code here, to run once:

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 

  pinMode(buzzer, OUTPUT);

  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);

  Serial.begin(9600);
  softwareSerial.begin(9600);
  
 
}


void loop() {

  
  /*long duration,  cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);

  //Serial.println(cm);*/

  long cm = 40;
  if(cm<20){
    
    obs_detected(), safeBack();
    softwareSerial.flush();
    
  }

  
  

  else if (cm>20){

    softwareSerial.flush();
    if(softwareSerial.available()){
      data = softwareSerial.read();
      Serial.println(data);

      
      if (data == 'F') goAhead();
      else if (data == 'B') goBack();
      else if (data == 'L') goLeft();
      else if (data == 'R') goRight();
      else if(data=='S') stopRobot();
      else if(data=="") stopRobot();      

    }

  }

  
  //else if (data == "I") curveLeft();
  //else if (data == "G") curveRight();


}

void goAhead(){ 
      
    
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){
   
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goLeft(){ 
     
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goRight(){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goAheadRight(){
    
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 
     
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  
   
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

 void curveLeft(){

    
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, 1023);
    
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, 100);
    
 }

 void curveRight(){

    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    analogWrite(ENA, 100);
    
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    analogWrite(ENB, 1023);

 }

 void safeBack(){

    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, speedCar);

    delay(150);

    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    analogWrite(ENA, speedCar);

    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    analogWrite(ENB, speedCar);

 }


 void alert(){
   tone(buzzer, 3000);
   delay(100);
   noTone(buzzer);
   
  }


void obs_detected(){
  
  alert();
  //stopRobot();
  
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

