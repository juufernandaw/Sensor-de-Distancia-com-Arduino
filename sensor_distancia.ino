#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


WiFiClient client;

const char* ssid = "CASA CINZA";
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
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.print("WiFi status: ");
  Serial.println(WiFi.status());

  Serial.print("IP address: ");
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
    Serial.println("Connected to server");

    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST("distance=" + String(distance));
    http.end();

    if (httpCode == 200) {
      Serial.println("Distance sent to server");
    } else {
      Serial.println("Failed to send distance to server");
    }

    client.stop();
  } else {
    Serial.println("Could not connect to server");
  }

  delay(5000);
}
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>

// const char* SSID = "CASA CINZA";
// const char* PASSWORD = "cinzacasa";
// const char* BASE_URL = "http://192.168.100.11:3000/distance";
// const int trig = 12;
// const int echo = 13;
// const int LED = 14;
// long duration;
// int distance;

// WiFiClient client;
// HTTPClient http;

// void setup() {
//   pinMode(trig, OUTPUT);
//   pinMode(echo, INPUT);
//   pinMode(LED, OUTPUT);
//   Serial.begin(115200);
//   WiFi.begin(SSID, PASSWORD);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(100);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.print("Connected to " + String(SSID) + " | IP => ");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
//   // Limpa o trig
//   digitalWrite(trig, LOW);
//   delayMicroseconds(2);

//     // Ao iniciar já liga o trig por 10 microsegundos
//   digitalWrite(trig, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trig, LOW);

//     // Faz a leitura da echo
//   duration = pulseIn(echo, HIGH);

//     // Calcula a distancia
//   distance= duration*0.034/2;
    
//   Serial.print("Distance: ");
//   Serial.println(distance);
//   delay(800);

//   if(distance<100) { // Se o valor for menor que 150 o LED é acionado
//     digitalWrite(LED, HIGH); // LED liga

//   } else {
//     digitalWrite(LED, LOW); // Led desliga
//   }
//   delay(800);
//   digitalWrite(LED, distance < 100 ? HIGH : LOW);
//   httpRequest();
//   delay(1000);
// }

// void httpRequest() {
//   String payload = "{\"distance\": " + String(distance) + "}";
//   http.begin(client, BASE_URL);
//   int httpCode = http.POST(payload);
//   if (httpCode < 0) {
//     Serial.println("request error - " + httpCode);
//     return;
//   }
//   if (httpCode != HTTP_CODE_OK) {
//     return;
//   }
//   String response = http.getString();
//   http.end();
//   Serial.println("##[RESULT]## ==> " + response);
// }
// // ############# LIBRARIES ############### //

// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>

// // ############# VARIABLES ############### //

// const char* SSID = "CASA CINZA"; // rede wifi
// const char* PASSWORD = "cinzacasa"; // senha da rede wifi

// String BASE_URL = "http://192.168.100.11:3000/distance";// como passar o ip localhost 

// // declara os pinos e as variáveis
// const int trig = 12;  // D6
// const int echo = 13;  // D7
// long duration;
// int distance;
// int LED = 14; // D5


// // ############# PROTOTYPES ############### //

// void initSerial();
// void initWiFi();
// void httpRequest(String path);

// // ############### OBJECTS ################# //

// WiFiClient client;
// HTTPClient http;

// // ############## SETUP ################# //

// void setup() {
//   initSerial();
//   initWiFi();
//   pinMode(trig, OUTPUT); // Trig = saída
//   pinMode(echo, INPUT); // Echo = entrada
//   Serial.begin(9600); // Inicia a taxa de velocidade
//   pinMode(LED, OUTPUT); // Led = saída
//   Serial.begin(115200);
// }

// // ############### LOOP ################# //

// void loop() {
//   Serial.println("[GET] /sensors - sending request...");
//   Serial.println("");
//   // Limpa o trig
//   digitalWrite(trig, LOW);
//   delayMicroseconds(2);

//     // Ao iniciar já liga o trig por 10 microsegundos
//   digitalWrite(trig, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trig, LOW);

//     // Faz a leitura da echo
//   duration = pulseIn(echo, HIGH);

//     // Calcula a distancia
//   distance= duration*0.034/2;
    
//   Serial.print("Distance: ");
//   Serial.println(distance);
//   delay(800);

//   if(distance<100) { // Se o valor for menor que 150 o LED é acionado
//     digitalWrite(LED, HIGH); // LED liga

//   } else {
//     digitalWrite(LED, LOW); // Led desliga
//   }
//   // httpREQUEST
//   httpRequest("distance"); //rota

//   Serial.println("");
//   delay(1000);

// }

// // ############# HTTP REQUEST ################ //

// void httpRequest(String path)
// {
//   String payload = makeRequest(path);

//   if (!payload) {
//     return;
//   }

//   Serial.println("##[RESULT]## ==> " + payload);

// }

// String makeRequest(String path)
// {
//   http.begin(client, BASE_URL);
//   int httpCode = http.POST("distance:"+String(distance));// como interporlar para mandar em json, nome:senha como mandar um json no post

//   if (httpCode < 0) {
//     Serial.println("request error - " + httpCode);
//     return "";

//   }

//   if (httpCode != HTTP_CODE_OK) {
//     return "";
//   }

//   String response =  http.getString();
//   http.end();

//   return response;
// }

// // ###################################### //

// // implementacao dos prototypes

// void initSerial() {
//   Serial.begin(115200);
// }

// void initWiFi() {
//   delay(10);
//   Serial.println("Conectando-se em: " + String(SSID));

//   WiFi.begin(SSID, PASSWORD);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(100);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.print("Conectado na Rede " + String(SSID) + " | IP => ");
//   Serial.println(WiFi.localIP());
// }