#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

ESP8266WebServer server(80);

const char* ssid = "HUAWEI-2.4G-Ss2X";
const char* password = "Nuep2aWb";

IPAddress ip(192, 168, 100, 102);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_index);

  server.begin();
  Serial.println("Server listening");
  Serial.println("Adafruit MLX90614 test");

  mlx.begin();
}

void loop() {
  server.handleClient();
  getdata();
}

void getdata() {
  float ambientTempC = mlx.readAmbientTempC();
  float objectTempC = mlx.readObjectTempC();

  Serial.print("Ambient = ");
  Serial.print(ambientTempC);
  Serial.print("*C\tObject = ");
  Serial.print(objectTempC);
  Serial.println("*C");

  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = ");
  Serial.print(mlx.readObjectTempF());
  Serial.println("*F");

  // Assuming you want to send temperature data
  server.send(200, "text/plain", String(ambientTempC) + "|" + String(objectTempC));

  Serial.println();
  delay(5000);
}

void handle_index() {
  // You can add any additional handling if needed
}
