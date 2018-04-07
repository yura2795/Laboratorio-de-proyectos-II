/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AD2.c
**     Project     : Comunicacion_Serial
**     Processor   : MC9S08QE128CLK
**     Component   : ADC
**     Version     : Component 01.690, Driver 01.25, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-04, 15:56, # CodeGen: 40
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**         AD control register         : ADCSC1      [$0010]
**         AD control register         : ADCCFG      [$0016]
**         AD control register         : ADCRH       [$0012]
**         AD control register         : ADCRL       [$0013]
**         AD control register         : ADCCVH      [$0014]
**         AD control register         : ADCCVL      [$0015]
**         AD control register         : ADCSC2      [$0011]
**         AD control register         : APCTL1      [$0017]
**         AD control register         : APCTL2      [$0018]
**         AD control register         : APCTL3      [$0019]
**         Interrupt name              : Vadc
**         User handling procedure     : AD2_OnEnd
**         Number of conversions       : 1
**         AD resolution               : 12-bit
**
**         Input pins
**
**              Port name              : PTA
**              Bit number (in port)   : 1
**              Bit mask of the port   : $0002
**              Port data register     : PTAD        [$0000]
**              Port control register  : PTADD       [$0001]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-4
**     Contents    :
**         Measure      - byte AD2_Measure(bool WaitForResult);
**         MeasureChan  - byte AD2_MeasureChan(bool WaitForResult, byte Channel);
**         GetChanValue - byte AD2_GetChanValue(byte Channel, void* Value);
**         GetValue16   - byte AD2_GetValue16(word *Values);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file AD2.c
** @version 01.25
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD2_module AD2 module documentation
**  @{
*/         


#include "Events.h"
#include "PE_Error.h"
#include "PE_Cnvrt.h"
#include "AD2.h"

#pragma MESSAGE DISABLE C5703 /* WARNING C5703: Parameter declared but not referenced */



/* Internal method prototypes */

static void SetOutV(void);
/*
** ===================================================================
**     Method      :  SetOutV (component ADC)
**
**     Description :
**         The method sets the corresponding flag, which indicates that a 
**         channel conversion has been completed.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void  HWEnDi(void);
/*
** ===================================================================
**     Method      :  HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void  AD2_Interrupt(void);
/*
** ===================================================================
**     Method      :  AD2_Interrupt (component ADC)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define STOP       0x00U
#define MEASURE    0x01U
#define CONTINUOUS 0x02U
#define SINGLE     0x03U

static volatile bool OutFlg;
static volatile byte ModeFlg;
extern volatile word PE_Cnvrt_ADResults[];
volatile word AD2_SumV;                /* Sum of measured values */
volatile word AD2_OutV;                /* Sum of measured values */

/*
** ===================================================================
**     Method      :  SetOutV (component ADC)
**
**     Description :
**         The method sets the corresponding flag, which indicates that a 
**         channel conversion has been completed.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetOutV(void)
{
  OutFlg = TRUE;
  AD2_OutV = AD2_SumV;
  AD2_SumV = 0U;
  if (ModeFlg == MEASURE) {
    ModeFlg = STOP;
    PE_Cnvrt_RunSto((PE_Cnvrt_ChanMaskType)0x02U);
  }
  AD2_OnEnd();
}

/*
** ===================================================================
**     Method      :  HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void  HWEnDi(void)
{
  OutFlg = FALSE;
  AD2_SumV = 0U;
  EnterCritical();
  if ((ModeFlg != STOP)) {                          /* Enable device? */
    PE_Cnvrt_RunSta((PE_Cnvrt_ChanMaskType)0x02U); /* Enable */
  } else {
    PE_Cnvrt_RunSto((PE_Cnvrt_ChanMaskType)0x02U); /* Disable */
  }
  ExitCritical();
}

