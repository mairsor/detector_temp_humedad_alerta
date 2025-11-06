#include <DHT.h> 
#define LED 3 //Pin al que está conectada el OUTPUT del Buzzer y también el LED
#define DHTPIN 6 // Pin al que está conectado el INPUT DIGITAL del sensor DHT11
#define DHTTYPE DHT22 //Tipo de sensor. También la librería <DTH.h> sirve para el DHT22

DHT dht(DHTPIN, DHTTYPE); //Variables importantes para el sensor DHT, configuración inicial del DHT

float humedad = 0;
float temperatura = 0;
float indicecalor = 0;
int frecuencia = 520;
float tempaviso = 30.5;

void setup() {
  
  Serial.begin(9600); //Para activar monitor serial

  dht.begin(); //Inicializar el sensor DHT

  pinMode(LED, OUTPUT);


}

void loop() {

  alertaLB(temperatura); //Función a la que se le da la variable float de temperatura

  //Si temperatura > 30, se prende el LED y el buzzer suena.
  //Caso contrario, se apagan ambos.

  //-------------------------------------
  humedad = dht.readHumidity(); //Leer humedad del sensor dht
  temperatura = dht.readTemperature(); //Leer temperatura del sensor dht

  indicecalor = dht.computeHeatIndex(temperatura, humedad, false);
  
  imprimir(humedad, temperatura, indicecalor);

  delay(1000);

}


void alertaLB(float temperatura){ //Función para prender el LED y el buzzer

  if(temperatura < tempaviso){
    //digitalWrite(LED, LOW); //Si el movimiento es 0, entonces se apaga el LED y el buzzer
    noTone(LED);
  }

  else{
    //digitalWrite(LED, HIGH); //Si el movimiento es 1, se prende el lud y el buzzer.
    tone(LED,frecuencia);    // inicia el zumbido
  }

}



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

  }
}