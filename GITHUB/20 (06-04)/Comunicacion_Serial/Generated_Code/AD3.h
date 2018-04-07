/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AD3.h
**     Project     : Comunicacion_Serial
**     Processor   : MC9S08QE128CLK
**     Component   : ADC
**     Version     : Component 01.690, Driver 01.25, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-04, 14:51, # CodeGen: 37
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
**         User handling procedure     : AD3_OnEnd
**         Number of conversions       : 1
**         AD resolution               : 12-bit
**
**         Input pins
**
**              Port name              : PTA
**              Bit number (in port)   : 6
**              Bit mask of the port   : $0040
**              Port data register     : PTAD        [$0000]
**              Port control register  : PTADD       [$0001]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-4
**     Contents    :
**         Measure      - byte AD3_Measure(bool WaitForResult);
**         MeasureChan  - byte AD3_MeasureChan(bool WaitForResult, byte Channel);
**         GetChanValue - byte AD3_GetChanValue(byte Channel, void* Value);
**         GetValue16   - byte AD3_GetValue16(word *Values);
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
** @file AD3.h
** @version 01.25
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD3_module AD3 module documentation
**  @{
*/         

#ifndef __AD3
#define __AD3

/* MODULE AD3. */

#include "Cpu.h"




byte AD3_GetValue16(word *Values);
/*
** ===================================================================
**     Method      :  AD3_GetValue16 (component ADC)
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

byte AD3_GetChanValue(byte Channel,void* Value);
/*
** ===================================================================
**     Method      :  AD3_GetChanValue (component ADC)
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

byte AD3_MeasureChan(bool WaitForResult,byte Channel);
/*
** ===================================================================
**     Method      :  AD3_MeasureChan (component ADC)
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

void AD3_Init(void);
/*
** ===================================================================
**     Method      :  AD3_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

byte  AD3_Measure(bool WaitForResult);
/*
** ===================================================================
**     Method      :  AD3_Measure (component ADC)
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
#endif /* ifndef __AD3 */

