//SD CARD MODULE
#include <SPI.h>
#include <SD.h> 
File myFile;

//TEMPERATURE SENSOR
#include "dht.h"
#define dht_apin 2 // Analog Pin sensor is connected to
 
dht DHT;


//SOIL MOISTURE SENSOR
const int soilpin=A1;
int ledsoil=12;

//ULTRASONIC SENSOR

const int trigPin = 10;
const int echoPin = 9;
long duration;
int distanceCm, distanceInch;


void setup() 
{
  //TEMPERATURE SENSOR
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 //end "setup()"

  //ULTRASONIC SENSOR
  pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
  
 //SOIL MOISTURE
 pinMode(ledsoil,OUTPUT);

 
//SD CARD
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop(){
  
  //SOIL MOISTURE 
int moisture=analogRead(soilpin);
  Serial.print("Soil Moisture =  ");
  Serial.println(moisture);
  if(moisture>1000)
  {
    digitalWrite(ledsoil,HIGH);
    delay(100);
  }
  else
{
  digitalWrite(ledsoil,LOW);
  delay(100);
}
  
//TEMPERATURE SENSOR
//Start of Program 
 
    DHT.read11(dht_apin);
    
    Serial.print("Current Humidity = ");
    Serial.print(DHT.humidity);
    Serial.println("%  ");
    Serial.print("Temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
  
// end loop() 


{
//UV SENSOR
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*3.3;
  Serial.print("Sensor Reading = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("Sensor Voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  delay(1000);

  //ULTRASONIC SENSOR
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  distanceInch = duration*0.0133/2;
//lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  Serial.print("Distance: "); // Prints string "Distance" on the LCD
  Serial.print(distanceCm); // Prints the distance value from the sensor
  Serial.println(" Cm");
  delay(10);

//lcd.setCursor(0,1);
  Serial.print("Distance: ");
  Serial.print(distanceInch);
  Serial.println(" Inch");
  delay(10);
  Serial.println("");
  }

}
