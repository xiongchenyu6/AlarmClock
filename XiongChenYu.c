 // Include lib
#include "reg52.h"
#include <string.h>
#include <intrins.h> 
//Define Pin and Button

#define RS			P16
#define RW			P17		
#define E		    P11
#define BL			P27
#define BZ			P26
#define PB1			P33
#define PB2			P10
#define PB3			P12	
#define PB4			P13
#define PB5			P14
#define CL	   	    0x3a
#define CM	        0x2c
#define DA		    0x2d
#define uchar unsigned char 
#define uint unsigned int 


uint year_moon,month_moon,day_moon;

unsigned char c_moon; 

unsigned char code year_code[255] = { 
0x04,0xBA,0x53, //2015 
0x0A,0x5B,0x48, //2016 
0x65,0x2B,0xBC, //2017 
0x05,0x2B,0x50, //2018 
0x0A,0x93,0x45, //2019 
0x47,0x4A,0xB9, //2020 
0x06,0xAA,0x4C, //2021 
0x0A,0xd5,0x41, //2022 
0x24,0xdA,0xB6, //2023 
0x04,0xB6,0x4A, //2024 
0x69,0x57,0x3d, //2025 
0x0A,0x4e,0x51, //2026 
0x0d,0x26,0x46, //2027 
0x5e,0x93,0x3A, //2028 
0x0d,0x53,0x4d, //2029 
0x05,0xAA,0x43, //2030 
0x36,0xB5,0x37, //2031 
0x09,0x6d,0x4B, //2032 
0xB4,0xAe,0xBf, //2033 
0x04,0xAd,0x53, //2034 
0x0A,0x4d,0x48, //2035 
0x6d,0x25,0xBC, //2036 
0x0d,0x25,0x4f, //2037 
0x0d,0x52,0x44, //2038 
0x5d,0xAA,0x38, //2039 
0x0B,0x5A,0x4C, //2040 
0x05,0x6d,0x41, //2041 
0x24,0xAd,0xB6, //2042 
0x04,0x9B,0x4A, //2043 
0x7A,0x4B,0xBe, //2044 
0x0A,0x4B,0x51, //2045 
0x0A,0xA5,0x46, //2046 
0x5B,0x52,0xBA, //2047 
0x06,0xd2,0x4e, //2048 
0x0A,0xdA,0x42, //2049 
0x35,0x5B,0x37, //2050 
0x09,0x37,0x4B, //2051 
0x84,0x97,0xC1, //2052 
0x04,0x97,0x53, //2053 
0x06,0x4B,0x48, //2054 
0x66,0xA5,0x3C, //2055 
0x0e,0xA5,0x4f, //2056 
0x06,0xB2,0x44, //2057 
0x4A,0xB6,0x38, //2058 
0x0A,0xAe,0x4C, //2059 
0x09,0x2e,0x42, //2060 
0x3C,0x97,0x35, //2061 
0x0C,0x96,0x49, //2062 
0x7d,0x4A,0xBd, //2063 
0x0d,0x4A,0x51, //2064 
0x0d,0xA5,0x45, //2065 
0x55,0xAA,0xBA, //2066 
0x05,0x6A,0x4e, //2067 
0x0A,0x6d,0x43, //2068 
0x45,0x2e,0xB7, //2069 
0x05,0x2d,0x4B, //2070 
0x8A,0x95,0xBf, //2071 
0x0A,0x95,0x53, //2072 
0x0B,0x4A,0x47, //2073 
0x6B,0x55,0x3B, //2074 
0x0A,0xd5,0x4f, //2075 
0x05,0x5A,0x45, //2076 
0x4A,0x5d,0x38, //2077 
0x0A,0x5B,0x4C, //2078 
0x05,0x2B,0x42, //2079 
0x3A,0x93,0xB6, //2080 
0x06,0x93,0x49, //2081 
0x77,0x29,0xBd, //2082 
0x06,0xAA,0x51, //2083 
0x0A,0xd5,0x46, //2084 
0x54,0xdA,0xBA, //2085 
0x04,0xB6,0x4e, //2086 
0x0A,0x57,0x43, //2087 
0x45,0x27,0x38, //2088 
0x0d,0x26,0x4A, //2089 
0x8e,0x93,0x3e, //2090 
0x0d,0x52,0x52, //2091 
0x0d,0xAA,0x47, //2092 
0x66,0xB5,0x3B, //2093 
0x05,0x6d,0x4f, //2094 
0x04,0xAe,0x45, //2095 
0x4A,0x4e,0xB9, //2096 
0x0A,0x4d,0x4C, //2097 
0x0d,0x15,0x41, //2098 
0x2d,0x92,0xB5, //2099 

}; 
unsigned char code day_code1[9]={0x0,0x1f,0x3b,0x5a,0x78,0x97,0xb5,0xd4,0xf3}; 
unsigned int code day_code2[3]={0x111,0x130,0x14e}; 
unsigned char date[]={"SunMonTueWedThuFriSat"};//setWeek
unsigned char minset=0, hrset=0; //SetTime
unsigned char lcdSetmin1=0, lcdSetmin2=0,lcdSethr1=0, lcdSethr2=0,lcdwhr1=0,lcdwhr2=0; //for Print SetTime
unsigned char Setday=1,Setmonth=1; //SetDate
unsigned char lcdSetday1=0, lcdSetday2=0,lcdSetmonth1=0, lcdSetmonth2=0; //for print SetDate
unsigned char holiday=0 ,SetAlarmmin=0, SetAlarmhr=0;	//SetAlarm
unsigned char lcdSetAlarmmin1, lcdSetAlarmmin2, lcdSetAlarmhr1, lcdSetAlarmhr2;	//for print SetAlarm
unsigned char bstopAlarm=0,bstopBL=0,bstopWatch=0,bstopSetTime,bstopTime=0,bstopSetDate=0;	//boolean
unsigned char msec,sec,min,hr,whr,day=1,month=1,week=12,fyear=20,byear=15;	//for timer0 alarm
unsigned char lcdmbyear1,lcdmbyear2; 
unsigned char lcdfyear1,lcdfyear2,lcdbyear1,lcdbyear2,lcdmsec1,lcdsec1,lcdmin1,lcdhr1,lcdday1,lcdmonth1,lcdmsec2,lcdsec2,lcdmin2,lcdhr2,lcdday2,lcdmonth2;	//for print timer0
unsigned char wmsec,wsec,wmin; //for timer1 stopwatch
unsigned char lcdwmsec1,lcdwsec1,lcdwmin1,lcdwmsec2,lcdwsec2,lcdwmin2;	//for print timer1
unsigned char bexitSetTimeHelp = 0, bexitWatchHelp = 0, exitTimeHelp = 0, bexitSetDateHelp = 0, exitSetAlarmHelp = 0, exitSetMenuHelp = 0, exitTimeHelp1=0;	 //boolean
unsigned char bstart=0,bclrWatchdisplay=0,alarmFlag=0,SnoozeFlag=0,bissextile=0;
unsigned char code table[]={0x03,0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x18,0x1E,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
0x07,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x10,0x18,0x1c,0x1E,0x1E,0x1E,0x1E,0x1E,0x0f,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,0x01, 
0x1f,0x1f,0x1f,0x1f,0x1f,0x1c,0x18,0x00,0x1c,0x18,0x10,0x00,0x00,0x00,0x00,0x00};
unsigned char utc3 = 0,utc1 = 0, utc2 = 0, utc = 8,tc=0;
void Conversion( unsigned char year,unsigned char month,unsigned char  day) 	 ;
//----- Delay Subroutine -------
void delay( unsigned long duration)
{
	while ( ( duration -- )!= 0);
}
//--------- Strobe Signal for LCD -----
void strobe()
{
	E = 1;
	delay( 50 );
	E = 0;
	delay( 50 );
}
//----- LCD initialisation -----
void LCD_init()
{
	unsigned char x;		
	for ( x = 0 ; x < 3 ; x ++){
		P0 = 0x30;
		RS = 0;
		RW = 0;
		strobe();
		delay( 750 );
	}	
	P0 = 0x38;
	strobe();
	P0 = 0x0c;
	strobe();
	P0 = 0x01;
	strobe();
	P0 = 0x02;
	strobe();
}
//----- LCD Character Print routine --------
void LCD_Print( unsigned char x)
{
	P0 = x;
	RS = 1;
	strobe();
}
//----- LCD Command ----------
void LCD_Command( unsigned char x)
{
	P0 = x;
	RS = 0;
	strobe();
}
//------ LCD Line Print ---------
void LCD_Print_Line( printData )
unsigned char *printData;
{
	unsigned char x;
	for( x = 0 ; x < strlen( printData ); x++)
		LCD_Print( printData[ x ] );	
}
void LCD_Print_Week()
{
	 LCD_Print(date[week]);
	 LCD_Print(date[week+1]);
     LCD_Print(date[week+2]);
}
void BackLight()
{
	
	BL=~BL;
	
}
void firstcheckholiday()
{
	if(month==1&&day==1||month==5&&day==1||month==8&&day==9||
	   month==12&&day==25||month==2&&day==19&&fyear==20&&byear==15||
	        month==2&&day==20&&fyear==20&&byear==15||
			month==2&&day==8 &&fyear==20&&byear==16||
	        month==2&&day==9 &&fyear==20&&byear==16||
			month==1&&day==28&&fyear==20&&byear==17||
	        month==1&&day==29&&fyear==20&&byear==17||
			month==2&&day==16&&fyear==20&&byear==18||
	        month==2&&day==17&&fyear==20&&byear==18||
			month==2&&day==5 &&fyear==20&&byear==19||
	        month==2&&day==6 &&fyear==20&&byear==19||
			month==1&&day==25&&fyear==20&&byear==20||
	        month==1&&day==26&&fyear==20&&byear==20||
			month==2&&day==12&&fyear==20&&byear==21||
	        month==2&&day==13&&fyear==20&&byear==21||
			month==2&&day==1 &&fyear==20&&byear==22||
	        month==2&&day==2 &&fyear==20&&byear==22||
			month==1&&day==22&&fyear==20&&byear==23||
	        month==1&&day==23&&fyear==20&&byear==23||
			month==2&&day==10&&fyear==20&&byear==24||
	        month==2&&day==11&&fyear==20&&byear==24||
			month==4&&day==3 &&fyear==20&&byear==15||
			month==6&&day==1 &&fyear==20&&byear==15||
			month==7&&day==17&&fyear==20&&byear==15||
			month==9&&day==24&&fyear==20&&byear==15||
			month==11&&day==10&&fyear==20&&byear==15)
	{
	     holiday=1;
	}
	else holiday=0;
}
void timer0 (void) interrupt 1					 //clock
{
	TF0=0;
	TH0=0XB1;
	TL0=0XE0;									 //10ms
	msec++;
	if(msec==100)
	{
		sec++;
		msec=0;
		if (sec == 60)
		{
			min++;
	    sec = 0;
		} 
		if (min == 60)
	    {
			hr++;
			min =0;
	    }
	    if (hr == 24 )
	    {
			hr=0;
			day++;
			week+=3;
	    }
		if(week==23)
		{
		    week=0;
		}
		if(day==32)
		{
		    day=1;
		    month++;
		}
		if(month==13)
		{
		    sec = 0;					
	 		min = 0;
			hr=0;
			day=1;
			month=1;
			byear++;
		}
		if(byear==99) fyear++;
	}
	lcdsec1 = (sec/10) | 0x30;
	lcdsec2 = (sec%10) | 0x30;
	lcdmin1 = (min/10) | 0x30;
	lcdmin2 = (min%10) | 0x30;
	lcdhr1 = (hr/10) | 0x30;
	lcdhr2 = (hr%10) | 0x30;
	lcdday1 = (day/10) | 0x30;
	lcdday2 = (day%10) | 0x30;
	lcdmonth1 = (month/10) | 0x30;
	lcdmonth2 = (month%10) | 0x30;
	lcdfyear1=(fyear/10) | 0x30;
	lcdfyear2=(fyear%10) | 0x30;
	lcdbyear1=(byear/10) | 0x30;
	lcdbyear2=(byear%10) | 0x30;
}
void timer1 (void) interrupt 3
{
	TF1=0;
	TH1=0XB1;
	TL1=0XE0;
	wmsec++;
	if(wmsec==100)
	{
		wsec++;
		wmsec=0;
		if (wsec == 60)
		{
			wmin++;
	    wsec = 0;
		} 
		if (wmin == 60)
	    {
			wmin =0;
	    }
	}
	lcdwmsec1 = (wmsec/10) | 0x30;
	lcdwmsec2 = (wmsec%10) | 0x30;
	lcdwsec1 = (wsec/10) | 0x30;
	lcdwsec2 = (wsec%10) | 0x30;
	lcdwmin1 = (wmin/10) | 0x30;
	lcdwmin2 = (wmin%10) | 0x30;
}
void LCD_PrintDate()
{
  LCD_Print_Week();
  LCD_Print(CM);
  LCD_Print(lcdmonth1);
  LCD_Print(lcdmonth2);
  LCD_Print(DA);
  LCD_Print(lcdday1);
  LCD_Print(lcdday2);
  LCD_Print(DA);
  LCD_Print(lcdfyear1);
  LCD_Print(lcdfyear2);
  LCD_Print(lcdbyear1);
  LCD_Print(lcdbyear2);
    LCD_Print(CM);
  if(holiday==1)
  {
      LCD_Print('H');
  }
  else LCD_Print(' ');
}
 void LCD_PrintTimeSet()
{
    lcdSethr1 = (hrset/10) | 0x30;
	lcdSethr2 = (hrset%10) | 0x30;
	lcdSetmin1 = (minset/10) | 0x30;
	lcdSetmin2 = (minset%10) | 0x30;
	
    LCD_Print(lcdSethr1);
    LCD_Print(lcdSethr2);
    LCD_Print(CL);
    LCD_Print(lcdSetmin1);
    LCD_Print(lcdSetmin2);
}
void LCD_PrintDateSet()
{
 	lcdSetday1 = (Setday/10) | 0x30;
	lcdSetday2 = (Setday%10) | 0x30;
	lcdSetmonth1 = (Setmonth/10) | 0x30;
	lcdSetmonth2 = (Setmonth%10) | 0x30;
	lcdfyear1=(fyear/10) | 0x30;
	lcdfyear2=(fyear%10) | 0x30;
	lcdbyear1=(byear/10) | 0x30;
	lcdbyear2=(byear%10) | 0x30;

    LCD_Print_Week();
    LCD_Print(CM);
    LCD_Print(lcdSetmonth1);
    LCD_Print(lcdSetmonth2);
    LCD_Print(DA);
    LCD_Print(lcdSetday1);
    LCD_Print(lcdSetday2);
	LCD_Print(DA);
	LCD_Print(lcdfyear1);
    LCD_Print(lcdfyear2);
	LCD_Print(lcdbyear1);
    LCD_Print(lcdbyear2);
}

