#include <TinyWireM.h>
//#include <avr/pgmspace.h>


#define BUZZER 1
#define TEMPO 100
#define ESPACIO 0

#define F3  174
#define G3  196
#define A3  220
#define BB3 233
#define C4  261
#define DB4 277
#define D4  293
#define EB4 311
#define E4  329
#define F4  349
#define GB4 369
#define G4  391
#define AB4 415
#define A4  440
#define BB4 466
#define B4  493
#define C5  523
#define DB5 554
#define D5  587

#define ENCENDIDO_PROGRESIVO  0
#define ENCENDIDO_PROG_INV    1
#define APAGADO_ENCENDIDO     2
#define ALEATORIO             3

#define JINGLE    0
#define MERRY     1
#define RUDOLPH   2
#define JOYWORLD  3


const int jingleFreq[] PROGMEM = {E4, E4, E4, E4, E4, E4, E4, G4, C4, D4, E4, ESPACIO, F4, F4, F4, F4, F4, E4, E4, E4, E4, D4, D4, E4, D4, G4, ESPACIO};
const int jingleDuration[] PROGMEM = {2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 2};
const int jingletDelay[]  PROGMEM = {4, 4, 8, 4, 4, 8,4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 2};
const int wewishFreq[] PROGMEM = {EB4, AB4, AB4, BB4, AB4, G4, F4, F4, F4,BB4, BB4, C5, BB4, AB4, G4, EB4, EB4, C5, C5, DB5, C5, BB4, AB4, F4, EB4, EB4, F4, BB4, G4, AB4, ESPACIO};
const int wewishDuration[] PROGMEM = {3, 3, 1, 1, 1, 1, 3, 2, 3, 3, 1, 1, 1, 1, 3, 2, 3, 3, 1, 1, 1, 1, 3, 2, 1, 1, 2, 2, 2, 6, 2};
const int wewishtDelay[] PROGMEM ={4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 2, 2, 4, 4, 4, 8, 2};
// int wewishDuration[] = {3.7, 3.7, 1.8, 1.8, 1.8, 1.8, 3.7, 2.8, 3.7, 3.7, 1.8, 1.8, 1.8, 1.8, 3.7, 2.8, 3.7, 3.7, 1.8, 1.8, 1.8, 1.8, 3.7, 2.8, 1.8, 1.8, 2.8, 2.8, 2.8, 6.5};
// int wewishtDelay[] ={4.1, 4.1, 2, 2, 2, 2, 4.1, 4.1, 4.1, 4.1, 2, 2, 2, 2, 4.1, 4.1, 4.1, 4.1, 2, 2, 2, 2, 4.1, 4.1, 2, 2, 4.1, 4.1, 4.1, 8.3};
const int rudolphFreq[] PROGMEM ={G4, A4, G4, E4, C5, A4, G4, G4, A4, G4, A4, G4, C5, B4, F4, G4, F4, D4, B4, A4, G4, G4, A4, G4, A4, G4, A4, E4, ESPACIO};
const int rudolphDuration[] PROGMEM ={2, 2, 4, 4, 4, 4, 12, 2, 2, 2, 2, 4, 4, 15, 2, 2, 4, 4, 4, 4, 12, 2, 2, 2, 2, 4, 4, 15, 2};
const int rudolphtDelay[] PROGMEM ={2, 2, 4, 4, 4, 4, 13, 2, 2, 2, 2, 4, 4, 17, 2, 2, 4, 4, 4, 4, 13, 2, 2, 2, 2, 4, 4, 17, 2};
// int rudolphDuration[] ={1.9, 1.9, 3.8, 3.8, 3.8, 3.8, 11.6, 1.9, 1.9, 1.9, 1.9, 3.8, 3.8, 15.5, 1.9, 1.9, 3.8, 3.8, 3.8, 3.8, 11.6, 1.9, 1.9, 1.9, 1.9, 3.8, 3.8, 15.5};
// int rudolphtDelay[] ={2.1, 2.1, 4.3, 4.3, 4.3, 4.3, 12.9, 2.1, 2.1, 2.1, 2.1, 4.3, 4.3, 17.2, 2.1, 2.15, 4.3, 4.3, 4.3, 4.3, 12.9, 2.1, 2.1, 2.1, 2.1, 4.3, 4.3, 17.2};
const int joyworldFreq[] PROGMEM ={D5, DB5, B4, A4, G4, GB4, E4, D4, A4, B4, B4, DB5, DB5, D5, D5, D5, DB5, B4, A4, A4, G4, GB4, D5, D5, DB5, B4, A4, A4, G4, GB4, GB4, GB4, GB4, GB4, GB4, G4, A4, G4, GB4, E4, E4, E4, E4, GB4, G4, GB4, E4, D4, GB4, G4, A4, G4, GB4, G4, GB4, E4, ESPACIO};
const int joyworldDuration[] PROGMEM ={5, 4, 1, 8, 3, 5, 5, 8, 3, 8, 3, 8, 3, 8, 3, 3, 3, 3, 3, 4, 1, 3, 3, 3, 3, 3, 3, 4, 1, 3, 3, 3, 3, 3, 1, 1, 8, 1, 1, 3, 3, 3, 1, 1, 8, 1, 1, 3, 5, 3, 4, 1, 3, 3, 5, 5, 2};
const int joyworldtDelay[] PROGMEM ={6, 4, 1, 9, 3, 6, 6, 9, 3, 9, 3, 9, 3, 9, 3, 3, 3, 3, 3, 4, 1, 3, 3, 3, 3, 3, 3, 4, 1, 3, 3, 3, 3, 3, 1, 1, 9, 1, 1, 3, 3, 3, 1, 1, 9, 1, 1, 3, 6, 3, 4, 1, 3, 3, 6, 6, 2};

