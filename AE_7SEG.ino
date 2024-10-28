//ARDUINO UNO
//AE-7SEG-BOARD * 2
//SCK D13
//LATCH D10
//SDI D11
#include <SPI.h>

int sck = 25;
int latch = 26;
int sdi = 27;
int scroll_speed = 200;
const byte digits[] = {
  0b11111100,  // 0
  0b01100000,  // 1
  0b11011010,  // 2
  0b11110010,  // 3
  0b01100110,  // 4
  0b10110110,  // 5
  0b10111110,  // 6
  0b11100000,  // 7
  0b11111110,  // 8
  0b11110110,  // 9
};

void setup() {
  pinMode(latch, OUTPUT);
  pinMode(sck, OUTPUT);
  pinMode(sdi, OUTPUT);
  Serial.begin(115200);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(0);
}

void loop() {
  // for (int j = 0; j < 10; j ++) {//１０の桁
  //   for (int i = 0; i < 10; i ++) {//１の桁
  //     //SPI
  //     digitalWrite(latch, 0);
  //     SPI.transfer (digits[j]+1);//10の桁 +1でドット表示
  //     SPI.transfer (digits[i]);//1の桁
  //     digitalWrite(latch, 1);
  //     //
  //     Serial.println("J:" + (String)j + "i:"+ (String)i);
  //     delay(scroll_speed);

  //   }
  // }
  for (int i = 0; i < 1000; i++) {
    // Serial.print(i);
    // Serial.println(" is " + String(Numlength(i)) + " digit");
    delay(500);

    int num = i;                      
    int digits = Numlength(num) + 1;  // 桁数を取得

    // 桁ごとに取り出して SPI で転送
    for (int j = digits; j > 0; j--) {
      int digit = num / pow(10, j - 1);  
      digit = digit % 10;                
      digitalWrite(latch, 0);
      SPI.transfer(digit);  

      Serial.print((String)digit + " ");  
    }
    digitalWrite(latch, 1);
    Serial.println();  
  }
}

int Numlength(int n) {
  int i = 0;
  while (n >= 10) {
    n = n / 10;
    i++;
  }
  return i;
}
