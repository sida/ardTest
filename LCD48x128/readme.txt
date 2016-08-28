■LCDメモ
SPI接続超小型グラフィック液晶
AQM1248-RN 48x128ドット
電源　3.3v

pin接続
1 VDD     ->   3.3v
2 /CS     ->   SS   (16 PB2 digital10)
3 /RESET  ->   Non
4 RS      ->   PB1  (15 PB1 digital9)
5 SCLK    ->   SCK  (19 PB5 digital13)
6 DSI     ->   MOSI (17 PB3 digital11)
7 GND     ->   GND

※MISOは未使用　18 PB4 ただしSPIに割り当てられているので空けておかないとダメ

