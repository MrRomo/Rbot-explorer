#include <WiFi.h>
#include <WiFiMulti.h>
#include "ESP32_SPIFFS_EasyWebSocket.h" //beta ver 1.60
// Definiciones de pines usados para los motores//
#define PIN_MOTOR_R_FWD 26
#define PIN_MOTOR_R_BWD 18
#define PIN_MOTOR_L_FWD 19
#define PIN_MOTOR_L_BWD 23


const char* ssid = "JR2GWIFI"; //Nombre de la rec
const char* password = "ADBAE5FA"; //Clave de la red

char receiver[4] = {22,21,17,16};

const char* HTM_head_file1 = "/EWS/LIPhead1.txt"; //Archivo de encabezado HTML 1
const char* HTM_head_file2 = "/EWS/LIPhead2.txt"; //Archivo de encabezado HTML 2

const char* HTML_body_file = "/EWS/dummy.txt"; //Archivo de elemento de body del HTML
const char* dummy_file = "/EWS/dummy.txt"; //Archivo ficticio para vincular archivos HTML

ESP32_SPIFFS_EasyWebSocket ews;
WiFiMulti wifiMulti;

IPAddress LIP; // Para obtener la direcciÃ³n IP local automÃ¡ticamente

String ret_str; //para almacenar la secuencia enviada desde el navegador
String SF_text = "text send?"; //String para reenviar la cadena de caracteres recibida desde el navegador desde ESP32
String obsColor[]= {"#ffffff","#ffffff","#ffffff"};
String statusR = "stop";

int PingSendTime = 10000; // intervalo para hacer ping desde el ESP 32 al navegador (ms)

long ESP32_send_LastTime;
int ESP32_send_Rate = 700;
byte cnt = 0;


//variables del sensor HC-SR04
float distancia_s = 40;
int angle = 0;
String measure, StateR;
bool firstMeasure = true;
bool check_ms = true;
bool switchDir = false;

