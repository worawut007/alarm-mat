/* LCD Keypad Shield (LCD1602) [D038] : http://rdiot.tistory.com/230 [RDIoT Demo] */

#include <LiquidCrystal.h>
#include <DS1302.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);// select the pins used on the LCD panel
DS1302 rtc(27, 29, 31);// RS,DAT,CLK

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
int FSR_Pin = A8; 
 
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   

    return btnNONE;                // when all others fail, return this.
}



 
void setup(){
  lcd.begin(16, 2); // set Lcd for output column 16 , row 2
   rtc.halt(false);
   rtc.writeProtect(false);            // set the LCD cursor   position 
   rtc.setDOW(4);        // Set Day-of-Week to FRIDAY
   rtc.setTime(22, 20, 0);     // Set the time to 12:00:00 (24hr format)
   rtc.setDate(1, 11, 2018);// Set the date mouth year
   
   Serial.begin(9600);
}
  
void loop(){
    int FSRReading = analogRead(FSR_Pin);// weigth 
    lcd_key = read_LCD_buttons();   // read the buttons
    int key_btn = lcd_key;
    lcd.setCursor(4,0); //column , row
    lcd.print(rtc.getTimeStr());// print time
    lcd.setCursor(1,1);
    lcd.print(rtc.getDOWStr(FORMAT_SHORT)); //print date column 0 row 0
    lcd.setCursor(5,1);
    lcd.print(rtc.getDateStr()); //print time column 6 row 1

   
    Serial.print(rtc.getDOWStr(FORMAT_SHORT));
    Serial.print(rtc.getDateStr());
    Serial.print(rtc.getTimeStr());
    Serial.println(); 
      delay(1000);
   
}
