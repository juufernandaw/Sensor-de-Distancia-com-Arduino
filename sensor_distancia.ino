// #include <ESP8266WiFi.h>
// #include <HTTPClient.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


#ifndef STASSID
#define STASSID "Juliaa"
#define STAPSK "julia2828"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.74.171";
const uint16_t port = 3000;

const int trig = 12;  // D6
const int echo = 13;  // D7
long duration;
int distance;
int LED = 14; // D5


void setup() {
  pinMode(trig, OUTPUT); // Trig = saída
  pinMode(echo, INPUT); // Echo = entrada
  Serial.begin(9600); // Inicia a taxa de velocidade
  pinMode(LED, OUTPUT); // Led = saída
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
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
  
  static bool wait = false;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) { client.println("hello from ESP8266"); }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  if (wait) {
    delay(3000);  // execute once every 5 minutes, don't flood remote service
  }
  wait = true;

  HTTPClient http;

  // URL do servidor local
  String serverURL = "http://localhost:3000";

  // Inicializa a conexão com o servidor
  http.begin(client, serverURL);

  // Envio da requisição GET para o servidor
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("Código de resposta do servidor: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println("Resposta do servidor:");
    Serial.println(payload);
  } else {
    Serial.print("Falha na conexão ao servidor. Código de erro: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
