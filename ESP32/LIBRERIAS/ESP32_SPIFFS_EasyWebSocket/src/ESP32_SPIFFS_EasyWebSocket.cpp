/*
  ESP32_SPIFFS_EasyWebSocket.cpp - WebSocket for ESP-WROOM-32 ( ESP32 & SPIFFS card use)
  Beta version 1.61

Copyright (c) 2018 Mgo-tec
This library improvement collaborator is Mr.Visyeii.
Part of WiFiServer.h(for ESP8266) library modified.

This library is used by the Arduino IDE(Tested in ver1.8.5).

Reference Blog --> https://www.mgo-tec.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Reference LGPL-2.1 license statement --> https://opensource.org/licenses/LGPL-2.1   

WiFi.h - Included WiFi library for esp32
Based on WiFi.h from Arduino WiFi shield library.
Copyright (c) 2011-2014 Arduino.  All right reserved.
Modified by Ivan Grokhotkov, December 2014
Licensed under the LGPL-2.1

SPIFFS.h - Included SPIFFS library for esp32
Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
Licensed under the Apache License, Version 2.0 (the "License");

Reference Apache License --> http://www.apache.org/licenses/LICENSE-2.0
*/

#include "ESP32_SPIFFS_EasyWebSocket.h"

static WiFiClient __client;
static WiFiServer __server(80);

static HTTPClientStatus1 _currentStatus;
static uint32_t _statusChange;

ESP32_SPIFFS_EasyWebSocket::ESP32_SPIFFS_EasyWebSocket(){}

//********AP(Router) Connection****
void ESP32_SPIFFS_EasyWebSocket::EWS_server_begin()
{
  // Start the server
  _currentStatus = HC_NONE1;
  __server.begin();
  Serial.println(F("Server started"));

  _Upgrade_first_on = false;
  _WifiConnectTime = millis();
}