void LCD_PrintLunar()
{
   
 	lcdSetday1 = (day_moon/10) | 0x30;
	lcdSetday2 = (day_moon%10) | 0x30;
	lcdSetmonth1 = (month_moon/10) | 0x30;
	lcdSetmonth2 = (month_moon%10) | 0x30;
	lcdmbyear1=(year_moon/10) | 0x30;
	lcdmbyear2=(year_moon%10) | 0x30;

    LCD_Print(lcdSetmonth1);
    LCD_Print(lcdSetmonth2);
    LCD_Print(DA);
    LCD_Print(lcdSetday1);
    LCD_Print(lcdSetday2);		
	LCD_Print(DA);
	LCD_Print(lcdfyear1);
    LCD_Print(lcdfyear2);
	LCD_Print(lcdmbyear1);
    LCD_Print(lcdmbyear2);
}
void LCD_PrintAlarm()
{
	lcdSetAlarmmin1 = (SetAlarmmin/10) | 0x30;
	lcdSetAlarmmin2 = (SetAlarmmin%10) | 0x30;
	lcdSetAlarmhr1 = (SetAlarmhr/10) | 0x30;
	lcdSetAlarmhr2 = (SetAlarmhr%10) | 0x30;

	LCD_Print(lcdSetAlarmhr1);
    LCD_Print(lcdSetAlarmhr2);
    LCD_Print(CL);
 	LCD_Print(lcdSetAlarmmin1);
 	LCD_Print(lcdSetAlarmmin2);	
}

