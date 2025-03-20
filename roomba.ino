#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include "webpage.h"
#include "style.h"

#define DHTPIN 20     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#define IN1 1    
#define IN2 2    
#define IN3 3    
#define IN4 4 

#define BUTTON_PIN 21


bool buttonState = false;  
bool lastButtonState = HIGH; 

const char* ssid = "Jupiter530";       
const char* password = "junjul01"; 

WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleCSS() {
    server.send(200, "text/css", cssPage);
}

void handleMotor() {
    if (server.hasArg("cmd") ) {
        String cmd = server.arg("cmd");
        if (cmd == "forward") {
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
        } else if (cmd == "backward") {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
        } else if (cmd == "stop") {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
        }
    }
   
    server.send(200, "text/plain", "OK");
}

void handleClean() {
    if (server.hasArg("amb")) {
        String amb = server.arg("amb");
        if (amb == "sedot") {
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
        } else if (amb == "stp") {
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        }
    }
   
    server.send(200, "text/plain", "OK");
}

void handleSensor() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        server.send(500, "application/json", "{\"error\":\"Failed to read DHT sensor\"}");
        return;
    }

    String json = "{\"temperature\": " + String(temperature, 1) + ", \"humidity\": " + String(humidity, 1) + "}";
    server.send(200, "application/json", json);
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(IN3, OUTPUT);

    pinMode(BUTTON_PIN, INPUT);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

    server.on("/", handleRoot);
    server.on("/style.css", handleCSS);
    server.on("/motor", handleMotor);
    server.on("/clean", handleClean);
    server.on("/sensor", handleSensor);
    
    server.begin();
}

void loop() {
    server.handleClient();
   bool currentButtonState = digitalRead(BUTTON_PIN);

    // offline
    if (currentButtonState == LOW && lastButtonState == HIGH) {
        buttonState = !buttonState; // Toggle state

        if (!buttonState) {
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
           
        } else {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        }

        delay(300); 
    }

    lastButtonState = currentButtonState; 
  
}
