#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "iQOO Z9 Lite 5G";
const char* password = "7795588287ManjuM";

WiFiServer server(80);

// LED pins
#define  RED_LED 25
#define  GREEN_LED 26
#define  BLUE_LED 27

bool blinkAll = false;

void setup() {
  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // ---- Individual control ----
    if (request.indexOf("/green_on") != -1) digitalWrite(GREEN_LED, HIGH);
    if (request.indexOf("/green_off") != -1) digitalWrite(GREEN_LED, LOW);

    if (request.indexOf("/blue_on") != -1) digitalWrite(BLUE_LED, HIGH);
    if (request.indexOf("/blue_off") != -1) digitalWrite(BLUE_LED, LOW);

    if (request.indexOf("/red_on") != -1) digitalWrite(RED_LED, HIGH);
    if (request.indexOf("/red_off") != -1) digitalWrite(RED_LED, LOW);

    // ---- All control ----
    if (request.indexOf("/all_on") != -1) {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      blinkAll = false;
    }

    if (request.indexOf("/all_off") != -1) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
      blinkAll = false;
    }

    // ---- Blink control ----
    if (request.indexOf("/blink_all") != -1) {
      blinkAll = true;
    }

    if (request.indexOf("/stop_blink") != -1) {
      blinkAll = false;
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("OK");

    client.stop();
  }

  // ---- Blink logic ----
  if (blinkAll) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(200);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(200);
  }
}