void DIDIDI()
{
   BZ = 1;
   delay(1000);
   BZ = 0;
   delay(1000);
}
void FlashLight()
{
   BL = 1;
   delay(1000);
   BL = 0;
   delay(1000);
}
void alarmCheck()
{	if(hr == 7&&min == 0)
{
 BL = 1;
}
if(hr==19&&min == 0)
{
 BL = 0;
}
	if (hr == SetAlarmhr && min == SetAlarmmin && alarmFlag == 1)
	{
		LCD_Command(0x01);
		for (;;)
		{
			LCD_Command(0x80);
			LCD_Print_Line("Button 3 to SNOOZE");
			//add
			DIDIDI();
			FlashLight();
			//
			LCD_Command(0xC0);
			LCD_Print_Line("Button 4 to cancel");
			if (PB3 == 0)
			{
				SnoozeFlag = 1;
				SetAlarmmin = min;
				SetAlarmmin += 1;
				break;
			}
			if (PB4 == 0)
			{
				alarmFlag = 0;
				SetAlarmhr = 0;
				SetAlarmmin =0;
				SnoozeFlag = 0;
				break;
			}
		}
		LCD_Command(0x01);
		BZ = 0;
		BL = 0;
	}
}
void setDate()
{
	LCD_Command(0x01);
	for(;;)
	{
		alarmCheck();

		 if(PB1==0)
		{ 
			Setmonth++;
			if(Setmonth>12)Setmonth=1;
			if(Setmonth==1 || Setmonth==3 || Setmonth==5 || Setmonth==7 || Setmonth==8 || Setmonth==10 || Setmonth==12  )
			{		week+=9;
			if(week>20) week=0; 
				delay(9000);
			}
			else if(Setmonth ==2)
			{
			    if(bissextile==1)
				{ 		week+=3;
			if(week>20) week=0; 
				    delay(9000);
				}
				else
				{		week+=0;
			if(week>20) week=0; 
				    delay(9000);
				}
			}
			else if(Setmonth==4 || Setmonth==9 || Setmonth==6 || Setmonth==11 )
			{
			week+=6;
			if(week>20) week=0; 
				delay(9000);
			} 
            delay(9000);
		}

		else if(PB2==0)
		{	
		    week+=3;
			if(week>20) week=0; 
			if(Setmonth==1 || Setmonth==3 || Setmonth==5 || Setmonth==7 || Setmonth==8 || Setmonth==10 || Setmonth==12  )
			{
				Setday++;
				if(Setday>31) Setday=1;
				delay(9000);
			}
			else if(Setmonth ==2)
			{
			    if(bissextile==1)
				{ 
				    Setday++;
				    if(Setday>29) Setday=1;
				    delay(9000);
				}
				else
				{
					Setday++;
				    if(Setday>28) Setday=1;
				    delay(9000);
				}
			}
			else if(Setmonth==4 || Setmonth==9 || Setmonth==6 || Setmonth==11 )
			{
				Setday++;
				if(Setday>30) Setday=1;
				delay(9000);
			} 
			else{}
		}
		
else if(PB3==0)
 { 
 if(week==0) 
 {
   week=18;
 }
  else
 {
 week-=3;
 }




if(Setmonth==1 || Setmonth==3 || Setmonth==5 || Setmonth==7 || Setmonth==8 || Setmonth==10 || Setmonth==12 )
 {
 Setday--;
 if(Setday<1) Setday=31;
 delay(9000);
 }
 else if(Setmonth ==2)
 {
 if(bissextile==1)
 { 
 Setday--;

if(Setday<1) Setday=29;

delay(9000);
 }
 else
 {
 Setday--;

if(Setday<1) Setday=28;

delay(9000);
 }
 }
 else if(Setmonth==4 || Setmonth==6 || Setmonth==9 || Setmonth==11 )
 {
 Setday--;
 if(Setday<1) Setday=30;
 delay(9000);
 }
 }

		else if(PB4==0)
		{
		      byear++;
			  if(byear==100) 
			  {
			     fyear++;
				 byear=0;
			  }

			  if((fyear%4*100+byear)%4==0)
			  {
			   week+=3;
		   	if(week>20) 
			  week=0; 
			  bissextile=1;
			  }
			  else
			  {
			  	   week+=6;
		   	if(week>20) 
			  week=0; 
			  bissextile=0;
			  }
			  delay(9000);
		}
		else if(PB5==0)
		{	 	
		    LCD_Command(0x01);
			delay(9000);
			break;
		}
		LCD_Command(0x80);
		LCD_Print_Line("SET DATE:");
		LCD_Command(0xC0);
		LCD_PrintDateSet();
		day=Setday;
		month=Setmonth;	
	}
}

