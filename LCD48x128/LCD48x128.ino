#include <SPI.h>

/***
  SPI接続超小型グラフィック液晶
  AQM1248-RN 48x128ドット
  電源　3.3v

  pin接続
  LCD            Arduino
  1 VDD     ->   3.3v
  2 /CS     ->   SS   (16 PB2 digital10)
  3 /RESET  ->   Non
  4 RS      ->   PB1  (15 PB1 digital9)
  5 SCLK    ->   SCK  (19 PB5 digital13)
  6 DSI     ->   MOSI (17 PB3 digital11)
  7 GND     ->   GND
***/

#define RS_PIN  9
#define CS_PIN 10

void LcdCommand(uint8_t cmd)
{
  digitalWrite(CS_PIN, LOW);
  digitalWrite(RS_PIN, LOW);
  SPI.transfer(cmd);
  digitalWrite(CS_PIN, HIGH);
}

void LcdData(uint8_t dat)
{
  digitalWrite(CS_PIN, LOW);
  digitalWrite(RS_PIN, HIGH);
  SPI.transfer(dat);
  digitalWrite(CS_PIN, HIGH);
}

void InitLcd()
{
  // http://akizukidenshi.com/download/ds/xiamen/AQM1248.pdf
  // Display OFF
  LcdCommand(0xae);
  // ADC = normal
  LcdCommand(0xa0);
  // Common output = revers
  LcdCommand(0xc8);
  // bias - 1/7
  LcdCommand(0xa3);

  // 内部レギュレータを順番にONする
  LcdCommand(0x2c);
  // 2ms
  delay(2);
  LcdCommand(0x2e);
  // 2ms
  delay(2);
  LcdCommand(0x2f);

  // コントラスト
  LcdCommand(0x23);  // Vo voltage resistor ratio set
  LcdCommand(0x81);  // Electronic volume mode set
  LcdCommand(0x1c);  // Electronic volume value set

  // 表示設定
  // display all point = normal(全点灯しない)
  LcdCommand(0xa4);
  // display start line = 0
  LcdCommand(0x40);
  // display normal/revers = normal (白黒反転しない)
  LcdCommand(0xa6);
  // display = ON
  LcdCommand(0xaf);
}

void setup() {
  pinMode(RS_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  InitLcd();
}

void loop() {
  for (int page = 0; page < 6; page++) {
    LcdCommand(0xb0 + page);
    LcdCommand(0x10);
    LcdCommand(0x00);
    for (int x = 0; x < 128; x++) {
      LcdData(0);
    } // for x
  } // for page

  delay(1000);

  for (int page = 0; page < 6; page++) {
    LcdCommand(0xb0 + page);
    LcdCommand(0x10);
    LcdCommand(0x00);
    for (int x = 0; x < 128; x++) {
      LcdData(x);
    } // for x
  } // for page

  delay(1000);
}

