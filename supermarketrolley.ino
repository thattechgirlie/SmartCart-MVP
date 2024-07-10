#include <MySQL_Connection.h> 
#include <MySQL_Cursor.h> 
#include <MySQL_Encrypt_Sha1.h> 
#include <MySQL_Packet.h> 
 
#include <Arduino.h> 
#include  <MFRC522.h> 
#include <SPI.h> 
#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
#include <Ethernet.h> 
  
 
#define SS_PIN 10 
#define RST_PIN 9 
#define LED_BLUE 5 
#define LED_RED 6 
#define buzzPin 7 
LiquidCrystal_I2C lcd(0x27, 16, 2); MFRC522 mfrc522(SS_PIN, RST_PIN);  char input[12]; int count = 0; int a; int j=0; int p1=0,p2=0,p3=0,p4=0;  int c1=0,c2=0,c3=0,c4=0; 
 
double total = 0; 
int count_prod = 0; 
void setup () { 
//  Pin direction 
  pinMode(7, OUTPUT);         //RED LED   pinMode(5, OUTPUT);         //BUZZER   pinMode(6, OUTPUT);         //BLUE LED 
 // Initialization 
  Serial.begin(9600);   SPI.begin();   mfrc522.PCD_Init();   
   
  delay(1000);   //lcd.begin();   lcd.init();   lcd.backlight();   lcd.setCursor(0, 0);   lcd.print(" AUTOMATIC BILL");   delay (2000);   lcd.setCursor(0, 1);   lcd.print("  GENERATOR       ");   delay (2000);   lcd.clear();   lcd.setCursor(0, 0);   lcd.print("   WELCOME TO ");   lcd.setCursor(0, 1);  
  lcd.print("SHOP NEXT LEVEL");   delay (2000);   lcd.clear();   lcd.setCursor(0, 0);   lcd.print("scan your items"); 
 
}  void loop() { 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {       return; 
  }       
     
 if ( ! mfrc522.PICC_ReadCardSerial())  
{ return; 
}  
 Serial.print("UID tag:");     String content= "";     byte letter;     count = 0; 
    while (Serial.available() && count < 3) 
   {     input[count] = Serial.read();     count++;     delay(5); 
   }      
    for (byte i = 0; i < mfrc522.uid.size; i++) { 
    Serial.print(mfrc522.uid.uidByte[i] < 0*10 ? " 0" : " " ); 
    Serial.print(mfrc522.uid.uidByte[i],HEX);         Sending_To_db(); 
    j=0; 
    content.concat(String(mfrc522.uid.uidByte[i] < 0*10 ? " 0" : " " ));     content.concat(String(mfrc522.uid.uidByte[i],HEX));  
       
  } 
    Serial.println();     Serial.print("Message:");     content.toUpperCase();     count = 0; 
    while (Serial.available() && count < 12) 
    { 
      input[count] = Serial.read();       count++;       delay(5); 
    } 
      int a=digitalRead(A4); 
       
    if (content.substring(1)=="77 72 28 3B") 
      { 
        Serial.print("Margarine Added       ");         lcd.setCursor(0, 0);         lcd.print("Margarine Added       ");         lcd.setCursor(0, 1);         lcd.print("Price(ksh):135.00      ");         Serial.print("Price(ksh):135.00      ");               digitalWrite(7,HIGH);         digitalWrite(5,LOW);         digitalWrite(6,HIGH);         delay(1000);         total = total + 135.00;         count_prod++;         digitalWrite(7,LOW);         digitalWrite(5,HIGH);         digitalWrite(6,LOW); 
               } 
 
              else 
        { 
        Serial.print("Not in cart!!!        ");         lcd.clear();         lcd.setCursor(0, 0);         lcd.print("Not in cart!!!        ");         digitalWrite(7,HIGH);         digitalWrite(5,LOW);         digitalWrite(6,HIGH);         delay(2000);         digitalWrite(7,LOW);         digitalWrite(5,HIGH);         digitalWrite(6,LOW);         lcd.clear(); 
        } 
      } 
 
 
       if (content.substring(1)=="39 3F 48 2C") 
       {         
         Serial.print("Milk Added       ");         lcd.setCursor(0, 0);         lcd.print("Milk Added       ");         lcd.setCursor(0, 1);         lcd.print("Price(ksh):60.00      ");         p2++; 
         Serial.print("Price(ksh):60.00      ");         digitalWrite(7,HIGH);         digitalWrite(5,LOW);         digitalWrite(6,HIGH);         delay(1000);         total = total + 60.00;         count_prod++;         digitalWrite(7,LOW);         digitalWrite(5,HIGH);         digitalWrite(6,LOW); 
       }         
                       else 
        { 
        Serial.print("Not in cart!!!        ");                   lcd.clear();         lcd.setCursor(0, 0);         lcd.print("Not in cart!!!        ");          digitalWrite(7,HIGH);         digitalWrite(5,LOW);         digitalWrite(6,HIGH);         delay(2000);         digitalWrite(7,LOW);         digitalWrite(5,HIGH);         digitalWrite(6,LOW);         lcd.clear(); 
        } 
      } 
 
      if (content.substring(1)=="17 31 30 3B") 
      { 
        
        Serial.print("Total Price :-");        lcd.clear();          lcd.setCursor(0, 0);        lcd.print("Total Price :-");        lcd.setCursor(0, 1);        lcd.print(total);        delay(5000);        lcd.clear();        lcd.setCursor(0, 0);        lcd.print("  THANKS FOR  ");        lcd.setCursor(0, 1);        lcd.print("   SHOPPING "); 
        
      }      
} void Sending_To_db()   
 {     if (p1,p2,p3,p4 =count)     { 
      Serial.print('connecting'); 
      Serial.print(" ");     }     else 
    { 
      Serial.print('new connection'); 
      Serial.print(" "); 
    } 
 } 
