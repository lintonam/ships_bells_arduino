#include <RtcDS3231.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ShipsBells.h>

int buzzer = 6; //the pin of the active buzzer
RtcDS3231 clock;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
ShipsBells shipsbells(6);

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printTime(const RtcDateTime& dt)
{
  //print the time to the lcd
  char timestring[10];

  snprintf_P(timestring,
    countof(timestring),
    PSTR("%02u:%02u:%02u"),
    dt.Hour(),
    dt.Minute(),
    dt.Second() );
  lcd.print(timestring);
}

void printDate(const RtcDateTime& dt)
{
  //print the time to the lcd
  char datestring[12];

  snprintf_P(datestring,
    countof(datestring),
    PSTR("%02u/%02u/%04u"),
    dt.Month(),
    dt.Day(),
    dt.Year() );
  lcd.print(datestring);
}

void bells(const RtcDateTime& now)
{
  int single_strikes;
  single_strikes = 0;
  int double_strikes;

  if (now.Minute() == 30 && now.Second() == 0) {
    single_strikes = 1;
  }

  double_strikes = now.Hour() % 4;
  if (double_strikes == 0 && single_strikes == 0) double_strikes = 4;

  Serial.println(double_strikes);
  Serial.println(single_strikes);

  if (double_strikes != 0 && (now.Minute() == 0 || now.Minute() == 30) && now.Second() == 0) {
    for (int i = 0; i < double_strikes; i++) {
      shipsbells.doubleStrike();
    }
  }

    if (single_strikes != 0 && now.Second() == 0) {
    for (int i = 0; i < single_strikes; i++) {
      shipsbells.singleStrike();
    }
  }
  single_strikes = 0;
  double_strikes = 0;
}

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

void loop()
{

  RtcDateTime now;
  //store DateTime in a local variable
  now = clock.GetDateTime();

  //set the lcd cursor to column 0, line 0
  lcd.setCursor(0, 0 );

  //print the date to the lcd
  printDate(now);

  //print a blank space
  lcd.print(" ");

  //print the temperature
  lcd.print(clock.GetTemperature().AsFloat());

  //set the lcd cursor to column 0, line 1
  lcd.setCursor(0, 1);

  //print the time to the lcd
  printTime(now);

  bells(now);

  delay(1000);

}
