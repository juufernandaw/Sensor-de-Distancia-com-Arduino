// declara os pinos e as variáveis
const int trigPin = 12;  //D6
const int echoPin = 13;  //D7
long duration;
int distance;
int LED_PIN = 14; //D5

void setup() {
  pinMode(trigPin, OUTPUT); // Trigpin = saída
  pinMode(echoPin, INPUT); // Echopin = entrada
  Serial.begin(9600); // Inicia a taxa de velocidade
  pinMode(LED_PIN,OUTPUT); // Led = saída
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Ao iniciar já liga o trigpin por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Faz a leitura da echopin
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distancia
  distance= duration*0.034/2;
  
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(800);

  if(distance<100) { // Se o valor for menor que 150 o LED é acionado
    digitalWrite(LED_PIN, HIGH); // LED liga

  } else {
    digitalWrite(LED_PIN, LOW); // Led desliga
  }
  
}
