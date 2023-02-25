#include "reg52.h"
#include <string.h>

//--- LCD Control Register Declaration -------
#define RS			P16	
#define RW			P17		
#define E			P11
unsigned char code table[]={0x03,0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x18,0x1E,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
0x07,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x10,0x18,0x1c,0x1E,0x1E,0x1E,0x1E,0x1E,0x0f,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,0x01, 
0x1f,0x1f,0x1f,0x1f,0x1f,0x1c,0x18,0x00,0x1c,0x18,0x10,0x00,0x00,0x00,0x00,0x00};

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


void main()
{		  
	char m=0;
	E = 0;  
 	LCD_init();				//initialize the LCD 
	LCD_Command( 0x01 ); // clear screen
  
		LCD_Command( 0x40 );
		for(m=0;m<64;m++)  
		 {
		LCD_Print(table[m]);
		}
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
		  

 	  while( 1);

	} 

