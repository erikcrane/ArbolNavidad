/*
 * Uso de protothreads para: 
 *      emitir sonido por buzzer
 *      encender luces
 *      leer pulsador
 * Utilizare la funcion tone() para generar el sonido por el buzzer
 */
#include <Wire.h>
#include <pt.h>
#include <timer.h>

#define BUZZER 9
#define TEMPO 200
#define ESPACIO 0
#define C 261
#define D 293
#define E 329
#define F 349
#define G 392

int freq[] = {E, E, E, E, E, E, E, G, C, D, E, ESPACIO, F, F, F, F, F, E, E, E, E, D, D, E, D, G};
int duration[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
int i, y = 0;
uint8_t leds = B11111111;
uint8_t add = B111000;
int play = 1;
static struct pt ptJingle, ptLight, ptButton;
static struct timer tLed, tSong, tButton;

int valorBoton = 1;
int botonApretado = 1;
int valorBotonNuevo = 1;

void transmitData(uint8_t data){
  Wire.beginTransmission(add);
  Wire.write(data);
  Wire.endTransmission();
}

static PT_THREAD(protothreadJingle (struct pt *pt)){
  PT_BEGIN(pt);
  while(play){
    if(freq[i] != 0){
      tone(BUZZER, freq[i], duration[i]*TEMPO);
      timer_set(&tSong, duration[i]*2*TEMPO);
    }else{
      timer_set(&tSong, duration[i]*TEMPO);
    }
    i++;
    if(i == sizeof(duration)/sizeof(int)) i = 0;
    PT_WAIT_UNTIL(pt, timer_expired(&tSong));
  }
  PT_END(pt);
}
static PT_THREAD (protothreadLights (struct pt *pt)){
  PT_BEGIN(pt);
  while(leds > B00000000){
    transmitData(leds);
    leds <<= 1;
    timer_set(&tLed, 100);
    PT_WAIT_UNTIL(pt, timer_expired(&tLed));
    if(leds == B00000000){
      transmitData(leds);
      timer_set(&tLed, 100);
      PT_WAIT_UNTIL(pt, timer_expired(&tLed));
    }
  }
  leds = B01111111;
  while(leds > B00000000){
    transmitData(leds);
    leds >>= 1;
    timer_set(&tLed, 100);
    PT_WAIT_UNTIL(pt, timer_expired(&tLed));
    if(leds == B00000000){
      transmitData(leds);
      timer_set(&tLed, 100);
      PT_WAIT_UNTIL(pt, timer_expired(&tLed));
    }
  }
  y=0;
  while(y<5){
    leds = B11111111;
    transmitData(leds);
    timer_set(&tLed, 300);
    PT_WAIT_UNTIL(pt, timer_expired(&tLed));
    leds = B00000000;
    transmitData(leds);
    timer_set(&tLed, 300);
    PT_WAIT_UNTIL(pt, timer_expired(&tLed));
    y++;
  }
  y=0;
  while(y<random(40,80)){
    leds = random(0,255);
    transmitData(leds);
    y++;
    timer_set(&tLed, 100);
    PT_WAIT_UNTIL(pt, timer_expired(&tLed));
  }
  leds = B11111111;
  PT_END(pt);  
}
static PT_THREAD(protothreadButton (struct pt *pt)){
  PT_BEGIN(pt);
  while(1){
    timer_set(&tButton, 50);
    PT_WAIT_UNTIL(pt, timer_expired(&tButton));
    valorBoton = PINB & 1;
    if(valorBoton == 0){
      timer_set(&tButton, 100);
      PT_WAIT_UNTIL(pt, timer_expired(&tButton));
    }
    valorBotonNuevo = PINB & 1;
    if(valorBotonNuevo == 0){
      botonApretado = 0;
    }
    if(botonApretado == 0 && valorBotonNuevo == 1){
      play = !play;
      //PORTB ^= 1 << 5;
      botonApretado = 1;
    }
  }
  PT_END(pt);
}
void setup() {
  PT_INIT(&ptJingle);
  PT_INIT(&ptLight);
  PT_INIT(&ptButton);

  Wire.begin();
  DDRB = B00100010;
  //DDRB |= B00000010;
  //DDRB &= B11111110;
  //Serial.begin(9600);
}

void loop() {
  protothreadJingle(&ptJingle);
  protothreadLights(&ptLight);
  protothreadButton(&ptButton);
}
