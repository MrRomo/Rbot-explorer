#include "WiFi.h"
#include "WiFiMulti.h"
#include "ESP32_SPIFFS_EasyWebSocket.h" //beta ver 1.60
#include "sensor.h"


const char* ssid = "CableNet_NORALBA_GUTIERREZ"; //Nombre de la rec
const char* password = "RICARDO96"; //Clave de la red
 
const char* HTM_head_file1 = "/EWS/LIPhead1.txt"; //Archivo de encabezado HTML 1
const char* HTM_head_file2 = "/EWS/LIPhead2.txt"; //Archivo de encabezado HTML 2

const char* HTML_body_file = "/EWS/dummy.txt"; //Archivo de elemento de body del HTML 
const char* dummy_file = "/EWS/dummy.txt"; //Archivo ficticio para vincular archivos HTML
 
ESP32_SPIFFS_EasyWebSocket ews;
WiFiMulti wifiMulti;
 
IPAddress LIP; // Para obtener la dirección IP local automáticamente
 
String ret_str; //para almacenar la secuencia enviada desde el navegador
String txt = "text send?"; //String para reenviar la cadena de caracteres recibida desde el navegador desde ESP32
String txtR = "Detenido";
String obsColor = "#ffffff";
 
int PingSendTime = 10000; // intervalo para hacer ping desde el ESP 32 al navegador (ms)
 
long ESP32_send_LastTime;
int ESP32_send_Rate = 500;
byte cnt = 0;

#define TRIGGER 2  //define la salida por donde se manda el TRIGGER como 9
#define ECHO 27 //define la salida por donde se recibe el ECHO como 10
#define azul 33 //Led azul, objeto a distancia mayor que 25cm
#define amarillo 18 //Led azul, indica objeto a distancia  menor que 25cm y mayor que 6cm
#define rojo 23 // Led rojo indica objeto a distancia menor que 6cm

 
 // Definiciones de pines usados para los motores//
#define PIN_MOTOR_R_FWD 22 
#define PIN_MOTOR_R_BWD 21
#define PIN_MOTOR_L_FWD 17
#define PIN_MOTOR_L_BWD 16 

  //variables del sensor HC-SR04
int distancia;  //crea la variable "distancia"
float tiempo;  //crea la variable tiempo (como float)
//Variables para evitar copar la cola
String dist, StateR;
bool firstMeasure=true;
bool check_ms=true;
  
 
//*************Configuración*************************
void setup(){
  Serial.begin(115200);
  delay(10);
  //watcher ();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
 
  wifiMulti.addAP(ssid, password);
 
  Serial.println(F("Connecting Wifi..."));
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println(F("WiFi connected"));
      Serial.println(F("IP address: "));
      LIP = WiFi.localIP(); //Obtener la dirección IP local de ESP32 automáticamente
      Serial.println(WiFi.localIP());
  }
  delay(1000);
 
  ews.EWS_server_begin();
 
  pinMode(PIN_MOTOR_R_FWD, OUTPUT);
  pinMode(PIN_MOTOR_R_BWD, OUTPUT);
  pinMode(PIN_MOTOR_L_FWD, OUTPUT);
  pinMode(PIN_MOTOR_L_BWD, OUTPUT);
  pinMode(TRIGGER, OUTPUT); //Declaramos el pin 9 como salida (TRIGGER ultrasonido)
  pinMode(ECHO, INPUT); //Declaramos el pin 8 como entrada (recepción del TRIGGER)

  digitalWrite(PIN_MOTOR_R_FWD, LOW);
  digitalWrite(PIN_MOTOR_R_BWD, LOW);
  digitalWrite(PIN_MOTOR_L_FWD, LOW);
  digitalWrite(PIN_MOTOR_L_BWD, LOW);

  //Configuramos los leds
  pinMode(azul, OUTPUT); 
  pinMode(amarillo, OUTPUT); 
  pinMode(rojo, OUTPUT); 
  
  Serial.println(); Serial.println("Initializing SPIFFS ...");
 
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS failed, or not present");
    return;
  }
 
  Serial.println("SPIFFS initialized. OK!");
  conectSecuence ();
 
  TaskHandle_t th; // Definición del manejador multitarea ESP32
  xTaskCreatePinnedToCore(Task1, "Task1", 4096, NULL, 5, &th, 0); //multitarea núcleo 0 ejecución
 
  ESP32_send_LastTime = millis();
}
//*************Loop*************************
void loop() {
  
  websocket_handshake();
  if(ret_str != "_close"){
    if(millis()-ESP32_send_LastTime > ESP32_send_Rate){
      ESP32_send_LastTime = millis();
      check_ms=true;
    }
    if(check_ms){
       websocket_send(txt,txtR);
       check_ms = false;
    }
    watcher ();
    txt = "Obstaculo a: "+ String(distancia) + " cm";
   
   
    ret_str = ews.EWS_ESP32CharReceive(PingSendTime);
    if(ret_str != "\0"){
      Serial.println(ret_str);
      if(ret_str != "Ping"){
        if(ret_str[0] != 't'){
          int ws_data = (ret_str[0]-0x30)*100 + (ret_str[1]-0x30)*10 + (ret_str[2]-0x30);
          Serial.println(ret_str[4]);
          switch(ret_str[4]){
             case 'W':
              Serial.println("Forward");
              motion(HIGH,LOW,HIGH,LOW);
              txtR = "Forward";
              break;
            case 'S':
              Serial.println("Backward");
              motion(LOW,HIGH,LOW,HIGH);
              txtR = "Backward";
              break;
            case 'A':
              Serial.println("Right");
              motion(HIGH,LOW,LOW,HIGH);
              txtR = "Right";
              break;
            case 'D':
              Serial.println("Left");
              motion(LOW,HIGH,HIGH,LOW);
              txtR = "Left";
              break;
            case 'Q':
              Serial.println("Stop");
              motion(LOW,LOW,LOW,LOW);
              txtR = "Stop";
              break;
          }
        }else if(ret_str[0] == 't'){
          txt = ret_str.substring(ret_str.indexOf('|')+1, ret_str.length()-1);
          Serial.println(txt);
        }
      }
    }
  }else if(ret_str == "_close"){
    ESP32_send_LastTime = millis();
    ret_str = "";
  }
}

