#include <Keypad.h>
#include <LiquidCrystal.h>

// Ustawienia dla klawiatury 4x4
const byte ROWS = 4; // liczba wierszy
const byte COLS = 4; // liczba kolumn
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // piny podłączone do wierszy klawiatury
byte colPins[COLS] = {5, 4, 3, 2}; // piny podłączone do kolumn klawiatury

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Ustawienia dla wyświetlacza 16x2
LiquidCrystal lcd(12, 11, 10, A0, A1, A2); // piny pod€łączone do wyświetlacza

void setup() {
    lcd.begin(16, 2); // inicjalizacja wyświetlacza 16x2
    lcd.print("(NIE)Normalny        Kalkulator"); // wyświetlenie komunikatu startowego
}

void loop() {
    static String input = "";
    char key = keypad.getKey(); // odczytanie naciśniętego klawisza

    if (key) {
        if (key >= '0' && key <= '9') {
            input += key; // dodanie cyfry do wejścia
            lcd.clear();
            lcd.print("Wpisano:");
            lcd.setCursor(0, 1);
            lcd.print(input);
        } else if (key == 'A') { // Dodawanie
            lcd.clear();
            lcd.print("Dodawanie:");
            lcd.setCursor(0, 1);
            lcd.print(input + " + ");
            input = "";
        } else if (key == 'B') { // Odejmowanie
            lcd.clear();
            lcd.print("Odejmowanie:");
            lcd.setCursor(0, 1);
            lcd.print(input + " - ");
            input = "";
        } else if (key == 'C') { // Mnożenie
            lcd.clear();
            lcd.print("Mnozenie:");
            lcd.setCursor(0, 1);
            lcd.print(input + " * ");
            input = "";
        } else if (key == 'D') { // Dzielenie
            lcd.clear();
            lcd.print("Dzielenie:");
            lcd.setCursor(0, 1);
            lcd.print(input + " / ");
            input = "";
        } else if (key == '#') { // Suma
            lcd.clear();
            lcd.print("Suma:");
            lcd.setCursor(0, 1);
            lcd.print(input);
            input = "";
        } else if (key == '*') { // Menu
            lcd.clear();
            lcd.print("Menu:");
            lcd.setCursor(0, 1);
            lcd.print("1:Rst 2:Pow 3:Log");
            delay(2000);
            lcd.clear();
            lcd.print("4:Prc 5:Conv");
            char menuKey = 0;
            while (!menuKey) {
                menuKey = keypad.getKey();
            }

            if (menuKey == '1') { // Reset
                input = "";
                lcd.clear();
                lcd.print("Zresetowano");
                delay(1000);
            } else if (menuKey == '2') { // Potęga
                lcd.clear();
                lcd.print("Potega:");
                lcd.setCursor(0, 1);
                lcd.print(input + "^");
                input = "";
            } else if (menuKey == '3') { // Logarytm
                lcd.clear();
                lcd.print("Logarytm:");
                lcd.setCursor(0, 1);
                lcd.print("log(" + input + ")");
                input = "";
            } else if (menuKey == '4') { // Przecinek
                input += ".";
                lcd.clear();
                lcd.print("Wpisano:");
                lcd.setCursor(0, 1);
                lcd.print(input);
            } else if (menuKey == '5') { // Konwersja
                lcd.clear();
                lcd.print("Conv: 1:Dec->Hex");
                lcd.setCursor(0, 1);
                lcd.print("2:Dec->Bin");
                delay(2000);
                lcd.clear();
                lcd.print("3:Hex->Dec");
                lcd.setCursor(0, 1);
                lcd.print("4:Bin->Dec");
                char convKey = 0;
                while (!convKey) {
                    convKey = keypad.getKey();
                }

                if (convKey == '1') { // Dec -> Hex
                    lcd.clear();
                    lcd.print("Dec->Hex:");
                    lcd.setCursor(0, 1);
                    lcd.print(String(input.toInt(), HEX));
                    input = "";
                } else if (convKey == '2') { // Dec -> Bin
                    lcd.clear();
                    lcd.print("Dec->Bin:");
                    lcd.setCursor(0, 1);
                    lcd.print(String(input.toInt(), BIN));
                    input = "";
                } else if (convKey == '3') { // Hex -> Dec
                    lcd.clear();
                    lcd.print("Hex->Dec:");
                    lcd.setCursor(0, 1);
                    lcd.print(String(strtol(input.c_str(), NULL, 16)));
                    input = "";
                } else if (convKey == '4') { // Bin -> Dec
                    lcd.clear();
                    lcd.print("Bin->Dec:");
                    lcd.setCursor(0, 1);
                    lcd.print(String(strtol(input.c_str(), NULL, 2)));
                    input = "";
                }
            }
        }
    }
}