//*********handleClient***************
void ESP32_SPIFFS_EasyWebSocket::handleClient()
{
  if (_currentStatus == HC_NONE1) {
    WiFiClient _local_client = __server.available();
    if (!_local_client) {
      return;
    }

#ifdef DEBUG_ESP_HTTP_SERVER
    DEBUG_OUTPUT.println("New client");
#endif

    __client = _local_client;
    _currentStatus = HC_WAIT_READ1;
    _statusChange = millis();
  }

  if (!__client.connected()) {
    __client = WiFiClient();
    _currentStatus = HC_NONE1;
    return;
  }

  // Wait for data from client to become available
  if (_currentStatus == HC_WAIT_READ1) {
    if (!__client.available()) {
      if (millis() - _statusChange > HTTP_MAX_DATA_WAIT) {
        __client = WiFiClient();
        _currentStatus = HC_NONE1;
      }
      yield();
      return;
    }

    if (!__client.connected()) {
      __client = WiFiClient();
      _currentStatus = HC_NONE1;
      return;
    } else {
      _currentStatus = HC_WAIT_CLOSE1;
      _statusChange = millis();
      return;
    }
  }

  if (_currentStatus == HC_WAIT_CLOSE1) {
    if (millis() - _statusChange > HTTP_MAX_CLOSE_WAIT) {
      __client = WiFiClient();
      _currentStatus = HC_NONE1;
    } else {
      yield();
      return;
    }
  }
}
//*********handleClient***************
bool ESP32_SPIFFS_EasyWebSocket::Get_Http_Req_Status(){
  String req;
  String hash_req_key;
  _GetLoopTime = millis();

  if(!_WS_on){
    handleClient();
  }else{
    return false;
  }

  if(__client){
    _GetLoopTime = millis();
    while(!_WS_on){
      if(millis()-_GetLoopTime > 5000L){
        ESP32_SPIFFS_EasyWebSocket::HandShake_timeout(1);
        break;
      }

      delay(1);
      switch(_Ini_html_on){
        case 0:
          _GetLoopTime = millis();
          while(__client){
            if(millis()-_GetLoopTime > 5000L){
              ESP32_SPIFFS_EasyWebSocket::HandShake_timeout(2);
              break;
            }
            if(__client.available()){
              req = __client.readStringUntil('\n');
              if(req.indexOf("GET / HTTP") != -1){
                Serial.println(F("-------HTTP Request from Browser"));
                Serial.println(req);
                return true;
              }else if(req.indexOf("GET /favicon") != -1){
                ESP32_SPIFFS_EasyWebSocket::Favicon_Response(req, 0, 1, 2);
                break;
              }
            }
						yield();
          }
          break;
        case 1:
          switch(_WS_on){
            case 0:
              ESP32_SPIFFS_EasyWebSocket::EWS_HTTP_Responce();
              _PingLastTime = millis();
              _PongLastTime = millis();
              break;
            case 1:
              Serial.println(F("-------WebSocket HandShake Complete!"));
              _GetLoopTime = millis();
              break;
          }
          break;
      }
	  	delay(1);
    }
  }
  return false;
}
//****************************************
bool ESP32_SPIFFS_EasyWebSocket::http_resp(){
  String req = "";
  while(req.indexOf("\r") != 0){
    req = __client.readStringUntil('\n');
    if(req.indexOf("Upgrade: websocket") != -1){
      Serial.println(F("-------Connection: Upgrade HTTP Request"));
      Serial.println(req);
      _Ini_html_on = 1;
      _Upgrade_first_on = true;
      ESP32_SPIFFS_EasyWebSocket::EWS_HTTP_Responce();
      _PingLastTime = millis();
      _PongLastTime = millis();
      break;
    }

    if(req.indexOf("Android") != -1){
      _Android_or_iPad = 'A';
    }else if(req.indexOf("iPad") != -1){
      _Android_or_iPad = 'i';
    }else if(req.indexOf("iPhone") != -1){
      _Android_or_iPad = 'P';
    }
    Serial.println(req);
    delay(1);
  }
  req = "";

  if(_Upgrade_first_on == true) return true;

  Serial.println(F("-------HTTP Response Send to Browser"));
  delay(10);

  __client.print(F("HTTP/1.1 200 OK\r\n"));
  __client.print(F("Content-Type:text/html\r\n"));
  __client.print(F("Connection:close\r\n\r\n"));

  return false;
}
//********hand shake time out *****************
void ESP32_SPIFFS_EasyWebSocket::HandShake_timeout(uint8_t Num){
  _WS_on = 0;
  _Ini_html_on = 0;
  _Upgrade_first_on = false;
  Serial.print(F("-------Received TimeOut "));
  Serial.println(Num);
  if(__client){
    __client.flush();
    delay(10);
    __client.stop();
    delay(10);
    Serial.print(F("-------TimeOut Client Stop "));
    Serial.println(Num);
  }
  Serial.print(F("-------The Handshake returns to the beginning "));
  Serial.println(Num);
}
//********WebSocket Hand Shake ****************
void ESP32_SPIFFS_EasyWebSocket::EWS_HandShake_main(uint8_t sel, const char* head_file1, const char* head_file2, const char* html_file1, const char* html_file2, IPAddress res_LIP, String res_html1, String res_html2, String res_html3, String res_html4, String res_html5, String res_html6, String res_html7){
  String req;
  String hash_req_key;
  _GetLoopTime = millis();

  while(__client){

    if( ESP32_SPIFFS_EasyWebSocket::http_resp() ) break;

    File HTML_head_F1, HTML_head_F2, HTML_1, HTML_2;

    HTML_head_F1 = ESP32_SPIFFS_EasyWebSocket::SPIFFS_open(head_file1);
    if(HTML_head_F1 == 0) return;

    if(sel >= 2){
      HTML_head_F2 = ESP32_SPIFFS_EasyWebSocket::SPIFFS_open(head_file2);
      if(HTML_head_F2 == 0) return;
    }
    if(sel >= 1 && sel <= 3){
      HTML_1 = ESP32_SPIFFS_EasyWebSocket::SPIFFS_open(html_file1);
      if(HTML_1 == 0) return;
      HTML_2 = ESP32_SPIFFS_EasyWebSocket::SPIFFS_open(html_file2);
      if(HTML_2 == 0) return;
    }

    ESP32_SPIFFS_EasyWebSocket::SPIFFS_Client_Write( HTML_head_F1, head_file1 );

    if(sel >= 2){
      __client.print(res_LIP);
      ESP32_SPIFFS_EasyWebSocket::SPIFFS_Client_Write( HTML_head_F2, head_file2 );
    }
    if(sel >= 1 && sel <= 3){
      ESP32_SPIFFS_EasyWebSocket::SPIFFS_Client_Write( HTML_1, html_file1 );
    }

    __client.print(res_html1);
    __client.print(res_html2);
    __client.print(res_html3);
    if(sel == 0 || sel >= 3){
      __client.print(res_html4);
      __client.print(res_html5);
      __client.print(res_html6);
      __client.print(res_html7);
    }
    if(sel >= 1 && sel <= 3){
      ESP32_SPIFFS_EasyWebSocket::SPIFFS_Client_Write( HTML_2, html_file2 );
      HTML_1.close();
      HTML_2.close();
    }
    if(sel >= 2){
      HTML_head_F2.close();
    }

    HTML_head_F1.close();

    res_html1 = "";
    res_html2 = "";
    res_html3 = "";
    res_html4 = "";
    res_html5 = "";
    res_html6 = "";
    res_html7 = "";

    Serial.println(F("---------------------HTTP response complete"));

    __client.flush();
    delay(10);
    __client.stop();
    delay(10);

    Serial.println(F("\n-------GET HTTP client stop"));
    req = "";
    _Ini_html_on = 1;
    _GetLoopTime = millis();

    if(_Android_or_iPad == 'i'){
      break;
    }
    break;
  }
}
//********Client write from SD*********************
void ESP32_SPIFFS_EasyWebSocket::SPIFFS_Client_Write(File SPIFFS_File, const char* file_name){
  if (SPIFFS_File == 0) {
    Serial.printf("%s File not found\n",file_name);
    return;
  }else{
    Serial.printf("%s File found. OK!\n",file_name);

    //size_t totalSize = SPIFFS_File.size();
    char c = 0x20;
    char c_print_buff[256];
    uint16_t index_count = 0;

    if(__client){    
      while(c!='\0'){
        c= SPIFFS_File.read();
        c_print_buff[index_count] = c;
        if(c>0xEF) break;
        index_count++;
        if (index_count == 256){
          __client.write((const char*)c_print_buff, 256);     
          Serial.print('.');
          index_count = 0;
        }
        delay(1);
      }
    }

    if (index_count > 0){
      __client.write((const char*)c_print_buff, index_count);
      index_count = 0;
    }
    Serial.println();
  }
}
//********Hand Shake Main *********************
File ESP32_SPIFFS_EasyWebSocket::SPIFFS_open(const char *filename){
  File f = SPIFFS.open(filename, FILE_READ);
  if (f == 0) {
    Serial.printf("%s File not found. Cannot opened.\n", filename);
    __client.print(F("ERROR!!<br>"));
    __client.print(filename);
    __client.print(F(" file has not been uploaded to the flash in SD card<br>"));
  }else{
    Serial.printf("%s File Open. OK!\n", filename);
  }
  return f;
}

//********WebSocket Hand Shake ****************
void ESP32_SPIFFS_EasyWebSocket::EWS_HandShake(const char* HTML_file, String res_html1, String res_html2, String res_html3, String res_html4, String res_html5, String res_html6, String res_html7)
{
  bool req_status = ESP32_SPIFFS_EasyWebSocket::Get_Http_Req_Status();

  if(req_status == true){
    ESP32_SPIFFS_EasyWebSocket::EWS_HandShake_main(0, HTML_file, "", "", "", IPAddress(0,0,0,0), res_html1, res_html2, res_html3, res_html4, res_html5, res_html6, res_html7);
  }
}

