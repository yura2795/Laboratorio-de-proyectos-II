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
#include "TI1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


bool boton1= FALSE;
bool boton2= FALSE;
bool inicio= FALSE;
bool m= FALSE;


/*PARA ENVIAR BLOQUE SERIAL

unsigned int Enviados= 5;

typedef union{
	unsigned char b5[5];
	//unsigned int b16;
}SENAL;

volatile SENAL bloque;

*/

//int estado = esperar;

//	PARA ENVIAR SE�AL DEL POTENCIOMETRO
 
unsigned int Enviados = 3;
unsigned char Button;

typedef union{
	unsigned char b8[2];
	unsigned int b16;
}SENAL;

volatile SENAL iADC, byte1, byte2;


unsigned char array[3];


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
	  		  AD1_Measure(TRUE);
	  		  AD1_GetValue16(&iADC.b16);
	  		  //byte2.b16[1] = !Bit1_GetVal();
	  		  iADC.b16 = iADC.b16 >>4;
			  byte1.b16 = iADC.b16 & 0x7F;
			  byte2.b16 = iADC.b16 >> 7;
			  byte2.b16=byte2.b16 & 0x1F; //000A1A1A1A1A1
			  
			  
			  boton1 = Bit1_GetVal();
			  boton2 = Bit3_GetVal();
			  inicio = Bit5_GetVal();
			  
			  if (inicio ==0)
				  {	  
				      Bit6_PutVal(inicio);				       
				      byte2.b16=byte2.b16 & 0x1F;
				      m=0;
				      
				      
				  }
			  else 
			  	  {
			  		  Bit6_PutVal(inicio); 
			  	  }
			  			  
			  
			  if (m==0)
			  	  {	  
				  	 
				      if (boton1 ==0)
				      		{
				      			  Bit2_PutVal(boton1); 
				      			  byte2.b16=byte2.b16 & 0x40;
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
				    		    
			   	  
				
					  
			  //Para enviar el bloque del protocolo por serial 
			  
			   	      
			   //byte2.b16[1]= Button;			   
			   array[0]=0xF2;
			   array[1]=byte2.b16;
			   array[2]=byte1.b16;	
			   
					  
			   estado = enviar;

	  	  case enviar: 	  
	  		  AS1_SendBlock(&array,3,&Enviados);
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
