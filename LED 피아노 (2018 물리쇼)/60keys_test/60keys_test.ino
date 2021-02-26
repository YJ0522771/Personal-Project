
#include <math.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <CapacitiveSensor.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define KEYS 60
#define CAP_SENDPIN 53;
#define CAP_TH 450
#define LEDPIN 10

boolean isChanged(uint8_t a[60], uint8_t b[60]);
int Red(uint16_t waveLength);
int Green(uint16_t waveLength);
int Blue(uint16_t waveLength);
uint16_t freq_to_waveleng(uint16_t f);


//char piano[12] = {'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'G', 'A', 'A', 'B'};


CapacitiveSensor cs0 = CapacitiveSensor(53, 51);
CapacitiveSensor cs1 = CapacitiveSensor(53, 49);
CapacitiveSensor cs2 = CapacitiveSensor(53, 47);
CapacitiveSensor cs3 = CapacitiveSensor(53, 45);
CapacitiveSensor cs4 = CapacitiveSensor(53, 43);
CapacitiveSensor cs5 = CapacitiveSensor(53, 41);
CapacitiveSensor cs6 = CapacitiveSensor(53, 39);
CapacitiveSensor cs7 = CapacitiveSensor(53, 37);
CapacitiveSensor cs8 = CapacitiveSensor(53, 35);
CapacitiveSensor cs9 = CapacitiveSensor(53, 33);
CapacitiveSensor cs10 = CapacitiveSensor(53, 31);
CapacitiveSensor cs11 = CapacitiveSensor(53, 29);

uint8_t cap_State[60] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t last_State[60] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Adafruit_MPR121 mpr1 = Adafruit_MPR121();
Adafruit_MPR121 mpr2 = Adafruit_MPR121();
Adafruit_MPR121 mpr3 = Adafruit_MPR121();
Adafruit_MPR121 mpr4 = Adafruit_MPR121();

uint16_t lasttouched[4] = {0, 0, 0, 0};
uint16_t currtouched[4] = {0, 0, 0, 0};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, LEDPIN, NEO_GRB + NEO_KHZ800);

uint8_t count = 0;    ////////눌려있는 건반 수
uint16_t frequency[60] = {65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 124, 
                          131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 
                          262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 
                          523, 554, 587, 622, 659, 699, 740, 784, 831, 880, 932, 988, 
                          1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976};

                          

void setup() {
  Serial.begin(9600);

  mp3_set_serial (Serial);  
  delay(1);  
  mp3_set_volume (15);

  while (!Serial) {
    delay(10);
  }

  if (!mpr1.begin(0x5A)) {
    while (1);
  }
  Serial.println("MPR121_1 found!");

  if (!mpr2.begin(0x5B)) {
    while (1);
  }
  Serial.println("MPR121_2 found!");

  if (!mpr3.begin(0x5C)) {
    while (1);
  }
  Serial.println("MPR121_3 found!");

  if (!mpr4.begin(0x5D)) {
    while (1);
  }
  Serial.println("MPR121_4 found!");

  randomSeed(analogRead(A0));  

  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  pixels.show();
}

