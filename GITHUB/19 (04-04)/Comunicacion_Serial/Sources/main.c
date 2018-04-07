/* ###################################################################
**     Filename    : main.c
**     Project     : Comunicacion_Serial
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-01-15, 14:06, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AS1.h"
#include "AD1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
#include "Bit4.h"
#include "Bit5.h"
#include "Bit6.h"
#include "Bit7.h"
#include "AD2.h"
#include "AD3.h"
#include "TI1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


bool boton1= TRUE;
bool boton2= TRUE;
bool inicio= TRUE;
bool GSR=TRUE;
bool m= 0;
//unsigned char codError;


/*PARA ENVIAR BLOQUE SERIAL

unsigned int Enviados= 5;

typedef union{
	unsigned char b5[5];
	//unsigned int b16;
}SENAL;

volatile SENAL bloque;

*/

//int estado = esperar;

//	PARA ENVIAR SEÑAL DEL POTENCIOMETRO
 
unsigned int Enviados = 7;
unsigned char Button;

typedef union{
	unsigned char b8[2];
	unsigned int b16;
}SENAL;

volatile SENAL iADC, iADC2, iADC3, iADC4,  byte1, byte2, byte3, byte4, byte5, byte6;


unsigned char array[7];


/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  
  //estado = enviar; 
    estado=esperar;
	
    
  //Para enviar un bloque por serial

  /* 
  bloque.b5[0]=0x59;
  bloque.b5[1]=0x55;
  bloque.b5[2]=0x52;
  bloque.b5[3]=0x41;
  bloque.b5[4]=0x20;
  */
  
  /* For example: for(;;) { } */

