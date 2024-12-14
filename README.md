# Sistem Kunci Pintu Arduino dengan Keypad

## Gambaran Proyek
Proyek ini adalah sistem kunci pintu elektronik berbasis Arduino yang menggunakan keypad untuk input, motor servo untuk membuka dan mengunci pintu, LED untuk indikasi status, dan speaker (buzzer) untuk umpan balik audio. Sistem ini juga dilengkapi dengan LCD untuk menampilkan status dan kode yang dimasukkan, sehingga memberikan antarmuka yang interaktif dan ramah pengguna.

## Simulasi
Proyek ini dapat disimulasikan menggunakan **SimulIDE** atau alat serupa untuk pengujian sebelum implementasi.

## Software :
- **Arduino IDE**
- **Simulide**

### Fitur:
- **Keypad 4x4**: Pengguna dapat memasukkan kode 4 digit melalui keypad 4x4.
- **Servo**: Servo mengunci atau membuka kunci pintu berdasarkan kebenaran kode yang dimasukkan.
- **Indikator LED**:
  - LED Hijau: Menyala saat pintu terbuka.
  - LED Merah: Menyala saat pintu terkunci.
- **Speaker Out**:
  - Beep pendek untuk kode yang benar.
  - Beep panjang untuk upaya yang gagal.
- **LCD HD44780**: Menampilkan kode yang dimasukkan dan status sistem.
- **Penguncian Keamanan**: Mengunci sistem sementara setelah 3 kali percobaan gagal.

## Komponen
- **Arduino Uno**
- **Keypad 4x4**
- **Motor Servo**
- **Layar LCD 16x2 (HD44780)**
- **LED Hijau**
- **LED Merah**
- **Buzzer**
- **Resistor (220Ω)**

## Diagram Koneksi
### Konfigurasi Pin:
| Komponen           | Pin Arduino    | Catatan                     |
|--------------------|----------------|-----------------------------|
| Keypad (Baris)     | 2, 3, 4, 5     | 4 pin untuk baris           |
| Keypad (Kolom)     | 6, 7, 8, 9     | 4 pin untuk kolom           |
| Motor Servo        | 10             | Pin sinyal                  |
| LED Hijau          | 11             | Hubungkan dengan resistor   |
| LED Merah          | 12             | Hubungkan dengan resistor   |
| Buzzer             | 13             | Opsional resistor 100Ω      |
| LCD RS             | A0             | Register Select LCD         |
| LCD EN             | A1             | Enable LCD                  |
| LCD D4, D5, D6, D7 | A2, A3, A4, A5 | Pin data LCD                |
| LCD VSS, RW        | GND            | Sambungan ke ground         |
| LCD VDD            | 5V             | Power                       |

## Simulasi di Simulide
1. **Upload File**: Open file coding dan upload file Arduino di Simulide
2. **Mulai Simulasi**: Mulai simulasi di Simuleide.
3. **Masukkan Kode**:
   - Gunakan keypad untuk memasukkan kode yang sudah ditentukan (default: `1234`).
   - Tekan `#` untuk mengonfirmasi.
   - Tekan `*` untuk menghapus input.
   - Tekan `A` untuk reset servo.
4. **Buka Pintu**:
   - Jika kode yang dimasukkan benar, servo akan membuka pintu, dan LED hijau menyala.
5. **Tutup Pintu**:
   - Tekan `A` untuk menutup kembali pintu.
6. **Percobaan Gagal**:
   - Setelah 3 kali percobaan gagal, sistem akan terkunci sementara dan menampilkan peringatan.

## Konfigurasi Kode
### Mengubah Kode:
Untuk mengubah kode default, ubah baris berikut pada kode Arduino:
```cpp
const String correctCode = "1234"; // Ganti "1234" dengan kode yang diinginkan
```

### Penguncian Keamanan:
Durasi penguncian setelah percobaan gagal ditentukan dalam milidetik:
```cpp
delay(5000); // Durasi penguncian 5 detik
```
Anda dapat mengubah durasi dengan memodifikasi nilai `5000`.

## Pustaka yang Digunakan
- **Keypad.h**: Untuk menangani input keypad.
- **LiquidCrystal.h**: Untuk mengontrol tampilan LCD.
- **Servo.h**: Untuk mengontrol motor servo.
