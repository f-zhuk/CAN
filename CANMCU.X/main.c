/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F26K83
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "CANopen/CO_MAIN.h"
#include "main.h"
//#include "CANopen/CO_PDO1.h"
//#include "CANopen/Timer.h"
#include "mcc_generated_files/mcc.h"


#define	RTR_DIS	bytes.B1.bits.b2
#define STD_DIS	bytes.B1.bits.b3
#define PDO_DIS	bytes.B1.bits.b4

// These are mapping constants for TPDO1 
// starting at 0x1A00 in the dictionary
const unsigned long uTPDO1Map = 0x60000108; // 0x1A00 subindex 1 in CO_PDO.def 
const unsigned long uRPDO1Map = 0x62000108; // 0x1600 subindex 1 in CO_PDO.def 
const unsigned long uPDO1Dummy = 0x00000008;

unsigned char uIOinFilter;					// 0x6003 filter
unsigned char uIOinPolarity;				// 0x6002 polarity
unsigned char uIOinIntChange;				// 0x6006 interrupt on change
unsigned char uIOinIntRise;					// 0x6007 interrupt on positive edge
unsigned char uIOinIntFall;					// 0x6008 interrupt on negative edge
unsigned char uIOinIntEnable;				// 0x6005 enable interrupts

unsigned char uIOinDigiInOld;				// 

// Static data refered to by the dictionary
const unsigned char rMaxIndex1 = 1;
const unsigned char rMaxIndex2 = 8;
const unsigned char uDemoTPDO1Len = 2;


unsigned char uLocalXmtBuffer[8];			// Local buffer for TPDO1
unsigned char uLocalRcvBuffer[8];			// local buffer fot RPDO1

UNSIGNED8 uDemoState; 					// Bits used to control various states
unsigned char uDemoSyncCount;			// Counter for synchronous types
unsigned char uDemoSyncSet;				// Internal TPDO type control


/*********************************************************************
 * Function:        void DemoInit(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the initialization to the demonstration
 *					object.
 *
 * Note:          	
 ********************************************************************/
void DemoInit(void)
{
	uDemoSyncSet = 255;

	uIOinFilter = 0;
	uIOinPolarity = 0;
	uIOinIntChange = 1;
	uIOinIntRise = 0;
	uIOinIntFall = 0;
	uIOinIntEnable = 1;

	uIOinDigiInOld = uLocalXmtBuffer[0] = 0;
	uLocalRcvBuffer[1] = uLocalXmtBuffer[1] = 0;
	uLocalRcvBuffer[2] = uLocalXmtBuffer[2] = 0;
	uLocalRcvBuffer[3] = uLocalXmtBuffer[3] = 0;
	uLocalRcvBuffer[4] = uLocalXmtBuffer[4] = 0;
	uLocalRcvBuffer[5] = uLocalXmtBuffer[5] = 0;
	uLocalRcvBuffer[6] = uLocalXmtBuffer[6] = 0;
	uLocalRcvBuffer[7] = uLocalXmtBuffer[7] = 0;


	// Convert to MCHP
	mTOOLS_CO2MCHP(mCOMM_GetNodeID().byte + 0xC0000180L);
	
	// Store the COB
	mTPDOSetCOB(1, mTOOLS_GetCOBID());

	// Convert to MCHP
	mTOOLS_CO2MCHP(mCOMM_GetNodeID().byte + 0xC0000200L);
	
	// Store the COB
	mRPDOSetCOB(1, mTOOLS_GetCOBID());
	
	// Set the pointer to the buffers
	mTPDOSetTxPtr(1, (unsigned char *)(&uLocalXmtBuffer[0]));
	//_uPDO1.TPDO.buf = (unsigned char *)(&uLocalXmtBuffer[0]);

	// Set the pointer to the buffers
	mRPDOSetRxPtr(1, (unsigned char *)(&uLocalRcvBuffer[0]));
    //_uPDO1.RPDO.buf = (unsigned char *)(&uLocalRcvBuffer[0]));

	// Set the length
	mTPDOSetLen(1, 8);
    //_uPDO1.TPDO.len = 8
}

/*********************************************************************
 * Function:        void CO_COMMSyncEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a SYNC event 
 *					handling function.
 *
 * Note:          	
 ********************************************************************/
void CO_COMMSyncEvent(void)
{
	// Process only if in a synchronous mode
	if ((uDemoSyncSet == 0) && (uDemoState.bits.b2))
	{
		// Reset the synchronous transmit and transfer to async
		uDemoState.bits.b2 = 0;
		uDemoState.bits.b0 = 1;
	}
	else
	if ((uDemoSyncSet >= 1) && (uDemoSyncSet <= 240))
	{
		// Adjust the sync counter
		uDemoSyncCount--;
		
		// If time to generate sync
		if (uDemoSyncCount == 0)
		{
			// Reset the sync counter
			uDemoSyncCount = uDemoSyncSet;
			
			// Start the PDO transmission
			uDemoState.bits.b0 = 1;
		}
	}
}