void setTime()
{
	LCD_Command(0x01);
	for(;;)
	{
		alarmCheck();
		if(PB1==0)
		{
			hrset++;
			if(hrset>23) hrset=0; 
			delay(9000);
		}
		else if(PB2==0)
		{
			minset++; 
			if(minset>59) minset=0;
			delay(9000);
		}
		else if(PB3==0)
		{
			if(minset<1) minset=60;
			minset--;
			delay(9000);
		}
		 
		else if(PB5==0)	
		{
		    LCD_Command(0x01);
			delay(9000);
			break;
		}	
		LCD_Command(0x80);
		LCD_Print_Line("SET TIME:");
		LCD_Command(0xC0);
		LCD_PrintTimeSet();
		if(minset!=0||hrset!=0)
		{	
			hr=hrset;
			min=minset;
		}
	}
}
void clrWatch()
{
	wmsec=0;
	wsec=0;
	wmin=0;
}

void LCD_PrintTime()
{
	LCD_Print(lcdhr1);
    LCD_Print(lcdhr2);
    LCD_Print(CL);
    LCD_Print(lcdmin1);
    LCD_Print(lcdmin2);
    LCD_Print(CL);
    LCD_Print(lcdsec1);
    LCD_Print(lcdsec2);
}

void LCD_PrintWatch()
{
	LCD_Print(lcdwmin1);
    LCD_Print(lcdwmin2);
    LCD_Print(CL);
    LCD_Print(lcdwsec1);
    LCD_Print(lcdwsec2);
	LCD_Print(CL);
    LCD_Print(lcdwmsec1);
    LCD_Print(lcdwmsec2);
}
void Runtimer1()
{
	for(;;)
	{
		alarmCheck();
		if((bclrWatchdisplay==1)&&(TR1==0))
		{
			LCD_Command(0x80);
			LCD_Print_Line("StopWatch:");
			LCD_Command(0xc4);
			LCD_Print_Line("00:00:00");
		}
		else
		{
			LCD_Command(0x80);
			LCD_Print_Line("StopWatch:");
			LCD_Command(0xc4);
			LCD_PrintWatch();
		}
		if((PB1==0)&&(bstopWatch==0))
		{
			bstopWatch=1;
		}
		if((PB1==1)&&(bstopWatch==1))
		{
			bstopWatch=2;
		}					
		if((PB1==0)&&(bstopWatch==2))
		{
			bstopWatch=0;
			bclrWatchdisplay=0;
			TR1=~TR1;
		}
		if(PB2==0)
		{
			bclrWatchdisplay=1;
			clrWatch();		
		}
	
		if(PB5==0)
		{	delay(9000);
			break;
		}
	}
}
void StopWatch()
{
	if(bstart==0)
	{
		LCD_Command(0x01);
		LCD_Command(0x80);
		LCD_Print_Line("StopWatch:");
		LCD_Command(0xc4);
		LCD_Print_Line("00:00:00");
	}
	else
	{
		LCD_Command(0x01);
		LCD_Command(0x80);
		LCD_Print_Line("StopWatch:");
		LCD_Command(0xc4);
		LCD_PrintWatch();
	}
	for(;;)
	{
		alarmCheck();
		if(bstart==1)
		{
			 Runtimer1();
		}
		while(PB1==0)
		{
			bstart=1;
			LCD_Command(0x01);
			TR1 = 1;
			Runtimer1();
		}
		if (PB5 == 0)
		{
			Runtimer1();
		}

		if(PB5==0)
		{
			break;
		}
	}
}
void lunar()
{ 

LCD_Command( 0x01 );
     
  	for(;;)
	{
		alarmCheck();
		LCD_Command(0x80);
		LCD_Print_Line("Lunar: ");
	   LCD_PrintLunar();
	   LCD_Command(0xc0);
	   	if(month==1&&day==1)
	        {
		        holiday=1;
	            LCD_Print_Line("New Year Day");
		    }
	        else if(month==5&&day==1)
	        {
	            holiday=1;
	     	    LCD_Print_Line("Labour Day");
		    }
            else if(month==8&&day==9)
	       {
	            holiday=1;
	        	LCD_Print_Line("National Day");
	     	}												   
            else if(month==12&&day==25)
	        {
	            holiday=1;
	     	    LCD_Print_Line("Christmas Day");
		    }
	        else if(month==2&&day==19&&fyear==20&&byear==15||
	               month==2&&day==20&&fyear==20&&byear==15||
			       month==2&&day==8 &&fyear==20&&byear==16||
	               month==2&&day==9 &&fyear==20&&byear==16||
			       month==1&&day==28&&fyear==20&&byear==17||
	               month==1&&day==29&&fyear==20&&byear==17||
			       month==2&&day==16&&fyear==20&&byear==18||
	               month==2&&day==17&&fyear==20&&byear==18||
			       month==2&&day==5 &&fyear==20&&byear==19||
	               month==2&&day==6 &&fyear==20&&byear==19||
			       month==1&&day==25&&fyear==20&&byear==20||
	               month==1&&day==26&&fyear==20&&byear==20||
			       month==2&&day==12&&fyear==20&&byear==21||
	               month==2&&day==13&&fyear==20&&byear==21||
			       month==2&&day==1 &&fyear==20&&byear==22||
	               month==2&&day==2 &&fyear==20&&byear==22||
			       month==1&&day==22&&fyear==20&&byear==23||
	               month==1&&day==23&&fyear==20&&byear==23||
			       month==2&&day==10&&fyear==20&&byear==24||
	               month==2&&day==11&&fyear==20&&byear==24)
	       {
	            holiday=1;
	     	    LCD_Print_Line("Chinese New Year");
		   }
	       else if(month==4&&day==3 &&fyear==20&&byear==15)
	       {
	            holiday=1;
	     	    LCD_Print_Line("Good Friday");
	        }
	        else if(month==6&&day==1 &&fyear==20&&byear==15)
	        {
	            holiday=1;
	     	    LCD_Print_Line("Vesak Day");
	       	}
	        else if(month==7&&day==17 &&fyear==20&&byear==15)
	        {
	            holiday=1;
	     	    LCD_Print_Line("Hari Raya");
	     	}
	        else if(month==9&&day==24 &&fyear==20&&byear==15)
	        {
	            holiday=1;
	          	LCD_Print_Line("Hari Raya Haji");
		    }
		    else if(month==11&&day==10 &&fyear==20&&byear==15)
	        {
	            holiday=1;
	     	    LCD_Print_Line("Deepavali");
		     }

             else 
			 {
			    holiday=0;
			 }
		if(PB5==0)
		{  delay(9000);
			break;
		}
	}

}
void worldtime()
{
	LCD_Command(0x01);
	for(;;)
	{
	 LCD_Command(0x80);
	LCD_Print_Line("UTC");
	if(utc <= 12)
	{
	LCD_Print_Line("+");
	utc1 = (utc/10) | 0x30;
	utc2 = (utc%10) | 0x30;
    }

    else

{
	LCD_Print_Line("-");
	utc3 = 25- utc;
	utc1 = (utc3/10) | 0x30;
	utc2 = (utc3%10) | 0x30;	
}
	   LCD_Print(utc1);
	  LCD_Print(utc2);	
	LCD_Print_Line(":00");
	  LCD_Command(0xc0);	
	lcdwhr1 = (whr/10) | 0x30;
	lcdwhr2 = (whr%10) | 0x30;
	LCD_Print(lcdwhr1);
    LCD_Print(lcdwhr2);
    LCD_Print(CL);
    LCD_Print(lcdmin1);
    LCD_Print(lcdmin2);
    LCD_Print(CL);
    LCD_Print(lcdsec1);
    LCD_Print(lcdsec2);
		if(PB1==0)
		{
			if (utc==24)
			{ 	utc=1;
			
			}
			else
			{
			 			
				utc++;
				
			}
			whr = hr;
	if(utc<=8)
	{
		tc = 8-utc;
		for(tc;tc>0;tc--)
		{
			if (whr==0)
			{
				whr=23;
				
			}else
				{
			whr -= 1; 
				}
		}
			
		
		
	}
	else
	{
		tc = utc-8;
	for(tc;tc>0;tc--)
		{
			if (whr>=23)
			{
				whr=0;
				
			}else
				{
			whr += 1; 
				}
		}
		
	}		
			delay(9000);
		}
		else if(PB2==0)
		{
			if(utc==1)
			{
				utc = 24;
				
			}else{
			utc--; }
			whr = hr;
	if(utc<=8)
	{
		tc = 8-utc;
		for(tc;tc>0;tc--)
		{
			if (whr==0)
			{
				whr=23;
				
			}else
				{
			whr -= 1; 
				}
		}
			
		
		
	}
	else
	{
		tc = utc-8;
	for(tc;tc>0;tc--)
		{
			if (whr>=23)
			{
				whr=0;
				
			}else
				{
			whr += 1; 
				}
		}
		
	}		
			delay(9000);
		}
		else if(PB5==0)	
		{
			delay(9000);
			break;
		}	

	}
}
	
	

