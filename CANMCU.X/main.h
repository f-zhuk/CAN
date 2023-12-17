/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// These are mapping constants for TPDO1 
// starting at 0x1A00 in the dictionary
extern const unsigned long uTPDO1Map;
extern const unsigned long uRPDO1Map;
extern const unsigned long uPDO1Dummy;

extern unsigned char uIOinDigiInputs;			// 0x6000 digital inputs
extern unsigned char uIOinPolarity;				// 0x6002 polarity
extern unsigned char uIOinFilter;				// 0x6003 filter
extern unsigned char uIOinIntEnable;			// 0x6005 enable interrupts
extern unsigned char uIOinIntChange;			// 0x6006 interrupt on change
extern unsigned char uIOinIntRise;				// 0x6007 interrupt on positive edge
extern unsigned char uIOinIntFall;				// 0x6008 interrupt on negative edge

extern unsigned char uDOUT_VAL;                 // 0x6200 Write output 8-bit
extern unsigned char uDOUT_POL;                 // 0x6202 Change polarity output 8-bit
extern unsigned char uDOUT_ERMOD;               // 0x6206 Error mode output 8-bit
extern unsigned char uDOUT_ERVAL;               // 0x6207 Error value output 8-bit
extern unsigned char uDOUT_MASK;                // 0x6208 Filter mask output 8-bit

extern unsigned char uIOinDigiInOld;			// 

extern unsigned char uLocalXmtBuffer[8];			// Local buffer for TPDO1
extern unsigned char uLocalRcvBuffer[8];			// local buffer fot RPDO1

extern const unsigned char uDemoTPDO1Len;
extern const unsigned char rMaxIndex1;
extern const unsigned char rMaxIndex2;


void DemoProcessEvents(void);
void DemoInit(void);
void CO_COMM_TPDO1_COBIDAccessEvent(void);
void CO_COMM_RPDO1_COBIDAccessEvent(void);
void CO_COMM_TPDO1_TypeAccessEvent(void);

#endif	/* XC_HEADER_TEMPLATE_H */

