#include <Wire.h>
#include <Arduino.h>
//library to read the temp/humid sensor
#include "DHT.h"
#define DHTPIN 2     // what pin the DHT is connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
// #define DHTTYPE DHT22   // DHT 22  (AM2302)
// #define DHTTYPE DHT21   // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
DHT dht(DHTPIN, DHTTYPE);

float t, h;
char msg[40];
char temp[6];
char hum[6];
String temp_string;
byte x = 0;
byte y = 0;
byte *t_byte = (byte*) &t;

int ftoa(char *a, float f)  //translates floating point readings into strings
{
  int left=int(f);
  float decimal = f-left;
  int right = decimal *100; //2 decimal points
  if (right > 10) {  //if the decimal has two places already. Otherwise
    sprintf(a, "%d.%d",left,right);
  } else { 
    sprintf(a, "%d.0%d",left,right); //pad with a leading 0
  }
}

float readTemp(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float t = dht.readTemperature();
  float tf = t * 1.8 +32;  //Convert from C to F 
  return   tf;
}

float readHumidity(){
  float h = dht.readHumidity();  
  return h;
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Wire.begin(10); // join i2c bus (address optional for master)
}

void loop()
{
  Serial.println("[INFO] Master02 send");
  // t = dht.readTemperature();
  
  // h = dht.readHumidity();
  ftoa(temp,dht.readTemperature());
  ftoa(hum,dht.readHumidity());
  // ftoa(temp_rand,random(10,20));
  // ftoa(hum_rand,random(70,90));
  
  //   //Compile a comma delimited string to send to the log
  //   sprintf(msg,"%s,%s",temp, hum);
  // Serial.println(t); 
  // dtostrf(t,4,2,temp);
  // dtostrf(h,4,2,hum);
  // sprintf(temp,"%.2f",t);
  // Serial.println(msg);
  // temp_string = String(t);
  // Serial.println(temp);
  // Serial.println(humid);
  // for (int i =0; i <= 5; i++){
  sprintf(msg,"Master02->Temp:%sC,Hum:%s%%%",temp, hum);
  Serial.println(msg);

  Wire.beginTransmission(1); // transmit to device #4
  Wire.write(msg); 
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(2);
  Wire.write(msg);        // sends five bytes 
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(3);
  Wire.write(msg);        // sends five bytes 
  Wire.endTransmission();    // stop transmitting
  
  delay(4000);
}