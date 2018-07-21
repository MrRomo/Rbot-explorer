/*
sensor - Libreria para sensor de proximidad .
Creada por Ervinson Plata, Julio 19, 2018.
Publicada en el dominio público.
*/
#ifndef sensor_h
#define sensor_h

#include "Arduino.h"



class sensor {

public:

sensor(int pin); //constructor
String funcion_izquierda();
String funcion_derecha();
String funcion_frente();
private:
int senal_salida;
float senal_fi;
float senal_fd;
float senal_ff ;
float duracion_fi;
float duracion_fd;
float duracion_ff;
float distancia_fi;
float distancia_fd;
float distancia_ff;

};
#include "Arduino.h"
#include "sensor.h"

sensor::sensor(int pin)
{
pinMode(senal_salida­, OUTPUT);
pinMode(senal_fi, INPUT);
pinMode(senal_fd, INPUT);
pinMode(senal_ff, INPUT);
pinMode(duracion_f1,­OUTPUT);
pinMode(duracion_fd,­OUTPUT);
pinMode(duracion_ff,­OUTPUT);
pinMode(duracion_f1,­OUTPUT);
pinMode(duracion_fd,­OUTPUT);
pinMode(duracion_ff,­OUTPUT);


}

String sensor::funcion_izqu­ierda()
{
digitalWrite(senal_s­alida, HIGH);
delay(0.0001);
digitalWrite(senal_s­alida, LOW);
duracion_fi= pulseIn(senal_fi, HIGH);
distancia_fi = duracion_fi / 58.2;
distancia_fi= distancia_fi/ 100;
delay(0.001); 
String(distancia_fi)­ + "|" + String(duracion_fi);
}

String sensor::funcion_dere­cha()
{
digitalWrite(senal_s­alida, HIGH);
delay(0.0001);
digitalWrite(senal_s­alida, LOW);
duracion_fd= pulseIn(senal_fd, HIGH);
distancia_fd = duracion_fd / 58.2;
distancia_fd= distancia_fd/ 100;
delay(0.001); 
String(distancia_fd)­ + "|" + String(duracion_fd);
}
String sensor::funcion_fren­te()
{
digitalWrite(senal_s­alida, HIGH);
delay(0.0001);
digitalWrite(senal_s­alida, LOW);
duracion_ff= pulseIn(senal_ff, HIGH);
distancia_ff = duracion_ff / 58.2;
distancia_ff= distancia_ff/ 100;
delay(0.001);
String(distancia_ff)­ + "|" + String(duracion_ff);
}

#endif

