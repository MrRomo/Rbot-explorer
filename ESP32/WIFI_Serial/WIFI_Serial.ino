#include <WiFi.h>
#include <WiFiMulti.h>
#include "ESP32_SPIFFS_EasyWebSocket.h" //beta ver 1.60

const char* ssid = "RicardoMovil"; //Nombre de la rec
const char* password = "Ricardo18"; //Clave de la red

const char* HTM_head_file1 = "/EWS/LIPhead1.txt"; //Archivo de encabezado HTML 1
const char* HTM_head_file2 = "/EWS/LIPhead2.txt"; //Archivo de encabezado HTML 2

const char* HTML_body_file = "/EWS/dummy.txt"; //Archivo de elemento de body del HTML
const char* dummy_file = "/EWS/dummy.txt"; //Archivo ficticio para vincular archivos HTML

ESP32_SPIFFS_EasyWebSocket ews;
WiFiMulti wifiMulti;

IPAddress LIP; // Para obtener la direcciÃ³n IP local automÃ¡ticamente

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


//variables del sensor HC-SR04
float distancia_f = 40;
float distancia_d = 50;
float distancia_i = 60;
String dist, StateR;
bool firstMeasure = true;
bool check_ms = true;

//*************ConfiguraciÃ³n*************************
void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

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
    websocket_send(SF_text, SR_text, SL_text);
    check_ms = false;
   
    
    SF_text = "Obstaculo a: " + String(distancia_f) + " cm";
    SR_text = "Obstaculo a: " + String(distancia_d) + " cm";
    SL_text = "Obstaculo a: " + String(distancia_i) + " cm";

    ret_str = ews.EWS_ESP32CharReceive(PingSendTime);
     while (Serial.available()>0) {
      char inByte = Serial.read();
      distancia_f = inByte;
    }
    if (ret_str != "\0") {
      if (ret_str != "Ping") {
        if (ret_str[0] != 't') {
          int ws_data = (ret_str[0] - 0x30) * 100 + (ret_str[1] - 0x30) * 10 + (ret_str[2] - 0x30);
          Serial.println(ret_str[4]);
          switch (ret_str[4]) {
            case 'W':
              Serial.println("Forward");
              Serial.write(2);
              statusR = "Forward";
              break;
            default:
              Serial.println("Stop");
              Serial.write(0);
              statusR = "Stop";
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
void websocket_handshake() {
  if (ews.Get_Http_Req_Status()) { //Determinar si hubo una solicitud GET del navegador
    String html_str1 = "", html_str2 = "", html_str3 = "", html_str4 = "", html_str5 = "", html_str6 = "", html_str7 = "";
   
    html_str1 = "<body> <style media=\"screen\"> body { background: linear-gradient(to left, #e01a1a,#000000); max-width: 80%; margin: auto; text-align: center; color:#fff; } fieldset { border-style: solid; border-color: rgb(255, 255, 255); border-radius: 5px; } .sensorF { border-style: solid; background: rgb(0, 204, 17); border-color: rgb(255, 255, 255); border-radius: 5px; } .sensorR { background: rgb(0, 204, 17); } .sensorL { background: rgb(0, 204, 17); } legend { font-style: italic; background: #000000bb; color:#fff; } span { style=\"font-size:20px; color:#fff;\" } .metric{ justify-content: space-around; display: flex; margin-top: 10px; } input { width:100px; height:40px; font-size:28px; color:#000; background-color:#fff; } .contenedor { width: 80%; margin: 20px auto; } </style> <header> <div class=\"portada\"> <br> Control de Robot <br><br> ESP32 por el metodo WebSocket <br><br> Por Ricardo Romo </div> </header> <div class=\"contenedor\"> <fieldset id=\"sensorF\" class=\"sensorF\"> <legend> Sensor Frontral </legend> <span id=\"SF\">Obstaculo a: 154.88 cm</span> </fieldset> </div> <div class=\"canvasDraw\" id=\"radar\"> <canvas width=\"300\" height=\"300\" id=\"plano\"></canvas> </div> <input type=\"button\" value=\"&nwarr; \" onclick=\"doSend(100,'h'); data_tmp = 0;\"> <input type=\"button\" value=\"&UpTeeArrow;\" onclick=\"doSend(100,'w'); data_tmp = 0;\"> <input type=\"button\" value=\"&nearr;\" onclick=\"doSend(100,'k'); data_tmp = 0;\"> <br><br> <input type=\"button\" value=\"&olarr;\" onclick=\"doSend(100,'a'); data_tmp = 0;\"> <input type=\"button\" value=\"&empty;\" onclick=\"doSend(100,'q'); data_tmp = 0;\"> <input type=\"button\" value=\"&orarr;\" onclick=\"doSend(100,'d'); data_tmp = 0;\"> <br><br> <input type=\"button\" value=\"&DownTeeArrow;\" onclick=\"doSend(100,'s'); data_tmp = 0;\"> <br><br> <fieldset id=\"sensor\"> <legend> Estado del Robot</legend> <span id=\"statusR\">stop</span> </fieldset> <br> <fieldset> <legend> WebSocket Status</legend> <span id=\"__wsStatus__\">WebSocket.CONNECTED</span> </fieldset> <br><br> <br><br> <input type=\"button\" value=\"WS-Reconnect\" onclick=\"init();\"> <br><br> <input type=\"button\" value=\"WS CLOSE\" onclick=\"WS_close()\"> <input type=\"button\" value=\"ReLoad\" onclick=\"window.location.reload()\"> <script type=\"text/javascript\"> var lienzoElement = document.getElementById(\"plano\"); var lienzo = lienzoElement.getContext(\"2d\"); var distancias = [150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80,150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80] var angulos =[180,90,0,45,140,123,15,50,60] setInterval(()=>{ rastreador() },200) function rastreador() { console.log(\"INNER\"); lienzo.beginPath(); lienzo.rect(0, 0, 300, 300); lienzo.fillStyle = \"black\"; lienzo.fill(); lienzo.closePath(); distancias.sort(function(a, b){return 0.5 - Math.random()}); for (var dist in distancias) { let tetha = (dist*5)*Math.PI/180; let x = distancias[dist]*Math.cos(tetha)+150 let y = -distancias[dist]*Math.sin(tetha) +300 console.log(`Distancia [${dist}]: ${distancias[dist]} - Angle: ${tetha}`); console.log(`X: ${x} - Y: ${y}`); dibujante(150, x , 300, y , \"yellow\"); } } function dibujante( xi, xf, yi, yf, colorLine){ lienzo.beginPath(); lienzo.strokeStyle=colorLine; lienzo.moveTo(xi,yi); lienzo.lineTo(xf,yf); lienzo.stroke(); lienzo.closePath(); } </script> </body> </html>";


    //FunciÃ³n de handshake de WebSocket
    ews.EWS_HandShake_main(3, HTM_head_file1, HTM_head_file2, HTML_body_file, dummy_file, LIP, html_str1, html_str2, html_str3, html_str4, html_str5, html_str6, html_str7);
  }
}

