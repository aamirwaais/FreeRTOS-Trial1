#include <WiFi.h>

static const BaseType_t coreOne = 0;
static const BaseType_t coreTwo = 1;

int LED1 = 26;
int LED2 = 27;

const char* ssid     = "EN20390600";
const char* password = "rtos123";

WiFiServer server(80);

void Task1(void *pvParameters) {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  server.begin();
  // start Task 2 in Task 1
  xTaskCreatePinnedToCore(Task2, "Task Start webserver", 4000, NULL, 1, NULL, coreTwo);
  
}

void Task2(void *pvParameters) {
  while(1) {
    WiFiClient client = server.available();   
    
    if (client) {                             
      Serial.println("New Client.");          
      String currentLine = "";                 
      
      while (client.connected()) {            
        
        if (client.available()) {           
          char c = client.read();             
          Serial.write(c); 
                            
          if (c == '\n') {                    
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              
              client.print("Click <a href=\"/H\">here</a> to turn the LEDs on.<br>");
              client.print("Click <a href=\"/L\">here</a> to turn the LEDs off.<br>");
  
              client.println();
              break;
            
            } else {   
              currentLine = "";
            }
          
          } else if (c != '\r') {  
            currentLine += c;      
          }
  
          if (currentLine.endsWith("GET /H")) {
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);                
          }
          
          if (currentLine.endsWith("GET /L")) {
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);               
          }
        }
      }
      
      client.stop();
      Serial.println("Client Disconnected.");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  xTaskCreatePinnedToCore(Task1, "WiFiConnect", 4000, NULL, 1, NULL, coreOne);
  
}

void loop() {}
