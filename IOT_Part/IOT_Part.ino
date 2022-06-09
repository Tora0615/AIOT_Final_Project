#include <ESP8266WiFi.h>
 
const char *ssid = "好運貓貓 x70";
const char *password = "01020102";
const char *host = "123.204.234.29";

void setup() {
  // LED Setup
  pinMode(LED_BUILTIN, OUTPUT);
  // Serial Setup
  Serial.begin(115200);
  delay(10);
  // Relay Setup
  pinMode(D5, OUTPUT);
  
  // Wifi Setup and show result
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); // connect to wifi
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("--------------------");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(5000);

  /* Connect to host */
  // print info 
  Serial.print("connecting to ");
  Serial.println(host);

  // connect and show info 
  WiFiClient client;
  const int httpPort = 5000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }else{
    Serial.println("connection successed");
  }

  /* Form host to get url's data*/
  // setup variable and print info
  String url = "/aiot";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println();

  /* send and get data (print function is used to send data to the connected server) */
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
  delay(1000);  // need to wait data back (this seems to be multi-thread action)
  
  /* process the data */
  Serial.println("Recieved data : ");
  while(client.available()){                      // if havn't read to the end
    
    String line = client.readStringUntil('\r');   // read line
    line.trim();                                  // eat useless part of string such as space
    Serial.println(line);

    // if data match target string (true/false)
    if (line.equals("true")){           
      // open the pump (Don't need delay)   (circuit conncet to nornal close (preset running the pump))
      digitalWrite(D5,LOW);                     // LOW let relay switch to nornal close, then the pump start

      // show the light
      digitalWrite(LED_BUILTIN, LOW);           // long and slow bright 
      delay(500);  
      digitalWrite(LED_BUILTIN, HIGH);          
      delay(500);                       
      // digitalWrite(LED_BUILTIN, LOW); 
      // delay(1000);  
      // digitalWrite(LED_BUILTIN, HIGH);          
      // delay(1000);                       
    }else if (line.equals("false")){
      // close the pump (Don't need delay)   (circuit conncet to nornal close (preset running the pump))
      digitalWrite(D5,HIGH);                    // HIGH let relay switch to nornal open, then the pump stop

      // show the light
      digitalWrite(LED_BUILTIN, LOW);           // short and quick bright 
      delay(125); 
      digitalWrite(LED_BUILTIN, HIGH);          
      delay(125);                       
      digitalWrite(LED_BUILTIN, LOW); 
      delay(125); 
      digitalWrite(LED_BUILTIN, HIGH);          
      delay(125);                       
      digitalWrite(LED_BUILTIN, LOW); 
      delay(125); 
      digitalWrite(LED_BUILTIN, HIGH);          
      delay(125);                       
      digitalWrite(LED_BUILTIN, LOW); 
      delay(125); 
      digitalWrite(LED_BUILTIN, HIGH);           
      delay(125);                    
    }
 }  
 Serial.println("--------------------");
}
