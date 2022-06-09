#include <ESP8266WiFi.h>
 
const char *ssid = "好運貓貓 x70";
const char *password = "01020102";
const char *host = "123.204.234.29";

void setup() {
  // LED Setup
  pinMode(LED_BUILTIN, OUTPUT);
  // Relay Setup
  pinMode(D5, OUTPUT);
  
  // Wifi Setup 
  WiFi.begin(ssid, password); // connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(5000);

  /* Connect to host */

  // connect 
  WiFiClient client;
  const int httpPort = 5000;
  if (!client.connect(host, httpPort)) {
    return;
  }

  /* Form host to get url's data*/
  // setup variable 
  String url = "/aiot";

  /* send and get data (print function is used to send data to the connected server) */
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
  delay(1000);  // need to wait data back (this seems to be multi-thread action)
  
  /* process the data, control relay and show the light*/
  while(client.available()){                      // if havn't read to the end
    // show the light
    digitalWrite(LED_BUILTIN, LOW); 
    delay(125); 
    digitalWrite(LED_BUILTIN, HIGH);          
    delay(125); 

    // read data line by line
    String line = client.readStringUntil('\r');   // read line
    line.trim();                                  // eat useless part of string such as space

    // if data match target string (true/false)
    if (line.equals("true")){           
      // open the pump (Don't need delay)   (circuit conncet to nornal close (preset running the pump))
      digitalWrite(D5,LOW);                     // LOW let relay switch to nornal close, then the pump start                   
    }else if (line.equals("false")){
      // close the pump (Don't need delay)   (circuit conncet to nornal close (preset running the pump))
      digitalWrite(D5,HIGH);                    // HIGH let relay switch to nornal open, then the pump stop                  
    }
 }  
}
