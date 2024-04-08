#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);

int raw = 0;
float temp = 0;

void setup() {
  pinMode( A0, INPUT );
  pinMode( 0, OUTPUT );
  pinMode( 4, OUTPUT );

}

void loop() {
  updateSerial();
  raw = analogRead(A0);
  temp = ( raw / 1023.0 ) * 5.0 * 1000 / 10;
  if (temp > 60) {
    digitalWrite(4, HIGH);
    Serial.begin(19200);                 
    mySerial.begin(19200);                 
    Serial.println("Initializing...");    
    delay(1000);                         

    mySerial.println("AT");           
    updateSerial();

    mySerial.println("AT+CMGF=1");                       
    updateSerial();
    mySerial.println("AT+CMGS=\"+7908180****\"");        
    updateSerial();
    mySerial.print("Temperature is BIG. Begin chill!"); 
    updateSerial();
    mySerial.write(26);
    delay(30000); 
  }
  else
    digitalWrite(4, LOW);
  if (temp < 50) {
    digitalWrite(0, HIGH);  
    mySerial.begin(19200);
    delay(1000);

    mySerial.println("AT");               
    updateSerial();

    mySerial.println("AT+CMGF=1");                       
    updateSerial();
    mySerial.println("AT+CMGS=\"+7908180****\"");         
    updateSerial();
    mySerial.print("Temperature is low. Start heating!"); 
    updateSerial();
    mySerial.write(26);
    delay(30000);
  }
  else
    digitalWrite(0, LOW);
}

void updateSerial()
{
  delay(500);                     
  while (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}
