/*****************************************************************************
 *
 * Microchip CANopen Stack (Dictionary Services)
 *
 *****************************************************************************
 * FileName:        CO_DICT.C
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.20.00 or higher
 * Linker:          MPLINK 03.40.00 or higher
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

/*********************************************************************
 * Be sure to include all headers here that relate to the symbols
 * below.
 ********************************************************************/

#include	"CO_DEV.h"		// Standard device information
#include	"CO_SYNC.h"		// SYNC Object support
#include	"CO_NMTE.h"		// Error protocols: heartbeat, node-guard
#include	"CO_SDO1.h"		// SDO1, the default SDO

// This is the scalar equivelant of a portion of the DICT_OBJ
typedef struct _DICTIONARY_OBJECT_TEMPLATE
{
	unsigned int index;
	unsigned char subindex;
	unsigned char ctl;
	unsigned int len;
	const unsigned char * pROM;
}DICT_OBJECT_TEMPLATE;


	
enum DICT_CTL					/* Memory access type */
	{
		ACCESS_BITS	= 0b00000111,
				
		NA			= 0b00000000,	/* Default, non-existant */
		CONST		= 0b00000101,	/* Default, read only from ROM */
		RW			= 0b00000011,	/* Default, read/write from RAM */
		RO			= 0b00000001,	/* Default, read only from RAM */
		WO			= 0b00000010,	/* Default, write only to RAM */
		RW_EE		= 0b00001011,	/* Default, read/write from EEDATA */
		RO_EE		= 0b00001001,	/* Default, read only from EEDATA */
		WO_EE		= 0b00001010,	/* Default, write only to EEDATA */
		FUNC		= 0b00010000,	/* Default, function specific */
		
		RD_BIT		= 0b00000001,	/* Read Access */
		//RD			= 0b01111111,	
		N_RD		= 0b01111110,	
		
		WR_BIT		= 0b00000010,	/* Write Access */
		//WR			= 0b01111111,	
		N_WR		= 0b01111101,
		
		ROM_BIT		= 0b00000100,	/* ROM based object */
		ROM			= 0b01111111,	
		N_ROM		= 0b01111011,
		
		EE_BIT		= 0b00001000,	/* EEDATA based object */
		EE			= 0b01111111,
		N_EE		= 0b01110111,
		
		FDEF_BIT	= 0b00010000,	/* Functionally defined access */
		FDEF		= 0b01111111,	
		N_FDEF		= 0b01101111,
		
		MAP_BIT		= 0b00100000,	/* PDO Mappability*/
		MAP			= 0b01111111,
		N_MAP		= 0b01011111,	
		
		FSUB_BIT	= 0b01000000,	/* Functionally defined sub-index */
		FSUB		= 0b01111111,
		N_FSUB		= 0b00111111	
	};


typedef struct _DICTIONARY_EXTENDED_OBJECT
{
	//enum _DICT_OBJECT_REQUEST		/* Command required for function */
	//{
	//	DICT_OBJ_INFO = 0,
	//	DICT_OBJ_READ,
	//	DICT_OBJ_WRITE
	//}cmd;

	unsigned char * pReqBuf;		/* Pointer to the requestors buffer */

	unsigned int reqLen;			/* Number of bytes requested */
	unsigned int reqOffst;			/* Starting point for the request */

	unsigned int index;				/* CANOpen Index */
	unsigned char subindex;			/* CANOpen Sub-index */

    enum DICT_CTL ctl;
	
	unsigned int len;				/* Size of the object in bytes */
	
	union DICT_PTRS					/* Pointers to objects */
	{
		void (* pFunc)(void);
		unsigned char * pRAM;
		const unsigned char * pROM;
		unsigned int pEEDATA;
	}p;
	
}DICT_OBJ;




typedef struct _MULTIPLEXOR
{
	UNSIGNED16 index;
	UNSIGNED8 sindex;
}MULTIPLEXOR;


typedef struct _DICTIONARY_DATA
{
	DICT_OBJ * obj;					/* Pointer to the local object */
	enum _DICT_OBJECT_REQUEST		/* Command required for function */
	{
		DICT_OBJ_INFO = 0,
		DICT_OBJ_READ = 1,
		DICT_OBJ_WRITE = 2
	}cmd;
	unsigned char ret;				/* Return status */
}DICT_PARAM;


extern DICT_PARAM uDict;