void loop() {
  long Direct_CapSensor[12];                      ///////////////////////////직접 연결한 센서

  Direct_CapSensor[0] = cs0.capacitiveSensorRaw(30);
  Direct_CapSensor[1] = cs1.capacitiveSensorRaw(30);
  Direct_CapSensor[2] = cs2.capacitiveSensorRaw(30);
  Direct_CapSensor[3] = cs3.capacitiveSensorRaw(30);
  Direct_CapSensor[4] = cs4.capacitiveSensorRaw(30);
  Direct_CapSensor[5] = cs5.capacitiveSensorRaw(30);
  Direct_CapSensor[6] = cs6.capacitiveSensorRaw(30);
  Direct_CapSensor[7] = cs7.capacitiveSensorRaw(30);
  Direct_CapSensor[8] = cs8.capacitiveSensorRaw(30);
  Direct_CapSensor[9] = cs9.capacitiveSensorRaw(30);
  Direct_CapSensor[10] = cs10.capacitiveSensorRaw(30);
  Direct_CapSensor[11] = cs11.capacitiveSensorRaw(30);

  for(uint8_t i = 0; i < 12; i++) {
    if(Direct_CapSensor[i] >= CAP_TH && !cap_State[i]) {
      Serial.print(i); Serial.println(" touched");
      cap_State[i] = 1;
      //mp3_play(i);

      
    }
    if(Direct_CapSensor[i] < CAP_TH && cap_State[i]) {
      Serial.print(i); Serial.println(" released");
      cap_State[i] = 0;
      //mp3_stop();
      
    }
  }
    
  currtouched[0] = mpr1.touched();                  //////////////////////////////MPR121 사용한 센서
  currtouched[1] = mpr2.touched();
  currtouched[2] = mpr3.touched();
  currtouched[3] = mpr4.touched();

  for(uint8_t j = 0; j < 4; j++) {
    for (uint8_t i = 0; i < 12; i++) {
      if ((currtouched[j] & _BV(i)) && !(lasttouched[j] & _BV(i)) ) {
        Serial.print((j+1)*12 + i); Serial.println(" touched");
        cap_State[(j+1)*12 + i] = 1;
        //mp3_play((j+1)*12 + i);

        
      }
      if (!(currtouched[j] & _BV(i)) && (lasttouched[j] & _BV(i)) ) {
        Serial.print((j+1)*12 + i); Serial.println(" released");
        cap_State[(j+1)*12 + i] = 0;
        //mp3_stop();
        
      }
    }
  }

  lasttouched[0] = currtouched[0];
  lasttouched[1] = currtouched[1];
  lasttouched[2] = currtouched[2];
  lasttouched[3] = currtouched[3];

  /*
  boolean print_state = false;
  
  for(uint8_t j = 0; j < 5; j++) {                   /////////////////////////////////////터치 중인 계이름 출력
    for (uint8_t i = 0; i < 12; i++) {
      if(cap_State[j*12 + i]) {  
        if(!print_state) {
          print_state = true; }
        
        Serial.print(piano[i]); Serial.print(j+2);
        if(i==1 || i==3 || i==6 || i==8 || i==10) {
          Serial.print("#");
        }
        Serial.print(" ");
      }
    }
  }
  if(print_state) {
    Serial.println(); 
  }
  */
   
  if(isChanged(cap_State, last_State)) {                //////////////////건반에 변화가 있을 때만 LED 조정
    //Serial.println("ture");
    count = 0;
    for(uint8_t i = 0; i < 60; i++) {
      if(cap_State[i]) {count++; }
      if(count == 16) { break; }
    }

    if(count == 0) {                                  ///////////////////전부 꺼짐
      for(uint8_t i = 0; i < 16; i++) {
        pixels.setPixelColor(i, pixels.Color(0,0,0)); 
        pixels.show(); 
      }

      for(uint8_t i = 0; i < 60; i++) {
        last_State[i] = cap_State[i];
      }
      
      return;
    }
    
    uint8_t LEDnum_one = 16 / count;
    uint16_t temp = count * LEDnum_one;
    uint8_t LEDnum[60] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for(uint8_t i = 0; i < 60; i++) {
      if(cap_State[i]) { LEDnum[i] = LEDnum_one; }
    }
    while(temp != 16) {
      for(uint8_t i = 0; i < 60; i++) {
        if(LEDnum[i] == LEDnum_one && rand()%2) {
          LEDnum[i]++;
          temp++;
        }
      }
    }

    uint8_t currentLED[16] = {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};

    for(uint8_t i = 0; i < 60; i++) {
      if(cap_State[i]) {
        for(uint8_t j = 0; j < LEDnum[i]; j++) {
          temp = rand() % 16;
          if(currentLED[temp] != 60) {
            j--;
          } else {
            currentLED[temp] = i;
          }
        }
      }
    }
   
    for(uint8_t i = 0; i < 16; i++) {
      //Serial.print(currentLED[i]); Serial.print(" ");
      temp = freq_to_waveleng(frequency[currentLED[i]]);
      int R, G, B;
      R = Red(temp);
      G = Green(temp);
      B = Blue(temp);
      pixels.setPixelColor(i, pixels.Color(R, G, B));  
      pixels.show();

      //Serial.print(temp); Serial.print(" ");
      //Serial.print(R); Serial.print(" ");
      //Serial.print(G); Serial.print(" ");
      //Serial.print(B); Serial.print(" ");
      //Serial.println();
    }
    
    //Serial.println();
    
    
  

  for(uint8_t i = 0; i < 60; i++) {
      last_State[i] = cap_State[i];
    }
  }
    
  delay(50);
  return;

}

boolean isChanged(uint8_t a[60], uint8_t b[60]) {
  for(uint8_t i = 0; i < 60; i++) {
    if(a[i] != b[i]) {
      return true;
    }
  }
  return false;
}

int Red(uint16_t waveLength) {
  if (waveLength <= 400) {
    return (int)(5.1913*waveLength - 1819.6);
  } else if (waveLength <= 467) {
    return (int)(-3.7849*waveLength + 1768.2);
  } else if (waveLength <= 550) {
    return 0;
  } else if (waveLength <= 588) {
    return (int)(6.8134*waveLength - 3751.1);
  } else if (waveLength <= 650) {
    return 255;
  } else {
    return (int)(-5.031*waveLength + 3526.2);
  }
}

int Green(uint16_t waveLength) {
  if (waveLength <= 467) {
    return 0;
  } else if (waveLength <= 510) {
    return (int)(5.7899*waveLength - 2702.4);
  } else if (waveLength <= 588) {
    return 255;
  } else if (waveLength <= 650) {
    return (int)(-4.1387*waveLength + 2690.2);
  } else {
    return 0; 
  }
}

int Blue(uint16_t waveLength) {
  if (waveLength <= 400) {
    return (int)(5.1974*waveLength - 1822);
  } else if (waveLength <= 510) {
    return 255;
  } else if (waveLength <= 550) {
    return (int)(-6.4625*waveLength + 3553.7);
  } else {
    return 0;
  }
}

uint16_t freq_to_waveleng(uint16_t f) {
  return (uint16_t)(1040-(64.9615*(log10(f)/log10(2)) - 31.222));
}