//********WebSocket Hand Shake (for devided HTML files)****************
void ESP32_SPIFFS_EasyWebSocket::EWS_Dev_HandShake(const char* HTML_head_file, const char* HTML_file1, String res_html1, String res_html2, String res_html3, const char* HTML_file2)
{
  bool req_status = ESP32_SPIFFS_EasyWebSocket::Get_Http_Req_Status();

  if(req_status == true){
    ESP32_SPIFFS_EasyWebSocket::EWS_HandShake_main(1, HTML_head_file, "", HTML_file1, HTML_file2, IPAddress(0,0,0,0), res_html1, res_html2, res_html3, "", "", "", "");
  }
}
//********WebSocket Hand Shake (for devided HTML header files & Auto Local IP address)****************
void ESP32_SPIFFS_EasyWebSocket::EWS_Dev_AutoLIP_HandShake(const char* HTML_head_file1, IPAddress res_LIP, const char* HTML_head_file2, const char* HTML_file1, String res_html1, String res_html2, String res_html3, String res_html4, String res_html5, String res_html6, String res_html7, const char* HTML_file2)
{
  bool req_status = ESP32_SPIFFS_EasyWebSocket::Get_Http_Req_Status();

  if(req_status == true){
    ESP32_SPIFFS_EasyWebSocket::EWS_HandShake_main(3, HTML_head_file1, HTML_head_file2, HTML_file1, HTML_file2, res_LIP, res_html1, res_html2, res_html3, res_html4, res_html5, res_html6, res_html7);
  }
}
//************HTTP Response**************************
void ESP32_SPIFFS_EasyWebSocket::EWS_HTTP_Responce()
{  
  String req;
  String hash_req_key;
  uint32_t LoopTime = millis();

  if(_Upgrade_first_on != true){
    handleClient();
  }

  while(__client){
    if(millis()-LoopTime > 5000L){
      _WS_on = 0;
      _Ini_html_on = 0;
      _Upgrade_first_on = false;
      Serial.println(F("-----------------------Received TimeOut 3"));
      if(__client){
        __client.flush();
        delay(10);
        __client.stop();
        delay(10);
        Serial.println(F("---------------------TimeOut Client Stop 3"));
      }
      Serial.println(F("-----------------------The Handshake returns to the beginning 3"));
      break;
    }

    if(__client.available()){
      req = __client.readStringUntil('\n');
      Serial.println(req);
      if (_Upgrade_first_on == true || req.indexOf("Upgrade: websocket") != -1){
        Serial.println(F("---------------------Websocket Requests received"));
        Serial.println(req);
 
        while(req.indexOf("\r") != 0){
          req = __client.readStringUntil('\n');
          Serial.println(req);
          if(req.indexOf("Sec-WebSocket-Key")>=0){
            hash_req_key = req.substring(req.indexOf(':')+2,req.indexOf('\r'));
            Serial.println();
            Serial.print(F("hash_req_key ="));
            Serial.println(hash_req_key);
          }
					yield();
        }

        delay(10);
        req ="";

        char h_resp_key[29];

        ESP32_SPIFFS_EasyWebSocket::Hash_Key(hash_req_key, h_resp_key);

        Serial.print(F("h_resp_key = "));
        Serial.println(h_resp_key);
        String str;

        str = "HTTP/1.1 101 Switching Protocols\r\n";
        str += "Upgrade: websocket\r\n";
        str += "Connection: Upgrade\r\n";
        str += "Sec-WebSocket-Accept: ";
        for(uint8_t i=0; i<28; i++){
          str += h_resp_key[i];
        }

        str += "\r\n\r\n";

        Serial.println(F("\n--------------------WebSocket HTTP Response Send"));
        Serial.println(str);
        __client.print(str);
        str = "";

        _WS_on = 1;
        Serial.println(F("-------------------WebSocket Response Complete!"));
        break;

      }else if(req.indexOf("favicon") != -1){
        ESP32_SPIFFS_EasyWebSocket::Favicon_Response(req, 0, 0, 0);
        LoopTime = millis();
      }else if(req.indexOf("apple-touch-icon") != -1){

        Serial.println();
        Serial.println(F("---------------------GET apple-touch-icon Request"));
        Serial.print(req);
        while(__client.available()){
          Serial.write(__client.read());
					yield();
        }
        __client.flush();
        delay(10);
        __client.stop();
        delay(10);
        Serial.println();
        Serial.println(F("---------------------apple-touch-icon_Client Stop"));
        LoopTime = millis();
      }
    }
		delay(1);
  }
}

