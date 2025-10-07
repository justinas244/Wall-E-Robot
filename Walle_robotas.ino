#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define MIN_PULSE_WIDTH 500
#define MAX_PULSE_WIDTH 2500
#define FREQUENCY       50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define CH1 23
#define CH2 25
#define CH3 27
#define CH4 29
#define CH5 31
#define CH6 33
#define CH7 35
#define CH8 37
#define CH9 39
#define CH10 41


int ch1Value, ch2Value, ch3Value, ch4Value, ch5Value, ch6Value;
int ch7Value, ch8Value, ch9Value, ch10Value;

int ch5 = 0;
int ch6 = 0;
int ch7 = 0;
int ch8 = 0;
int ch9 = 0;
int ch10 = 0;

// Servo kanalai
int kaklas_v = 0;
int kaklas_s = 1;
int antakis_L = 2;
int antakis_D = 3;

int akis_L = 5;
int akis_D = 4;

int riesa_D = 6;
int ranka_D = 7;
int pirstas_D = 8;

int riesa_L = 9;
int ranka_L = 10;
int pirstas_L = 11;

int rankaL = 12;
int rankaD = 13;

/////////////////////////////////////
int pwm_a = 6;
int ain2  = 22;
int ain1  = 24;

int pwm_b = 5;
int bin2  = 26;
int bin1  = 28;

int stop_pin = 30;
int play_pin = 34;
int pause_pin = 32;
int sviesa_pin = 36;

long desiredTarget = 0;

int greitis = 0;



 float switch1Smoothed;
 float switch1Prev;

 float switch2Smoothed;
 float switch2Prev;

int apsisukimo_greitis = 150; // max 255 KELTI CIA DOMAI

static int lastCh3Target = 0;


static long lastTarget = 0;
void setup() {

  
    pwm.begin();
   pwm.setPWMFreq(FREQUENCY);

    pinMode(pwm_a,OUTPUT);
    pinMode(ain2,OUTPUT);
    pinMode(ain1,OUTPUT);
    
    pinMode(pwm_b,OUTPUT);
    pinMode(bin2,OUTPUT);
    pinMode(bin1,OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
  pinMode(CH7, INPUT);
  pinMode(CH8, INPUT);
  pinMode(CH9, INPUT);
  pinMode(CH10, INPUT);

  pinMode(stop_pin, INPUT_PULLUP);
  pinMode(play_pin, INPUT_PULLUP);
  pinMode(pause_pin, INPUT_PULLUP);
  pinMode(sviesa_pin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial3.begin(9600);


  moveMotor(kaklas_v,  90);
  moveMotor(kaklas_s,  90);
  
  //moveMotor(akis_L,  90);
  //moveMotor(akis_D,  90);
  
  moveMotor(riesa_D, 90 );
  moveMotor(ranka_D,  90);
  moveMotor(pirstas_D,  90);
  moveMotor(riesa_L,  90);
  moveMotor(ranka_L,  90);
  moveMotor(pirstas_L,  90);

  moveMotor(rankaL,  90);
  moveMotor(rankaD,  130);
  delay(1000);
  
 /* moveMotor(rankaL,  180);
  moveMotor(rankaD,  180);
  delay(4000);
  moveMotor(rankaL,  0);
  moveMotor(rankaD,  0);
  delay(4000);*/
  
}

// Funkcija, kuri priima laipsnius ir konvertuoja į PWM signalą
void moveMotor(int motorOut, int degrees) {
  degrees = constrain(degrees, 0, 180);  // užtikrinam, kad nepatektų blogų reikšmių

  int pulse_wide = map(degrees, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motorOut, 0, pulse_width);
  
  
}

void loop() {
  
  int stop_m = digitalRead(stop_pin);
  int play_m = digitalRead(play_pin);
  int pause_m = digitalRead(pause_pin);
  int sviesa_m = digitalRead(sviesa_pin);


  
  ch1Value = readChannel(CH1, -100, 107, 0);
  ch2Value = readChannel(CH2, -100, 103, 0);
  ch3Value = readChannel(CH3, 0, 190, 0);
  //ch3Value = readChannel(CH3, -3000, 3000, 0);   // Stepper valdymas
  ch4Value = readChannel(CH4, 0, 190, 90);
  
  //ch4Value = readChannel(CH4, 30, 110, 90);   // akis L 
   //ch4Value = readChannel(CH4, 40, 110, 90);   // akis D 
   
  ch5Value = readChannel(CH5, 0, 110, 0);

 ch6Value = readChannel(CH6, 0, 100, 0); 
 ch7Value = readChannel(CH7, 50, 260, 50); // Potenciometrai
 ch8Value = readChannel(CH8, 50, 260, 50); //Potenciometrai
 ch9Value = readChannel(CH9, 0, 100, 0); 
 ch10Value = readChannel(CH10, 0, 100, 0); 


  switch1Smoothed = (ch3Value * 0.2) + (switch1Prev * 0.8);
  switch1Prev = switch1Smoothed;

  switch2Smoothed = (ch4Value * 0.2) + (switch2Prev * 0.8);
  switch2Prev = switch2Smoothed;

  if( ch5Value >50){
  moveMotor(kaklas_v,  switch1Smoothed);
  moveMotor(kaklas_s,  switch2Smoothed);
  
    if(ch6Value > 50){ moveMotor(rankaD,  190); }  // Antakiu kilnojimo animacija
    else {    
     moveMotor(rankaD,  130);
    }

    
  //if(ch1Value <= 20 && ch1Value >= -20 ){ 
   if(ch2Value <= 5 && ch2Value >= -5 ){
    
      if(ch1Value <= 5 && ch1Value >= -5 ) { greitis =0;    motor(0, 0);  }
          else{
            apsisukimo_greitis  = map(ch1Value,-100,100,-ch8Value,ch8Value);
            motor(-apsisukimo_greitis,apsisukimo_greitis);
          }
       
    }
    else{
      apsisukimo_greitis  = map(ch1Value,-100,100,-ch8Value,ch8Value);
      greitis = map(ch2Value,-100,100,-ch7Value,ch7Value);
      motor(greitis-apsisukimo_greitis, greitis+apsisukimo_greitis);
    }
  }else{
    motor(0,0);
  }

  
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" Ch4: ");
  Serial.println(ch4Value);

  
}

void motor(int left, int right){ 
  right = constrain(right, -255, 255);
  left  = constrain(left, -255, 255);
  
 left = left * (-1);
 right =  right * (-1);
 
  if(right>=0){
    analogWrite(pwm_b, right);
    digitalWrite(bin2,HIGH);
    digitalWrite(bin1,LOW);
  }
  else{
    analogWrite(pwm_b, right*(-1));
    digitalWrite(bin1,HIGH);
    digitalWrite(bin2,LOW);
  }
 if(left>=0){
    analogWrite(pwm_a, left);
    digitalWrite(ain2,HIGH);
    digitalWrite(ain1,LOW);
  }
  else{
    analogWrite(pwm_a, left*(-1));
    digitalWrite(ain1,HIGH);
    digitalWrite(ain2,LOW);
  }
}