//************* Funcion de sensor HC-SR04 ****************************************
void watcher () {
  digitalWrite(TRIGGER,LOW); //Por cuestión de estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH); //envío del TRIGGER ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(ECHO, HIGH);  //funcion para medir el tiempo y guardarla en la variable "tiempo"
  distancia = 0.01715*tiempo; //fórmula para calcular la distancia
   
  /*Monitorización en centímetros por el monitor serial*/
  /*Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");*/
  digitalWrite(azul,LOW);
  digitalWrite(amarillo,LOW);
  digitalWrite(rojo,LOW);
  if(distancia>25) {
      digitalWrite(azul,HIGH);
      obsColor ="#00cc11";
  }else if((distancia<=25)&&(distancia>6)) {
      digitalWrite(amarillo,HIGH);
      obsColor ="#cccc00";
  }else if(distancia<=6) {
      digitalWrite(rojo,HIGH);
      obsColor ="#cc0000";
      /*
      motion(LOW,LOW,LOW,LOW);
      delay(1000);
      motion(LOW,HIGH,HIGH,LOW);
      delay(500);
      motion(LOW,LOW,LOW,LOW);
      */
  }
}
//************* Funcion de los motores ****************************************
void motion(int R_FWD, int R_BWD, int L_FWD, int L_BWD) {
   digitalWrite(PIN_MOTOR_R_FWD, R_FWD);
   digitalWrite(PIN_MOTOR_R_BWD, R_BWD);
   digitalWrite(PIN_MOTOR_L_FWD, L_FWD);
   digitalWrite(PIN_MOTOR_L_BWD, L_BWD);
}
 
//************* multitarea ****************************************
void Task1(void *pvParameters){
  while(1){
    // Crear otra tarea aquí 
    delay(1); //Requerido para multitareas while loop
  }
}
 
//**************************************************************
void websocket_send(String str_txt,String str_txt2){
 String strb;
 if(firstMeasure){
  firstMeasure=false;
  strb = "-" +str_txt + "-";
 }else{
  firstMeasure=true;
  strb = str_txt ;
 }
  ews.EWS_ESP32_Str_SEND(strb, "wroomTXT"); //enviar una cadena en el navegador  sobre el sensor
  ews.EWS_ESP32_Str_SEND(obsColor, "sensor"); //enviar una cadena en el navegador  sobre el color del sensor
  ews.EWS_ESP32_Str_SEND(str_txt2, "statusR"); //enviar una cadena en el navegador  sobre el estado del robot
}
//************************* Websocket handshake **************************************

