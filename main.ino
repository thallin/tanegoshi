#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


const int pinBuzzer = 2;
const int verde = 4;
const int azul = 3;
const int vermelho = 5;
int compasso = 900;

// Jingle Bells
 
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};
 
int tempo[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};
 
// We wish you a merry Christmas
 
int wish_melody[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};
 
int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};
 
// Santa Claus is coming to town
 
int santa_melody[] = {
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};
 
int santa_tempo[] = {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
};

//Mario main theme melody
int mario_melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int mario_tempo[] = {
  9, 9, 9, 10,
  10, 13, 15, 10,
  10, 10, 9, 9,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
//Choro da planta
int choro_melody[] = {
  NOTE_C5,NOTE_G4,NOTE_E4,NOTE_A4,NOTE_B4,NOTE_A4,NOTE_GS4,NOTE_AS4, NOTE_GS4,NOTE_E4,NOTE_D4,NOTE_E4 
};
//Choro da planta tempo
int choro_tempo[] = {
  4,4,4,9,9,8,9,9,8,12,12,4 
};

int ldrValor1 = 0;
int ldrValor2 = 0;
int ldrValor3 = 0;
int soilValor = 0;
int cont = 0;

void setup() {
  pinMode(pinBuzzer, OUTPUT); // Buzzer
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(azul, OUTPUT);
  ligaAzul();
  sing(6);
  Serial.begin(9600); //Inicia a comunicação serial
}

void loop() {
  cont++;
  if(cont<=10){
    ldrValor1 += analogRead(0);
    ldrValor2 += analogRead(1);
    ldrValor3 += analogRead(2);
    soilValor += analogRead(3);
  }else{ 
    /*
    *Dry: (520 430]
    *Wet: (430 350]
    *Water: (350 260]
    */   
    int ldrValor = (ldrValor1/10 + ldrValor2/10 + ldrValor3/10)/3;
    if(soilValor/10 >= 350 && soilValor/10 < 430){
      ligaVerde();
    }else if(soilValor/10 >= 430 || soilValor/10 < 350){
      ligaVermelho();
    }
    Serial.print(ldrValor);
    Serial.print(" Solo: ");
    Serial.println(soilValor/10);
    ldrValor1 = 0;
    ldrValor2 = 0;
    ldrValor3 = 0;
    soilValor = 0;
    cont=0;
  }
  delay(1000);
}

void ligaVerde(){
    digitalWrite(verde, HIGH);
    digitalWrite(azul, LOW);
    digitalWrite(vermelho, LOW);
}
void ligaVermelho(){
    digitalWrite(verde, LOW);
    digitalWrite(azul, LOW);
    digitalWrite(vermelho, HIGH);
}
void ligaAzul(){
    digitalWrite(verde, LOW);
    digitalWrite(azul, HIGH);
    digitalWrite(vermelho, LOW);
}

void sing(int s) {
  // intera as notas da melodia:
  int som = s;
  if (som == 3) {
    Serial.println(" 'We wish you a Merry Christmas'");
    int size = sizeof(wish_melody) / sizeof(int);
    for (int estaNota = 0; estaNota < size; estaNota++) {
     
      // Tomamos 1 segundo divido pelo tipo da nota para calcular a duração
      //ex.  semínima = compasso / 4
      int notaTempo = compasso / wish_tempo[estaNota];
 
      buzz(pinBuzzer, wish_melody[estaNota], notaTempo);
 
      // para distinguir melhor as notas, defimos um tempo mínimo entre ela
      int pausaNotas = notaTempo * 1.30;
      delay(pausaNotas);
 
      // interrompe a melodia:
     buzz(pinBuzzer, 0, notaTempo);
    }
 
  } else if (som == 2) {
    Serial.println(" 'Santa Claus is coming to town'");
    int size = sizeof(santa_melody) / sizeof(int);
    for (int estaNota = 0; estaNota < size; estaNota++) {
        
      // Tomamos 1 segundo divido pelo tipo da nota para calcular a duração
      //ex.  semínima = compasso / 4
      int notaTempo = compasso / santa_tempo[estaNota];
 
      buzz(pinBuzzer, santa_melody[estaNota], notaTempo);
 
      // para distinguir melhor as notas, defimos um tempo mínimo entre ela
      int pausaNotas = notaTempo * 1.30;
      delay(pausaNotas);
 
      // interrompe a melodia:
      buzz(pinBuzzer, 0, notaTempo);
 
    }
  } else if (som == 4) {
    Serial.println(" 'Its Mario Time'");
    int size = sizeof(mario_melody) / sizeof(int);
    for (int estaNota = 0; estaNota < size; estaNota++) {
        
      // Tomamos 1 segundo divido pelo tipo da nota para calcular a duração
      //ex.  semínima = compasso / 4
      int notaTempo = compasso / mario_tempo[estaNota];
 
      buzz(pinBuzzer, mario_melody[estaNota], notaTempo);
 
      // para distinguir melhor as notas, defimos um tempo mínimo entre ela
      int pausaNotas = notaTempo * 1.30;
      delay(pausaNotas);
 
      // interrompe a melodia:
      buzz(pinBuzzer, 0, notaTempo);
 
    }
  } else if (som == 5) {
    Serial.println(" 'underworld is coming to town'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int estaNota = 0; estaNota < size; estaNota++) {
        
      // Tomamos 1 segundo divido pelo tipo da nota para calcular a duração
      //ex.  semínima = compasso / 4
      int notaTempo = compasso / underworld_tempo[estaNota];
 
      buzz(pinBuzzer, underworld_melody[estaNota], notaTempo);
 
      // para distinguir melhor as notas, defimos um tempo mínimo entre ela
      int pausaNotas = notaTempo * 1.30;
      delay(pausaNotas);
 
      // interrompe a melodia:
      buzz(pinBuzzer, 0, notaTempo);
 
    }
  } else if (som == 6) {
    Serial.println(" 'Choro is coming to town'");
    int size = sizeof(choro_melody) / sizeof(int);
    for (int estaNota = 0; estaNota < size; estaNota++) {
        
      // Tomamos 1 segundo divido pelo tipo da nota para calcular a duração
      //ex.  semínima = compasso / 4
      int notaTempo = compasso / choro_tempo[estaNota];
 
      buzz(pinBuzzer, choro_melody[estaNota], notaTempo);
 
      // para distinguir melhor as notas, defimos um tempo mínimo entre ela
      int pausaNotas = notaTempo * 1.30;
      delay(pausaNotas);
 
      // interrompe a melodia:
      buzz(pinBuzzer, 0, notaTempo);
 
    }
  } else {
 
    Serial.println(" 'Jingle Bells'");
    int size = sizeof(melody) / sizeof(int);
    for (int estaNota = 0; estaNota < size; estaNota++) {
       
      // Tomamos 1 segundo divido pelo tipo da nota para calcular a duração
      //ex.  semínima = compasso / 4
      int notaTempo = compasso / tempo[estaNota];
 
      buzz(pinBuzzer, melody[estaNota],notaTempo);
 
      // para distinguir melhor as notas, defimos um tempo mínimo entre ela
      int pausaNotas = notaTempo * 1.30;
      delay(pausaNotas);
 
      // interrompe a melodia:
      buzz(pinBuzzer, 0, notaTempo);
    }
  }
}
 
void buzz(int pin , int frequencia, float dur) {
   
  digitalWrite(13, HIGH);
    
  int delayValor = 1000000 / frequencia / 2; // calcula o delay entre transições
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
 
  int numCiclos = frequencia * dur / 1000; // calcula o número de ciclos adequado
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
 
  for (int i = 0; i < numCiclos; i++) { // para definir a duração da nota
    digitalWrite(pin, HIGH); // buzzer em HIGH para emprurrar o diafragama do buzzer
    delayMicroseconds(delayValor); // espera o valor calculado do delay
    digitalWrite(pin, LOW); // buzzer em LOW para puxar o diafragama do buzzer
    delayMicroseconds(delayValor); // espera o valor calculado do delay
    }
 
  digitalWrite(13, LOW);
}
