/*
SENSOR CAHAYA BNI + Panic button
below. Or just customize this script to talk to other HTTP servers.
 *ON >70%
 *OFF <30%
 *not define 30<val<70
 *
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "miconos-wowowow";//miconos-wowowow Smart Living
const char* password = "miconos1"; // miconos1
//https://api.telegram.org/bot216353971:AAHyd_ZKzWFAUeSGI2fdkQJfdhmLZYLG0G0/sendMessage?chat_id=-198645569&text=/alive
const char* host = "dapuralena.com"; //Http://broadlink.id/lampubni/tambah.php?id=SC0001&pesan=BNI0001_200L/OFF|1 http://www.broadlink.id/lampubni/tambah.php?ids=sc0001&pesan=tes
const char* url1 = "/lampubni/tambah.php?ids=SC0001&pesan=";
const char* url2 = "&pesan=";
const char* urlInfo = "alive";
const char* urlSOS = "alert!";


const char* urlInfoLampu = "SC0001:BNI0001_200L/OFF|1";
const char* urlSensorId = "SC0001";  //
const char* urlBniCab = "BNI0001";
const char* urlValLux = ""; //?lux
int tempValLux=0;
String statLamp;
String tempStatLamp;

int button;
int interupt = 0;
const byte interruptPin = 0;
unsigned long previousMillis = 0;
unsigned long liveticker = 0;
IPAddress dns(8, 8, 8, 8);  //Google dns
IPAddress ip(8, 8, 8, 8);
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(13, OUTPUT);
  pinMode(0, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptpressed, FALLING);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WIFI_Connect();
  digitalWrite(13, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());
  WiFi.config(WiFi.localIP(), WiFi.gatewayIP() , WiFi.subnetMask(), IPAddress(8, 8, 8, 8));
  delay(1000);
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());
  //  Serial.println(WiFi.localDns());
}


void loop() {
  delay(2000); //1000
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("Connected to ");
    Serial.println(ssid);
  } else {
    WIFI_Connect; // RESET secara software jika  koneksi putus
  }

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  int sensorVal = analogRead(A0); // read analog input pin 0
  //Serial.print(sensorVal, DEC); // prints the value read
  int persenVal =map(sensorVal,0,1023,0,100);
  //Serial.print(persenVal); //sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 100);
  Serial.println(sensorVal);
  Serial.print(String(persenVal)); 
  Serial.print(" %"); 
  Serial.print(" \n"); // prints a space between the numbers
  delay(1000); // wait 100ms for next reading
 
  if (persenVal>70){
      statLamp ="ON";
    }
    else if (persenVal<30)
    {
      statLamp ="OFF";
    }  
 
    
  if (tempStatLamp!=statLamp){ //jika ON atau OFF berubah status?
    liveticker = liveticker + 1;
    String url = url1;
    url += urlSensorId;
    url += url2;
    url += urlBniCab;
    url += "_";
    url += persenVal;
    url += "%/";
    url += statLamp;
    url += "|";
    url += String(liveticker); //"SC0001:BNI0001_200L/OFF|1";
  
    Serial.println("connecting to ");
    Serial.println(host);
    Serial.println("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    Serial.println();
    Serial.println("closing connection");

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    //tempValLux=sensorVal;
      tempStatLamp=statLamp;
  }
  
  
  
  //Panic Button
  button = digitalRead(0);
  Serial.println(button);
  Serial.println(interupt);
  if ((button == LOW) or (interupt == 1)) {
    liveticker = liveticker + 1;
    interupt = 0;
    String url = url1;
    url += urlSensorId;
    url += url2;
    url += urlSOS;
    url += "-val";
    url += persenVal;
    url += "%-nom";
    url += String(liveticker); 
    
    Serial.println("connecting to ");
    Serial.println(host);
    Serial.println("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    Serial.println();
    Serial.println("closing connection");

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  }
  else if (button == HIGH) {
    Serial.println("no request");
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1800000) { //60000=1menit taip 30menitkirim status
      // We now create a URI for the request\
      liveticker = liveticker + 1;
      String url = url1;
      url += urlSensorId;
      url += url2;
      url += urlInfo;
      url += "-val";
      url += persenVal;
      url += "%-nom";
      url += String(liveticker); 
      
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      Serial.print("connecting to ");
      Serial.println(host);
      Serial.println("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
      Serial.println();
      Serial.println("closing connection");

      unsigned long timeout = millis();
      while (client.available() == 0) {
        if (millis() - timeout > 5000) {
          Serial.println(">>> Client Timeout !");
          client.stop();
          return;
        }
      }
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

}

void interruptpressed() {
  interupt = 1;
}

void WIFI_Connect()
{
  digitalWrite(13, 0);
  WiFi.disconnect();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Wait for connection
  for (int i = 0; i < 25; i++)
  {
    if ( WiFi.status() != WL_CONNECTED ) {
      delay ( 250 );
      digitalWrite(13, 0);
      Serial.print ( "." );
      delay ( 250 );
      digitalWrite(13, 1);
    }
  }
  digitalWrite(13, 1);
}