for(;;){

	//boton1 = Bit1_GetVal();
	//Bit2_PutVal(boton1);
	//boton2 = Bit3_GetVal();
	//Bit4_PutVal(boton2);
	//Bit2_PutVal(boton1);

//   	PARA EL POTENCIOMETRO 	  
	  switch (estado){
	    		
	  	  case esperar:
	  		  break;
	    			
	  	  case medir:
	  		  
	  		  //AD1_Measure(TRUE);
	  		  //AD1_GetValue(&iADC.b16);
	  		  AD1_MeasureChan(TRUE,0);
	  		  AD1_GetChanValue(0, &iADC.b16);	  		  
	  		  //AD1_Measure(TRUE);
	  		  //AD1_GetValue16(&iADC.b16);
	  		  //byte2.b16[1] = !Bit1_GetVal();
	  		  iADC.b16 = iADC.b16 >>4;
			  byte1.b16 = iADC.b16 & 0x7F;
			  byte2.b16 = iADC.b16 >> 7;
			  byte2.b16=byte2.b16 & 0x1F; //000A1A1A1A1A1
			  
			  
			  AD2_MeasureChan(TRUE,0);
			  AD2_GetChanValue(0, &iADC2.b16);	  		  
			  //AD1_Measure(TRUE);
			  //AD1_GetValue16(&iADC.b16);
			  //byte2.b16[1] = !Bit1_GetVal();
			  iADC2.b16 = iADC2.b16 >>4;
			  byte3.b16 = iADC2.b16 & 0x7F;
			  byte4.b16 = iADC2.b16 >> 7;
			  byte4.b16=byte4.b16 & 0x1F; //000A1A1A1A1A1	  		  
			  
			  //AD1_Measure(TRUE);
			  
			  AD3_MeasureChan(TRUE,0);
			  AD3_GetChanValue(0, &iADC3.b16);	  		  
			  //AD1_Measure(TRUE);
			  //AD1_GetValue16(&iADC.b16);
			  //byte2.b16[1] = !Bit1_GetVal();
			  iADC3.b16 = iADC3.b16 >>4;
			  byte5.b16 = iADC3.b16 & 0x7F;
			  byte6.b16 = iADC3.b16 >> 7;
			  byte6.b16=byte6.b16 & 0x1F; //000A1A1A1A1A1
			 /*
			  AD1_MeasureChan(TRUE,1);
			  AD1_GetChanValue(1, &iADC2.b16);	  		  
			  //AD1_Measure(TRUE);
			  //AD1_GetValue16(&iADC.b16);
			   //byte2.b16[1] = !Bit1_GetVal();
			  iADC2.b16 = iADC2.b16 >>4;
			  byte3.b16 = iADC2.b16 & 0x7F;
			  byte4.b16 = iADC2.b16 >> 7;
			  byte4.b16=byte4.b16 & 0x1F; //000A1A1A1A1A1
			  
			  
			  AD1_MeasureChan(TRUE,2);
			  AD1_GetChanValue(2, &iADC3.b16);	  		  
			  //AD1_Measure(TRUE);
			  //AD1_GetValue16(&iADC.b16);
			  //byte2.b16[1] = !Bit1_GetVal();
			  iADC3.b16 = iADC3.b16 >>4;
			  byte5.b16 = iADC3.b16 & 0x7F;
			  byte6.b16 = iADC3.b16 >> 7;
			  byte6.b16=byte6.b16 & 0x1F; //000A1A1A1A1A1
			  /*
			   
			   */
			  
			  GSR=Bit7_GetVal();
			  
			  
			  Bit6_PutVal(inicio);
			  Bit2_PutVal(boton1); 
			  Bit4_PutVal(boton2);	
			 			  
			  inicio = Bit5_GetVal();
			 			  
			 if (inicio ==0)
			 {	  
			 		Bit6_PutVal(inicio);	
			 		byte2.b16=byte2.b16 | 0x20;					  	  
			 		 m=1;			  				      
			 			  				      
			  }
			 			  
			 if(m==1)
			 {
			 		 byte2.b16=byte2.b16 | 0x20;	
			 		 Bit6_PutVal(inicio);	
			 		 boton1 = Bit1_GetVal();
			 		 boton2 = Bit3_GetVal();
			 				  				  
			 }
			 			  
			  if (boton1 ==0)
			 {	  
			 		 Bit2_PutVal(boton1);	
			 		 Bit6_PutVal(inicio);							 
			 		 Bit4_PutVal(boton2);	
			 		 byte2.b16=byte2.b16 & 0x1F;
			 		 byte2.b16=byte2.b16 | 0x40;	
			 		 m=0;			  				      
			 			  			  				      
			  }
			 else
			 			  {
			 				  Bit2_PutVal(boton1);
			 			  }
			 			  
			 			  if (boton2 ==0)
			 			 {	  
			 				  Bit2_PutVal(boton1);	
			 				  Bit6_PutVal(inicio);							 
			 			 	  Bit4_PutVal(boton2);	
			 			 	  byte2.b16=byte2.b16 & 0x1F;
			 			 	  byte2.b16=byte2.b16 & 0xBF;	
			 			 	  m=0;			  				      
			 			 			  			  				      
			 			  }
			 			 else
			 			 {
			 			 	  Bit4_PutVal(boton2);
			 			 }
			 			 	
	  	
			  array[0]=0xF2;
			  array[1]=byte2.b16;
			  array[2]=byte1.b16;
			 			  
			  			 
			 
			 array[3]=byte4.b16;
			 array[4]=byte3.b16;
			 
			 array[5]=byte6.b16;
			 array[6]=byte5.b16;
			 						 			  
			   			 /* 
			 			  if (inicio ==0)
			 				  {	  
			 				      Bit6_PutVal(inicio);				       
			 				      byte2.b16=byte2.b16 | 0x40;				      
			 				      m=0;
			 				      
			 				      
			 				  }
			 			  else 
			 			  	  {
			 			  		  Bit6_PutVal(inicio); 
			 			  		  byte2.b16=byte2.b16 | 0x40;	
			 			  	  }
			 			
			 			  if (m==0)
			 			  	  {	  
			 				  	 
			 				      if (boton1 ==0)
			 				      		{
			 				      			  Bit2_PutVal(boton1); 
			 				      			  byte2.b16=byte2.b16 | 0x40;
			 				      			  m=1;
			 				      			 
			 				      		}
			 				       else
			 				      		{
			 				      			  Bit2_PutVal(boton1);
			 				      			  if (boton2 == 0)
			 				      			  	  {
			 				      			 		  Bit4_PutVal(boton2);	
			 				      			 		  byte2.b16=byte2.b16 & 0xBF;
			 				      			 		  m=1;
			 				      			 	  }
			 				      			  else
			 				      			 	   {
			 				      			 		   Bit4_PutVal(boton2);
			 				      			 	   }
			 				      	    }
			 			  	  }		 			  		
			  
			  array[0]=0xF2;
			  array[1]=byte2.b16;
			  array[2]=byte1.b16;
			  
			  
			  AD1_MeasureChan(TRUE,1);
			  AD1_GetChanValue(1, &iADC2.b16);	  		  
			  //AD1_Measure(TRUE);
			  //AD1_GetValue16(&iADC.b16);
			  //byte2.b16[1] = !Bit1_GetVal();
			  iADC2.b16 = iADC2.b16 >>4;
			  byte3.b16 = iADC2.b16 & 0x7F;
			  byte4.b16 = iADC2.b16 >> 7;
			  byte4.b16=byte4.b16 & 0x1F; //000A1A1A1A1A1
						 			  
			 			  
			  
			 	
				    		    
			   	  
			*/	
					  
			  //Para enviar el bloque del protocolo por serial 
			  
			   	      
			   //byte2.b16[1]= Button;			   
			  	
			  // array[3]=byte4.b16;
			   //array[4]=byte3.b16;	
					  
			   estado = enviar;

	  	  case enviar: 	  
	  		  AS1_SendBlock(&array,7,&Enviados);
	  		  estado = esperar;
	  		  
	  	  default:
	  		  break;
	    	
	  }  
}
//PAra enviar bloque 

 	  
	 /* switch(estado){
	  	  	  case  enviar:
	  	  		  AS1_SendBlock(&bloque.b5,5,&Enviados);
	  	  		  estado=esperar;
	  	  		  
	  	  	  case esperar:
	  	  		  break;
	  	  		  
	    }		  
	  }/*
	  
//Para enviar caracter

	  /*if (estado==esperar){
 		  //
 	  }
 	  if(estado==enviar){
 		  AS1_SendChar(0x41);
 		  estado=esperar;
 	  }
   }/*
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  //#ifdef PEX_RTOS_START
   	//   PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
 //#endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
