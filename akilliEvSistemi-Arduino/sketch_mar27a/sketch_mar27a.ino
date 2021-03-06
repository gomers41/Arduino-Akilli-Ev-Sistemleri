#include <LiquidCrystal.h>
#include <Keypad.h>


const byte satir_sayisi = 4; //four rows
const byte sutun_sayisi = 3; //three columns
char keys[satir_sayisi][sutun_sayisi] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};
const int kirmizi=6;
const int yesil=5;

char sifre[4]={'1','9','0','5'};
char girilen_sifre[4];
int say=0;

int sensor=53;
int lamba=52;
boolean hareket_sensor_degeri=0;

int buzzer=3;
int yangin_sensoru=4;
int yangin_sensor_degeri=0;

int lm35=A10;

byte satir_pinleri[satir_sayisi] = {10, 9, 8, 7}; 
byte sutun_pinleri[sutun_sayisi] = {13, 12, 11}; 


LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Keypad keypad = Keypad( makeKeymap(keys), satir_pinleri, sutun_pinleri, satir_sayisi, sutun_sayisi );

void setup() {

  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(sensor,INPUT);
  pinMode(lamba,OUTPUT);
  pinMode(yangin_sensoru,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(lm35, INPUT);
  
  
}

void loop() {
  
   sifre_girme();
   delay(100);
   hareketSensoru();
   yanginSensoru();
   sicaklik();
   
}
void sifre_girme(){
   char basilan_tus = keypad.getKey();

    if (basilan_tus!=NO_KEY) {
        girilen_sifre[say]=basilan_tus;
        //lcd.print("*");
        say++;
    }
    digitalWrite(kirmizi,LOW);
    digitalWrite(yesil,LOW);
    if(say==4){
      if(sifre[0]==girilen_sifre[0]&&sifre[1]==girilen_sifre[1]&&sifre[2]==girilen_sifre[2]&&sifre[3]==girilen_sifre[3]){
       digitalWrite(5,HIGH);
       delay(1000);
       digitalWrite(5,LOW);
      }
      else{
        digitalWrite(6,HIGH);
        delay(1000);
        digitalWrite(6,LOW);
        delay(1000);
      }
    say=0;
    }
}
void hareketSensoru(){
  hareket_sensor_degeri=digitalRead(sensor);
  if(hareket_sensor_degeri==1){
    digitalWrite(lamba,HIGH);
   }else{
    digitalWrite(lamba,LOW);
   }
}
void yanginSensoru(){
   yangin_sensor_degeri=digitalRead(yangin_sensoru);
   if(yangin_sensor_degeri==1){
    digitalWrite(3,HIGH);
   }else{
    digitalWrite(3,LOW);
   }
}
void sicaklik()
{
  float isi = analogRead(lm35);  
  float c = (isi / 10230) * 5000;
 // Serial.println(c); 
  if (c >= 20 && c <= 30)  
  {
    lcd.setCursor(0, 0);
    lcd.print(c);  
    lcd.setCursor(0, 1);
    lcd.print("Sicaklik normal"); 
  }
  else if (c < 20) 
  {
    lcd.setCursor(0, 0);
    lcd.print(c);
    lcd.setCursor(0, 1);
    lcd.print("Sicaklik  dusuk");
  }
  else if (c > 30)  
  {
    lcd.setCursor(0, 0);
    lcd.print(c);
    lcd.setCursor(0, 1);
    lcd.print("Sicaklik yuksek");
  }
  
}
