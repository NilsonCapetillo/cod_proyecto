
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "nilson-b3d50.firebaseio.com"
#define FIREBASE_AUTH "FjqCiCIMZfLUM2Ke6TDXXutpmzKsQPO3DxM98IFZ"
#define WIFI_SSID "Izzinet19979499" //Nombre de la conexion
#define WIFI_PASSWORD "1972DE1970" //Cambiar por el Password de tu WIFI alexis13

const int sPIR = 16; // Pin GPIO2 para el sensor de movimiento
const int sPIR2 = 3; // Pin GPIO2 para el sensor de movimiento
int mov = 0;
int mov2 = 0;
int intruso = 0;
int nointruso = 0;
int sensorValue = 0;
int GasSensorPin = 0;   //Gas Sensor Connection
int gas = 0;


//AQUI SE CONECTA AL WIFI
void setup() {
  Serial.begin(9600);
  // conectamos el wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(". ERROR");
  }
  Serial.println("");
  Serial.println("WiFi Conectado!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //inicializamos la comunicacion con firebase
//TERMINA LA PARTE DE CONFIGURACION DE WIFI

  pinMode(sPIR,INPUT); //declaramos el pin de el Sensor como una entrada
  pinMode(sPIR2,INPUT); //declaramos el pin de el Sensor como una ENTRADA
}

void loop() {
   sensorValue = analogRead(GasSensorPin);       // read analog input pin 0------ 
 Serial.println(sensorValue, DEC);  // prints the value read ---- imprime el valor leido
 if(analogRead(sensorValue)>800){ //SI EL VALOR LEIDO ES MAYOR A 800 SE IMPRIME 'FUGA DE GAS'
    Serial.println("FUGA DE GAS");
    Firebase.setInt("GAS", 1);//EL ATRIBUTO 'GAS' PASA A VALER 1
    gas++;
  }
  else{
    Firebase.setInt("GAS", 0);//SI NO, 'GAS' VALE 0
    }
 delay(100); 
  
  mov= digitalRead(sPIR); //LEE EL VALOR DEL PIN DIGITAL 'sPIR'
  //Firebase.setInt("Movimiento", mov);
  //delay(50);


  
  if(mov == HIGH){
    Serial.print(mov); 
    Serial.print(" : "); Serial.println("Movimiento detectado.");
    //Firebase.setInt("Movimiento", 1);
    intruso++;
    delay(1000);
  }else{
    //Firebase.setInt("Movimiento", 0);
    //Serial.print(mov); Serial.print(" : "); Serial.println("No se  detecta movimiento");
    nointruso++;
    delay(1000);
  }

  if(intruso == 2){
    Firebase.setInt("Movimiento", 1);
    Firebase.setInt("intruso", 1);
    
    nointruso = 0;
  }
  if(nointruso == 6){
    Firebase.setInt("Movimiento", 0);
    Firebase.setInt("intruso", 0);
    nointruso = 0;
  }

   if(intruso == 6){
    Firebase.setInt("Movimiento1", 1);
    intruso = 0;
    nointruso = 0;
  }else{
    Firebase.setInt("Movimiento1", 0);
  }
    if(gas == 4){
    Firebase.setInt("GAS1", 1);
    gas = 0;
    nointruso = 0;
  }else{
    Firebase.setInt("GAS1", 0);
  }
}
