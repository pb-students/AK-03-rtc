#include <xc.h>
#include"config_877A.h"

#include "atraso.h" // opoznienia
#include "lcd.h"
#include "i2c.h"
#include "rtc.h"

#include <string.h> // dla strcmp()


void main() 
{
  // przyciski
  TRISB=0x07;
    
  // rtc
  TRISC=0x01;
  i2c_init();
  
  // wyświetlacz
  TRISD=0x00; 
  TRISE=0x00;
  lcd_init();
  lcd_cmd(0x0C);
  lcd_cmd(L_CLR);
  
   
  
  // zad. 1
  // sekundy
/*
  while(1)
  {
    rtc_r();
    lcd_cmd(L_L1);
    lcd_dat(time[6]);
    lcd_dat(time[7]);
    atraso_ms(1000);
   }
  */
  
  
  // zad. 2
  // biezacy czas z RTC
  /*
  while(1)
  {
    rtc_r();
    lcd_cmd(L_L1);
    lcd_str((const char *)time);
    lcd_cmd(L_L2);
    lcd_str((const char *)date);
    atraso_ms(1000); 
  }
  */



 
  // zad. 3  
  /*
  // wstępne wartości
  rtc_r();
  int hh = ((int)time[0] - 48) * 10 + ((int)time[1] - 48); 
  int mm = ((int)time[3] - 48) * 10 + ((int)time[4] - 48);
  int ss = ((int)time[6] - 48) * 10 + ((int)time[7] - 48);
  

  
  char newtime[8];
  int parts = 0;
  while(1)
  {
      lcd_cmd(L_L1);
      newtime[0] = (hh / 10) + '0';
      newtime[1] = (hh % 10) + '0';
      newtime[2] = ':';
      newtime[3] = (mm / 10) + '0';
      newtime[4] = (mm % 10) + '0';
      newtime[5] = ':';
      newtime[6] = (ss / 10) + '0';
      newtime[7] = (ss % 10) + '0';
      lcd_str(newtime);
      atraso_ms(100);
      
      
      
      if (!PORTBbits.RB0)  // zwiekszenie sekund o 1
      {
          ss++;
          if (ss >= 60) ss = ss % 60;
      }
      if (!PORTBbits.RB1)  // zwiekszenie minut o 1
      {
          mm++;
          if (mm >= 60) mm = mm % 60;
      }  
      if (!PORTBbits.RB2)  // zwiekszenie godzin o 1
      {
          hh++;
          if (hh >= 24) hh = hh % 24;
      }  

      // normalna zmiana czasu
      parts++;
      if (parts == 10) 
      {
        parts = 0;  
        ss++;
        if (ss >= 60) 
        {
          ss = 0;
          mm++;
          if (mm >= 60)
          {
            mm = 0;
            hh++;
            if (hh >= 24) hh = 0;
          }
        }
      }
  }
  
  */
  
  
  // zad. 5
  
  char alarm1[] = "05:27:10";
  char alarm2[] = "13:44:30";
  char tekst[] = "ALARM";
  while (1)
  {
    rtc_r();
    lcd_cmd(L_L1);
    lcd_str((const char *)time);
    if (strcmp(alarm1, time) == 0 || strcmp(alarm2, time) == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            rtc_r();            
            lcd_cmd(L_L1);
            lcd_str((const char *)time);
            lcd_cmd(L_L2);
            lcd_str(tekst);
            atraso_ms(500);
            lcd_cmd(L_CLR);
        }
    }
    atraso_ms(500); 
  }
}
