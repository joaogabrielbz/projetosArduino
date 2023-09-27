
int buzPin = 7;       
int trigPin = 8;     
int echoPin = 4;   
float speed = 0.0347;
float dist;        
float pingTime;      
int buzNear = 20; 
int buzHigh = 50;   
int buzMid  =130;    
int buzFar = 600;     
int delayFar = 260;
 
 
void setup() {
  Serial.begin(9600);
  pinMode(buzPin,OUTPUT);     
  pinMode(trigPin,OUTPUT);    
  pinMode(echoPin,INPUT);     
 
}
 
void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);          
  pingTime = pulseIn(echoPin,HIGH);   
  dist = (speed*pingTime*0.5);    
  Serial.print("Distance: ");
  Serial.println(dist);       
  
  if(dist<=10.0){
    digitalWrite(buzPin,HIGH);        
    delay(20);
    digitalWrite(buzPin,LOW);
    delay(20);
  }  
  else if(dist<=30.0 && dist>10.0)
  {
    digitalWrite(buzPin,HIGH);
    delay(buzHigh);
    digitalWrite(buzPin,LOW);
    delay(buzHigh);
  }
  else if((dist>30.0) && (dist<60.0))
  {
    digitalWrite(buzPin,HIGH);
    delay(buzMid);
    digitalWrite(buzPin,LOW);
    delay(buzMid);
  }
  else if(dist>=60.0 && dist<120.0)
  {
    digitalWrite(buzPin,HIGH);
    delay(buzFar);
    digitalWrite(buzPin,LOW);
    delay(delayFar);
  }
  
}