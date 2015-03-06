#include <LiquidCrystal.h>
#define LED 13
#define ROWS 4
#define COLS 20

/*
all characters > 31 and < 128 will be printed as is

cursor position:
128 - 147 -> row 1
148 - 167 -> row 2
168 - 187 -> row 3
188 - 207 -> row 4

240 = led on
241 = led off
242 = right to left
243 = left to right
244 = autoscroll on
245 = autoscroll off
246 = scroll right
247 = scroll left
248 = display on
249 = display off
250 = cursor on
251 = cursor off
252 = blink on
253 = blink off
254 = cursor home
255 = clear screen

LCD pinout
1 0v
2 +5
3 kontrast
4 rs
5 rw
6 e
7 d0
8 d1
9 d2
10 d3
11 d4
12 d5
13 d6
14 d7
15 LED A
16 LED K

initialize the library with the numbers of the interface pins
       (rs, rw, enable, d4, d5, d6, d7) */
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

unsigned char c, mode, row, col;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);  // background LED
  // set up the LCD's number of columns and rows:
  lcd.begin(COLS, ROWS);
  lcd.clear();
  row=0;
  col=0;
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop(){
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // read all the available characters
    while (Serial.available() > 0) {
      c=Serial.read();
      if(c>31 && c<128){
        // display each character to the LCD
        lcd.write(c);
        col++;
        if(col>=COLS){
          col=0;
          row++;
          if(row>=ROWS)row=0;
          lcd.setCursor(col,row);
        }
      }else if(c>127){
        if(c<148){
          row=0;
          col=c-128;
          lcd.setCursor(col,row);
        }else if(c<168){
          row=1;
          col=c-148;
          lcd.setCursor(col,row);
        }else if(c<188){
          row=2;
          col=c-168;
          lcd.setCursor(col,row);
        }else if(c<208){
          row=3;
          col=c-208;
          lcd.setCursor(col,row);
        }else if(c==255){
          lcd.clear();
          row=0;
          col=0;
        }else if(c==254){
          lcd.home();
          row=0;
          col=0;
        }else if(c==253){
          lcd.noBlink();
        }else if(c==252){
          lcd.blink();
        }else if(c==251){
          lcd.noCursor();
        }else if(c==250){
          lcd.cursor();
        }else if(c==249){
          lcd.noDisplay();
        }else if(c==248){
          lcd.display();
        }else if(c==247){
          lcd.scrollDisplayLeft();
        }else if(c==246){
          lcd.scrollDisplayRight();
        }else if(c==245){
          lcd.noAutoscroll();
        }else if(c==244){
          lcd.autoscroll();
        }else if(c==243){
          lcd.leftToRight();
        }else if(c==242){
          lcd.rightToLeft();
        }else if(c==241){
          digitalWrite(LED, LOW);
        }else if(c==240){
          digitalWrite(LED, HIGH);
        }
      }
    }
  }
}