void Time()
{
	LCD_Command( 0x01 );
	for(;;)
	{
		alarmCheck();
		firstcheckholiday();
		LCD_Command(0x80);
		LCD_PrintDate();
		LCD_Command(0xc1);
		LCD_Print_Line("Time: ");
		LCD_PrintTime();
		if(PB1==0)
		{
			bstopSetTime=1;
		}
		if((PB1==1)&&(bstopSetTime==1))	   
		{
			setTime();
			bstopSetTime=0;
		}
		if(PB2==0)
		{
			bstopSetDate=1;
		}
		if((PB2==1)&&(bstopSetDate==1))
		{
			setDate();
			bstopSetDate=0;
		}	
	      if(PB3==0)
		{	Conversion(byear,month,day);
	
	    	         	
			lunar();
		}	      
		if(PB4==0)
		{	
	worldtime();
		}

		if(PB5==0)
		{	 delay(9000);
			break;
		}
	}
}




void setAlarm()
{
	LCD_Command(0x01);	
	for(;;)
	{
		//alarmCheck();
		if(PB1==0)
		{
			SetAlarmhr++;
			if(SetAlarmhr>23) SetAlarmhr=0; 
			delay(9000);
			alarmFlag=1;
		}
		
		if(PB2==0)
		{
			SetAlarmmin++; 
			if(SetAlarmmin>59)SetAlarmmin=0;
			delay(9000);
			alarmFlag=1;
		}
		if(PB3==0)
		{
			if(SetAlarmmin<1)SetAlarmmin=60;
			SetAlarmmin--;
            delay(9000);
			alarmFlag=1;	
		}
		
		if(PB5==0)
		{	delay(9000);
			break;
		}
		LCD_Command(0x80);
	    LCD_Print_Line("SET ALARM");
	    LCD_Command(0xC0);
	    LCD_PrintAlarm();
	}
}
void opening ()
{	 char m=0;

   LCD_Command( 0x40 );
		for(m=0;m<64;m++)  
		 {
		LCD_Print(table[m]);
		}
		LCD_Command( 0x80 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc0 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x81 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc1 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);

		LCD_Command( 0x01 );
			LCD_Command( 0x82 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc2 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x83 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc3 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x84 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc4 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x85 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc5 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x86 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc6 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x87 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc7 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x88 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc8 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x89 );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xc9 );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x8a );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}
    	LCD_Command( 0xca );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);
		LCD_Command( 0x01 );
			LCD_Command( 0x8b );	
		for(m=0;m<4;m++)  
		{
		  LCD_Print(m);
		
		}						
    	LCD_Command( 0xcb );	
		for(m=4;m<8;m++)  
		{
		  LCD_Print(m);
		
		}
	delay(2000);

}
void main()
{  
	BZ= 0;  //Off Buzzer
	BL= 0;	//Off BL	
	E = 0;  
	LCD_init();	//initialize the LCD 
	LCD_Command( 0x01 );	// clear screen
	EA=1;
    ET0=1;
	ET1=1;
    TMOD = 0x11;
    TR0 = 1;
	TR1 = 0;
    opening ();  
	LCD_Command( 0x01 );	
	for(;;)
	{
		alarmCheck();
		LCD_Command(0x80);
		LCD_Print_Line("B1 Date B2 SetA       ");
		LCD_Command(0xc0);
		LCD_Print_Line("B3 StopW B5 BL       ");

		if(PB1==0)
		{
			bstopTime=1;
		}
		if((PB1==1)&&(bstopTime==1))
		{
			Time();
			bstopTime=0;
		}

		if(PB2==0)										   
		{
			setAlarm();
		}

		while(PB3==0)
		{
			StopWatch();
		}
				
		if (PB5 == 0)
		{
			bstopBL=1;
		}
		if ((PB5 == 1)&&(bstopBL==1))
		{
			BackLight();
			bstopBL	=0;
		}

	}
}






