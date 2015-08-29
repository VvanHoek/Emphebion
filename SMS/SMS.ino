//*****************************************************************************************************//
// Module om berichten te sturen met de SIM900 arduino GSM shield                                      //
// ****************************************************************************************************//
// Arduino databases toevoegen met voorgedefineerde functies
#include <SoftwareSerial.h>

// Constante waardes instellen
#define GSM_TX 2
#define GSM_RX 3
#define GSM_PW 7
#define GSM_TB 1                                      // Testbench inschakelen: 1 = aan; 0 = uit

// Maakt de Globale variabelen aan (overal toegankelijk)
   // Telefoon nummers van actieve spelleiders
const char nummer1[] PROGMEM = "AT+CMGS=\"+31621477770\"";
const char nummer2[] PROGMEM = "AT+CMGS=\"+31653832199\"";
const char nummer3[] PROGMEM = "AT+CMGS=\"+31652342086\"";

PROGMEM const char* nummers[] = {nummer1,nummer2,nummer3};                          // Bevat een lijst met de nummers van de huidige actieve spelleiders
char actief_nr[23];


   // Programma variablen
SoftwareSerial GSM_Shield(GSM_TX, GSM_RX);
char bericht[200];
char RX_kar;
char ontvangen[100];
const char code[11] = "yso4jkd36f";
int sendOnce = 0;
int ls;

// Setup routine om alle basis instellingen goed te zetten
void setup(){
  Serial.begin(19200);        
  GSM_Shield.begin(19200);
  GSM_Shield.print("AT+IPR=19200");                   // Stel de Baudrate in
  GSM_Shield_power();                                 // Zet het GSM-Shield aan
  delay(100);
}
 
// Function om het GSM-Shield aan te zetten
    // "NET-LED" knipperd eens per 0.8s als het een netwerk zoekt
    // "NET-LED" knipperd eens per 3s als het een netwerk heeft
void GSM_Shield_power(){
  digitalWrite(GSM_PW, HIGH);
  delay(4000);
  digitalWrite(GSM_PW, LOW);
  delay(10000);                                       // Geef het GSM-Shield de tijd een netwerk te vinden
}

// Functie voor het versturen van een SMS bericht:
   // Input: bericht, nummer
void verstuurSMS(String bericht, const char* nummers[]){
  for(int i = 0; i <= sizeof(nummers)+1; i++){
    GSM_Shield.print("AT+CMGF=1\r");
    delay(100);
    strcpy_P(actief_nr, (char*)pgm_read_word(&(nummers[i])));
    Serial.println(actief_nr);
    GSM_Shield.println(actief_nr);                      // AT commando om het bericht te sturen naar het gegeven telefoon nummer
    delay(100);
    GSM_Shield.println(bericht);                        // Het bericht zelf, max 200 tekens (heeft geen AT commando meer nodig)
    Serial.println(bericht);
    delay(100);
    GSM_Shield.write(26);                               // Sluit het vorige AT commando at met een ^z teken (ASCII Decimaal: 26)
    delay(100);
    GSM_Shield.println();
    delay(10000);                                        // Geeft het GSM-Shield tijd om het bericht te versturen
    Serial.print("Send message: ");
    Serial.print(i);
    Serial.print(" of ");
    Serial.println(sizeof(nummers)+1);
  }
}

 
void loop(){
  if(GSM_TB == 1){                                    // Testbench om de serielepoort en de commando's te testen
    if(GSM_Shield.available())
    Serial.write(GSM_Shield.read());
    if(Serial.available())
    GSM_Shield.write(Serial.read());
  }
  else{                                               // Hoofd functie van het programma, zolang er niet getest wordt
    if(sendOnce == 0){
      sendOnce = 1;
      leegString(bericht);
      strcat(bericht,"Oscar is lonesome, Oscar needs huggs! Please reactivate me... Please?!");
      verstuurSMS(bericht,nummers);
      Serial.print("End");
    }

//    GSM_Shield.println("AT+CMGR=1");
//    for(int i = 0; i > 100; i++){
//      ls = (char)GSM_Shield.readBytes(ontvangen,sizeof(ontvangen));
//    }
//    Serial.println(ontvangen);

//    if(GSM_Shield.available()){
//      int msg_length = GSM_Shield.available();
//      delay(100);
//      char RX_bericht[msg_length];
//      int t = 0;
//      while(msg_length > 0){
//        RX_kar = GSM_Shield.read();
//        delay(100);
//        RX_bericht[t] = RX_kar;       
//        msg_length--;
//        t++;
//      }
//      Serial.println(RX_bericht);
//      int msg_check = 1;
//      for(int p = 0; p < sizeof(code); p++){
//        if(RX_bericht[p] =! code[p])
//          msg_check = 0;
//      }
//      if(msg_check == 1){
//        Serial.println("passed");
//        leegString(bericht);
//        strcat(bericht,"Identity confirmed");
//      }
//    }

//    do{}while(1);
  }
}

void leegString(char string[]){
  for (int i = 0; i < sizeof(string); i++){
    bericht[i] = (char)0;
  }
}
