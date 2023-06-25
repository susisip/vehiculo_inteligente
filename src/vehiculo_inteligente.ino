// Inicialización de pines
int trigPin=5; //amarillo
int echoPin=3; // naranja

int Motor1Pin1=8;//azul
int Motor1Pin2=7;//blanco
int Motor1VelocidadPin=9;//rojo

int Motor2Pin1=13;//verde
int Motor2Pin2=12;//naranja
int Motor2VelocidadPin=11;//morado

int led=4;

// Parámetros y variables globales
int MAX_DISTANCIA=30;
int VELOCIDAD=130;
int distanciaCm;

// Configuración de pines y velocidad de comunicación (9600 baudios)
void setup() {

  // Configuración para sensor ultrasonidos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Configuración para motor 1
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(Motor1VelocidadPin, OUTPUT);

  // Configuración para motor 2
  pinMode(Motor2Pin1, OUTPUT);
  pinMode(Motor2Pin2, OUTPUT);
  pinMode(Motor2VelocidadPin, OUTPUT);

  // Configuración para LED indicador
  pinMode(led,OUTPUT);
  
  Serial.begin(9600);
}

// Algoritmo tipo bicho
void loop() {
  long distancia = LeerDistanciaUltrasonidos(trigPin, echoPin);
  Serial.println(distancia);
  if (distancia > MAX_DISTANCIA) {
    // No se ha detectado ningún obstáculo, mover hacia adelante
    adelante();
    digitalWrite(led,LOW);
    
  } else {
    // Obstaculo detectado, hacia atrás y vuelta
    atras();
    digitalWrite(led,HIGH);
    
    delay(1000); // espera 1 segundo
    giroDerecha();
    delay(500); // espera 0.5 segundos
  }
}

long LeerDistanciaUltrasonidos(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duracion = pulseIn(echoPin, HIGH);
  // Velocidad de sonido, 34300 cm/sec. Divide por 2 (va y vuelve).
  //return duracion / 29 / 2;
  distanciaCm = duracion * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanciaCm;
  //sabemos que la velocidad del sonido es 343 m/s en condiciones de temperatura 20 ºC,
  //50% de humedad, presión atmosférica a nivel del mar. Transformando unidades resulta
} //343 m/s * 100 cm/m  * 1s/1000000microsegundos  =1/29,2 cm/microsegundos



// Función para avanzar
void adelante() {
  // Rueda 1 adelante
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor1Pin2, LOW);
  analogWrite(Motor1VelocidadPin, VELOCIDAD);
  
  // Rueda 2 adelante
  digitalWrite(Motor2Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  analogWrite(Motor2VelocidadPin, VELOCIDAD);
}

// Función para retroceder
void atras() {
  // Rueda 1 atrás
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  analogWrite(Motor1VelocidadPin, VELOCIDAD);
  
  // Rueda 2 atrás
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
  analogWrite(Motor2VelocidadPin, VELOCIDAD);
}

// Función para girar hacia la derecha
void giroDerecha() {
  // Rueda 1 adelante
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor1Pin2, LOW);
  analogWrite(Motor1VelocidadPin, VELOCIDAD);
  
  // Rueda 2 parada
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, LOW);
  analogWrite(Motor2VelocidadPin, 0);
}