//************Hash sha1 base64 encord**************************
void ESP32_SPIFFS_EasyWebSocket::Hash_Key(String h_req_key, char* h_resp_key)
{
  char Base64[65] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                      'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
                      'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
                      'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
                      '='
                    };
  uint8_t hash_six[28];
  uint8_t dummy_h1, dummy_h2;
  uint8_t i, j;
  i=0;
  j=0;

  String merge_str;

  merge_str = h_req_key + String(_GUID_str);
  Serial.println(F("--------------------Hash key Generation"));
  Serial.print(F("merge_str ="));
  Serial.println(merge_str);
  Serial.print(F("SHA1:"));

  uint8_t hash[20];
  ESP32_SPIFFS_EasyWebSocket::sha1(merge_str, &hash[0]);

  for( i = 0; i < 20; i++) {
    hash_six[j] = hash[i]>>2;
    
    hash_six[j+1] = hash[i+1] >> 4;
    bitWrite(hash_six[j+1], 4, bitRead(hash[i],0));
    bitWrite(hash_six[j+1], 5, bitRead(hash[i],1));

    if(j+2 < 26){
      hash_six[j+2] = hash[i+2] >> 6;
      bitWrite(hash_six[j+2], 2, bitRead(hash[i+1],0));
      bitWrite(hash_six[j+2], 3, bitRead(hash[i+1],1));
      bitWrite(hash_six[j+2], 4, bitRead(hash[i+1],2));
      bitWrite(hash_six[j+2], 5, bitRead(hash[i+1],3));
    }else if(j+2 == 26){
      dummy_h1 = 0;
      dummy_h2 = 0;
      dummy_h2 = hash[i+1] << 4;
      dummy_h2 = dummy_h2 >>2;
      hash_six[j+2] = dummy_h1 | dummy_h2;
    }

    if( j+3 < 27 ){
      hash_six[j+3] = hash[i+2];
      bitWrite(hash_six[j+3], 6, 0);
      bitWrite(hash_six[j+3], 7, 0);
    }else if(j+3 == 27){
      hash_six[j+3] = '=';
    }

    h_resp_key[j] = Base64[hash_six[j]];
    h_resp_key[j+1] = Base64[hash_six[j+1]];
    h_resp_key[j+2] = Base64[hash_six[j+2]];

    if(j+3==27){
      h_resp_key[j+3] = Base64[64];
      break;
    }else{
      h_resp_key[j+3] = Base64[hash_six[j+3]];
    }

    i = i + 2;
    j = j + 4;
  }
  h_resp_key[28] = '\0';

  Serial.print(F("hash_six = "));
  for(i=0; i<28; i++){
    Serial.print(hash_six[i],BIN);
    Serial.print('_');
  }
  Serial.println();
}

void ESP32_SPIFFS_EasyWebSocket::EWS_ESP8266_Str_SEND(String str, String id)
{
  ESP32_SPIFFS_EasyWebSocket::EWS_ESP32_Str_SEND(str, id);
}

void ESP32_SPIFFS_EasyWebSocket::EWS_ESP32_Str_SEND(String str, String id)
{
  str += '|' + id + '|';
  __client.write(B10000001);
  __client.write(str.length());
  __client.print(str); 
}

String ESP32_SPIFFS_EasyWebSocket::EWS_ESP8266CharReceive(uint16_t pTime)
{
  return ESP32_SPIFFS_EasyWebSocket::EWS_ESP32CharReceive(pTime);
}

String ESP32_SPIFFS_EasyWebSocket::EWS_ESP32CharReceive(uint16_t pTime)
{
  uint8_t b=0;
  uint8_t data_len;
  uint8_t mask[4];
  uint8_t i;
  String str_close = "_close";

  if(_WS_on){
    if(pTime > 0){
      if(millis()-_PingLastTime > pTime){
        ESP32_SPIFFS_EasyWebSocket::EWS_PING_SEND();
        _PingLastTime = millis();
      }

      if((millis() - _PongLastTime) > (pTime + 500)){
        __client.flush();
        delay(10);
        __client.stop();
        delay(10);
        Serial.println();
        Serial.println(F("-----------------Ping Non-Response Client.STOP"));
        _WS_on = 0;
        _Ini_html_on = 0;
        _Upgrade_first_on = false;
        return str_close;
      }
    }
  }

  if(__client.available()){
    b = __client.read();
    if(b == B10000001 || b == B10001010){
      switch (b){
        case B10000001:
          _PingLastTime = millis();
          _PongLastTime = millis();
          break;
        case B10001010:
          _PongLastTime = millis();
          Serial.println(F("Pong Receive**********"));
          break;
      }

      b = __client.read();
      data_len = b - B10000000;

      for(i=0; i<4; i++){
        mask[i] = __client.read();
      }

      uint8_t m_data[data_len];
      char data_c[data_len + 1];

      for(i = 0; i<data_len; i++){
        m_data[i] = __client.read();
        data_c[i] = mask[i%4]^m_data[i];
      }
      data_c[data_len] = '\0';

      return String(data_c);

    }else if(b == B10001000){
      Serial.println(F("------------------Close Command Received"));
      b = __client.read();
      Serial.println(b,BIN);
      data_len = b - B10000000;
      if(data_len == 0){
        while(__client.available()){
          b = __client.read();
					yield();
        }
        Serial.println(F("Closing HandShake OK!"));
      }else{
        for(i=0; i<4; i++){
          mask[i] = __client.read();
        }

        uint8_t m_data2[data_len];
        char data_c2[data_len + 1];

        for(i = 0; i<data_len; i++){
          m_data2[i] = __client.read();
          data_c2[i] = mask[i%4]^m_data2[i];
          if(i>1){
            Serial.write(data_c2[i]);
          }
        }
        data_c2[data_len] = '\0';
        Serial.println(F("----Closing Message"));
      }    

      delay(1);
      __client.write(B10001000);
      delay(1);
      Serial.println(F("------------------Close Command Send"));

      __client.flush();
      delay(10);
      __client.stop();
      delay(10);
      Serial.println();
      Serial.println(F("------------------Client.STOP"));
      _WS_on = 0;
      _Ini_html_on = 0;
      _Upgrade_first_on = false;

      while(__client){
        if(__client.available()){
          String req = __client.readStringUntil('\n');
          Serial.println(req);
          if(req.indexOf("GET /favicon") != -1){
            Favicon_Response(req, 0, 0, 0);
            break;
          }
        }
				delay(1);
      }

      return str_close;
    }else{
      return String('\0');
    }
  }else{
    return String('\0');
  }
}

