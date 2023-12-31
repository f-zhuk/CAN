
/*****************************************************************************
 *
 * Microchip CANopen Stack (Dictionary Services)
 *
 *****************************************************************************
 * FileName:        CO_DICT.C
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
 * Dictionary services.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/

#include	"CO_DEFS.def"			// Global definitions
#include	"CO_TYPES.h"			// Standard types
#include	"CO_ABERR.h"			// Abort types
#include	"CO_DICT.h"				// Dictionary header
#include	"CO_MEMIO.h"			// Memory IO
#include	"CO_DICT.def"			// Standard type and device specific objects
#include	"CO_MFTR.def"			// Manufacturer specific objects
#include	"CO_PDO.def"			// PDO objects
#include	"CO_STD.def"			// CANopen standard objects


// Params used by the dictionary
DICT_PARAM	uDict;


const unsigned char * _pTmpDBase;
unsigned char 		_tDBaseLen;

unsigned char		_uDictTemp[4];
MULTIPLEXOR			_tMplex;

const unsigned char	__dummy[4] = {0,0,0,0};

									
/* Dictionary database built into ROM */								
const DICT_OBJECT_TEMPLATE _db_objects[] = {
    {0x0001,0x00, WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]},
    {0x0002,0x00, WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]},
    {0x0003,0x00, WO | ROM_BIT | MAP_BIT,2,(const unsigned char *)&__dummy[0]},
    {0x0004,0x00, WO | ROM_BIT | MAP_BIT,4,(const unsigned char *)&__dummy[0]},
    {0x0005,0x00, WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]},
    {0x0006,0x00, WO | ROM_BIT | MAP_BIT,2,(const unsigned char *)&__dummy[0]},
    {0x0007,0x00, WO | ROM_BIT | MAP_BIT,4,(const unsigned char *)&__dummy[0]} 
};

const DICT_OBJECT_TEMPLATE _db_device[] = 			{DICTIONARY_DEVICE_INFO};

const DICT_OBJECT_TEMPLATE _db_sdo[] = 				{DICTIONARY_SDO};

const DICT_OBJECT_TEMPLATE _db_pdo1_rx_comm[] = 		{DICTIONARY_PDO1_RX_COMM};
#if CO_NUM_OF_PDO > 1
const DICT_OBJECT_TEMPLATE _db_pdo2_rx_comm[] = 		{DICTIONARY_PDO2_RX_COMM};
#endif
#if CO_NUM_OF_PDO > 2
const DICT_OBJECT_TEMPLATE _db_pdo3_rx_comm[] = 		{DICTIONARY_PDO3_RX_COMM};
#endif
#if CO_NUM_OF_PDO > 3
const DICT_OBJECT_TEMPLATE _db_pdo4_rx_comm[] = 		{DICTIONARY_PDO4_RX_COMM};
#endif

const DICT_OBJECT_TEMPLATE _db_pdo1_rx_map[] = 		{DICTIONARY_PDO1_RX_MAP};
#if CO_NUM_OF_PDO > 1
const DICT_OBJECT_TEMPLATE _db_pdo2_rx_map[] = 		{DICTIONARY_PDO2_RX_MAP};
#endif
#if CO_NUM_OF_PDO > 2
const DICT_OBJECT_TEMPLATE _db_pdo3_rx_map[] = 		{DICTIONARY_PDO3_RX_MAP};
#endif
#if CO_NUM_OF_PDO > 3
const DICT_OBJECT_TEMPLATE _db_pdo4_rx_map[] = 		{DICTIONARY_PDO4_RX_MAP};
#endif

const DICT_OBJECT_TEMPLATE _db_pdo1_tx_comm[] = 		{DICTIONARY_PDO1_TX_COMM};
#if CO_NUM_OF_PDO > 1
const DICT_OBJECT_TEMPLATE _db_pdo2_tx_comm[] = 		{DICTIONARY_PDO2_TX_COMM};
#endif
#if CO_NUM_OF_PDO > 2
const DICT_OBJECT_TEMPLATE _db_pdo3_tx_comm[] = 		{DICTIONARY_PDO3_TX_COMM};
#endif
#if CO_NUM_OF_PDO > 3
const DICT_OBJECT_TEMPLATE _db_pdo4_tx_comm[] = 		{DICTIONARY_PDO4_TX_COMM};
#endif