void _CO_DictObjectRead(void);
void _CO_DictObjectWrite(void);
void _CO_DictObjectDecode(void);
void _CO_DictTest(void);
void _CO_TestObjectAccessEvent(void);


#define	mCO_DictObjectRead(myObj)	{uDict.obj = &myObj; _CO_DictObjectRead();}
#define	mCO_DictObjectWrite(myObj) 	{uDict.obj = &myObj; _CO_DictObjectWrite();}
#define mCO_DictObjectDecode(myObj)	{uDict.obj = &myObj; _CO_DictObjectDecode();}
#define mCO_DictGetCmd()			uDict.cmd
#define mCO_DictGetRet()			uDict.ret
#define mCO_DictSetRet(retVal)		uDict.ret = retVal

// from .def

/*********************************************************************
 * This memory region defines the data types. All the indices in this
 * definition must range from 0x0001 to 0x009F. According to the 
 * CANOpen specification these are not required to be handled. If 
 * they are implimented then they should be read only and return the 
 * length of the object.
 ********************************************************************/
#define		DICTIONARY_DATA_TYPES \\
			{0x0001,0x00,WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]}, \
			{0x0002,0x00,WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]}, \
			{0x0003,0x00,WO | ROM_BIT | MAP_BIT,2,(const unsigned char *)&__dummy[0]}, \
			{0x0004,0x00,WO | ROM_BIT | MAP_BIT,4,(const unsigned char *)&__dummy[0]}, \
			{0x0005,0x00,WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]}, \
			{0x0006,0x00,WO | ROM_BIT | MAP_BIT,2,(const unsigned char *)&__dummy[0]}, \
			{0x0007,0x00,WO | ROM_BIT | MAP_BIT,4,(const unsigned char *)&__dummy[0]}

/*********************************************************************
 * This memory region defines the device. All the indices in this
 * definition must range from 0x1000 to 0x10FF. 
 ********************************************************************/
#define		DICTIONARY_DEVICE_INFO                                                                      \
			{0x1000,0x00,CONST,4,(const unsigned char *)&rCO_DevType},                                  \
			{0x1001,0x00,RO,1,(const unsigned char *)&uCO_DevErrReg},                                 \
			{0x1002,0x00,RO,4,(const unsigned char *)&uCO_DevManufacturerStatReg},					\
			{0x1005,0x00,FUNC | RW,4,(const unsigned char *)&_CO_COMM_SYNC_COBIDAccessEvent},         \
			{0x1008,0x00,CONST,24,(const unsigned char *)&rCO_DevName},                               \
			{0x1009,0x00,CONST,4,(const unsigned char *)&rCO_DevHardwareVer},                         \
			{0x100A,0x00,CONST,4,(const unsigned char *)&rCO_DevSoftwareVer},                         \
			{0x100C,0x00,FUNC | RW,2,(const unsigned char *)&_CO_COMM_NMTE_GuardTimeAccessEvent},     \
			{0x100D,0x00,FUNC | RW,1,(const unsigned char *)&_CO_COMM_NMTE_LifeFactorAccessEvent},	\
			{0x1017,0x00,FUNC | RW,2,(const unsigned char *)&_CO_COMM_NMTE_HeartBeatAccessEvent},     \
			{0x1018,0x00,CONST,1,(const unsigned char *)&rCO_DevIdentityIndx},						\
			{0x1018,0x01,CONST,4,(const unsigned char *)&rCO_DevVendorID},                            \
			{0x1018,0x02,CONST,4,(const unsigned char *)&rCO_DevProductCode},                         \
			{0x1018,0x03,CONST,4,(const unsigned char *)&rCO_DevRevNo},								\
			{0x1018,0x04,CONST,4,(const unsigned char *)&rCO_DevSerialNo}
			
/*********************************************************************
 * This memory region defines the SDOs. All the indices in this
 * definition must range from 0x1200 to 0x12FF. SDO servers range
 * from 0x1200 to 0x127F. SDO clients range from 0x1280 to 0x13FF.
 ********************************************************************/
#define		DICTIONARY_SDO \
			{0x1200,0x00,CONST,1,(const unsigned char *)&_uSDO1COMMIndx}, \
			{0x1200,0x01,FUNC | RO,4,(const unsigned char *)&_CO_COMM_SDO1_CS_COBIDAccessEvent}, \
			{0x1200,0x02,FUNC | RO,4,(const unsigned char *)&_CO_COMM_SDO1_SC_COBIDAccessEvent}