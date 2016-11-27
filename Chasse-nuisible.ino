/*
 * Chasse-nuisible v1.0 2016
 * (c) Emmanuel Frémion F8EBY
 * https://www.f8eby.org
 * 
 */

 
int const multiFreq = 10; // Multiplicateur les ultrasons
int const multiDuree = 100; // Multiplicateur pour durée (100 ms à 3 s)
unsigned int FreqOut; // Fréquence générée de sortie
unsigned long DureeOut; // Durée du son généré
#define PinOut 10 // Broche de sortie
#define TestPin 9 // Entrée pour bouton de test
#define StopPin 8 // Entrée pour bouton qui arrête le son
#define LedPin 13 // Sortie LED intégrée pour indiquer le mode test

void setup() {
  // Code exécuté une seule fois.
  randomSeed(analogRead(0));
  pinMode(TestPin,INPUT_PULLUP);
  pinMode(StopPin,INPUT_PULLUP);
  pinMode(LedPin,OUTPUT);
  digitalWrite(LedPin, LOW);
  Serial.begin(115200);
  Serial.flush();
}

void loop() {
  // Code exécuté en permanence.

  // Mode test enclenché ?
  if (digitalRead(TestPin) == LOW) // Oui
  { // Gamme de fréquence de 2,5kHz à 6,5kHz pour vérifier la fonctionnement
    FreqOut = random(250,650)*multiFreq;
    digitalWrite(LedPin, HIGH);
  }
  else // Gamme de fréquence de 25kHz à 65kHz
  {
    FreqOut = random(250,650)*multiFreq*10;  
    digitalWrite(LedPin, LOW);
  }
  DureeOut = (random(1,30)*multiDuree);
  Serial.print(FreqOut);
  Serial.print(" -> ");
  Serial.println(DureeOut);

  // Position son arrêté ?
  if (digitalRead(StopPin) == HIGH)
  {
    // Génération de la fréquence aléatoire pendant la durée aléatoire
    tone(PinOut,FreqOut);
  }
  else
  {
    noTone(PinOut);
  }
  // on laisse le générateur actif pendant la durée aléatoire prévue
  delay(DureeOut);
}
