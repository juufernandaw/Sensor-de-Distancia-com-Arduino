#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


WiFiClient client;

const char* ssid = "Juliaa";
const char* password = "cinzacasa";
const char* serverName = "http://192.168.100.11:3000/distance";
const int trig = 12;
const int echo = 13;
const int LED = 14;
long duration;
int distance;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.println("Conectando com a rede WIFI...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando com a rede WIFI...");
  }
  Serial.println("Conectado com a rede WIFI...");

  Serial.print("Status do WIFI: ");
  Serial.println(WiFi.status());

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
    // Limpa o trig
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

    // Ao iniciar já liga o trig por 10 microsegundos
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

    // Faz a leitura da echo
  duration = pulseIn(echo, HIGH);

    // Calcula a distancia
  distance= duration*0.034/2;
    
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(800);

  if(distance<100) { // Se o valor for menor que 150 o LED é acionado
    digitalWrite(LED, HIGH); // LED liga

  } else {
    digitalWrite(LED, LOW); // Led desliga
  }
  delay(800);

  if (client.connect("192.168.100.11", 3000)) {
    Serial.println("Conectado ao servidor");

    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST("distance=" + String(distance));
    http.end();

    if (httpCode == 200) {
      Serial.println("Distancia enviada ao servidor!");
    } else {
      Serial.println("ERRO! Não foi possível enviar a distancia para o servidor");
    }

    client.stop();
  } else {
    Serial.println("Não foi possivel conectar ao servidor remoto.");
  }

  delay(1000);
}
