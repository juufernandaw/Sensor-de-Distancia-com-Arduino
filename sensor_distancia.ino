// declara os pinos e as variáveis
const int trig = 12;  // D6
const int echo = 13;  // D7
long duration;
int distance;
int LED = 14; // D5

void setup() {
  pinMode(trig, OUTPUT); // Trig = saída
  pinMode(echo, INPUT); // Echo = entrada
  Serial.begin(9600); // Inicia a taxa de velocidade
  pinMode(LED,OUTPUT); // Led = saída
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
  
}
