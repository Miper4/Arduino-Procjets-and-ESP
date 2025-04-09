#include <Keypad.h>
#include <LiquidCrystal.h>

// Ustawienia dla klawiatury 4x4
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {35, 36, 37, 38}; 
byte colPins[COLS] = {39, 40, 41, 42}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Ustawienia dla wyświetlacza 16x2
LiquidCrystal lcd(4, 5, 11, 12, 13, 14); 

static double input;
static double wynik;
static double liczba1;
static double liczba2;
static bool up = false;
static bool down = false;
static bool isFraction = false; // Flaga do obsługi części ułamkowej
static double fractionMultiplier = 0.1; // Mnożnik dla części ułamkowej
static int reset = 0;


void setup() {
    Serial.begin(9600);
    lcd.begin(20, 4); 
    lcd.print("Normalny");
    lcd.setCursor(0, 1);
    lcd.print("Kalkulator");
    lcd.setCursor(0, 2);
    lcd.print("Kornelzen&Knapik");
    delay(2000);
    lcd.clear();
}

void back(){
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Powrot do menu");                 
  delay(400);                 
  reset = 0;
  input = 0;
  liczba1 = 0;
  liczba2 = 0;
  wynik = 0;                  
  lcd.clear();
}

void fwynik(){
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Wynik:"); 
  lcd.setCursor(0, 1); 
  lcd.print(wynik); 
  lcd.setCursor(0, 2); 
  lcd.print("Nacisnij # aby"); 
  lcd.setCursor(0, 3); 
  lcd.print("powrocic do menu"); 
}

void zapis(){
  char key = keypad.getKey();
  while (key != '#') {
   key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      if (isFraction) {
        input += (key - '0') * fractionMultiplier;
        fractionMultiplier *= 0.1; // Przesuwanie miejsca dziesiętnego
      } else {
        input = input * 10 + (key - '0');
        }
        lcd.setCursor(0, 2);
        lcd.print(input);
    } else if (key == '*') { // Separator dziesiętny
        isFraction = true;
      }
  }
}

