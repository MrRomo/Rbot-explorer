#include <WiFi.h>
#include <WiFiMulti.h>
#include "ESP32_SPIFFS_EasyWebSocket.h" //beta ver 1.60

const char* ssid = "JR2GWIFI"; //Nombre de la rec
const char* password = "ADBAE5FA"; //Clave de la red

const char* HTM_head_file1 = "/EWS/LIPhead1.txt"; //Archivo de encabezado HTML 1
const char* HTM_head_file2 = "/EWS/LIPhead2.txt"; //Archivo de encabezado HTML 2

const char* HTML_body_file = "/EWS/dummy.txt"; //Archivo de elemento de body del HTML
const char* dummy_file = "/EWS/dummy.txt"; //Archivo ficticio para vincular archivos HTML

ESP32_SPIFFS_EasyWebSocket ews;
WiFiMulti wifiMulti;

IPAddress LIP; // Para obtener la dirección IP local automáticamente

String ret_str; //para almacenar la secuencia enviada desde el navegador
String SF_text = "text send?"; //String para reenviar la cadena de caracteres recibida desde el navegador desde ESP32
String SL_text = "text send?"; //String para reenviar la cadena de caracteres recibida desde el navegador desde ESP32
String SR_text = "text send?"; //String para reenviar la cadena de caracteres recibida desde el navegador desde ESP32
String obsColor[]= {"#ffffff","#ffffff","#ffffff"};
String statusR = "stop";

int PingSendTime = 10000; // intervalo para hacer ping desde el ESP 32 al navegador (ms)

long ESP32_send_LastTime;
int ESP32_send_Rate = 300;
byte cnt = 0;
//Definicion de los sensores
//----------sensor frontal ---------------------
#define TRIGGER_F 2  //define la salida por donde se manda el TRIGGER como 9
#define ECHO_F 27 //define la salida por donde se recibe el ECHO como 10

//----------sensor derecha---------------------
#define TRIGGER_D 19  //define la salida por donde se manda el TRIGGER como 9
#define ECHO_D 26 //define la salida por donde se recibe el ECHO como 10

//----------sensor izquierda ---------------------
#define TRIGGER_I 32  //define la salida por donde se manda el TRIGGER como 9
#define ECHO_I 25 //define la salida por donde se recibe el ECHO como 10

#define azul 33 //Led azul, objeto a distancia mayor que 25cm
#define amarillo 18 //Led azul, indica objeto a distancia  menor que 25cm y mayor que 6cm
#define rojo 23 // Led rojo indica objeto a distancia menor que 6cm


// Definiciones de pines usados para los motores//
#define PIN_MOTOR_R_FWD 22
#define PIN_MOTOR_R_BWD 21
#define PIN_MOTOR_L_FWD 17
#define PIN_MOTOR_L_BWD 16

//variables del sensor HC-SR04
float distancia_f = 0;
float distancia_d = 0;
float distancia_i = 0;
String dist, StateR;
bool firstMeasure = true;
bool check_ms = true;

