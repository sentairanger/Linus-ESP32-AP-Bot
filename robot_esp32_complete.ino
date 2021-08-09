#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESP32Servo.h>

// Servos
Servo servo1;
Servo servo2;

// Servo ints
int servoOne = 18;
int servoTwo = 19;

// Motor pins
int in_1 = 27;
int in_2 = 26;
int in_3 = 33;
int in_4 = 25;
// enable pins
int en_1 = 14;
int en_2 = 32;
// Linus eye
int eye = 2;

// Setting PWM properties
const int freq = 2000;
const int pwmChannel = 4;
const int resolution = 8;
int dutyCycle = 0;

// Set these to your desired credentials.
const char *ssid = "LinuxAP";
const char *password = "Utep123ti*";

WiFiServer server(80);


void setup() {
  // Allocation of Servo Timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);

  servo1.attach(servoOne, 500, 2400);
  servo2.attach(servoTwo, 500, 2400);
  
  pinMode(in_1, OUTPUT);
  pinMode(in_2, OUTPUT);
  pinMode(in_3, OUTPUT);
  pinMode(in_4, OUTPUT);
  pinMode(en_1, OUTPUT);
  pinMode(en_2, OUTPUT);
  pinMode(eye, OUTPUT);
  

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(en_1, pwmChannel);
  ledcAttachPin(en_2, pwmChannel);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            // HTML header
            client.println("<html>");
            client.println("<head>");
            // CSS
            client.println("<style> body { background: aqua;}");
            client.println("button { padding: 16px 32px; font-size: 16px; background: #3193D4; } </style>");
            // Main body
            client.println("</head><body><h1>Robot Control</h1>");
            client.println("<button onmousedown=location.href='/forward\' onmouseup=location.href='/stop\'>Forward</button>");
            client.println("<button onmousedown=location.href='/backward\' onmouseup=location.href='/stop\'>Backward</button>");
            client.println("<button onmousedown=location.href='/left\' onmouseup=location.href='/stop\'>Left</button>");
            client.println("<button onmousedown=location.href='/right\' onmouseup=location.href='/stop\'>Right</button>");
            client.println("<h2> Linus Eye </h2>");
            client.println("<button onmousedown=location.href='/O\' onmouseup=location.href='/L\'>Eye On</button>");
            client.println("<h2>Robot PWM</h2>");
            client.println("<button onmousedown=location.href='/T\'>30%</button>");
            client.println("<button onmousedown=location.href='/H\'>50%</button>");
            client.println("<button onmousedown=location.href='/F\'>100%</button>");
            client.println("<h2> Servo One </h2>");
            client.println("<button onmousedown=location.href='/Z\'>Min</button>");
            client.println("<button onmousedown=location.href='/N\'>Mid</button>");
            client.println("<button onmousedown=location.href='/F\'>Max</button>");
            client.println("<h2> Servo Two </h2>");
            client.println("<button onmousedown=location.href='/M\'>Min</button>");
            client.println("<button onmousedown=location.href='/D\'>Mid</button>");
            client.println("<button onmousedown=location.href='/X\'>Max</button>");  
            client.println("</body></html>");         

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

       
        if (currentLine.endsWith("GET /forward")) {
          digitalWrite(in_1, HIGH);
          digitalWrite(in_2, LOW);
          digitalWrite(in_3, HIGH);
          digitalWrite(in_4, LOW);
          
        }
        if (currentLine.endsWith("GET /backward")) {
          digitalWrite(in_1, LOW);
          digitalWrite(in_2, HIGH);
          digitalWrite(in_3, LOW);
          digitalWrite(in_4, HIGH);
                       
        }
        if (currentLine.endsWith("GET /left")) {
          digitalWrite(in_1, LOW);
          digitalWrite(in_2, HIGH);
          digitalWrite(in_3, HIGH);
          digitalWrite(in_4, LOW);
                       
        }
        if (currentLine.endsWith("GET /right")) {
          digitalWrite(in_1, HIGH);
          digitalWrite(in_2, LOW);
          digitalWrite(in_3, LOW);
          digitalWrite(in_4, HIGH);
                       
        }
        
        
        
        if (currentLine.endsWith("GET /stop")) {
          digitalWrite(in_1, LOW);
          digitalWrite(in_2, LOW);
          digitalWrite(in_3, LOW);
          digitalWrite(in_4, LOW);
         
          }
         if (currentLine.endsWith("GET /T")) {
          ledcWrite(pwmChannel, 77);
          
          }
        if (currentLine.endsWith("GET /H")) {
          ledcWrite(pwmChannel, 128);
          
          }
        if (currentLine.endsWith("GET /F")) {
          ledcWrite(pwmChannel, 255);
          
          }           
        if (currentLine.endsWith("GET /O")) {
          digitalWrite(eye, HIGH);               
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(eye, LOW);                
        }
         if (currentLine.endsWith("GET /Z")) {
          servo1.write(0);
                     
        }
        if (currentLine.endsWith("GET /N")) {
          servo1.write(90);              
        }
        
        if (currentLine.endsWith("GET /E")) {
           servo1.write(180);             
        }
        if (currentLine.endsWith("GET /M")) {
          servo2.write(0);
                     
        }
        if (currentLine.endsWith("GET /D")) {
          servo2.write(90);              
        }
        
        if (currentLine.endsWith("GET /X")) {
           servo2.write(180);             
        }
        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