char get_moon_day(uchar month_p,uint table_addr) 
{ 
uchar temp; 
 switch (month_p) 
 { 
 case 1:{temp=year_code[table_addr]&0x08; 
  if (temp==0)return(0);else return(1);} 
 case 2:{temp=year_code[table_addr]&0x04; 
  if (temp==0)return(0);else return(1);} 
 case 3:{temp=year_code[table_addr]&0x02; 
  if (temp==0)return(0);else return(1);} 
 case 4:{temp=year_code[table_addr]&0x01; 
  if (temp==0)return(0);else return(1);} 
 case 5:{temp=year_code[table_addr+1]&0x80; 
  if (temp==0) return(0);else return(1);} 
 case 6:{temp=year_code[table_addr+1]&0x40; 
  if (temp==0)return(0);else return(1);} 
 case 7:{temp=year_code[table_addr+1]&0x20; 
  if (temp==0)return(0);else return(1);} 
 case 8:{temp=year_code[table_addr+1]&0x10; 
  if (temp==0)return(0);else return(1);} 
 case 9:{temp=year_code[table_addr+1]&0x08; 
  if (temp==0)return(0);else return(1);} 
 case 10:{temp=year_code[table_addr+1]&0x04; 
  if (temp==0)return(0);else return(1);} 
 case 11:{temp=year_code[table_addr+1]&0x02; 
  if (temp==0)return(0);else return(1);} 
 case 12:{temp=year_code[table_addr+1]&0x01; 
  if (temp==0)return(0);else return(1);} 
 case 13:{temp=year_code[table_addr+2]&0x80; 
  if (temp==0)return(0);else return(1);} 
 } 
}
 