const DICT_OBJECT_TEMPLATE _db_pdo1_tx_map[] = 		{DICTIONARY_PDO1_TX_MAP};
#if CO_NUM_OF_PDO > 1
const DICT_OBJECT_TEMPLATE _db_pdo2_tx_map[] = 		{DICTIONARY_PDO2_TX_MAP};
#endif
#if CO_NUM_OF_PDO > 2
const DICT_OBJECT_TEMPLATE _db_pdo3_tx_map[] = 		{DICTIONARY_PDO3_TX_MAP};
#endif
#if CO_NUM_OF_PDO > 3
const DICT_OBJECT_TEMPLATE _db_pdo4_tx_map[] = 		{DICTIONARY_PDO4_TX_MAP};
#endif

const DICT_OBJECT_TEMPLATE _db_manufacturer_g1[] = 	{DICTIONARY_MANUFACTURER_SPECIFIC_1};
const DICT_OBJECT_TEMPLATE _db_manufacturer_g2[] = 	{DICTIONARY_MANUFACTURER_SPECIFIC_2};
const DICT_OBJECT_TEMPLATE _db_manufacturer_g3[] = 	{DICTIONARY_MANUFACTURER_SPECIFIC_3};
const DICT_OBJECT_TEMPLATE _db_manufacturer_g4[] = 	{DICTIONARY_MANUFACTURER_SPECIFIC_4};
const DICT_OBJECT_TEMPLATE _db_standard_g1[] = 		{DICTIONARY_STANDARD_1};
const DICT_OBJECT_TEMPLATE _db_standard_g2[] = 		{DICTIONARY_STANDARD_2};
const DICT_OBJECT_TEMPLATE _db_standard_g3[] = 		{DICTIONARY_STANDARD_3};
const DICT_OBJECT_TEMPLATE _db_standard_g4[] = 		{DICTIONARY_STANDARD_4};			

								



/*********************************************************************
 * Function:        void _CO_DictObjectRead(void)
 *
 * PreCondition:    _CO_DictObjectDecode() must have been called to 
 *					fill in the object structure.
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Read the object referenced by uDict.obj.
 *
 * Note:            
 ********************************************************************/
void _CO_DictObjectRead(void)
{
	// If the object is valid, control code must be something other than 0
	if (uDict.obj->ctl) 
	{	
		// Process any functionally defined objects
		if (uDict.obj->ctl & FDEF_BIT)
		{
			uDict.ret = E_SUCCESS;
			uDict.cmd = DICT_OBJ_READ;
			uDict.obj->p.pFunc();	
			return;
		}
		else	

		// Decode the type of object
		switch (uDict.obj->ctl & ACCESS_BITS)
		{
			case CONST:
				//Copy ROM to RAM, uDict.obj->reqLen specifies the amount
				CO_MEMIO_CopyRomToRam(uDict.obj->p.pROM + uDict.obj->reqOffst, uDict.obj->pReqBuf, uDict.obj->reqLen);
				break;

			case RO:
			case RW:
				//Copy RAM to RAM, uDict.obj->reqLen specifies the amount
				CO_MEMIO_CopySram(uDict.obj->p.pRAM + uDict.obj->reqOffst, uDict.obj->pReqBuf, uDict.obj->reqLen);
				break;
				
//			case RW_EE:
//			case RO_EE:
//				break;
						
			default:
				// Error, cannot read object
				uDict.ret = E_CANNOT_READ;
				return;
		}
	}
	
	uDict.ret = E_SUCCESS;
	return;
}



/*********************************************************************
 * Function:        void _CO_DictObjectWrite(void)
 *
 * PreCondition:    _CO_DictObjectDecode() must have been called to 
 *					fill in the object structure.
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Write the object referenced by uDict.obj.
 *
 * Note:            
 ********************************************************************/
void _CO_DictObjectWrite(void)
{
	// If the object is found
	if (uDict.obj->ctl) 
	{
		if (uDict.obj->ctl & FDEF_BIT)
		{
			uDict.ret = E_SUCCESS;
			uDict.cmd = DICT_OBJ_WRITE;
			uDict.obj->p.pFunc();	
			return;
		}
		else	

		// Decode the type of object
		switch (uDict.obj->ctl & ACCESS_BITS)
		{							
			case RW:
			case WO:
				//Copy RAM to RAM, uDict.obj->reqLen specifies the amount
				CO_MEMIO_CopySram(uDict.obj->pReqBuf, uDict.obj->p.pRAM, uDict.obj->reqLen);
				break;
			
//			case RW_EE:
//			case WO_EE:
//				break;
						
			default:
				// Error, write not allowed
				uDict.ret = E_CANNOT_WRITE;
				return;
		}
	}
	
	uDict.ret = E_SUCCESS;
	return;
}