String ESP32_SPIFFS_EasyWebSocket::EWS_ESP32DataReceive_SPIFFS_write(uint16_t pTime, char bin_file[14])
{
  uint8_t b=0;
  uint8_t data_len;
  uint8_t mask[4];
  uint8_t i;
  String str_close = "_close";

  if(_WS_on){
    if(pTime > 0){
      if(millis()-_PingLastTime > pTime){
        ESP32_SPIFFS_EasyWebSocket::EWS_PING_SEND();
        _PingLastTime = millis();
      }

      if((millis() - _PongLastTime) > (pTime + 500)){
        __client.flush();
        delay(10);
        __client.stop();
        delay(10);
        Serial.println();
        Serial.println(F("-----------------Ping Non-Response Client.STOP"));
        _WS_on = 0;
        _Ini_html_on = 0;
        _Upgrade_first_on = false;
        return str_close;
      }
    }
  }

  if(__client.available()){
    b = __client.read();
    if(b == B10000001 || b == B10000010 || b == B10001010){
      //B10000001 Text frame
      //B10000010 Binary frame
      //B10001010 Pong frame
      switch (b){
        case B10000001:
          Serial.println(F("WebSocket Text Receive*********"));
          _PingLastTime = millis();
          _PongLastTime = millis();
          break;
        case B10000010:
          Serial.println(F("WebSocket Binary Receive*********"));
          ESP32_SPIFFS_EasyWebSocket::EWS_ESP32_Binary_Receive(bin_file);
          _PingLastTime = millis();
          _PongLastTime = millis();
          return "_Binary";
          break;
        case B10001010:
          Serial.println(F("Pong Receive**********"));
          _PongLastTime = millis();
          break;
      }

      b = __client.read();
      data_len = b - B10000000;

      for(i=0; i<4; i++){
        mask[i] = __client.read();
      }

      uint8_t m_data[data_len];
      char data_c[data_len + 1];
          
      for(i = 0; i<data_len; i++){
        m_data[i] = __client.read();
        data_c[i] = mask[i%4]^m_data[i];
      }
      data_c[data_len] = '\0';

      return String(data_c);

    }else if(b == B10001000){
      Serial.println(F("------------------Close Command Received"));
      b = __client.read();
      Serial.println(b,BIN);
      data_len = b - B10000000;
      if(data_len == 0){
        while(__client.available()){
          b = __client.read();
					yield();
        }
        Serial.println(F("Closing HandShake OK!"));
      }else{
        for(i=0; i<4; i++){
          mask[i] = __client.read();
        }

        uint8_t m_data2[data_len];
        char data_c2[data_len + 1];

        for(i = 0; i<data_len; i++){
          m_data2[i] = __client.read();
          data_c2[i] = mask[i%4]^m_data2[i];
          if(i>1){
            Serial.write(data_c2[i]);
          }
        }
        data_c2[data_len] = '\0';
        Serial.println(F("----Closing Message"));
      }    

      delay(1);
      __client.write(B10001000);
      delay(1);
      Serial.println(F("------------------Close Command Send"));

      __client.flush();
      delay(10);
      __client.stop();
      delay(10);
      Serial.println();
      Serial.println(F("------------------Client.STOP"));
      _WS_on = 0;
      _Ini_html_on = 0;
      _Upgrade_first_on = false;

      while(__client){
        if(__client.available()){
          String req = __client.readStringUntil('\n');
          Serial.println(req);
          if(req.indexOf("GET /favicon") != -1){
            Favicon_Response(req, 0, 0, 0);
            break;
          }
        }
				delay(1);
      }

      return str_close;
    }
  }else{
    return String('\0');
  }
  return "";
}
//********************************************************
void ESP32_SPIFFS_EasyWebSocket::EWS_ESP32_Binary_Receive(char bin_file[14])
{
  uint8_t b=0;
  uint8_t data_len;
  uint8_t mask[4];
  uint16_t i;
  uint32_t iii;
  String str_close = "_close";
  String bin_file_str = String(bin_file);

  if(__client.available()){
      if(SPIFFS.remove(bin_file)){
        Serial.print(F("Removed ")); Serial.println(bin_file);
      }else{
        Serial.print(F("Not removed ")); Serial.println(bin_file);
      }
      File B_F = SPIFFS.open(bin_file, FILE_WRITE);

      b = __client.read();
      if(b >= B10000000){
        Serial.println(F("Mask Bit Received--------"));
      }else{
        Serial.println(F("UnMask Bit Received-------"));
      }
      data_len = b - B10000000;
      Serial.print(F("data_len =" ));
      Serial.println(data_len);

      uint8_t data_ext_len[8];
      uint16_t data_len16 = 0;
      uint32_t data_len32 = 0;

      if(data_len == 126){
        __client.read(data_ext_len, 2);
        data_len16 = data_ext_len[0]<<8 | data_ext_len[1];
        Serial.print(F("data_len16 =" ));
        Serial.println(data_len16);
      }else if(data_len ==127){
        __client.read(data_ext_len, 8);
        Serial.println(F("data_ext_len[i]-----------"));
        for(i=0;i<8;i++){
          Serial.println(data_ext_len[i]);
        }
        for(i=4; i<8; i++){
          data_len32 = data_ext_len[i]<<(8*(7-i)) | data_len32;
        }
        //data_len32 = data_ext_len[0]<<56 | data_ext_len[1]<<48 | data_ext_len[2]<<40 | data_ext_len[3]<<32 | data_ext_len[4]<<24 | data_ext_len[5]<<16 | data_ext_len[6]<<8 | data_ext_len[7];
        if(data_len32 >= 0xffffffff){
          Serial.print(F("data_len32 overload!----------"));
        }else{
          Serial.print(F("data_len32 =" ));
          Serial.print(data_len32); //シリアルでは64bitはオーバーロードしてしまうので注意
          Serial.println();
        }
      }

      for(i=0; i<4; i++){
        mask[i] = __client.read();
      }

      uint32_t Max_len;

      if(data_len32 > 0){
        Max_len = data_len32;
      }else if(data_len16>0){
        Max_len = data_len16;
      }else{
        Max_len = data_len;
      }

      uint8_t mbit;
      uint8_t maskP;

      iii = 0;
      for(iii = 0; iii<Max_len; iii++){
        maskP = iii%4;
        mbit = mask[maskP]^__client.read();
        B_F.write(mbit);
      }
      B_F.close();

      Serial.print(F("\ni max = "));
      Serial.println(iii);
  }
}

