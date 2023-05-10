// ############# LIBRARIES ############### //

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// ############# VARIABLES ############### //

const char* SSID = "CASA CINZA"; // rede wifi
const char* PASSWORD = "cinzacasa"; // senha da rede wifi

String BASE_URL = "http://192.168.100.11:3000/distance";// como passar o ip localhost 

// declara os pinos e as variáveis
const int trig = 12;  // D6
const int echo = 13;  // D7
long duration;
int distance;
int LED = 14; // D5


// ############# PROTOTYPES ############### //

void initSerial();
void initWiFi();
void httpRequest(String path);

// ############### OBJECTS ################# //

WiFiClient client;
HTTPClient http;

// ############## SETUP ################# //

void setup() {
  initSerial();
  initWiFi();
  pinMode(trig, OUTPUT); // Trig = saída
  pinMode(echo, INPUT); // Echo = entrada
  Serial.begin(9600); // Inicia a taxa de velocidade
  pinMode(LED, OUTPUT); // Led = saída
  Serial.begin(115200);
}

// ############### LOOP ################# //

void loop() {
  Serial.println("[GET] /sensors - sending request...");
  Serial.println("");
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
  // httpREQUEST
  httpRequest("distance"); //rota

  Serial.println("");
  delay(1000);

}

// ############# HTTP REQUEST ################ //

void httpRequest(String path)
{
  String payload = makeRequest(path);

  if (!payload) {
    return;
  }

  Serial.println("##[RESULT]## ==> " + payload);

}

String makeRequest(String path)
{
  http.begin(client, BASE_URL);
  int httpCode = http.POST("distance:"+String(distance));// como interporlar para mandar em json, nome:senha como mandar um json no post

  if (httpCode < 0) {
    Serial.println("request error - " + httpCode);
    return "";

  }

  if (httpCode != HTTP_CODE_OK) {
    return "";
  }

  String response =  http.getString();
  http.end();

  return response;
}

// ###################################### //

// implementacao dos prototypes

void initSerial() {
  Serial.begin(115200);
}

void initWiFi() {
  delay(10);
  Serial.println("Conectando-se em: " + String(SSID));

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado na Rede " + String(SSID) + " | IP => ");
  Serial.println(WiFi.localIP());
}