uint8_t song = 0;
uint8_t musica = 1;
long tLights, tBuzzer, tButton;
uint8_t nota = 0;

long tDelay(long timeAcumulated){
  return millis() - timeAcumulated;
}
void transmitData(uint8_t data){
  uint8_t add = B111000;
  static uint8_t ledsSent = B00000000;

  if(ledsSent != data){
    TinyWireM.beginTransmission(add);
    TinyWireM.write(data);
    TinyWireM.endTransmission();
    ledsSent =  data;
    tLights = millis();
  }
}
void lights(){
  static uint8_t counter = 0;
  static uint8_t effect = 0;
  static uint8_t leds = B11111111;

  switch(effect){
    case ENCENDIDO_PROGRESIVO:{
      transmitData(leds);
      if(tDelay(tLights) > 100){
        if(leds != B00000000){
          leds <<= 1;
        }else{
          leds = B11111111;
          effect ++;
        }
      }
    }break;
    case ENCENDIDO_PROG_INV:{
      transmitData(leds);
      if(tDelay(tLights) > 100){
        if(leds != B00000000){
          leds >>= 1;
        }else{
          leds = B11111111;
          effect ++;
        }
      }
    }
    break;
    case APAGADO_ENCENDIDO:{
      if(counter < 10){
        transmitData(leds);

        if(tDelay(tLights) > 300){
          if(leds == B00000000){
            leds = B11111111;
          }else{
            leds = B00000000;
          }
          counter ++;
        }
      }else{
        leds = B11111111;
        counter = 0;
        effect ++;
      }
    }break;
    case ALEATORIO:{
      if(counter < random(40,80)){
        transmitData(leds);

        if(tDelay(tLights) > 100){
          leds = random(0,255);
          counter ++;
        }
      }else{
        counter = 0;
        effect = 0;
        leds = B11111111;
      }
    }break;
  }
}

void nextSong(){
  if(song == 3){
    song = 0;
  }else{
    song ++;
  }
  nota = 0;
  tBuzzer = 0;
}
void playMusic(int freq[], int duration[], int tdelay[], int tamano){
  static uint8_t notaAnterior = 0;

  if(nota < tamano){
    if(notaAnterior == nota){
      tone(BUZZER, pgm_read_word(&freq[nota]), pgm_read_word(&duration[nota])*TEMPO);
      tBuzzer = millis();
      nota++;
    }
    if(tDelay(tBuzzer) > pgm_read_word(&tdelay[notaAnterior])*TEMPO){
      notaAnterior = nota;
    }
  }else{
    nextSong();
  }
}
void music(){
  
  switch(song){
    case JINGLE:{
      playMusic(jingleFreq, jingleDuration, jingletDelay, sizeof(jingleFreq)/sizeof(int));
    }break;
    case MERRY:{
      playMusic(wewishFreq, wewishDuration, wewishtDelay, sizeof(wewishFreq)/sizeof(int));
    }break;
    case RUDOLPH:{
      playMusic(rudolphFreq, rudolphDuration, rudolphtDelay, sizeof(rudolphFreq)/sizeof(int));
    }break;
    case JOYWORLD:{
      playMusic(joyworldFreq, joyworldDuration, joyworldtDelay, sizeof(joyworldFreq)/sizeof(int));
    }break;
  }
}
void button(){
  static uint8_t botonNoFiltrado = 1;
  static uint8_t botonNoFiltradoAnt = 1;
  static uint8_t botonFiltrado = 1;
  static uint8_t botonFiltradoAnt = 1;
  static long tiempo = 0;
  static long tiempo2 = 0;
  static long duracionPulso = 0;

  botonNoFiltrado = PINB & B00001000;
  if(botonNoFiltrado != botonNoFiltradoAnt){
    tiempo = millis();
    botonNoFiltradoAnt = botonNoFiltrado;
  }
  if(millis() - tiempo > 50 && botonFiltrado != botonNoFiltrado){
    botonFiltrado = botonNoFiltrado;
  }
  
  if(botonFiltrado != botonFiltradoAnt){
    if(botonFiltrado == 0){
      tiempo2 = millis();
    }else{
      duracionPulso = millis() - tiempo2;
    }
    if(duracionPulso > 1000){
      musica = !musica;
    }
    if(duracionPulso > 0 && duracionPulso < 1000){
      nextSong();
    }
    botonFiltradoAnt = botonFiltrado;
    duracionPulso = 0;
  }
}
void setup() {
  TinyWireM.begin();
  DDRB |= B00000010;
  DDRB &= B11110111;
}

void loop() {
  lights();
  if(musica == 1)
    music();
  button();
}