void ESP32_SPIFFS_EasyWebSocket::EWS_PING_SEND()
{
  __client.write(B10001001);
  __client.write(4);
  __client.print(F("Ping"));
  Serial.println();
  Serial.println(F("Ping Send-----------"));
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Body_style(String text_color, String bg_color)
{
  String str;
  str = "<body style='color:";
  str += text_color;
  str += "; background:";
  str += bg_color;
  str += ";'>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_OnOff_Button(String button_id, uint16_t width, uint16_t height, uint8_t font_size, String f_color, String b_color)
{
  String str;
  str = "<input type='button' value='OFF' onClick=\"OnOffBt(this,'";
  str += button_id;
  str += "');\"";
  str += " style='width:";
  str += String(width);
  str += "px; ";
  str += "height:";
  str += String(height);
  str += "px; font-size:";
  str += String(font_size);
  str += "px; color:";
  str += f_color;
  str += "; background-color:";
  str += b_color;
  str += ";' >\r\n";

  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_On_Momentary_Button(String button_id, String text, uint16_t width, uint16_t height, uint8_t font_size, String f_color, String b_color)
{
  String str;
  str = "<input type='button' value='";
  str += text;
  str += "' onClick=\"doSend(100,'";
  str += button_id;
  str += "'); data_tmp = 0;\"";
  str += " style='width:";
  str += String(width);
  str += "px; ";
  str += "height:";
  str += String(height);
  str += "px; font-size:";
  str += String(font_size);
  str += "px; color:";
  str += f_color;
  str += "; background-color:";
  str += b_color;
  str += ";' >\r\n";

  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Touch_Slider_BT(String slider_id, String vbox_id)
{
  String str;
  str += "<input type='range' ontouchmove=\"doSend(this.value,'";
  str += slider_id;
  str += "'); document.getElementById('";
  str += vbox_id;
  str += "').value=this.value;\">\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Touch_Slider_T(String slider_id, String txt_id)
{
  String str;
  str += "<input type='range' ontouchmove=\"doSend(this.value,'";
  str += slider_id;
  str += "'); document.getElementById('";
  str += txt_id;
  str += "').innerHTML=this.value;\">\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Mouse_Slider_BT(String slider_id, String vbox_id)
{
  String str;
  str += "<input type='range' onMousemove=\"doSend(this.value,'";
  str += slider_id;
  str += "'); document.getElementById('";
  str += vbox_id;
  str += "').value=this.value;\">\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Mouse_Slider_T(String slider_id, String txt_id)
{
  String str;
  str += "<input type='range' onMousemove=\"doSend(this.value,'";
  str += slider_id;
  str += "'); document.getElementById('";
  str += txt_id;
  str += "').innerHTML=this.value;\">\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Sl_BoxText(String vbox_id, uint16_t width, uint16_t height, uint8_t font_size, String color)
{
  String str;
  str = "<input type='number' id='";
  str += vbox_id;
  str += "' style='width:";
  str += String(width);
  str += "px; ";
  str += "height:";
  str += String(height);
  str += "px; font-size:";
  str += String(font_size);
  str += "px; color:";
  str += String(color);
  str += ";' >\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Sl_Text(String text_id, uint8_t font_size, String color)
{
  String str;
  str = "<span id='";
  str += text_id;
  str += "' style='font-size:";
  str += String(font_size);
  str += "px; color:";
  str += String(color);
  str += ";' ></span>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_BrowserReceiveTextTag2(String id, String name, String b_color, uint8_t font_size, String fnt_col)
{
  String str;
  str = "<fieldset style='border-style: solid; border-color:";
	str += b_color;
	str += ";'>\r\n";
  str += "<legend style='font-style: italic; color:";
	str += b_color;
	str += ";'>\r\n";
  str += name;
  str += "</legend><span id='";
  str += id;
  str += "' style='font-size:";
  str += String(font_size);
  str += "px; color:" + fnt_col + ";'></span></fieldset>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Close_Button2(String name, String BG_col, uint16_t width, uint16_t height, String font_col, uint8_t font_size)
{
  String str;
  str = "<input type='button' value='";
  str += name;
  str += "' style='background-color:";
	str += BG_col;
	str += "; width:";
  str += String(width);
  str += "px; height:";
  str += String(height);
  str += "px; color:";
  str += font_col;
  str += "; font-size:";
  str += String(font_size);
  str += "px; border-radius:10px;' onclick='WS_close()'>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Window_ReLoad_Button2(String name, String BG_col, uint16_t width, uint16_t height, String font_col, uint8_t font_size)
{
  String str;
  str = "<input type='button' value='";
  str += name;
  str += "' style='background-color:";
	str += BG_col;
	str += "; width:";
  str += String(width);
  str += "px; height:";
  str += String(height);
  str += "px; color:";
  str += font_col;
  str += "; font-size:";
  str += String(font_size);
  str += "px; border-radius:10px;' onclick='window.location.reload()'>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_WebSocket_Reconnection_Button2(String name, String BG_col, uint16_t width, uint16_t height, String font_col, uint8_t font_size)
{
  String str;
  str = "<input type='button' value='";
  str += name;
  str += "' style='background-color:";
  str += BG_col;
  str += "; width:";
  str += String(width);
  str += "px; height:";
  str += String(height);
  str += "px; color:";
  str += font_col;
  str += "; font-size:";
  str += String(font_size);
  str += "px; border-radius:10px;' onclick='init();'>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_BrowserSendRate()
{
  String str;
  str += "<form name='fRate'>\r\n";
  str += "  <select id='selRate'>\r\n";
  str += "    <option value=0>0ms</option>\r\n";
  str += "    <option value=5>5ms</option>\r\n";
  str += "    <option value=10>10ms</option>\r\n";
  str += "    <option value=15>15ms</option>\r\n";
  str += "    <option value=20>20ms</option>\r\n";
  str += "    <option value=25>25ms</option>\r\n";
  str += "    <option value=30>30ms</option>\r\n";
  str += "    <option value=35>35ms</option>\r\n";
  str += "    <option value=40>40ms</option>\r\n";
  str += "    <option value=45>45ms</option>\r\n";
  str += "    <option value=50>50ms</option>\r\n";
  str += "  </select>\r\n";
  str += "  <input type='button' value='Rate Exec' onclick='onButtonRate();' />\r\n";
  str += "  Browser Transfer Rate= <span id='RateTxt'>0</span>ms\r\n";
  str += "</form>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_ESP32_SendRate(String button_id)
{    
  String str;
  str += "<form name='F_esp32SR'>\r\n";
  str += "  <select id='sel_esp32SR'>\r\n";
  str += "    <option value=0>0ms</option>\r\n";
  str += "    <option value=25>25ms</option>\r\n";
  str += "    <option value=50>50ms</option>\r\n";
  str += "    <option value=75>75ms</option>\r\n";
  str += "    <option value=100>100ms</option>\r\n";
  str += "    <option value=150>150ms</option>\r\n";
  str += "    <option value=200>200ms</option>\r\n";
  str += "    <option value=250>250ms</option>\r\n";
  str += "    <option value=300>300ms</option>\r\n";
  str += "    <option value=500>500ms</option>\r\n";
  str += "    <option value=999>999ms</option>\r\n";
  str += "  </select>\r\n";
  str += "  <input type='button' value='Rate Exec' onclick='doSend(document.F_esp32SR.sel_esp32SR.value,\"";
  str += button_id;
  str += "\"); document.getElementById(\"esp32send_RateTxt\").innerHTML=document.F_esp32SR.sel_esp32SR.value;'>\r\n";
  str += "  ESP32 Transfer Rate= <span id='esp32send_RateTxt'>0</span>ms\r\n";
  str += "</form>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Status_Text2(String name, String b_color, uint8_t font_size, String f_color)
{
  String str;
  str = "<fieldset style='border-style: solid; border-color:";
	str += b_color;
	str += ";'>\r\n";
  str += "<legend style='font-style: italic; color:";
	str += b_color;
	str += ";'>\r\n";
  str += name;
  str += "</legend><span id='__wsStatus__' style='font-size:";
  str += String(font_size);
  str += "px; color:";
  str += f_color;
  str += ";' ></span></fieldset>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_Canvas_Slider_T(String slider_id, uint16_t width, uint16_t height, String frame_col, String fill_col)
{
  String str;
  str = "<canvas id='" + slider_id + "' width='" + String(width) + "' height='" + String(height) + "'></canvas>\r\n";
  
  str += "<script type='text/javascript'>\r\n";
  str += "  fnc_" + slider_id + "();\r\n";
  str += "  function fnc_" + slider_id + "(){\r\n";
  str += "    var c_w = " + String(width) + ";\r\n";
  str += "    var c_h = " + String(height) + ";\r\n";
  str += "    var line_width = 5;\r\n";
  str += "    var canvas2 = document.getElementById('" + slider_id + "');\r\n";
  str += "    var ctx2 = canvas2.getContext('2d');\r\n";
  str += "    ctx2.clearRect(0, 0, c_w, c_h);\r\n";
  str += "    ctx2.beginPath();\r\n";
  str += "    ctx2.lineWidth = line_width;\r\n";
  str += "    ctx2.strokeStyle = '" + frame_col + "';\r\n";
  str += "    ctx2.strokeRect(0,0,c_w,c_h);\r\n";

  str += "    canvas2.addEventListener('touchmove', slider_" + slider_id + ", false);\r\n";
  str += "    canvas2.addEventListener('touchstart', slider_" + slider_id + ", false);\r\n";
  
  str += "    function slider_" + slider_id + "(event3) {\r\n";
  str += "      event3.preventDefault();\r\n";
  str += "      event3.stopPropagation();\r\n";
  str += "      var evt555=event3.touches[0];\r\n";
  str += "      var OffSet2 = evt555.target.getBoundingClientRect();\r\n";
  str += "      var ex = evt555.clientX - OffSet2.left;\r\n";
  str += "      if( ex < 0 ){ex = 0;}\r\n";
  str += "      else if(ex>c_w){ex = c_w;}\r\n";
  str += "      var e_cl_X = Math.floor(ex);\r\n";
  str += "      ctx2.clearRect(0, 0, c_w, c_h);\r\n";
  str += "      ctx2.beginPath();\r\n";
  str += "      ctx2.fillStyle = '" + fill_col + "';\r\n";
  str += "      ctx2.rect(0,0, e_cl_X, c_h);\r\n";
  str += "      ctx2.fill();\r\n";
  str += "      ctx2.beginPath();\r\n";
  str += "      ctx2.lineWidth = line_width;\r\n";
  str += "      ctx2.strokeStyle = '" + frame_col + "';\r\n";
  str += "      ctx2.strokeRect(0,0,c_w,c_h);\r\n";
  str += "      doSend(String(e_cl_X), '" + slider_id + "');\r\n";
  str += "    };\r\n";
  str += "  };\r\n";
  str += "</script>\r\n";
  return str;
}

String ESP32_SPIFFS_EasyWebSocket::EWS_TextBox_Send(String id, String txt, String BT_txt)
{
  String str;
  str = "<form>\r\n";
  str += "<input type='text' id='" + id + "' value='" + txt + "'>\r\n";
  str += "<input type='button' value='" + BT_txt + "' onclick='doSend_TextBox(\"" + id + "\");'>\r\n";
  str += "</form>\r\n";
  return str;
}

bool ESP32_SPIFFS_EasyWebSocket::HTTP_SPIFFS_Pic_Send(const char* Serv, const char* dir)
{
  String req = "";
  uint8_t b;
  uint8_t data_len;
  uint8_t mask[4];
  uint16_t i;
  uint32_t iii;
  String cut_str = " HTTP/1.1";
  bool ret_send = false;

  if(!_WS_on){
    handleClient();
  }

  while(__client){
    if(__client.available()){
      b = __client.read();
      if(b == B10000001 || b == B10000010 || b == B10001010 || b == B10001000){
        //B10000001 Text frame
        //B10000010 Binary frame
        //B10001010 Pong frame
        switch (b){
          case B10000001:
            Serial.println(F("WebSocket Text Receive*********"));
            _PingLastTime = millis();
            _PongLastTime = millis();
            break;
          case B10000010:
            Serial.println(F("WebSocket Binary Receive*********"));
            _PingLastTime = millis();
            _PongLastTime = millis();
            break;
          case B10001010:
            _PongLastTime = millis();
            Serial.println(F("Pong Receive**********"));
            break;
          case B10001000:
            Serial.println(F("----------------HTTP_SPIFFS_Pic_Send Close Command Received"));
            _PingLastTime = millis();
            _PongLastTime = millis();
            break;
        }

        b = __client.read();
        if(b >= B10000000){
          Serial.println(F("Mask Bit Received--------"));
        }else{
          Serial.println(F("UnMask Bit Received-------"));
        }
        data_len = b - B10000000;
        Serial.print(F("data_len =" ));
        Serial.println(data_len);

        for(i=0; i<4; i++){
          mask[i] = __client.read();
        }

        uint8_t mbit;
        uint8_t maskP;

        iii = 0;
        for(iii = 0; iii<data_len; iii++){
          maskP = iii%4;
          mbit = mask[maskP]^__client.read();
          if(iii>1){
            Serial.write(mbit);
          }
					yield();
        }
        Serial.println(F("----Closing Message"));
        Serial.println();
        while(__client.available()){
          Serial.println(__client.read());
					yield();
        }

        __client.flush();
        delay(10);
        __client.stop();
        delay(10);
        Serial.println();
        Serial.println(F("------------------Client.STOP"));

        _WS_on = 0;
        _Ini_html_on = 0;
        _Upgrade_first_on = false;
      }

      while(__client){
        if(__client.available()){
          req = __client.readStringUntil('\n');
          if(req != "") Serial.println(req);
          if(req.indexOf(dir) > 0){
            Serial.println(req);
            String file_path = req.substring(req.indexOf(dir), req.indexOf(cut_str));
            while(__client.available()){
              Serial.write(__client.read());
							delay(1);
            }
            Serial.print(F("--------------")); Serial.print(file_path); Serial.println(F(" open & send\n"));

            req = "";

            __client.print(F("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n"));
            __client.print(F("Connection:close\r\n\r\n"));
            File jpeg_F = SPIFFS.open(file_path, FILE_READ);
            //size_t totalSize = jpeg_F.size();

            char* c_fpath = 0;
            file_path.toCharArray(c_fpath, file_path.length());

            ESP32_SPIFFS_EasyWebSocket::SPIFFS_Client_Write(jpeg_F, c_fpath);

            jpeg_F.close();

            __client.flush();
            delay(10);
            __client.stop();
            delay(10);
            Serial.println(F("\n--------------------GET JPEG HTTP client stop"));
            req = "";
            file_path = "";
            _WS_on = 0;
            _Ini_html_on = 0;
            _Upgrade_first_on = false;
            return true;
          }
        }
				yield();
      }
    }
		yield();
  }
  return ret_send;
}
void ESP32_SPIFFS_EasyWebSocket::Favicon_Response(String str, uint8_t ws, uint8_t ini_htm, uint8_t up_f)
{
  Serial.println(F("-----------------------Favicon GET Request Received"));
  Serial.println(str);
  while(__client.available()){
    Serial.write(__client.read());
		yield();
  }
  delay(1);

  __client.print(F("HTTP/1.1 404 Not Found\r\n"));
  __client.print(F("Connection:close\r\n\r\n"));

  __client.flush();
  delay(10);
  __client.stop();
  delay(10);

  Serial.println(F("-----------------Client.stop (by Favicon Request)"));

  switch(ws){
    case 1:
      _WS_on = 1;
      break;
    case 2:
      _WS_on = 0;
      break;
  }
  switch(ini_htm){
    case 1:
      _Ini_html_on = 1;
      break;
    case 2:
      _Ini_html_on = 0;
      break;
  }
  switch(up_f){
    case 1:
      _Upgrade_first_on = true;
      break;
    case 2:
      _Upgrade_first_on = false;
      break;
  }
}
//************** mbedtls sha1 *****************************************
void ESP32_SPIFFS_EasyWebSocket::sha1( String str_data, uint8_t hash[20] ){
  mbedtls_sha1_context ctx;
  uint8_t *data = (uint8_t *)str_data.c_str();

  mbedtls_sha1_starts(&ctx);
  mbedtls_sha1_update(&ctx, data, str_data.length());
  mbedtls_sha1_finish(&ctx, hash);
}
//*****************************************
uint8_t ESP32_SPIFFS_EasyWebSocket::WebSocket_Status(){
  return _WS_on;
}
//**************************************************************
String ESP32_SPIFFS_EasyWebSocket::Color_Picker(uint16_t top_px, uint16_t left_px, String default_col, String ID){
  String str = "";

  str += "<div style='position: relative; top:";
  str += String(top_px);
  str += "px; left:";
  str += String(left_px);
  str += "px; width:50px; height:0px'>\r\n";
  str += "<input type='color' value='" + default_col + "' id='" + ID +"' ";
  str += "onchange='Color_Picker_Send(100, \"" + ID + "\", this.value);'>\r\n";
  str += "</div>\r\n";

  return str;
}