//*************Configuración*************************
void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  wifiMulti.addAP(ssid, password);

  Serial.println(F("Connecting Wifi..."));
  if (wifiMulti.run() == WL_CONNECTED) {
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

  pinMode(TRIGGER_F, OUTPUT); //Declaramos el pin 9 como salida (TRIGGER ultrasonido)
  pinMode(ECHO_F, INPUT); //Declaramos el pin 8 como entrada (recepción del TRIGGER)

  pinMode(TRIGGER_D, OUTPUT); //Declaramos el pin 9 como salida (TRIGGER ultrasonido)
  pinMode(ECHO_D, INPUT); //Declaramos el pin 8 como entrada (recepción del TRIGGER)

  pinMode(TRIGGER_I, OUTPUT); //Declaramos el pin 9 como salida (TRIGGER ultrasonido)
  pinMode(ECHO_I, INPUT); //Declaramos el pin 8 como entrada (recepción del TRIGGER

  motion(LOW, LOW, LOW, LOW);

  //Configuramos los leds
  pinMode(azul, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT);

  //setear las distancias
//  distancia_f = watcher (TRIGGER_F, ECHO_F, 0);
//  distancia_d = watcher (TRIGGER_D, ECHO_D, 1);
//  distancia_i = watcher (TRIGGER_I, ECHO_I, 2);

  Serial.println(); Serial.println("Initializing SPIFFS ...");

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS failed, or not present");
    return;
  }

  Serial.println("SPIFFS initialized. OK!");
  conectSecuence ();
  startSequence ();

  TaskHandle_t th; // Definición del manejador multitarea ESP32
  xTaskCreatePinnedToCore(Task1, "Task1", 4096, NULL, 5, &th, 0); //multitarea núcleo 0 ejecución

  ESP32_send_LastTime = millis();
}
//*************Loop*************************
void loop() {

  websocket_handshake();
  if (ret_str != "_close") {
    if (millis() - ESP32_send_LastTime > ESP32_send_Rate) {
      ESP32_send_LastTime = millis();
      check_ms = true;
    }
    if (check_ms) {
      websocket_send(SF_text, SR_text, SL_text);
      check_ms = false;

    }
//    distancia_f = watcher (TRIGGER_F, ECHO_F,0);
//    distancia_d = watcher (TRIGGER_D, ECHO_D,1);
//    distancia_i = watcher (TRIGGER_I, ECHO_I,2);
//    responseWatcher();
    //Serial.print("Distancia- F: " + String(distancia_f) + " - I: " +  String(distancia_i) + " - D: " +  String(distancia_d) + "\n");
    SF_text = "Obstaculo a: " + String(distancia_f) + " cm";
    SR_text = "Obstaculo a: " + String(distancia_d) + " cm";
    SL_text = "Obstaculo a: " + String(distancia_i) + " cm";

    ret_str = ews.EWS_ESP32CharReceive(PingSendTime);
    if (ret_str != "\0") {
      Serial.println(ret_str);
      if (ret_str != "Ping") {
        if (ret_str[0] != 't') {
          int ws_data = (ret_str[0] - 0x30) * 100 + (ret_str[1] - 0x30) * 10 + (ret_str[2] - 0x30);
          Serial.println(ret_str[4]);
          switch (ret_str[4]) {
            case 'W':
              Serial.println("Forward");
              Serial.write(2);
              motion(HIGH, LOW, LOW, HIGH);
              statusR = "Forward";
              break;
            case 'S':
              Serial.println("Backward");
              motion(LOW, HIGH, HIGH, LOW);
              statusR = "Backward";
              break;
            case 'A':
              Serial.println("Right");
              motion(HIGH, LOW, HIGH, LOW);
              statusR = "Right";
              break;
            case 'D':
              Serial.println("Left");
              motion(LOW, HIGH, LOW, HIGH);
              statusR = "Left";
              break;
            case 'Q':
              Serial.println("Left Quarter");
              motion(LOW, LOW, LOW, LOW);
              statusR = "Stop";
              break;
            case 'h':
              Serial.println("Stop");
              motion(HIGH, LOW, HIGH, LOW);
              delay(200);
              motion(LOW, LOW, LOW, LOW);
              statusR = "Left Quarter";
              break;
            case 'k':
              Serial.println("Right Quarter");
              motion(LOW, HIGH, LOW, HIGH);
              delay(200);
              motion(LOW, LOW, LOW, LOW);
              statusR = "Right Quarter";
              break;
          }
        }
      }
    }
  } else if (ret_str == "_close") {
    ESP32_send_LastTime = millis();
    ret_str = "";
  }
}

