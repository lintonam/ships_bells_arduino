#include <RtcDS3231.h>
#include <LiquidCrystal.h>
#include <Wire.h>

int buzzer = 6; //the pin of the active buzzer
RtcDS3231 clock;
RtcDateTime dt;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {

  //setup serial to be used for debugging
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor ---");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //Initialize DS3231
  clock.Begin();

  //Set clock time to compile time
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  clock.SetDateTime(compiled);

  //initialize the buzzer pin as output
  pinMode(buzzer, OUTPUT);

}

void loop() {

  //store DateTime in a local variable
  dt = clock.GetDateTime();

  //set the lcd cursor to column 0, line 0
  lcd.setCursor(0, 0 );

  //print the date to the lcd
  lcd.print(String(dt.Month()) + "/" + String(dt.Day()) + "/" + String(dt.Year()));

  //set the lcd cursor to column 0, line 1
  lcd.setCursor(0, 1);

  //print the time to the lcd
  lcd.print(String(dt.Hour()) + ":" + String(dt.Minute()) + ":" + String(dt.Second()));

  int single_strikes;
  single_strikes = 0;
  int double_strikes;

  if (dt.Minute() == 30 && dt.Second() == 0) {
    single_strikes = 1;
  }

  double_strikes = dt.Hour() % 4;
  if (double_strikes == 0 && single_strikes == 0) double_strikes = 4;

  Serial.println(double_strikes);
  Serial.println(single_strikes);

  if (double_strikes != 0 && (dt.Minute() == 0 || dt.Minute() == 30) && dt.Second() == 0) {
    for (int i = 0; i < double_strikes; i++) {
      digitalWrite(buzzer,HIGH);
      delay(200);
      digitalWrite(buzzer,LOW);
      delay(350);
      digitalWrite(buzzer,HIGH);
      delay(200);
      digitalWrite(buzzer,LOW);
      delay(500);
    }
  }

    if (single_strikes != 0 && dt.Second() == 0) {
    for (int i = 0; i < single_strikes; i++) {
      digitalWrite(buzzer,HIGH);
      delay(200);
      digitalWrite(buzzer,LOW);
      delay(350);
    }
  }
  single_strikes = 0;
  double_strikes = 0;
  delay(1000);

}
