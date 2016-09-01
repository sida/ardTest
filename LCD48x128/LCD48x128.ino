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


/*
 * LCDのメモリマップ構造
 * 
 * 縦8ドットが横に128個並んだものがページ
 * 縦8ドットをカラムと呼ぶ。128カラム。
 * ページはさらに縦に6ページあり縦8*6の46ドットになる
 * 
 * 1回書き込みをするとカラムのアドレスがインクリメントされる
 */

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
  pinMode(RS_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);

  // http://akizukidenshi.com/download/ds/xiamen/AQM1248.pdf
  // Display OFF
  LcdDisplay(false);
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
  LcdContrast(0x1c);

  // 表示設定
  // display all point = normal(全点灯しない)
  LcdCommand(0xa4);
  // display start line = 0
  LcdCommand(0x40);
  // display normal/revers = normal (白黒反転しない)
  LcdCommand(0xa6);
  // display = ON
  LcdDisplay(true);
}


void LcdDisplay(bool on)
{
  uint8_t cmd = 0xAE;
  if (on){
    cmd |= 1;
  }
  LcdCommand(cmd);
}

// コントラスト
// value 下位6bit有効 
void LcdContrast(uint8_t value)
{
  LcdCommand(0x23);  // Vo voltage resistor ratio set
  LcdCommand(0x81);  // Electronic volume mode set
  LcdCommand(value & 0x3f);  // Electronic volume value set
}

// ページアドレスの設定　0-7 6,7は表示されない
void LcdSetPageAdress(uint8_t page)
{
  page &= 0x07;
  LcdCommand(0xb0 | page);
}

// カラムアドレスの設定 0-131 表示出来るのは0-127
void LcdSetColumnAdress(uint8_t column)
{
  uint8_t upper = column >> 4;
  uint8_t lower = column & 0x0f;
  LcdCommand(0x10 | upper);
  LcdCommand(lower);
}

void setup() {

//  Serial.begin(9600);  
  InitLcd();
  LcdContrast(0x20);
}

void loop() {
//  Serial.println("start");

  for (int page = 0; page < 6; page++) {
    LcdSetPageAdress(page);
    LcdSetColumnAdress(0);

    uint8_t val = 0;
    if (page & 0x01){
      val = 0xff;
    }
    for (int x = 0; x < 128; x++) {
      LcdData(val);
    }
  }

  delay(1000);

  for (int page = 0; page < 6; page++) {
    LcdSetPageAdress(page);
    LcdSetColumnAdress(0);

    uint8_t val = 0x0f;
//    if (page & 0x01){
//      val = 0xf0;
//    }
    for (int x = 0; x < 128; x++) {
      LcdData(val);
    }
  }

  delay(1000);
}

