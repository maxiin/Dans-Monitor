#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_RESET A4

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

String command;
int DAN_Y = 2;
int DAN_X = 4;
int DAN_PADDING = 10;

void setup(void) {
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  printDan();
}

void printDan() {
  tft.setCursor(0, 0);
  tft.setTextColor(MAGENTA);
  fillDan(60,0,8);
  fillDan(56,1,16);
  fillDan(2,2,12); fillDan(54,2,20);
  fillDan(0,3,12); fillDan(52,3,24);
  fillDan(0,4,4); fillDan(50,4,6); fillDan(68,4,8);
  fillDan(0,5,4); fillDan(50,5,4); fillDan(70,5,4);
  fillDan(0,6,2);
  //LINE 7 is BLANK
  fillDan(64,8,2);
  fillDan(60,9,8);
  fillDan(20,10,4); fillDan(56,10,8); fillDan(66,10,4);
  fillDan(16,11,12); fillDan(52,11,8); fillDan(66,11,4);
  fillDan(12,12,8); fillDan(24,12,8); fillDan(48,12,22);
  fillDan(8,13,8); fillDan(28,13,8); fillDan(44,13,8);
  fillDan(6,14,6); fillDan(32,14,6); fillDan(40,14,8);
  fillDan(6,15,2); fillDan(36,15,8);
}

void fillDan(int x, int y, int width){
  tft.fillRect(DAN_Y * x + DAN_PADDING, DAN_X * y + DAN_PADDING,  DAN_Y * width,  DAN_X, MAGENTA);
}

void loop(void) {
  readSerial();
}

void readSerial() {
  if(Serial.available()){
    tft.fillRect(0, tft.height() / 2, tft.width(), tft.height() / 2, BLACK);
    tft.setCursor(0, tft.height() / 2);
    tft.setTextSize(2);
    tft.setTextColor(GREEN);

    String read1 = Serial.readStringUntil('\n');
    if(read1 == "OS"){
      tft.setTextColor(RED);
      String os1 = Serial.readStringUntil('\n');
      String os2 = Serial.readStringUntil('\n');

      tft.setCursor(tft.width() / 2 + 20, 10);
      tft.println(os1);
      tft.setTextSize(1);
      tft.setCursor(tft.width() / 2 + 20, 40);
      tft.println(os2);
    } else {
      String cpu = read1;
      String mem = Serial.readStringUntil('\n');
      String timed = Serial.readStringUntil('\n');
      tft.println(cpu);
      tft.println(mem);
      tft.println(timed); 
    }
  }
}