/*********************************************************************
 * Function:        void _CO_DictObjectDecode(void)
 *
 * PreCondition:    The multiplexor referenced by uDict must have been
 *					initialized.
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Find the object in the dictionary and return 
 * 					information related to the object. The user must
 * 					pass a pointer to a structure that contains the 
 *					multiplexor. The decode process will fill the 
 *					rest of the structure with other pertenent
 *					information.
 *
 * Note:            
 ********************************************************************/
/* Decode the object*/
void _CO_DictObjectDecode(void)
{			
	// Copy the multiplexor to a local storage area
	_tMplex = *(MULTIPLEXOR *)(&(uDict.obj->index));

	switch (_tMplex.index.bytes.B1.byte & 0xF0)
	{		
		case 0x00:		// Data types
			_pTmpDBase = (const unsigned char *)_db_objects;
			_tDBaseLen = sizeof(_db_objects)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		
		case 0x20:		// Manufacturer specific
			_pTmpDBase = (const unsigned char *)_db_manufacturer_g1;
			_tDBaseLen = sizeof(_db_manufacturer_g1)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		case 0x30:
			_pTmpDBase = (const unsigned char *)_db_manufacturer_g2;
			_tDBaseLen = sizeof(_db_manufacturer_g2)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		case 0x40:
			_pTmpDBase = (const unsigned char *)_db_manufacturer_g3;
			_tDBaseLen = sizeof(_db_manufacturer_g3)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		case 0x50:
			_pTmpDBase = (const unsigned char *)_db_manufacturer_g4;
			_tDBaseLen = sizeof(_db_manufacturer_g4)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
			
		case 0x60:		// Standard
			_pTmpDBase = (const unsigned char *)_db_standard_g1;
			_tDBaseLen = sizeof(_db_standard_g1)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		case 0x70:
			_pTmpDBase = (const unsigned char *)_db_standard_g2;
			_tDBaseLen = sizeof(_db_standard_g2)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		case 0x80:
			_pTmpDBase = (const unsigned char *)_db_standard_g3;
			_tDBaseLen = sizeof(_db_standard_g3)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		case 0x90:
			_pTmpDBase = (const unsigned char *)_db_standard_g4;
			_tDBaseLen = sizeof(_db_standard_g4)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
					
		case 0x10:
			switch (_tMplex.index.bytes.B1.byte & 0x0F)
			{
				case 0x00:		// Device specific information
					_pTmpDBase = (const unsigned char *)_db_device;
					_tDBaseLen = sizeof(_db_device)/sizeof(DICT_OBJECT_TEMPLATE);
					break;
					
				case 0x02:		// SDO Server/Client
					_pTmpDBase = (const unsigned char *)_db_sdo;
					_tDBaseLen = sizeof(_db_sdo)/sizeof(DICT_OBJECT_TEMPLATE);
					break;
					
				case 0x04:		// PDO Receive Comm
					if (_tMplex.index.bytes.B0.byte == 0x00)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo1_rx_comm;
						_tDBaseLen = sizeof(_db_pdo1_rx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#if CO_NUM_OF_PDO > 1
					if (_tMplex.index.bytes.B0.byte == 0x01)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo2_rx_comm;
						_tDBaseLen = sizeof(_db_pdo2_rx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else
					#endif
					#if CO_NUM_OF_PDO > 2
					if (_tMplex.index.bytes.B0.byte == 0x02)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo3_rx_comm;
						_tDBaseLen = sizeof(_db_pdo3_rx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#endif
					#if CO_NUM_OF_PDO > 3
					if (_tMplex.index.bytes.B0.byte == 0x03)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo4_rx_comm;
						_tDBaseLen = sizeof(_db_pdo4_rx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#endif 
					{
						// Index not found in database
						uDict.ret = E_OBJ_NOT_FOUND;
						return;
					}
					break;
					
					
				case 0x06:		// PDO Receive Map					
					if (_tMplex.index.bytes.B0.byte == 0x00)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo1_rx_map;
						_tDBaseLen = sizeof(_db_pdo1_rx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#if CO_NUM_OF_PDO > 1
					if (_tMplex.index.bytes.B0.byte == 0x01)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo2_rx_map;
						_tDBaseLen = sizeof(_db_pdo2_rx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else
					#endif
					#if CO_NUM_OF_PDO > 2
					if (_tMplex.index.bytes.B0.byte == 0x02)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo3_rx_map;
						_tDBaseLen = sizeof(_db_pdo3_rx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#endif
					#if CO_NUM_OF_PDO > 3
					if (_tMplex.index.bytes.B0.byte == 0x03)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo4_rx_map;
						_tDBaseLen = sizeof(_db_pdo4_rx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else  
					#endif
					{
						// Index not found in database
						uDict.ret = E_OBJ_NOT_FOUND;
						return;
					}
					break;
					
					
				case 0x08:		// PDO Transmit Comm				
					if (_tMplex.index.bytes.B0.byte == 0x00)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo1_tx_comm;
						_tDBaseLen = sizeof(_db_pdo1_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#if CO_NUM_OF_PDO > 1
					if (_tMplex.index.bytes.B0.byte == 0x01)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo2_tx_comm;
						_tDBaseLen = sizeof(_db_pdo2_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else
					#endif
					#if CO_NUM_OF_PDO > 2
					if (_tMplex.index.bytes.B0.byte == 0x02)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo3_tx_comm;
						_tDBaseLen = sizeof(_db_pdo3_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#endif
					#if CO_NUM_OF_PDO > 3
					if (_tMplex.index.bytes.B0.byte == 0x03)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo4_tx_comm;
						_tDBaseLen = sizeof(_db_pdo4_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else  
					#endif
					{
						// Index not found in database
						uDict.ret = E_OBJ_NOT_FOUND;
						return;
					}
					break;
				
				
				case 0x0A:		// PDO Transmit Map					
					if (_tMplex.index.bytes.B0.byte == 0x00)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo1_tx_map;
						_tDBaseLen = sizeof(_db_pdo1_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#if CO_NUM_OF_PDO > 1
					if (_tMplex.index.bytes.B0.byte == 0x01)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo2_tx_map;
						_tDBaseLen = sizeof(_db_pdo2_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else
					#endif
					#if CO_NUM_OF_PDO > 2
					if (_tMplex.index.bytes.B0.byte == 0x02)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo3_tx_map;
						_tDBaseLen = sizeof(_db_pdo3_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					#endif
					#if CO_NUM_OF_PDO > 3
					if (_tMplex.index.bytes.B0.byte == 0x03)
					{
						_pTmpDBase = (const unsigned char *)_db_pdo4_tx_map;
						_tDBaseLen = sizeof(_db_pdo4_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else  
					#endif
					{
						// Index not found in database
						uDict.ret = E_OBJ_NOT_FOUND;
						return;
					}
					break;
					
					
//				case 0x05:
//				case 0x07:
//				case 0x09:
//				case 0x0B:
//					_pTmpDBase = (const unsigned char *)_db_pdo_tx_map;
//					_tDBaseLen = sizeof(_db_pdo_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
//					break;
				
				default:
					// Index not found in database
					uDict.ret = E_OBJ_NOT_FOUND;
					return;
			}
			break;

		default:
			// Index not found in database
			uDict.ret = E_OBJ_NOT_FOUND;
			return;
	}

	
	// Adjust the status
	uDict.ret = E_OBJ_NOT_FOUND;
	
	// Copy the index and sub-index to local memory
	*(_DATA4 *)(&(_uDictTemp[0])) = *(const _DATA4 *)_pTmpDBase;

	// Scan the database and load the pointer
	while(_tDBaseLen)
	{					
		// Match the index 
		if ((_uDictTemp[1] == _tMplex.index.bytes.B1.byte) &&
			(_uDictTemp[0] == _tMplex.index.bytes.B0.byte))
		{
			// Adjust the status
			uDict.ret = E_SUBINDEX_NOT_FOUND;
													
			// If the sub index matches then return success code
			if ((_uDictTemp[2] == _tMplex.sindex.byte) ||
			 	(_uDictTemp[3] & FSUB_BIT))
			{
				// Copy control information
		    	*((DICT_OBJECT_TEMPLATE *)(&(uDict.obj->index))) = *((const DICT_OBJECT_TEMPLATE *)(_pTmpDBase));
		    				    	
		    	// If functionally defined sub-index, copy sub-index from request
		    	if (_uDictTemp[3] & FSUB_BIT) uDict.obj->subindex = _tMplex.sindex.byte;
						
				// If function specific then call the app function for 
				// read/write, mapping, and length info
				if (_uDictTemp[3] & FDEF_BIT) //if (uDict.obj->ctl & FDEF_BIT)
				{
					uDict.ret = E_SUCCESS;
					uDict.cmd = DICT_OBJ_INFO;
					uDict.obj->p.pFunc();	
					return;
				}
				else
				{
					uDict.ret = E_SUCCESS;
					return;
				}
			}
		}

		// Adjust the pointer
		_pTmpDBase += sizeof(DICT_OBJECT_TEMPLATE);
		
		_tDBaseLen--;
		
		// Copy the index and sub-index to local memory
		*(_DATA4 *)(&(_uDictTemp[0])) = *(const _DATA4 *)_pTmpDBase;
	}
	return;
}