void zerowanie(){
  char key = keypad.getKey();
  liczba1 = input; 
  input = 0;
  key = 0;
  isFraction = false;
  fractionMultiplier = 0.1;                  
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Podaj liczbe 2:"); 
}
void loop() {
    char key = keypad.getKey();
    lcd.setCursor(0, 0);
    lcd.print("Prosty A");
    lcd.setCursor(0, 1);
    lcd.print("Zaawansowany B");
    lcd.setCursor(0, 2);
    lcd.print("Dodatkowe C");
    lcd.setCursor(0, 3);
    lcd.print("Dodatkowe D");

    if (key) {
        if(key == 'A'){
          reset++;
          lcd.clear(); 
            while(key != 'A', key != 'B', key != 'C', key != 'D', key != '#', reset != 0) {
                lcd.setCursor(0, 0); 
                lcd.print("A +");
                lcd.setCursor(0, 1); 
                lcd.print("B -"); 
                lcd.setCursor(0, 2); 
                lcd.print("C *"); 
                lcd.setCursor(0, 3); 
                lcd.print("D /");
                lcd.setCursor(14, 0);
                lcd.print("Menu #");  
                key = keypad.getKey(); 
                if (key == 'A') {                     
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                    lcd.print("Wybrano dodawanie"); 
                    lcd.setCursor(0, 1); 
                    lcd.print("Podaj liczbe 1:");                     
                    delay(200);                    
                    zapis();                    
                    zerowanie();                   
                    delay(200);                    
                    zapis();                   
                    liczba2 = input; 
                    input = 0;
                    wynik = liczba1 + liczba2; 
                    key = 0;
                    isFraction = false;
                    fractionMultiplier = 0.1;                    
                    fwynik();                    
                    delay(200);                    
                    while (key != '#') { 
                        key = keypad.getKey(); 
                    }                    
                    lcd.clear(); 
                    lcd.setCursor(0, 0);                 
                } else if (key == 'B') {                    
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                    lcd.print("Wybrano Odejmowanie"); 
                    lcd.setCursor(0, 1); 
                    lcd.print("Podaj liczbe 1:");                    
                    delay(200);                   
                    zapis();                    
                    zerowanie();                    
                    delay(200);                    
                    zapis();                    
                    liczba2 = input; 
                    input = 0;
                    wynik = liczba1 - liczba2; 
                    key = 0;
                    isFraction = false;
                    fractionMultiplier = 0.1;                   
                    fwynik();                     
                    delay(200);                    
                    while (key != '#') { 
                        key = keypad.getKey(); 
                    }                    
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                } else if (key == 'C') {                   
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                    lcd.print("Wybrano mnozenie"); 
                    lcd.setCursor(0, 1); 
                    lcd.print("Podaj liczbe 1:");                     
                    delay(200);                    
                    zapis();                    
                    zerowanie();                    
                    delay(200);                    
                    zapis();                    
                    liczba2 = input; 
                    input = 0;
                    wynik = liczba1 * liczba2; 
                    key = 0;
                    isFraction = false;
                    fractionMultiplier = 0.1;                    
                    fwynik();                    
                    delay(200);                   
                    while (key != '#') { 
                        key = keypad.getKey(); 
                    }
                    lcd.clear(); 
                    lcd.setCursor(0, 0);                 
                } else if (key == 'D') {                
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                    lcd.print("Wybrano dzielnie"); 
                    lcd.setCursor(0, 1); 
                    lcd.print("Podaj liczbe 1:");                 
                    delay(200);                
                    zapis();                 
                    zerowanie();                
                    delay(200);                 
                    zapis();                   
                    liczba2 = input; 
                    input = 0;
                    wynik = liczba1 / liczba2; 
                    key = 0;
                    isFraction = false;
                    fractionMultiplier = 0.1;                    
                    fwynik();                    
                    delay(200);                    
                    while (key != '#') { 
                        key = keypad.getKey(); 
                    }
                    lcd.clear(); 
                    lcd.setCursor(0, 0);                 
                } else if (key == '#') {
                  back();
                }
            }
        }
        if(key == 'B'){
            reset++;
            lcd.clear(); 
            while(key != 'A', key != 'B', key != 'C', key != 'D', key != '#', reset != 0) {
                lcd.setCursor(0, 0); 
                lcd.print("A Pierwiastek");
                lcd.setCursor(0, 1); 
                lcd.print("B Potega"); 
                lcd.setCursor(0, 2); 
                lcd.print("C Logarytm"); 
                lcd.setCursor(0, 3); 
                lcd.print("D Silnia");
                lcd.setCursor(14, 0);
                lcd.print("Menu #");  
                key = keypad.getKey();
                if(key == 'A'){                   
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                    lcd.print("Wybrano pierwiastek"); 
                    lcd.setCursor(0, 1); 
                    lcd.print("Podaj liczbe:");                     
                    delay(200);                    
                    zapis();                   
                    liczba1 = input; 
                    input = 0;
                    wynik = sqrt(liczba1); 
                    key = 0;
                    isFraction = false;
                    fractionMultiplier = 0.1;                    
                    fwynik();                    
                    delay(200);                   
                    while (key != '#') { 
                        key = keypad.getKey(); 
                    }
                    lcd.clear(); 
                    lcd.setCursor(0, 0);                     
                } else if (key == 'B') {                        
                        lcd.clear(); 
                        lcd.setCursor(0, 0); 
                        lcd.print("Wybrano potegowanie"); 
                        lcd.setCursor(0, 1); 
                        lcd.print("Podaj liczbe:");                        
                        delay(200);                        
                        zapis();                        
                        liczba1 = input; 
                        input = 0;
                        key = 0;
                        isFraction = false;
                        fractionMultiplier = 0.1;                        
                        lcd.clear();
                        lcd.setCursor(0, 1);
                        lcd.print("Podaj potege:");                         
                        delay(200);                       
                        zapis();                        
                        liczba2 = input; 
                        input = 0;
                        wynik = pow(liczba1, liczba2); 
                        key = 0;
                        isFraction = false;
                        fractionMultiplier = 0.1;                       
                        fwynik();                        
                        delay(200);                    
                        while (key != '#') { 
                        key = keypad.getKey(); 
                    }
                    lcd.clear(); 
                    lcd.setCursor(0, 0);                         
                } else if (key == 'C') {                       
                        lcd.clear(); 
                        lcd.setCursor(0, 0); 
                        lcd.print("Wybrano logarytm"); 
                        lcd.setCursor(0, 1); 
                        lcd.print("Podaj logarytm:");                         
                        delay(200);                        
                        zapis();                       
                        liczba1 = input; 
                        input = 0; 
                        key = 0;
                        isFraction = false;
                        fractionMultiplier = 0.1;                       
                        lcd.clear();
                        lcd.setCursor(0, 1); 
                        lcd.print("Podaj podstawe:");                         
                        delay(200);                       
                        zapis();
                        liczba2 = input; 
                        input = 0; 
                        key = 0;
                        isFraction = false;
                        fractionMultiplier = 0.1;
                        wynik = log(liczba1) / log(liczba2);
                        liczba1 = 0;
                        liczba2 = 0;
                        fwynik();
                        delay(200);
                        while (key != '#') { 
                        key = keypad.getKey(); 
                    }
                    lcd.clear(); 
                    lcd.setCursor(0, 0);
                } else if (key == 'D') { 
                        lcd.clear(); 
                        lcd.setCursor(0, 0); 
                        lcd.print("Wybrano silnie"); 
                        lcd.setCursor(0, 1); 
                        lcd.print("Podaj liczbe:");     
                        delay(200);  
                        zapis(); 
                        liczba1 = input; 
                        input = 0;
                        wynik = tgamma(liczba1 + 1); // Silnia
                        key = 0;
                        isFraction = false;
                        fractionMultiplier = 0.1;  
                        fwynik();
                        delay(200);
                        while (key != '#') { 
                        key = keypad.getKey(); 
                    }
                    lcd.clear(); 
                    lcd.setCursor(0, 0); 
                } else if (key == '#') {
                    back();
                } 
            }       
        }
    }     
}
