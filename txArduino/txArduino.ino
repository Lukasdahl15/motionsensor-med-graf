// Vi har to software(tilbehør?) som vil have brug for at låne et biblioteket til at fungerer. Så vi bruger #include til at hente dem ned fra guderne.
#include <LiquidCrystal.h>
#include <Analog_Keypad.h>
// Vi skal også definer hvad for nogle pins vores display bruger som er 13, 12, 7, 6, 5, 4. 
LiquidCrystal lcd(13, 12, 7, 6, 5, 4);
// Da vi har mange forskellige specifikke tal vi skal gemme, har vi valgt at lave en variablen til dem. 
float afstand;
int trigPin = 9;
int echoPin = 8;
const int pwmPin = 10;
const byte NUM_KEYS = 12;
const byte KEYB_PIN = A2;
int buzzerThreshold = 20;
unsigned long tid = 0;
// Da vi bruger keypaden på Arduinoen skal vi have aktiveret og definet hvilken keys er hvad. 
char hexaKeys[NUM_KEYS] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B' };
Analog_Keypad myKeypad = Analog_Keypad(hexaKeys, KEYB_PIN, NUM_KEYS);


void setup() {
  // initialisere seriel nummet til 9600 bits ver sekund
  Serial.begin(9600);
  // myKeypad.begin skal bare være der til at sætte keypadet igang.. lol 
  myKeypad.begin();
  myKeypad.setDebounceTime(50);
// til Displayed, da den er 16 * 2 pixels  
  lcd.begin(16, 2);
  lcd.print("Afstand:");
  // pinMode bliver bruget til at setup Piezzo og Prog Shield Ultralyd Afstanderen til enden INPUT eller OUTPUT
  pinMode(pwmPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  if ((millis() - tid) > 333) {
    tid += 333;
    // Prog Shield Ultralyd Afstand
    // Da Prog Shield Ultralyd Afstand er afstands måler som måler afstand ved hjælp af at udsende bølger ud og modtag dem igen.  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    // Afstanden kommer ud i mikrosekunder og skal om skrives til cm, det bliver gjort ved hjælp af formelen mikrosekunder * 0.034 / 2
    afstand = (duration * 0.034) / 2;
    // printer afstanden som blev målet af Prog Shield Ultralyd Afstand og printe det i serial monitoren, som vil se sådan ud "Afstand: x cm"
    Serial.print("Afstand: ");
    Serial.print(afstand);
    Serial.println(" cm");
    // Piezzoen som lamer alt for meget
    if (afstand < buzzerThreshold) {
      analogWrite(pwmPin, 128);  // Tænd Piezzo
    } else {
      analogWrite(pwmPin, 0);  // Sluk Piezzo
    }
    // Display
    lcd.setCursor(0, 0);
    lcd.print("Afst.: ");
    lcd.print(afstand);
    lcd.print(" cm    ");
    lcd.setCursor(0, 1);
    lcd.print("Thresh.: ");
    lcd.print(buzzerThreshold);
    lcd.print(" cm    ");
  }
  char key = myKeypad.getKey();  // Læser tastetryk fra keypad
  if (key != NO_KEY) {
    if (key == 'A') { // Hvis 'A' bliver læst som et tastetryk vil den gør hvad står i "if statementet"
      buzzerThreshold += 5;  // Øg threshold med 5 cm
      Serial.print("Ny threshold: "); // printer den nye threshold
      Serial.println(buzzerThreshold);
    } else if (key == 'B') { // Hvis 'B' bliver læst som et tastetryk vil den gør hvad står i "if else statementet"
      buzzerThreshold -= 5;  // Sænk threshold med 5 cm
      Serial.print("Ny threshold: "); // printer den nye threshold
      Serial.println(buzzerThreshold);
    }else if (key == '0') { // Hvis '0' bliver læst som et tastetryk vil den gør hvad står i "if else statementet"
      buzzerThreshold = 20;  // Sæt threshold til 20 cm
      Serial.print("Ny threshold: "); // printer den nye threshold
      Serial.println(buzzerThreshold);
    }
  }
}