//************* Funcion de sensor HC-SR04 ****************************************
float  watcher (int TRIGGER, int ECHO, int color) {
  float distancia = 0;
  float tiempo = 0;

  digitalWrite(TRIGGER, LOW); //Por cuestión de estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(TRIGGER, HIGH); //envío del TRIGGER ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(ECHO, HIGH);  //funcion para medir el tiempo y guardarla en la variable "tiempo"
  distancia = 0.01715 * tiempo; //fórmula para calcular la distancia

  /*Monitorización en centímetros por el monitor serial*/
  //  Serial.print("Distancia: ");
  //  Serial.print(distancia);
  //  Serial.println(" cm");
  digitalWrite(azul, LOW);
  digitalWrite(amarillo, LOW);
  digitalWrite(rojo, LOW);
  if (distancia > 25) {
    obsColor[color] = "#00cc11";
  } else if ((distancia <= 25) && (distancia > 8)) {
    obsColor[color] = "#cccc00";
  } else if (distancia <= 8) {
    obsColor[color] = "#cc0000";
  }
   if (distancia_f > 25) {
    digitalWrite(azul, HIGH);
  } else if ((distancia_f <= 25) && (distancia_f > 8)) {
    digitalWrite(amarillo, HIGH);
  } else if (distancia_f <= 8) {
    digitalWrite(rojo, HIGH);
  }
  return distancia;
}
void responseWatcher() {
  if (distancia_f <= 8) {
    motion(LOW, LOW, LOW, LOW);
    delay(1000);
    motion(HIGH, LOW, HIGH, LOW);
    delay(500);
    motion(LOW, LOW, LOW, LOW);
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
void Task1(void *pvParameters) {
  while (1) {
    // Crear otra tarea aquí
    delay(1); //Requerido para multitareas while loop
  }
}

//**************************************************************
void websocket_send(String sf_txt, String sr_txt, String sl_txt) {
  String stra, strb, strc;
  if (firstMeasure) {
    firstMeasure = false;
    stra = "-" + sf_txt + "-";
    strb = "-" + sr_txt + "-";
    strc = "-" + sl_txt + "-";
  } else {
    firstMeasure = true;
    stra = sf_txt ;
    strb = sr_txt ;
    strc = sl_txt ;
  }
  ews.EWS_ESP32_Str_SEND(stra, "SF"); //enviar una cadena en el navegador  sobre el sensor frontal
  ews.EWS_ESP32_Str_SEND(strb, "SR"); //enviar una cadena en el navegador  sobre el sensor derecha
  ews.EWS_ESP32_Str_SEND(strc, "SL"); //enviar una cadena en el navegador  sobre el sensor izquierda
  ews.EWS_ESP32_Str_SEND(obsColor[0], "sensorF"); //enviar una cadena en el navegador  sobre el color del sensor frontal
  ews.EWS_ESP32_Str_SEND(obsColor[1], "sensorR"); //enviar una cadena en el navegador  sobre el color del sensor derecho
  ews.EWS_ESP32_Str_SEND(obsColor[2], "sensorL"); //enviar una cadena en el navegador  sobre el color del sensor izquierdo
  ews.EWS_ESP32_Str_SEND(statusR, "statusR"); //enviar una cadena en el navegador  sobre el estado del robot
}
//************************* Websocket handshake **************************************
void startSequence () {
  for ( int i = 0; i < 10; i++) {
    digitalWrite(azul, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(rojo, LOW);
    delay(100);
    digitalWrite(azul, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(rojo, LOW);
    delay(100);
    digitalWrite(azul, LOW);
    digitalWrite(amarillo, LOW);
    digitalWrite(rojo, HIGH);
    delay(100);
  }

}
void conectSecuence () {
  digitalWrite(azul, HIGH);
  digitalWrite(amarillo, HIGH);
  digitalWrite(rojo, HIGH);
  delay(100);
  digitalWrite(azul, LOW);
  delay(100);
  digitalWrite(azul, HIGH);
  delay(100);
  digitalWrite(rojo, LOW);
  delay(100);
  digitalWrite(rojo, HIGH);
  delay(100);
  digitalWrite(amarillo, LOW);
  delay(100);
  digitalWrite(amarillo, HIGH);
  delay(100);
  digitalWrite(azul, LOW);
  digitalWrite(amarillo, LOW);
  digitalWrite(rojo, LOW);
  delay(100);
  digitalWrite(azul, HIGH);
  digitalWrite(amarillo, HIGH);
  digitalWrite(rojo, HIGH);
  delay(500);
  digitalWrite(azul, LOW);
  digitalWrite(amarillo, LOW);
  digitalWrite(rojo, LOW);
  delay(100);
  digitalWrite(azul, HIGH);
  digitalWrite(amarillo, HIGH);
  digitalWrite(rojo, HIGH);
  delay(500);

}

//************************* Websocket handshake **************************************
void websocket_handshake() {
  if (ews.Get_Http_Req_Status()) { //Determinar si hubo una solicitud GET del navegador
    String html_str1 = "", html_str2 = "", html_str3 = "", html_str4 = "", html_str5 = "", html_str6 = "", html_str7 = "";
   
    html_str1 = "<body> <style media=\"screen\"> body { background: linear-gradient(to left, #e01a1a,#000000); max-width: 80%; margin: auto; text-align: center; color:#fff; } fieldset { border-style: solid; border-color: rgb(255, 255, 255); border-radius: 5px; } .sensorF { border-style: solid; background: rgb(0, 204, 17); border-color: rgb(255, 255, 255); border-radius: 5px; } .sensorR { background: rgb(0, 204, 17); } .sensorL { background: rgb(0, 204, 17); } legend { font-style: italic; background: #000000bb; color:#fff; } span { style=\"font-size:20px; color:#fff;\" } .metric{ justify-content: space-around; display: flex; margin-top: 10px; } input { width:100px; height:40px; font-size:28px; color:#000; background-color:#fff; } .contenedor { width: 80%; margin: 20px auto; } </style> <header> <div class=\"portada\"> <br> Control de Robot <br><br> ESP32 por el metodo WebSocket <br><br> Por Ricardo Romo </div> </header> <div class=\"contenedor\"> <fieldset id=\"sensorF\" class=\"sensorF\"> <legend> Sensor Frontral </legend> <span id=\"SF\">Obstaculo a: 154.88 cm</span> </fieldset> <div class=\"metric\"> <fieldset id=\"sensorR\" class=\"sensorR\"> <legend> Sensor Derecho</legend> <span id=\"SR\">Obstaculo a: 213.07 cm</span> </fieldset> <fieldset id=\"sensorL\" class=\"sensorL\"> <legend> Sensor Izquierdo</legend> <span id=\"SL\">Obstaculo a: 95.13 cm</span> </fieldset> </div> </div> <input type=\"button\" value=\"&nwarr; \" onclick=\"doSend(100,'h'); data_tmp = 0;\"> <input type=\"button\" value=\"&UpTeeArrow;\" onclick=\"doSend(100,'W'); data_tmp = 0;\"> <input type=\"button\" value=\"&nearr;\" onclick=\"doSend(100,'k'); data_tmp = 0;\"> <br><br> <input type=\"button\" value=\"&olarr;\" onclick=\"doSend(100,'A'); data_tmp = 0;\"> <input type=\"button\" value=\"&empty;\" onclick=\"doSend(100,'Q'); data_tmp = 0;\"> <input type=\"button\" value=\"&orarr;\" onclick=\"doSend(100,'D'); data_tmp = 0;\"> <br><br> <input type=\"button\" value=\"&DownTeeArrow;\" onclick=\"doSend(100,'S'); data_tmp = 0;\"> <br><br> <fieldset id=\"sensor\"> <legend> Estado del Robot</legend> <span id=\"statusR\">stop</span> </fieldset> <br> <fieldset> <legend> WebSocket Status</legend> <span id=\"__wsStatus__\">WebSocket.CONNECTED</span> </fieldset> <br><br> <br><br> <input type=\"button\" value=\"WS-Reconnect\" onclick=\"init();\"> <br><br> <input type=\"button\" value=\"WS CLOSE\" onclick=\"WS_close()\"> <input type=\"button\" value=\"ReLoad\" onclick=\"window.location.reload()\"> </body> </html>";
    //Función de handshake de WebSocket
    ews.EWS_HandShake_main(3, HTM_head_file1, HTM_head_file2, HTML_body_file, dummy_file, LIP, html_str1, html_str2, html_str3, html_str4, html_str5, html_str6, html_str7);
  }
}