//*************ConfiguraciÃ³n*************************
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  pinMode(PIN_MOTOR_R_FWD, OUTPUT);
  pinMode(PIN_MOTOR_R_BWD, OUTPUT);
  pinMode(PIN_MOTOR_L_FWD, OUTPUT);
  pinMode(PIN_MOTOR_L_BWD, OUTPUT);
  for (char i = 0; i < 4; i++) {
    pinMode(receiver[i],INPUT);
  }
  wifiMulti.addAP(ssid, password);

  Serial.println(F("Connecting Wifi..."));
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.println(F("Connecting ..."));
    delay(1000);
  }
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println(F("WiFi connected"));
    Serial.println(F("IP address: "));
    LIP = WiFi.localIP(); //Obtener la direcciÃ³n IP local de ESP32 automÃ¡ticamente
    Serial.println(WiFi.localIP());
  }
  delay(1000);

  ews.EWS_server_begin();

  Serial.println(); Serial.println("Initializing SPIFFS ...");

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS failed, or not present");
    return;
  }

  Serial.println("SPIFFS initialized. OK!");

  TaskHandle_t th; // DefiniciÃ³n del manejador multitarea ESP32
  xTaskCreatePinnedToCore(Task1, "Task1", 4096, NULL, 5, &th, 0); //multitarea nÃºcleo 0 ejecuciÃ³n

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
    if(switchDir){
      angle+=1;
      if(angle>=36){
        switchDir = false;
      }
    }
    else {
      angle-=1;
      if(angle<=0){
        switchDir = true;
      }
    }


    //distancia_s = random(60, 150);
    //distancia_s = readPines()*10;
    if(Serial.available()){
      distancia_s = Serial.read();
      Serial.println(distancia_s );
    }
    measure = String(angle)+"|"+String(distancia_s);
    websocket_send(measure);
    check_ms = false;


    SF_text = "Obstaculo a: " + String(distancia_s) + " cm";

    ret_str = ews.EWS_ESP32CharReceive(PingSendTime);

    if (ret_str != "\0") {
      if (ret_str != "Ping") {
        if (ret_str[0] != 't') {
          int ws_data = (ret_str[0] - 0x30) * 100 + (ret_str[1] - 0x30) * 10 + (ret_str[2] - 0x30);
          Serial.println(ret_str[4]);
          switch (ret_str[4]) {
             case 'w':
              Serial.println("Forward");
               motion(LOW, LOW, LOW, LOW);
               delay(20);
              motion(HIGH, LOW, LOW, HIGH);
              statusR = "Forward";
              break;
            case 's':
              Serial.println("Backward");
              motion(LOW, LOW, LOW, LOW);
              delay(20);
              motion(LOW, HIGH, HIGH, LOW);
              statusR = "Backward";
              break;
            case 'a':
              Serial.println("Right");
              motion(LOW, LOW, LOW, LOW);
              delay(20);
              motion(HIGH, LOW, HIGH, LOW);
              statusR = "Right";
              break;
            case 'd':
              Serial.println("Left");
              motion(LOW, LOW, LOW, LOW);
               delay(20);
              motion(LOW, HIGH, LOW, HIGH);
              statusR = "Left";
              break;
            case 'q':
              Serial.println("Left Quarter");
              motion(LOW, LOW, LOW, LOW);
              delay(20);
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


//************* multitarea ****************************************
void Task1(void *pvParameters) {
  while (1) {
    // Crear otra tarea aquÃ­
    delay(1); //Requerido para multitareas while loop
  }
}

//**************************************************************
void websocket_send(String sf_txt) {
  ews.EWS_ESP32_Str_SEND(sf_txt, "Sensor"); //enviar una cadena en el navegador  sobre el sensor frontal
  ews.EWS_ESP32_Str_SEND(obsColor[0], "SensorF"); //enviar una cadena en el navegador  sobre el color del sensor frontal
  ews.EWS_ESP32_Str_SEND(statusR, "statusR"); //enviar una cadena en el navegador  sobre el estado del robot
}
//************************* Websocket handshake **************************************
void websocket_handshake() {
  if (ews.Get_Http_Req_Status()) { //Determinar si hubo una solicitud GET del navegador
    String html_str1 = "", html_str2 = "", html_str3 = "", html_str4 = "", html_str5 = "", html_str6 = "", html_str7 = "";

    html_str1 = "<body> <style media=\"screen\"> body { background: linear-gradient(to left, #e01a1a,#000000); max-width: 80%; margin: auto; text-align: center; color:#fff; } fieldset { border-style: solid; border-color: rgb(255, 255, 255); border-radius: 5px; } .sensorF { border-style: solid; background: rgb(0, 204, 17); border-color: rgb(255, 255, 255); border-radius: 5px; } .sensorR { background: rgb(0, 204, 17); } .sensorL { background: rgb(0, 204, 17); } legend { font-style: italic; background: #000000bb; color:#fff; } span { style=\"font-size:20px; color:#fff;\" } .metric{ justify-content: space-around; display: flex; margin-top: 10px; } input { width:100px; height:40px; font-size:28px; color:#000; background-color:#fff; } .contenedor { width: 80%; margin: 20px auto; } </style> <header> <div class=\"portada\"> <br> Control de Robot <br><br> ESP32 por el metodo WebSocket <br><br> Por Ricardo Romo </div> </header> <div class=\"contenedor\"> <fieldset id=\"sensorF\" class=\"sensorF\"> <legend> Sensor Frontral </legend> <span id=\"SF\">Obstaculo a: 154.88 cm</span> </fieldset> </div> <div class=\"canvasDraw\" id=\"radar\"> <canvas width=\"300\" height=\"300\" id=\"plano\"></canvas> </div> <input type=\"button\" value=\"&nwarr; \" onclick=\"doSend(100,'h'); data_tmp = 0;\"> <input type=\"button\" value=\"&UpTeeArrow;\" onclick=\"doSend(100,'w'); data_tmp = 0;\"> <input type=\"button\" value=\"&nearr;\" onclick=\"doSend(100,'k'); data_tmp = 0;\"> <br><br> <input type=\"button\" value=\"&olarr;\" onclick=\"doSend(100,'a'); data_tmp = 0;\"> <input type=\"button\" value=\"&empty;\" onclick=\"doSend(100,'q'); data_tmp = 0;\"> <input type=\"button\" value=\"&orarr;\" onclick=\"doSend(100,'d'); data_tmp = 0;\"> <br><br> <input type=\"button\" value=\"&DownTeeArrow;\" onclick=\"doSend(100,'s'); data_tmp = 0;\"> <br><br> <fieldset id=\"sensor\"> <legend> Estado del Robot</legend> <span id=\"statusR\">stop</span> </fieldset> <br> <fieldset> <legend> WebSocket Status</legend> <span id=\"__wsStatus__\">WebSocket.CONNECTED</span> </fieldset> <br><br> <br><br> <input type=\"button\" value=\"WS-Reconnect\" onclick=\"init();\"> <br><br> <input type=\"button\" value=\"WS CLOSE\" onclick=\"WS_close()\"> <input type=\"button\" value=\"ReLoad\" onclick=\"window.location.reload()\"> <script src=\"https://ricardoromo.co/Rbot/index.js\" charset=\"utf-8\"></script> </body> </html>";


    //FunciÃ³n de handshake de WebSocket
    ews.EWS_HandShake_main(3, HTM_head_file1, HTM_head_file2, HTML_body_file, dummy_file, LIP, html_str1, html_str2, html_str3, html_str4, html_str5, html_str6, html_str7);
  }
}
void motion(int R_FWD, int R_BWD, int L_FWD, int L_BWD) {
  digitalWrite(PIN_MOTOR_R_FWD, R_FWD);
  digitalWrite(PIN_MOTOR_R_BWD, R_BWD);
  digitalWrite(PIN_MOTOR_L_FWD, L_FWD);
  digitalWrite(PIN_MOTOR_L_BWD, L_BWD);
}
