// Inputs 
int arA = 5;
int arB = 6;
int deA = 9;
int deB = 10;
int vel = 255; // speed (0-255)
int input = 'g';
int lightsensor;
int lightled = 12;
int redled = 22;
int greenled =24;
int blueled = 26;
int buzz = 28;
#include <dht11.h>
#define DHT11PIN 30
dht11 DHT11;
#include <OLED_I2C.h>
OLED  myOLED(SDA, SCL);
extern uint8_t SmallFont[];
#define echoPin1 42
#define trigPin1 44
#define echoPin2 46
#define trigPin2 48
long duration1;
long distance1;
long duration2;
long distance2;
unsigned long Time;
unsigned long nTime;
unsigned long pTime;
int delay_stop = 1000;



//--------------------SETUP------------------------------  
void setup() {

  
Serial.begin(9600); // connect bt 


pinMode(deA, OUTPUT);
pinMode(deB, OUTPUT);
pinMode(arA, OUTPUT);
pinMode(arB, OUTPUT);

pinMode(trigPin1,OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2,OUTPUT);
pinMode(echoPin2, INPUT);
  


pinMode(lightled,OUTPUT);
pinMode(redled,OUTPUT);
pinMode(greenled,OUTPUT);
pinMode(blueled,OUTPUT);
pinMode(buzz,OUTPUT);
  
  
if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
    
myOLED.setFont(SmallFont);


}

//------------------LOOP-------------------------------------
void loop() {
Time = millis();
if(Serial.available()>0){ // read input from bt
input = Serial.read();
}
if(input=='a'){ // Forward
 Serial.println(input);
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, vel);
 analogWrite(arA, vel);
 delay(delay_stop);
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, 0);
 input = 'g';
}
if(input=='d'){ // left
 Serial.println(input);
 analogWrite(deB, vel); 
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, vel);
 delay(delay_stop);
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, 0);
 input = 'g';
}

if(input=='b'){ // right
 Serial.println(input);
 analogWrite(deB, 0);
 analogWrite(arB, vel);
 analogWrite(arA, 0);
 analogWrite(deA, vel);
 delay(delay_stop);
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, 0);
 input = 'g';
}
if(input =='e'){ // Reverse
 Serial.println(input);
 analogWrite(deA, 0);
 analogWrite(arA, 0);
 analogWrite(deB, vel);
 analogWrite(arB, vel);
 delay(delay_stop);
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, 0);
 input = 'g';
}

/*if(Time - pTime >1000){ // Stop
 Serial.println(input);
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, 0);
}*/

if(input == 'f'){
 digitalWrite(lightled,HIGH); 
}

if(input == 'v'){
 digitalWrite(lightled,LOW); 
}

if(input == 'm'){
 digitalWrite(buzz,HIGH); 
}

if(input == 'n'){
 digitalWrite(buzz,LOW); 
}

lightsensor = analogRead(A0);


//---- sensors and oled------------------------------

    
digitalWrite(trigPin1,LOW);
delayMicroseconds(2);

digitalWrite(trigPin1,HIGH);
delayMicroseconds(10);

digitalWrite(trigPin1,LOW);

duration1 = pulseIn(echoPin1,HIGH);

distance1 = duration1/58.2;



    
digitalWrite(trigPin2,LOW);
delayMicroseconds(2);

digitalWrite(trigPin2,HIGH);
delayMicroseconds(10);

digitalWrite(trigPin2,LOW);

duration2 = pulseIn(echoPin2,HIGH);

distance2 = duration2/58.2;


    
delay(50);

    
int chk = DHT11.read(DHT11PIN);
   
myOLED.clrScr();

//myOLED.print("", CENTER, 0);
myOLED.print("Distance1 : ", LEFT, 16);
myOLED.print("Distance2 : ", LEFT, 26);
myOLED.print("lightvalue : ", LEFT, 36);
myOLED.print("Temperature : ", LEFT, 46);
myOLED.print("humidity : ", LEFT, 56);

  
myOLED.printNumF(float(distance1), 2, RIGHT, 16);
myOLED.printNumF(float(distance2), 2, RIGHT, 26);
myOLED.printNumF(float(lightsensor), 2, RIGHT, 36);
myOLED.printNumF(float((float)DHT11.temperature), 2, RIGHT, 46);
myOLED.printNumF(float((float)DHT11.humidity), 2, RIGHT, 56);



myOLED.update();

digitalWrite(redled,HIGH);
digitalWrite(greenled,HIGH);
digitalWrite(blueled,HIGH);
}
