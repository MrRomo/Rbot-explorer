#include "FS.h"
#include <SPIFFS.h>
 
//********************************************************************
void setup() {  
  Serial.begin(115200);
  Serial.println("----------------------");
 
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
 
  Serial.printf("Flash Chip Size = %d byte\r\n", ESP.getFlashChipSize());
 
  delay(100);
 
  //deleteFile(SPIFFS, "/xxx.txt");
 
  listDir(SPIFFS, "/", 0); //SPIFFSフラッシュ　ルートのファイルリスト表示
 
  SPIFFS.end();
}
//********************************************************************
void loop() {
 
}
//********************************************************************
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);
 
    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }
 
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
//********************************************************************
void deleteFile(fs::FS &fs, const char * path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}
