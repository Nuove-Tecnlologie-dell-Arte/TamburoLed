#include <FastLED.h>
#define NUM_LEDS 60  // Cambia il numero in base al tuo setup
#define DATA_PIN 6   // Cambia il pin in base al tuo cablaggio
int valore = 0;
CRGB leds[NUM_LEDS];  // Crea un array di colori per i LED

void setup() {
  randomSeed(analogRead(0));
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  // Altri inizializzazioni del tuo progetto
  Serial.begin(115200);
}


void loop() {
  CRGB coloreDesiderato = CRGB(random(256), random(256), random(256)); // Rosso pieno (255, 0, 0)
byte luminositaDesiderata;

  int valore = analogRead(A0);
  //valore = valore - 400;
  int newValue= map(valore, 0, 1023, 0, 255);
  if (valore < 800) {
   luminositaDesiderata = 0;
   //luminositaDesiderata = newValue;

  } else {
       luminositaDesiderata = newValue;
       CRGB coloreConLuminosita;
  coloreConLuminosita.r = (coloreDesiderato.r * luminositaDesiderata) / 255;
  coloreConLuminosita.g = (coloreDesiderato.g * luminositaDesiderata) / 255;
  coloreConLuminosita.b = (coloreDesiderato.b * luminositaDesiderata) / 255;

  for (int luminositaCorrente = 255; luminositaCorrente >= luminositaDesiderata; luminositaCorrente--) {
    coloreConLuminosita.nscale8(luminositaCorrente); // Applica la luminosità corrente al colore
    fill_solid(leds, NUM_LEDS, coloreConLuminosita);
    FastLED.show();
    //delay(10); // Aggiungi un ritardo per controllare la velocità del fade
  }

  }
  

  Serial.println(valore);
spegniLED();
  delay(1); // Pausa per un secondo prima di riavviare il fade
}
void spegniLED() {
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Imposta tutti i LED su colore nero
  FastLED.show(); // Visualizza il cambio
}