/*********************************************************************
 * Function:        void DemoProcessEvents(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a demo state
 *					machine for cooperative multitasking.
 *
 * Note:          	
 ********************************************************************/
void DemoProcessEvents(void)
{
	//unsigned char change;
	//unsigned char rise;
	//unsigned char fall;

	// Read the input port
	//(*(UNSIGNED8 *)uLocalXmtBuffer).bits.b0 = PORTBbits.RB5;					
	//(*(UNSIGNED8 *)uLocalXmtBuffer).bits.b1 = PORTBbits.RB4;					
	

	// Determine the change if any
	//change = uIOinDigiInOld ^ uLocalXmtBuffer[0];
	
	// Determine if there were any rise events
	//rise = (uIOinIntRise & change) & uLocalXmtBuffer[0];
		
	// Determine if there were any fall events
	//fall = (uIOinIntFall & change) & ~uLocalXmtBuffer[0];

	// Determine if there were any change events
	//change = (uIOinIntChange & change);

	// Cycle the current value to the old
	//uIOinDigiInOld = uLocalXmtBuffer[0];

	// If any of these are true then indicate an interrupt condition
	//if (uIOinIntEnable & (change | rise | fall)) uDemoState.bits.b1 = 1;

	//if (uDemoState.bits.b1)
	//{
	//	switch (uDemoSyncSet)
	//	{
	//		case 0:				// Asyclic synchronous transmit
	//			// Set a synchronous transmit flag
	//			uDemoState.bits.b2 = 1;
	//			break;

	//		case 254:			// Asynchronous transmit
	//		case 255:						
				// Reset the asynchronous transmit flag
	//			uDemoState.bits.b0 = 1;
	//			break;
	//	}
	//}

    (*(UNSIGNED8 *)uLocalXmtBuffer).byte ++;
	// If ready to send 
	if (mTPDOIsPutRdy(1))// && uDemoState.bits.b0)
	{
		// Tell the stack data is loaded for transmit
		mTPDOWritten(1);
		
		// Reset any synchronous or asynchronous flags
		//uDemoState.bits.b0 = 0;
		//uDemoState.bits.b1 = 0;
	}

	// If any data has been received
	//if (mRPDOIsGetRdy(1))
	//{
		// Write out the first byte of the buffer
	//	LATB = uLocalRcvBuffer[0];
		
		// PDO read, free the driver to accept more data
	//	mRPDORead(1);
	//}
}

/*********************************************************************
 * Function:        void CO_COMM_RPDO1_COBIDAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a RPDO COB access
 *					handling function.
 *
 * Note:          	This function is called from the dictionary.
 ********************************************************************/