void Conversion( unsigned char year,unsigned char month,unsigned char  day) 
{ 
 uchar temp1,temp2,temp3,month_p; 
 uint temp4,table_addr; 
 char flag2,flag_y; 
  table_addr=(year-15)*0x3;  
 temp1=year_code[table_addr+2]&0x60; 
 temp1=_cror_(temp1,5); 
 temp2=year_code[table_addr+2]&0x1f; 
 if(temp1==0x1) 
 { 
  temp3=temp2-1; 
 } 
 else 
 { 
  temp3=temp2+0x1f-1; 
 } 
 if (month<10) 
 { 
  temp4=day_code1[month-1]+day-1; 
 } 
 else 
 { 
  temp4=day_code2[month-10]+day-1; 
 } 
 if ((month>0x2)&&(year%0x4==0)) 
 { 
  temp4+=1; 
 } 
 if (temp4>=temp3) 
 { 
 temp4-=temp3; 
 month=0x1; 
 month_p=0x1;
 flag2=get_moon_day(month_p,table_addr); 
 flag_y=0; 
 if(flag2==0)temp1=0x1d; 
 else temp1=0x1e; 
 temp2=year_code[table_addr]&0xf0; 
 temp2=_cror_(temp2,4);
 while(temp4>=temp1) 
 { 
 temp4-=temp1; 
 month_p+=1; 
 if(month==temp2) 
 { 
 flag_y=~flag_y; 
 if(flag_y==0) 
 month+=1; 
 } 
 else month+=1; 
 flag2=get_moon_day(month_p,table_addr); 
 if(flag2==0)temp1=0x1d; 
 else temp1=0x1e; 
 } 
 day=temp4+1; 
 } 
 else 
 { 
 temp3-=temp4; 
 year-=1; 
 table_addr-=0x3; 
 month=0xc; 
 temp2=year_code[table_addr]&0xf0; 
 temp2=_cror_(temp2,4); 
 if (temp2==0) 
 month_p=0xc; 
 else 
 month_p=0xd; 
 flag_y=0; 
 flag2=get_moon_day(month_p,table_addr); 
 if(flag2==0)temp1=0x1d; 
 else temp1=0x1e; 
 while(temp3>temp1) 
 { 
  temp3-=temp1; 
  month_p-=1; 
  if(flag_y==0)month-=1; 
  if(month==temp2)flag_y=~flag_y; 
  flag2=get_moon_day(month_p,table_addr); 
  if(flag2==0)temp1=0x1d; 
  else temp1=0x1e; 
 } 
 day=temp1-temp3+1; 
 } 
 c_moon=1; 
 year_moon=year; 
month_moon=month; 
day_moon=day; 	
} 							   

 
