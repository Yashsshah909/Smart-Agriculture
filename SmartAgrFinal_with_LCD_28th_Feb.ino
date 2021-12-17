#include <SoftwareSerial.h>

#include <I2CSoilMoistureSensor.h>

#include <dht.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

SoftwareSerial SIM900(9, 10); // gsm module connected here
String textForSMS;

#define dht_apin 7 // Analog Pin sensor is connected to
 
dht DHT;

int msensor = A1; // moisture sensor is connected with the analog pin A1 of the Arduino
int msvalue = 0; // moisture sensor value 
int waterpump = 13; 
int Fan=12;
int pump;
int fan;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Welcome to Smart");
  lcd.setCursor(2,1);
  lcd.print("Agriculture");
  lcd.setCursor(1, 0);
  delay(1500);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("GSM is");
  lcd.setCursor(2,1);
  lcd.print("Inatilizing");
  delay(1500);
  lcd.clear();
  SIM900.begin(9600); // original 9600. while enter 9600 for sim900A
  pinMode(msensor, INPUT);
  pinMode(waterpump, OUTPUT);  
  pinMode(Fan,OUTPUT);
  SoftwareSerial mySerial(9, 10); //for GSM purpose 9=Tx & 10=Rx
  Serial.println("Welcome to Smart Agriculture");
  delay(1000);
}
void loop(){
  smsensor();
  dht11();
  lcdend();
  //gsmpump();
  //gsmfan1();
}

void smsensor() {
  msvalue = analogRead(msensor);
  Serial.print("Soil Moisture Value = ");
  Serial.println(msvalue);
  lcd.setCursor(1,0);
  lcd.print("Moisture= ");
  lcd.print(msvalue);
  delay(2000);
  lcd.clear();
  if (msvalue <= 800 )
{
  digitalWrite(waterpump, LOW); 

  lcd.setCursor(3,1);
  lcd.print("Pump is Off");
  delay(2000);
  lcd.clear();
  
}

  else 
{
  digitalWrite(waterpump, HIGH); 
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("Pump is on");
  delay(2000);
  lcd.clear();
}
}
void dht11(){
    DHT.read11(dht_apin);
    float hum = DHT.humidity;
    float temp = DHT.temperature;
  
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(hum);
  lcd.setCursor(0,0);
  lcd.print("Temperature = ");
  lcd.print(temp);
  delay(2000);
  lcd.clear();
  lcd.print("Humidity = ");
  lcd.print(hum);
  delay(2000);
  lcd.clear();
if (temp <= 27)
{
  digitalWrite(Fan,HIGH);
  lcd.setCursor(3,0);
  lcd.print("Fan is On");
  delay(2000);
  lcd.clear();
}
if (temp > 27)
{ 
  digitalWrite(Fan,LOW);
  lcd.setCursor(3,0);
  lcd.print("Fan is Off");
  delay(2000);
  lcd.clear();
}

}
void gsmpump() {
  
 boolean flag1 = false; 
 pump = digitalRead(13);  // reading the coming signal from the soil sensor
  if((pump == LOW)&&(flag1 == false)) // if water level is full then cut the relay
  {
     textForSMS =  "\nPump is ON";
//    sendSMS(textForSMS);
  Serial.println(textForSMS);
  Serial.println("message sent."); 
  flag1 = true;
  delay(1000);
  }
  else{
  boolean flag2 = false;
  if((pump == HIGH) && (flag2 == false))
  {
      textForSMS =  "\nPump is OFF";
//    sendSMS(textForSMS);
  Serial.println(textForSMS);
  Serial.println("message sent."); 
  flag2 = true;
  delay(1000);
  }
  delay(1000);
}
}
void gsmfan1() {
boolean flag1 = false; 
 fan = digitalRead(12);  // reading the coming signal from the soil sensor
  if((fan == LOW)&&(flag1 == false)) // if water level is full then cut the relay
  {
     textForSMS =  "\nFan is ON";
//    sendSMS(textForSMS);
  Serial.println(textForSMS);
  Serial.println("message sent."); 
  flag1 = true;
  delay(1000);
  }
  else{
  boolean flag2 = false;
  if((fan == HIGH) && (flag2 == false))
  {
      textForSMS =  "\nFan is OFF";
//    sendSMS(textForSMS);
    Serial.println(textForSMS);
  Serial.println("message sent."); 
  flag2 = true;
  delay(1000);
  }
  delay(1000);
}
}


//void sendSMS(String message)
//{
//  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
//  delay(1000);
// SIM900.println("AT + CMGS = \"+919619810601\"");  // recipient's mobile number, in international format
// 
//  delay(1000);
//  SIM900.println(message);                         // message to send
//  delay(1000);
//  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
//  delay(1000); 
//  SIM900.println();
//  delay(100);                                     // give module time to send SMS
// 
//}
void lcdend()
{
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Thank You!");
  delay(2000);
  lcd.clear();
}