void CO_COMM_RPDO1_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
        case DICT_OBJ_INFO:		// Get information not required for this object
			break;
          
		case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			//mTOOLS_MCHP2CO(mRPDOGetCOB(1));
            mTOOLS_MCHP2CO(uRPDOComm1.word);
			
			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// Translate the COB to MCHP format
			mTOOLS_CO2MCHP(*(unsigned long *)(uDict.obj->pReqBuf));
			
			// If the request is to stop the PDO
			if ((*(UNSIGNED32 *)(&mTOOLS_GetCOBID())).PDO_DIS)
			{
				// And if the COB received matches the stored COB and type then close
				//if (!((mTOOLS_GetCOBID() ^ mRPDOGetCOB(1)) & 0xFFFFEFFFL))
                if (!((mTOOLS_GetCOBID() ^ uRPDOComm1.word) & 0xFFFFEFFFL))    
				{
					// but only close if the PDO endpoint was open
					if (mRPDOIsOpen(1)) {mRPDOClose(1);}
		
					// Indicate to the local object that this PDO is disabled
					//(*(UNSIGNED32 *)(&mRPDOGetCOB(1))).PDO_DIS = 1;
                    (*(UNSIGNED32 *)(&uRPDOComm1.word)).PDO_DIS = 1;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}

			// Else if the TPDO is not open then start the TPDO
			else
			{
				// And if the COB received matches the stored COB and type then open
				if (!((mTOOLS_GetCOBID() ^ mRPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only open if the PDO endpoint was closed
					if (!mRPDOIsOpen(1)) {mRPDOOpen(1);}
						
					// Indicate to the local object that this PDO is enabled
					(*(UNSIGNED32 *)(&mRPDOGetCOB(1))).PDO_DIS = 0;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}
			break;
	}	
}

/*********************************************************************
 * Function:        void CO_COMM_TPDO1_COBIDAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a TPDO COB access
 *					handling function.
 *
 * Note:          	This function is called from the dictionary.
 ********************************************************************/
void CO_COMM_TPDO1_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information not required for this object
			break;
            
        case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			mTOOLS_MCHP2CO(mTPDOGetCOB(1));
			
			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// Translate the COB to MCHP format
			mTOOLS_CO2MCHP(*(unsigned long *)(uDict.obj->pReqBuf));
			
			// If the request is to stop the PDO
			if ((*(UNSIGNED32 *)(&mTOOLS_GetCOBID())).PDO_DIS)
			{
				// And if the COB received matches the stored COB and type then close
				if (!((mTOOLS_GetCOBID() ^ mTPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only close if the PDO endpoint was open
					if (mTPDOIsOpen(1)) {mTPDOClose(1);}
		
					// Indicate to the local object that this PDO is disabled
					(*(UNSIGNED32 *)(&mTPDOGetCOB(1))).PDO_DIS = 1;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}

			// Else if the TPDO is not open then start the TPDO
			else
			{
				// And if the COB received matches the stored COB and type then open
				if (!((mTOOLS_GetCOBID() ^ mTPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only open if the PDO endpoint was closed
					if (!mTPDOIsOpen(1)) {mTPDOOpen(1);}
						
					// Indicate to the local object that this PDO is enabled
					(*(UNSIGNED32 *)(&mTPDOGetCOB(1))).PDO_DIS = 0;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}
			break;
	}	
}

/*********************************************************************
 * Function:        void CO_COMM_TPDO1_TypeAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a TPDO type access
 *					handling function.
 *
 * Note:          	This function is called from the dictionary.
 ********************************************************************/
void CO_COMM_TPDO1_TypeAccessEvent(void)
{
	unsigned char tempType;
	
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// Write the Type to the buffer
			*(uDict.obj->pReqBuf) = uDemoSyncSet;
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			tempType = *(uDict.obj->pReqBuf);
			if ((tempType >= 0) && (tempType <= 240))
			{
				// Set the new type and resync
				uDemoSyncCount = uDemoSyncSet = tempType;
			}
			else 
			if ((tempType == 254) || (tempType == 255))
			{
				uDemoSyncSet = tempType;
			}
			else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			
			break;
	}	
}

/*********************************************************************
 * Function:        void CO_PDO1LSTimerEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        none
 *
 * Note:          	none
 ********************************************************************/
void CO_PDO1LSTimerEvent(void)
{
	
}



/*********************************************************************
 * Function:        void CO_PDO1TXFinEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        none
 *
 * Note:          	none
 ********************************************************************/
void CO_PDO1TXFinEvent(void)
{
	
}

/*
                         Main application
 */
void TMR0_Blink(void){
    
    ////uCAN_MSG send;
    ////uint8_t i= 7;
 
    ////send.frame.id = 0xAA;
    ////send.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    ////send.frame.dlc = 1;
           
    ////send.array[0] = 0x55;
    
    ////CAN_transmit(&send);
    
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
    //if(COMM_NETCTL_EN)
    //{
	// If ready to send 
    //*((UNSIGNED8 *)(mTPDOGetTxPtr(1))) = 0x04;
    //*((UNSIGNED8 *)(_uPDO1.TPDO.buf)) = 0x08;
	if (mTPDOIsPutRdy(1))// && uDemoState.bits.b0)
	{
        (*(UNSIGNED8 *)uLocalXmtBuffer).byte ++;
        (*(UNSIGNED8 *)uLocalXmtBuffer).bits.b0 = 1;
		// Tell the stack data is loaded for transmit
		mTPDOWritten(1);
        IO_RB4_Toggle();
		
		// Reset any synchronous or asynchronous flags
		//uDemoState.bits.b0 = 0;
		//uDemoState.bits.b1 = 0;
	}
    //}
    //DemoProcessEvents();
    _CO_COMMLSTimeEventManager();
}

void UART1_Write_String(uint8_t *buffer_ptr)
{
    while(*buffer_ptr)
    {
        while(!UART1_is_tx_ready());
        UART1_Write(*buffer_ptr);
        buffer_ptr++;
    }
}

void main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    // Perform any application specific initialization
    //TimerInit(); // Init my timer
    TMR0_SetInterruptHandler(TMR0_Blink);
    TMR0_StartTimer();
    mSYNC_SetCOBID(0x12); // Set the SYNC COB ID (MCHP format)
    mCO_SetNodeID(0x02); // Set the node_id
    mCO_SetBaud(0x00); // Set the baudrate 100kbit/s default
    mNMTE_SetHeartBeat(0x10); // Set the initial heartbeat
    mNMTE_SetGuardTime(0x00); // Set the initial guard time
    mNMTE_SetLifeFactor(0x00); // Set the initial life time
    DemoInit();
    _CO_COMMResetEventManager(); // Initialize CANopen to run/**/
    //mCO_InitAll();
    mNMT_GotoOperState();
    
    while(1)
    {
    // Process CANopen events
        CO_ProcessAllEvents();
        //UART1_Write_String("Hello\r\n");
        //COMM_NETCTL_TF = 0;
        // Process application specific functions
        // 1ms timer events
        /*if (TimerIsOverflowEvent())
        {
        // Process timer related events
            mCO_ProcessAllTimeEvents();
        // Perform other time functions
        }*/
        //IO_RB4_Toggle();
        __delay_ms(50);
    }
}
/**
 End of File
*/