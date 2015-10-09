//*****************************************************************************************************//
// Module om berichten te sturen met de SIM900 arduino GSM shield                                      //
// ****************************************************************************************************//
// Arduino databases toevoegen met voorgedefineerde functies
#include <avr/pgmspace.h>

class TelephoneNumber
{
public:
  TelephoneNumber() = delete;
  TelephoneNumber(const char* tel): m_telephoneNumber(tel) {};
  ~TelephoneNumber() {};

  operator const char*() {return m_telephoneNumber;};

private:
  const char* m_telephoneNumber;
};

#define Tel(s) PSTR(s)

// Setup routine om alle basis instellingen goed te zetten
void setup() {
  Serial.begin(9600);
}

void loop() {
  TelephoneNumber Jan = Tel("0618466546");
 //Serial.println(t);
 Serial.println(Jan);
 Serial.println(PSTR("DIT IS EEN TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
}