void conectSecuence () {
  digitalWrite(azul,HIGH);
  digitalWrite(amarillo,HIGH);
  digitalWrite(rojo,HIGH);
  delay(100);
  digitalWrite(azul,LOW);
  delay(100);
  digitalWrite(azul,HIGH);
  delay(100);
  digitalWrite(rojo,LOW);
  delay(100);
  digitalWrite(rojo,HIGH);
  delay(100);
  digitalWrite(amarillo,LOW);
  delay(100);
  digitalWrite(amarillo,HIGH);
  delay(100);
  digitalWrite(azul,LOW);
  digitalWrite(amarillo,LOW);
  digitalWrite(rojo,LOW);
  delay(100);
  digitalWrite(azul,HIGH);
  digitalWrite(amarillo,HIGH);
  digitalWrite(rojo,HIGH);
  delay(500);
  digitalWrite(azul,LOW);
  digitalWrite(amarillo,LOW);
  digitalWrite(rojo,LOW);
  delay(100);
  digitalWrite(azul,HIGH);
  digitalWrite(amarillo,HIGH);
  digitalWrite(rojo,HIGH);
  delay(500);
  
}

//************************* Websocket handshake **************************************
void websocket_handshake(){  
  if(ews.Get_Http_Req_Status()){ //Determinar si hubo una solicitud GET del navegador
    String html_str1="", html_str2="", html_str3="", html_str4="", html_str5="", html_str6="", html_str7="";
 
    //※Solo se puede ingresar una función EWS_Canvas_Slider_T por variable String
    html_str1 += "<body style='background: linear-gradient(to left, #e01a1a,#000000);";
    html_str1 += "max-width: 80%; margin: auto; text-align: center; color:#fff;'>\r\n";
    html_str1 += "<font size=5>\r\n";
    html_str1 += "<br>\r\n";
    html_str1 += "Control de Robot\r\n";
    html_str1 += "<br><br>\r\n";
    html_str1 += "ESP32 por el metodo WebSocket\r\n";
    html_str1 += "<br><br>\r\n";
    html_str1 += "Por Ricardo Romo\r\n";
    html_str1 += "</font><br><br>\r\n";
    
    html_str1 += ews.EWS_BrowserSendRate();
    html_str1 += "<br>\r\n";
    html_str1 += ews.EWS_ESP32_SendRate("!esp32t-Rate");
    html_str1 += "<br>\r\n";
    
    html_str2 += ews.EWS_BrowserReceiveTextTag2("wroomTXT", "from ESP32 DATA of front HC-SR04", "#fff", 20,"#fff");
    html_str2 += "<br>\r\n";
    
    html_str3 += ews.EWS_BrowserReceiveTextTag2("statusR", "Estado del Robot", "#fff", 20,"#00FF00");
    html_str3 += "<br>\r\n";
    
    html_str4 += ews.EWS_Status_Text2("WebSocket Status","#fff", 20,"#FF00FF");
    html_str4 += "<br><br>\r\n";
   
    html_str5 += ews.EWS_On_Momentary_Button("W", "Adelante", 100,40,18,"#000","#fff");
    html_str5 += "<br><br>\r\n";
    html_str5 += ews.EWS_On_Momentary_Button("A", "Izquierda", 100,40,18,"#000","#fff");
    html_str5 += ews.EWS_On_Momentary_Button("Q", "Detenerse", 100,40,18,"#000","#fff");
    html_str5 += ews.EWS_On_Momentary_Button("D", "Derecha", 100,40,18,"#000","#fff");
    html_str5 += "<br><br>\r\n";
    html_str5 += ews.EWS_On_Momentary_Button("S", "Atras", 100,40,15,"#000","#eee");
    
 
    html_str7 += "<br><br>\r\n";
    html_str7 += ews.EWS_WebSocket_Reconnection_Button2("WS-Reconnect", "white", 200, 40, "black" , 17);
    html_str7 += "<br><br>\r\n";  
    html_str7 += ews.EWS_Close_Button2("WS CLOSE", "#fff", 150, 40, "red", 17);
    html_str7 += ews.EWS_Window_ReLoad_Button2("ReLoad", "#fff", 150, 40, "blue", 17);
    html_str7 += "</body></html>";
 
    //Función de handshake de WebSocket
    ews.EWS_HandShake_main(3, HTM_head_file1, HTM_head_file2, HTML_body_file, dummy_file, LIP, html_str1, html_str2, html_str3, html_str4, html_str5, html_str6, html_str7);
  }
}
