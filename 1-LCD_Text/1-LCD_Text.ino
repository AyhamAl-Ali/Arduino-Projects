#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Set the LCD address to 0x27 by Teach Me Something
String Leftscroll   = "LCD Projects";
String Rightscroll  = "Subscribe Teach Me Something";
int x=0;
int y=0;
int z=0;
int i=0;
int j=0;

void setup() {
  Serial.begin(9600);
  lcd.begin(); // configuramos el LCD de 16x2
  x=Leftscroll.length();
  y=Rightscroll.length();
  z=max(x,y);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Scroll Text in");
lcd.setCursor(0,1);
lcd.print("  Both Direction");
delay(2000);
lcd.clear();

}

void loop() {
i=0;
j=0;
x=4; // Delete this line if required
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Scroll Text in");
lcd.setCursor(0,1);
lcd.print("  Both Direction");
delay(2000);
lcd.clear();
delay(500);
for (int a=15; a>=-z;a--)
    {
      lcd.clear();
      if(x+a-16>=0)
      {
        lcd.setCursor(0,0);
        lcd.print(Leftscroll.substring(x+a-16,x));
         }
      else
      {
        i++;
        if(i<16)
        {
          lcd.setCursor(i,0);
          lcd.print(Leftscroll.substring(0,x));
        }
      }
      
      if(a>=0)
      {
        lcd.setCursor(a,1);
        lcd.print(Rightscroll.substring(0,15));
      }
      else
      {
        j++;
        lcd.setCursor(0,1);
        lcd.print(Rightscroll.substring(j,y));
      }
            
    delay(500);
}
}
