/*****************************************************************************
 *
 * Microchip CANopen Stack (Main Managing Routines)
 *
 *****************************************************************************
 * FileName:        CO_MAIN.H
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.30.00 or higher
 * Linker:          MPLINK 03.70.00 or higher
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") is intended and supplied to you, the Company's
 * customer, for use solely and exclusively with products manufactured
 * by the Company. 
 *
 * The software is owned by the Company and/or its supplier, and is 
 * protected under applicable copyright laws. All rights are reserved. 
 * Any use in violation of the foregoing restrictions may subject the 
 * user to criminal sanctions under applicable laws, as well as to 
 * civil liability for the breach of the terms and conditions of this 
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * 
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/

#include	"CO_DEFS.def"			// Global definitions
#include	"CO_TYPES.h"			// Data types
#include	"CO_CANDRV.h"			// Driver services
#include	"CO_COMM.h"				// Object
#include	"CO_DICT.h"				// Dictionary services
#include	"CO_NMT.h"				// Networm Management
#include	"CO_SYNC.h"				// SYNC Object support
#include	"CO_SDO1.h"				// SDO1, the default SDO
#include	"CO_NMTE.h"				// Error protocols: heartbeat, node-guard
#include	"CO_PDO.h"				// PDOs
#include	"CO_TOOLS.h"			// COB ID tools
#include	"CO_ABERR.h"			// CANopen errors

#include	<xc.h>


/*********************************************************************
 * Function:        void CO_ProcessAllEvents(void)
 *
 * PreCondition:    All driver and CANopen initialization must be 
 *					complete before calling this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function is the main entry into CANopen
 *					background processing. In addition the driver 
 *					background functions are controlled from here.
 *
 * Note:          	This function should be called as often as 
 *					necessary to capture CAN events.
 ********************************************************************/
void CO_ProcessAllEvents(void);
#define mCO_ProcessAllEvents()		CO_ProcessAllEvents()



/*********************************************************************
 * Function:        void mCO_SetNodeID(NodeID)
 *
 * PreCondition:    none
 *
 * Input:       	NodeID
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Set the node ID.
 *
 * Note:          	This should be called at least one time to 
 * 					set the ID.
 ********************************************************************/
#define mCO_SetNodeID(NodeID) 		_uCO_nodeID.byte = NodeID



/*********************************************************************
 * Function:        unsigned char mCO_SetNodeID(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	_uCO_nodeID.byte  
 *
 * Side Effects:    none
 *
 * Overview:        Return the ID currently used be the stack.
 *
 * Note:          	
 ********************************************************************/
#define mCO_GetNodeID()				_uCO_nodeID.byte



/*********************************************************************
 * Function:        void mCO_SetBaud(bitrate)
 *
 * PreCondition:    none
 *
 * Input:       	bitrate
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Set the bit rate. Valid values are from 0 to 8.
 *
 * Note:          	Values higher than 8 are possible, but have the
 *					effect of forcing the device to use the default.
 ********************************************************************/
#define mCO_SetBaud(bitrate)		_uCO_baud.byte = bitrate


/*********************************************************************
 * Function:        unsigned char mCO_GetBaud(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	_uCO_baud.byte  
 *
 * Side Effects:    none
 *
 * Overview:        Return the bitrate currently used be the stack.
 *
 * Note:          	
 ********************************************************************/
#define mCO_GetBaud()				_uCO_baud.byte
	
