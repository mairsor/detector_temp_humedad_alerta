#include <DHT.h> 
#define LED 3 //Pin al que está conectada el OUTPUT del Buzzer y también el LED
#define DHTPIN 6 // Pin al que está conectado el INPUT DIGITAL del sensor DHT11
#define DHTTYPE DHT22 //Tipo de sensor. También la librería <DTH.h> sirve para el DHT22

DHT dht(DHTPIN, DHTTYPE); //Variables importantes para el sensor DHT, configuración inicial del DHT

float humedad = 0;
float temperatura = 0;
float indicecalor = 0;
float tempaviso = 30.5;
int frecuencia = 520;

//---------------Estados del sistema-----------------------
enum Estado { 
  NORMAL, 
  ALERTA_TEMP
  };

Estado estadoActual = NORMAL;

//-------------Variables para temporización----------------
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 1000; // 1 segundo


void setup() {
  
  Serial.begin(9600); //Para activar monitor serial
  dht.begin(); //Inicializar el sensor DHT
  pinMode(LED, OUTPUT); //Indicar que el pin del LED será de salida.

}

void loop() {
  unsigned long tiempoActual = millis();

  //-----------------Ejecutar tarea cada 1 segundo sin bloquear-------------------------
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    // Leer sensores
    humedad = dht.readHumidity(); //Leer humedad del sensor dht
    temperatura = dht.readTemperature(); //Leer temperatura del sensor dht
    indicecalor = dht.computeHeatIndex(temperatura, humedad, false); //Calcular índice de calor

    // Evaluar estado
    switch (estadoActual) {
      case NORMAL:
        if (temperatura >= tempaviso) {
          estadoActual = ALERTA_TEMP;
        }
        apagarAlerta();
        break;

      case ALERTA_TEMP:
        prenderAlerta();
        if (temperatura < tempaviso) {
          estadoActual = NORMAL;
        }
        break;
    }

    // Mostrar datos
    imprimir(humedad, temperatura, indicecalor);
  }

}





//--------------------Encender LED y buzzer----------------------
void prenderAlerta() {
  tone(LED, frecuencia);
  digitalWrite(LED, HIGH);
}

//--------------------Apagar LED y buzzer------------------------
void apagarAlerta() {
  noTone(LED);
  digitalWrite(LED, LOW);
}


//------------------Función de impresión ----------------------
void imprimir(float humedad, float temperatura, float indicecal){ //Función para imprimir los datos

  if(isnan(humedad) || isnan(temperatura)){
    Serial.println("Error obtenido en los datos");
  }
  // Para comprobar si los datos están correctos

  else{
    Serial.print("Humedad: ");
    Serial.println(humedad);

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");

    Serial.print("Índice de calor: ");
    Serial.print(indicecal);
    Serial.println("°C");
    Serial.println("---------------------------");

  }
}