/*
** ===================================================================
**     Method      :  AD2_Interrupt (component ADC)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void  AD2_Interrupt(void)
{
  if (ModeFlg != STOP) {
    AD2_SumV = PE_Cnvrt_ADResults[1];
    SetOutV();
  }
}

/*
** ===================================================================
**     Method      :  AD2_Measure (component ADC)
**     Description :
**         This method performs one measurement on all channels that
**         are set in the component inspector. (Note: If the <number of
**         conversions> is more than one the conversion of A/D
**         channels is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for result of
**                           the conversion
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already
**                           running
** ===================================================================
*/
byte  AD2_Measure(bool WaitForResult)
{
  if (ModeFlg != STOP) {
    return ERR_BUSY;
  }
  EnterCritical();
  ModeFlg = MEASURE;
  OutFlg = FALSE;
  AD2_SumV = 0U;
  PE_Cnvrt_RunSta((PE_Cnvrt_ChanMaskType)0x02U);
  ExitCritical();
  if (WaitForResult) {
    while (ModeFlg == MEASURE) {}
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  AD2_MeasureChan (component ADC)
**     Description :
**         This method performs measurement on one channel. (Note:
**         If the <number of conversions> is more than one the
**         conversion of the A/D channel is performed specified
**         number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for result of
**                           the conversion. If interrupt service is
**                           disabled and at the same time a number
**                           of conversions is greater than 1, the
**                           parameter is ignored and the method
**                           waits for result every time then.
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored, because the
**                           parameter is set inside this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already
**                           running
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
** ===================================================================
*/
byte  AD2_MeasureChan(bool WaitForResult,byte Channel)
{
  if (ModeFlg != STOP) {
    return ERR_BUSY;
  }
  EnterCritical();
  ModeFlg = MEASURE;
  OutFlg = FALSE;
  AD2_SumV = 0U;
  PE_Cnvrt_RunSta((PE_Cnvrt_ChanMaskType)0x02U);
  ExitCritical();
  if (WaitForResult) {
    while (ModeFlg == MEASURE) {}
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  AD2_GetChanValue (component ADC)
**     Description :
**         Returns the last measured value of the required channel.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored.
**       * Value           - Pointer to the measured value. Data
**                           type is a byte, a word or an int. It
**                           depends on the supported modes,
**                           resolution, etc. of the AD converter.
**                           See the Version specific information for
**                           the current CPU in <General Info>.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun
**                           flag was detected after last value(s)
**                           was obtained (for example by GetValue).
**                           This error may not be supported on some
**                           CPUs (see generated code).
** ===================================================================
*/
byte AD2_GetChanValue(byte Channel,void* Value)
{
  if (!OutFlg) {
    return ERR_NOTAVAIL;
  }
  *(word*)Value = AD2_OutV;            /* Save measured values to the output buffer */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  AD2_GetValue16 (component ADC)
**     Description :
**         This method returns the last measured values of all
**         channels justified to the left. Compared with <GetValue>
**         method this method returns more accurate result if the
**         <number of conversions> is greater than 1 and <AD
**         resolution> is less than 16 bits. In addition, the user
**         code dependency on <AD resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Values          - Pointer to the array that
**                           contains the measured data.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun
**                           flag was detected after last value(s)
**                           was obtained (for example by GetValue).
**                           This error may not be supported on some
**                           CPUs (see generated code).
** ===================================================================
*/
byte AD2_GetValue16(word *Values)
{
  if (!OutFlg) {
    return ERR_NOTAVAIL;
  }
  *Values = (word)((AD2_OutV) << 4);   /* Save measured values to the output buffer */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  AD2_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD2_Init(void)
{
  OutFlg = FALSE;
  ModeFlg = STOP;
  PE_Cnvrt_SetPro((byte)1, AD2_Interrupt);
  PE_Cnvrt_SetSpe((byte)0x01U, (byte)0x44U);
  HWEnDi();                            /* Enable/disable device according to the status flags */
}


/* END AD2. */


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
