// Import library
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Konfigurasi LCD
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// Konfigurasi Servo
Servo servo;
#define SERVO_PIN 10

// Konfigurasi LED
#define LED_GREEN 11
#define LED_RED 12

// Konfigurasi Speaker
#define BUZZER_PIN 13

// Konfigurasi Keypad
const byte ROWS = 4; // 4 baris
const byte COLS = 4; // 4 kolom
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};    // Pin baris keypad
byte colPins[COLS] = {9, 8, 7, 6};    // Pin kolom keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variabel
const String correctCode = "1234";  // Kode kunci pintu
String inputCode = "";             // Menyimpan input dari keypad
int attempts = 0;                   // Jumlah percobaan gagal

void setup() {
  // Setup LCD
  lcd.begin(16, 2);
  lcd.print("Masukkan Kode:");

  // Setup Servo
  servo.attach(SERVO_PIN);
  servo.write(0); // Pintu terkunci (posisi awal)

  // Setup LED
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);

  // Setup Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    tone(BUZZER_PIN, 1000, 100); //jika ditekan
    delay(100);
    if (key == '#') {
      // Cek kode ketika tombol '#' ditekan
      checkCode();
    } else if (key == '*') {
      // Reset input ketika tombol '*' ditekan
      inputCode = "";
      lcd.clear();
      lcd.print("Masukkan Kode:");
    } else if (key == 'A') {
      // Mengunci Kembali
      inputCode = "";
      lcd.clear();
      lcd.print("Pintu Terkunci Lagi");
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
      servo.write(0);
      delay(1000);
      lcd.clear();
      lcd.print("Masukkan Kode:");

    } else {
      // Masukkan input
      inputCode += key;
      lcd.setCursor(0, 1);
      lcd.print(inputCode);
    }
  }
}

void checkCode() {
  lcd.clear();
  if (inputCode == correctCode) {
    // Kode benar
    tone(BUZZER_PIN, 1500, 500); // Bunyi pendek jika password benar
    delay(500);
    lcd.print("Kode Anda Benar");
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);

    // Buka pintu
    servo.write(90); // Servo bergerak ke 90 derajat (pintu terbuka)
  } else {
    // Kode salah
    lcd.print("Kode Anda Salah");
    tone(BUZZER_PIN, 500, 500); // Bunyi panjang setelah 3 kesalahan
    
    attempts++;

    // Reset jika percobaan gagal mencapai 3 kali
    if (attempts >= 3) {
      lcd.clear();
      lcd.print("3X Kode Salah ");
      tone(BUZZER_PIN, 500, 1000); // Bunyi panjang setelah 3 kesalahan
      delay(5000); // Kunci sementara selama 5 detik
      lcd.clear();
      lcd.print("Masukkan Kode:");
      attempts = 0;
    }
  }
  inputCode = "";
}