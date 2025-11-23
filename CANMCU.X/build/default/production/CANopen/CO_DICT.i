# 1 "CANopen/CO_DICT.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/home/fedor/.mchp_packs/Microchip/PIC18F-K_DFP/1.5.114/xc8/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "CANopen/CO_DICT.c" 2
# 46 "CANopen/CO_DICT.c"
# 1 "CANopen/CO_DEFS.def" 1
# 47 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_TYPES.h" 1
# 46 "CANopen/CO_TYPES.h"
typedef struct _SID
{
 union _SIDH
 {
  unsigned char byte;
  struct _SIDH_BITS
  {
   unsigned SIDH:8;
  }bits;
 }h;
 union _SIDL
 {
  unsigned char byte;
  struct _SIDL_BITS
  {
   unsigned :2;
   unsigned fen:1;
   unsigned EXIDEN:1;
   unsigned :1;
   unsigned SIDL:3;
  }bits;
 }l;
}CAN_SID;


typedef struct _EID
{
 union _EIDUH
 {
  unsigned char byte;
  struct _EIDUH_BITS
  {
   unsigned EIDUH:8;
  }bits;
 }uh;
 union _EIDUL
 {
  unsigned char byte;
  struct _EIDUL_BITS
  {
   unsigned EIDUL1:2;
   unsigned fen:1;
   unsigned EXIDEN:1;
   unsigned :1;
   unsigned EIDUL2:3;
  }bits;
 }ul;
 union _EIDH
 {
  unsigned char byte;
  struct _EIDH_BITS
  {
   unsigned EIDH:8;
  }bits;
 }h;
 union _EIDL
 {
  unsigned char byte;
  struct _EIDL_BITS
  {
   unsigned EIDL:8;
  }bits;
 }l;
}CAN_EID;



typedef union _CID
{
 CAN_EID ext;
 CAN_SID std;
}CAN_CID;



typedef union _DLC
{
 unsigned char byte;
 struct _DLC_BITS
 {
  unsigned count:4;
  unsigned :2;
  unsigned rtr:1;
  unsigned :1;
 }bits;
}CAN_DLC;



typedef struct _CAN_MSG
{
 CAN_CID cid;
 CAN_DLC dlc;
 unsigned char D0;
 unsigned char D1;
 unsigned char D2;
 unsigned char D3;
 unsigned char D4;
 unsigned char D5;
 unsigned char D6;
 unsigned char D7;
}CAN_MSG;





typedef union _CAN_MSGHANDLE
{
 unsigned char byte;
 struct _CAN_MSGHANDLE_BITS
 {
  unsigned h1:1;
  unsigned h2:1;
  unsigned h3:1;
  unsigned h4:1;
  unsigned h5:1;
  unsigned h6:1;
  unsigned h7:1;
  unsigned h8:1;
 }bits;
 struct _CAN_MSGHANDLE_NIB
 {
  unsigned num:3;
  unsigned grp:2;
  unsigned hwbuf:3;
 }msg;
}CAN_HMSG;





typedef struct _CAN_DATA
{
 unsigned char B0;
 unsigned char B1;
 unsigned char B2;
 unsigned char B3;
 unsigned char B4;
 unsigned char B5;
 unsigned char B6;
 unsigned char B7;
}CAN_DATA;


struct _BITS
{
 unsigned b0:1;
 unsigned b1:1;
 unsigned b2:1;
 unsigned b3:1;
 unsigned b4:1;
 unsigned b5:1;
 unsigned b6:1;
 unsigned b7:1;
};

union _UINT8
{
 unsigned char byte;
 struct _BITS bits;
};

union _SINT8
{
 char byte;
 struct _BITS bits;
};

struct _INT16
{
 union _UINT8 B0;
 union _UINT8 B1;
};

struct _INT24
{
 union _UINT8 B0;
 union _UINT8 B1;
 union _UINT8 B3;
};

struct _INT32
{
 union _UINT8 B0;
 union _UINT8 B1;
 union _UINT8 B2;
 union _UINT8 B3;
};


struct _INT40
{
 union _UINT8 B0;
 union _UINT8 B1;
 union _UINT8 B2;
 union _UINT8 B3;
 union _UINT8 B4;
};


struct _INT48
{
 union _UINT8 B0;
 union _UINT8 B1;
 union _UINT8 B2;
 union _UINT8 B3;
 union _UINT8 B4;
 union _UINT8 B5;
};


struct _INT56
{
 union _UINT8 B0;
 union _UINT8 B1;
 union _UINT8 B2;
 union _UINT8 B3;
 union _UINT8 B4;
 union _UINT8 B5;
 union _UINT8 B6;
};


struct _INT64
{
 union _UINT8 B0;
 union _UINT8 B1;
 union _UINT8 B2;
 union _UINT8 B3;
 union _UINT8 B4;
 union _UINT8 B5;
 union _UINT8 B6;
 union _UINT8 B7;
};


union _UINT16
{
 unsigned int word;
 struct _INT16 bytes;
};

union _SINT16
{
 signed int word;
 struct _INT16 bytes;
};

union _UINT24
{
 __uint24 word;
 struct _INT24 bytes;
};

union _SINT24
{
 __int24 word;
 struct _INT24 bytes;
};


union _UINT32
{
 unsigned long word;
 struct _INT32 bytes;
};

union _SINT32
{
 signed long word;
 struct _INT32 bytes;
};


union _UINT40
{
 unsigned long word;
 struct _INT40 bytes;
};

union _SINT40
{
 signed long word;
 struct _INT40 bytes;
};


union _UINT48
{
 unsigned long word;
 struct _INT48 bytes;
};

union _SINT48
{
 signed long word;
 struct _INT48 bytes;
};


union _UINT56
{
 unsigned long word;
 struct _INT56 bytes;
};

union _SINT56
{
 signed long word;
 struct _INT56 bytes;
};


union _UINT64
{
 unsigned long word;
 struct _INT64 bytes;
};

union _SINT64
{
 signed long word;
 struct _INT64 bytes;
};


union _FLOAT
{
 double word;
};




typedef enum _BOOL { FALSE = 0, TRUE } BOOLEAN;
typedef union _SINT8 INTEGER8;
typedef union _UINT8 UNSIGNED8;
typedef union _SINT16 INTEGER16;
typedef union _UINT16 UNSIGNED16;
typedef union _SINT24 INTEGER24;
typedef union _UINT24 UNSIGNED24;
typedef union _SINT32 INTEGER32;
typedef union _UINT32 UNSIGNED32;
typedef union _SINT40 INTEGER40;
typedef union _UINT40 UNSIGNED40;
typedef union _SINT48 INTEGER48;
typedef union _UINT48 UNSIGNED48;
typedef union _SINT56 INTEGER56;
typedef union _UINT56 UNSIGNED56;
typedef union _SINT64 INTEGER64;
typedef union _UINT64 UNSIGNED64;
typedef union _FLOAT FLOAT;
typedef unsigned char * STRING;




typedef struct _DATA_BLOCK_4
{
 unsigned char bytes[4];
}_DATA4;

typedef struct __DATA7
{
 unsigned char myDat[7];
}_DATA7;

typedef struct __DATA8
{
 unsigned char myDat[8];
}_DATA8;
# 48 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_ABERR.h" 1
# 47 "CANopen/CO_ABERR.h"
typedef enum _SDO_REQ_STATUS
{
 E_SUCCESS = 0,
 E_TOGGLE,
 E_SDO_TIME,
 E_CS_CMD,
 E_MEMORY_OUT,
 E_UNSUPP_ACCESS,
 E_CANNOT_READ,
 E_CANNOT_WRITE,
 E_OBJ_NOT_FOUND,
 E_OBJ_CANNOT_MAP,
 E_OBJ_MAP_LEN,
 E_GEN_PARAM_COMP,
 E_GEN_INTERNAL_COMP,
 E_HARDWARE,
 E_LEN_SERVICE,
 E_LEN_SERVICE_HIGH,
 E_LEN_SERVICE_LOW,
 E_SUBINDEX_NOT_FOUND,
 E_PARAM_RANGE,
 E_PARAM_HIGH,
 E_PARAM_LOW,
 E_MAX_LT_MIN,
 E_GENERAL,
 E_TRANSFER,
 E_LOCAL_CONTROL,
 E_DEV_STATE
}REQ_STAT;
# 49 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_DICT.h" 1
# 50 "CANopen/CO_DICT.h"
# 1 "CANopen/CO_DEV.h" 1
# 47 "CANopen/CO_DEV.h"
extern const unsigned long rCO_DevType;
extern const unsigned char rCO_DevName[];
extern const unsigned char rCO_DevHardwareVer[];
extern const unsigned char rCO_DevSoftwareVer[];

extern const unsigned char rCO_DevIdentityIndx;
extern const unsigned long rCO_DevVendorID;
extern const unsigned long rCO_DevProductCode;
extern const unsigned long rCO_DevRevNo;
extern const unsigned long rCO_DevSerialNo;

extern unsigned char uCO_DevErrReg;
extern unsigned long uCO_DevManufacturerStatReg;
extern unsigned long uCO_DevPredefinedErrField;
# 51 "CANopen/CO_DICT.h" 2
# 1 "CANopen/CO_SYNC.h" 1
# 54 "CANopen/CO_SYNC.h"
extern UNSIGNED32 _uSYNC_COBID;
# 74 "CANopen/CO_SYNC.h"
void _CO_COMM_SYNC_Open(void);
# 92 "CANopen/CO_SYNC.h"
void _CO_COMM_SYNC_Close(void);
# 111 "CANopen/CO_SYNC.h"
void _CO_COMM_SYNC_RXEvent(void);
# 129 "CANopen/CO_SYNC.h"
void _CO_COMM_SYNC_COBIDAccessEvent(void);
# 52 "CANopen/CO_DICT.h" 2
# 1 "CANopen/CO_NMTE.h" 1
# 73 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_HeartBeatAccessEvent(void);
# 91 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_GuardTimeAccessEvent(void);
# 109 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_LifeFactorAccessEvent(void);
# 128 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_Open(void);
# 146 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_Close(void);
# 165 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_RXEvent(void);
# 185 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_TXEvent(void);
# 204 "CANopen/CO_NMTE.h"
void _CO_COMM_NMTE_LSTimerEvent(void);

extern UNSIGNED8 _uNMTEState;
extern UNSIGNED8 _uNMTELocalState;
extern UNSIGNED16 _uNMTEHeartBeat;
extern UNSIGNED16 _uNMTEGuardTime;
extern UNSIGNED8 _uNMTELifeFactor;
# 53 "CANopen/CO_DICT.h" 2
# 1 "CANopen/CO_SDO1.h" 1
# 51 "CANopen/CO_SDO1.h"
extern const unsigned char _uSDO1COMMIndx;
# 71 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_CS_COBIDAccessEvent(void);
# 90 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_SC_COBIDAccessEvent(void);
# 110 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_Open(void);
# 129 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_Close(void);
# 148 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_LSTimerEvent(void);
# 166 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_TXEvent(void);
# 184 "CANopen/CO_SDO1.h"
void _CO_COMM_SDO1_RXEvent(void);
# 54 "CANopen/CO_DICT.h" 2


typedef struct _DICTIONARY_OBJECT_TEMPLATE
{
 unsigned int index;
 unsigned char subindex;
 unsigned char ctl;
 unsigned int len;
 const unsigned char * pROM;
}DICT_OBJECT_TEMPLATE;



enum DICT_CTL
 {
  ACCESS_BITS = 0b00000111,

  NA = 0b00000000,
  CONST = 0b00000101,
  RW = 0b00000011,
  RO = 0b00000001,
  WO = 0b00000010,
  RW_EE = 0b00001011,
  RO_EE = 0b00001001,
  WO_EE = 0b00001010,
  FUNC = 0b00010000,

  RD_BIT = 0b00000001,

  N_RD = 0b01111110,

  WR_BIT = 0b00000010,

  N_WR = 0b01111101,

  ROM_BIT = 0b00000100,
  ROM = 0b01111111,
  N_ROM = 0b01111011,

  EE_BIT = 0b00001000,
  EE = 0b01111111,
  N_EE = 0b01110111,

  FDEF_BIT = 0b00010000,
  FDEF = 0b01111111,
  N_FDEF = 0b01101111,

  MAP_BIT = 0b00100000,
  MAP = 0b01111111,
  N_MAP = 0b01011111,

  FSUB_BIT = 0b01000000,
  FSUB = 0b01111111,
  N_FSUB = 0b00111111
 };


typedef struct _DICTIONARY_EXTENDED_OBJECT
{







 unsigned char * pReqBuf;

 unsigned int reqLen;
 unsigned int reqOffst;

 unsigned int index;
 unsigned char subindex;

    enum DICT_CTL ctl;

 unsigned int len;

 union DICT_PTRS
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
 DICT_OBJ * obj;
 enum _DICT_OBJECT_REQUEST
 {
  DICT_OBJ_INFO = 0,
  DICT_OBJ_READ = 1,
  DICT_OBJ_WRITE = 2
 }cmd;
 unsigned char ret;
}DICT_PARAM;


extern DICT_PARAM uDict;



void _CO_DictObjectRead(void);
void _CO_DictObjectWrite(void);
void _CO_DictObjectDecode(void);
void _CO_DictTest(void);
void _CO_TestObjectAccessEvent(void);
# 50 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_MEMIO.h" 1
# 75 "CANopen/CO_MEMIO.h"
void CO_MEMIO_CopySram(unsigned char *pIn, unsigned char *pOut, unsigned int len);
# 98 "CANopen/CO_MEMIO.h"
void CO_MEMIO_CopyRomToRam(const unsigned char *pIn, unsigned char *pOut, unsigned int len);
# 51 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_DICT.def" 1






# 1 "CANopen/CO_DEV.h" 1
# 47 "CANopen/CO_DEV.h"
extern const unsigned long rCO_DevType;
extern const unsigned char rCO_DevName[];
extern const unsigned char rCO_DevHardwareVer[];
extern const unsigned char rCO_DevSoftwareVer[];

extern const unsigned char rCO_DevIdentityIndx;
extern const unsigned long rCO_DevVendorID;
extern const unsigned long rCO_DevProductCode;
extern const unsigned long rCO_DevRevNo;
extern const unsigned long rCO_DevSerialNo;

extern unsigned char uCO_DevErrReg;
extern unsigned long uCO_DevManufacturerStatReg;
extern unsigned long uCO_DevPredefinedErrField;
# 8 "CANopen/CO_DICT.def" 2
# 52 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_MFTR.def" 1
# 53 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_PDO.def" 1


# 1 "CANopen/DemoObj.h" 1
# 48 "CANopen/DemoObj.h"
extern const unsigned long uTPDO1Map;
extern const unsigned long uRPDO1Map;
extern const unsigned long uPDO1Dummy;

extern unsigned char uIOinFilter;
extern unsigned char uIOinPolarity;
extern unsigned char uIOinIntChange;
extern unsigned char uIOinIntRise;
extern unsigned char uIOinIntFall;
extern unsigned char uIOinIntEnable;
extern unsigned char uIOinDigiInputs;

extern unsigned char uIOinDigiInOld;

extern unsigned char uLocalXmtBuffer[8];
extern unsigned char uLocalRcvBuffer[8];

extern const unsigned char uDemoTPDO1Len;
extern const unsigned char rMaxIndex1;
extern const unsigned char rMaxIndex2;


void DemoProcessEvents(void);
void DemoInit(void);
void CO_COMM_TPDO1_COBIDAccessEvent(void);
void CO_COMM_RPDO1_COBIDAccessEvent(void);
void CO_COMM_TPDO1_TypeAccessEvent(void);
# 4 "CANopen/CO_PDO.def" 2
# 54 "CANopen/CO_DICT.c" 2
# 1 "CANopen/CO_STD.def" 1






# 1 "CANopen/DemoObj.h" 1
# 48 "CANopen/DemoObj.h"
extern const unsigned long uTPDO1Map;
extern const unsigned long uRPDO1Map;
extern const unsigned long uPDO1Dummy;

extern unsigned char uIOinFilter;
extern unsigned char uIOinPolarity;
extern unsigned char uIOinIntChange;
extern unsigned char uIOinIntRise;
extern unsigned char uIOinIntFall;
extern unsigned char uIOinIntEnable;
extern unsigned char uIOinDigiInputs;

extern unsigned char uIOinDigiInOld;

extern unsigned char uLocalXmtBuffer[8];
extern unsigned char uLocalRcvBuffer[8];

extern const unsigned char uDemoTPDO1Len;
extern const unsigned char rMaxIndex1;
extern const unsigned char rMaxIndex2;


void DemoProcessEvents(void);
void DemoInit(void);
void CO_COMM_TPDO1_COBIDAccessEvent(void);
void CO_COMM_RPDO1_COBIDAccessEvent(void);
void CO_COMM_TPDO1_TypeAccessEvent(void);
# 8 "CANopen/CO_STD.def" 2
# 55 "CANopen/CO_DICT.c" 2



DICT_PARAM uDict;


const unsigned char * _pTmpDBase;
unsigned char _tDBaseLen;

unsigned char _uDictTemp[4];
MULTIPLEXOR _tMplex;

const unsigned char __dummy[4] = {0,0,0,0};



const DICT_OBJECT_TEMPLATE _db_objects[] = {
    {0x0001,0x00, WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]},
    {0x0002,0x00, WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]},
    {0x0003,0x00, WO | ROM_BIT | MAP_BIT,2,(const unsigned char *)&__dummy[0]},
    {0x0004,0x00, WO | ROM_BIT | MAP_BIT,4,(const unsigned char *)&__dummy[0]},
    {0x0005,0x00, WO | ROM_BIT | MAP_BIT,1,(const unsigned char *)&__dummy[0]},
    {0x0006,0x00, WO | ROM_BIT | MAP_BIT,2,(const unsigned char *)&__dummy[0]},
    {0x0007,0x00, WO | ROM_BIT | MAP_BIT,4,(const unsigned char *)&__dummy[0]}
};

const DICT_OBJECT_TEMPLATE _db_device[] = {{0x1000,0x00,CONST,4,(const unsigned char *)&rCO_DevType}, {0x1001,0x00,RO,1,(const unsigned char *)&uCO_DevErrReg}, {0x1002,0x00,RO,4,(const unsigned char *)&uCO_DevManufacturerStatReg}, {0x1005,0x00,FUNC | RW,4,(const unsigned char *)&_CO_COMM_SYNC_COBIDAccessEvent}, {0x1008,0x00,CONST,24,(const unsigned char *)&rCO_DevName}, {0x1009,0x00,CONST,4,(const unsigned char *)&rCO_DevHardwareVer}, {0x100A,0x00,CONST,4,(const unsigned char *)&rCO_DevSoftwareVer}, {0x100C,0x00,FUNC | RW,2,(const unsigned char *)&_CO_COMM_NMTE_GuardTimeAccessEvent}, {0x100D,0x00,FUNC | RW,1,(const unsigned char *)&_CO_COMM_NMTE_LifeFactorAccessEvent}, {0x1017,0x00,FUNC | RW,2,(const unsigned char *)&_CO_COMM_NMTE_HeartBeatAccessEvent}, {0x1018,0x00,CONST,1,(const unsigned char *)&rCO_DevIdentityIndx}, {0x1018,0x01,CONST,4,(const unsigned char *)&rCO_DevVendorID}, {0x1018,0x02,CONST,4,(const unsigned char *)&rCO_DevProductCode}, {0x1018,0x03,CONST,4,(const unsigned char *)&rCO_DevRevNo}, {0x1018,0x04,CONST,4,(const unsigned char *)&rCO_DevSerialNo}};

const DICT_OBJECT_TEMPLATE _db_sdo[] = {{0x1200,0x00,CONST,1,(const unsigned char *)&_uSDO1COMMIndx}, {0x1200,0x01,FUNC | RO,4,(const unsigned char *)&_CO_COMM_SDO1_CS_COBIDAccessEvent}, {0x1200,0x02,FUNC | RO,4,(const unsigned char *)&_CO_COMM_SDO1_SC_COBIDAccessEvent}};

const DICT_OBJECT_TEMPLATE _db_pdo1_rx_comm[] = {{0x1400,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x1400,0x01,RW | FUNC,4,(const unsigned char *)&CO_COMM_RPDO1_COBIDAccessEvent}};
# 96 "CANopen/CO_DICT.c"
const DICT_OBJECT_TEMPLATE _db_pdo1_rx_map[] = {{0x1600,0x00,CONST,1,(const unsigned char *)&rMaxIndex2}, {0x1600,0x01,CONST,4,(const unsigned char *)&uRPDO1Map}, {0x1600,0x02,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1600,0x03,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1600,0x04,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1600,0x05,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1600,0x06,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1600,0x07,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1600,0x08,CONST,4,(const unsigned char *)&uPDO1Dummy}};
# 107 "CANopen/CO_DICT.c"
const DICT_OBJECT_TEMPLATE _db_pdo1_tx_comm[] = {{0x1800,0x00,CONST,1,(const unsigned char *)&uDemoTPDO1Len}, {0x1800,0x01,RW | FUNC,4,(const unsigned char *)&CO_COMM_TPDO1_COBIDAccessEvent}, {0x1800,0x02,RW | FUNC,1,(const unsigned char *)&CO_COMM_TPDO1_TypeAccessEvent}};
# 118 "CANopen/CO_DICT.c"
const DICT_OBJECT_TEMPLATE _db_pdo1_tx_map[] = {{0x1A00,0x00,CONST,1,(const unsigned char *)&rMaxIndex2}, {0x1A00,0x01,CONST,4,(const unsigned char *)&uTPDO1Map}, {0x1A00,0x02,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1A00,0x03,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1A00,0x04,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1A00,0x05,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1A00,0x06,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1A00,0x07,CONST,4,(const unsigned char *)&uPDO1Dummy}, {0x1A00,0x08,CONST,4,(const unsigned char *)&uPDO1Dummy}};
# 129 "CANopen/CO_DICT.c"
const DICT_OBJECT_TEMPLATE _db_manufacturer_g1[] = {{0x2000,0x00,0,1,(const unsigned char *)&__dummy}, {0x2000,0x00,0,1,(const unsigned char *)&__dummy}};
const DICT_OBJECT_TEMPLATE _db_manufacturer_g2[] = {{0x3000,0x00,0,1,(const unsigned char *)&__dummy}, {0x3000,0x00,0,1,(const unsigned char *)&__dummy}};
const DICT_OBJECT_TEMPLATE _db_manufacturer_g3[] = {{0x4000,0x00,0,1,(const unsigned char *)&__dummy}, {0x4000,0x00,0,1,(const unsigned char *)&__dummy}};
const DICT_OBJECT_TEMPLATE _db_manufacturer_g4[] = {{0x5000,0x00,0,1,(const unsigned char *)&__dummy}, {0x5000,0x00,0,1,(const unsigned char *)&__dummy}};
const DICT_OBJECT_TEMPLATE _db_standard_g1[] = {{0x6000,0x00,RO,1,(const unsigned char *)&uLocalXmtBuffer[0]}, {0x6002,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x6002,0x01,RW,1,(const unsigned char *)&uIOinPolarity}, {0x6003,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x6003,0x01,RW,1,(const unsigned char *)&uIOinFilter}, {0x6005,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x6005,0x01,RW,1,(const unsigned char *)&uIOinIntEnable}, {0x6006,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x6006,0x01,RW,1,(const unsigned char *)&uIOinIntChange}, {0x6007,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x6007,0x01,RW,1,(const unsigned char *)&uIOinIntRise}, {0x6008,0x00,CONST,1,(const unsigned char *)&rMaxIndex1}, {0x6008,0x01,RW,1,(const unsigned char *)&uIOinIntFall}, {0x6200,0x00,RW,1,(const unsigned char *)&uLocalRcvBuffer[0]}};
const DICT_OBJECT_TEMPLATE _db_standard_g2[] = {{0x7000,0x00,0,1,(const unsigned char *)&__dummy}, {0x7000,0x00,0,1,(const unsigned char *)&__dummy}};
const DICT_OBJECT_TEMPLATE _db_standard_g3[] = {{0x8000,0x00,0,1,(const unsigned char *)&__dummy}, {0x8000,0x00,0,1,(const unsigned char *)&__dummy}};
const DICT_OBJECT_TEMPLATE _db_standard_g4[] = {{0x9000,0x00,0,1,(const unsigned char *)&__dummy}, {0x9000,0x00,0,1,(const unsigned char *)&__dummy}};
# 158 "CANopen/CO_DICT.c"
void _CO_DictObjectRead(void)
{

 if (uDict.obj->ctl)
 {

  if (uDict.obj->ctl & FDEF_BIT)
  {
   uDict.ret = E_SUCCESS;
   uDict.cmd = DICT_OBJ_READ;
   uDict.obj->p.pFunc();
   return;
  }
  else


  switch (uDict.obj->ctl & ACCESS_BITS)
  {
   case CONST:

    CO_MEMIO_CopyRomToRam(uDict.obj->p.pROM + uDict.obj->reqOffst, uDict.obj->pReqBuf, uDict.obj->reqLen);
    break;

   case RO:
   case RW:

    CO_MEMIO_CopySram(uDict.obj->p.pRAM + uDict.obj->reqOffst, uDict.obj->pReqBuf, uDict.obj->reqLen);
    break;





   default:

    uDict.ret = E_CANNOT_READ;
    return;
  }
 }

 uDict.ret = E_SUCCESS;
 return;
}
# 220 "CANopen/CO_DICT.c"
void _CO_DictObjectWrite(void)
{

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


  switch (uDict.obj->ctl & ACCESS_BITS)
  {
   case RW:
   case WO:

    CO_MEMIO_CopySram(uDict.obj->pReqBuf, uDict.obj->p.pRAM, uDict.obj->reqLen);
    break;





   default:

    uDict.ret = E_CANNOT_WRITE;
    return;
  }
 }

 uDict.ret = E_SUCCESS;
 return;
}
# 281 "CANopen/CO_DICT.c"
void _CO_DictObjectDecode(void)
{

 _tMplex = *(MULTIPLEXOR *)(&(uDict.obj->index));

 switch (_tMplex.index.bytes.B1.byte & 0xF0)
 {
  case 0x00:
   _pTmpDBase = (const unsigned char *)_db_objects;
   _tDBaseLen = sizeof(_db_objects)/sizeof(DICT_OBJECT_TEMPLATE);
   break;

  case 0x20:
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

  case 0x60:
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
    case 0x00:
     _pTmpDBase = (const unsigned char *)_db_device;
     _tDBaseLen = sizeof(_db_device)/sizeof(DICT_OBJECT_TEMPLATE);
     break;

    case 0x02:
     _pTmpDBase = (const unsigned char *)_db_sdo;
     _tDBaseLen = sizeof(_db_sdo)/sizeof(DICT_OBJECT_TEMPLATE);
     break;

    case 0x04:
     if (_tMplex.index.bytes.B0.byte == 0x00)
     {
      _pTmpDBase = (const unsigned char *)_db_pdo1_rx_comm;
      _tDBaseLen = sizeof(_db_pdo1_rx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
     }
     else
# 371 "CANopen/CO_DICT.c"
     {

      uDict.ret = E_OBJ_NOT_FOUND;
      return;
     }
     break;


    case 0x06:
     if (_tMplex.index.bytes.B0.byte == 0x00)
     {
      _pTmpDBase = (const unsigned char *)_db_pdo1_rx_map;
      _tDBaseLen = sizeof(_db_pdo1_rx_map)/sizeof(DICT_OBJECT_TEMPLATE);
     }
     else
# 410 "CANopen/CO_DICT.c"
     {

      uDict.ret = E_OBJ_NOT_FOUND;
      return;
     }
     break;


    case 0x08:
     if (_tMplex.index.bytes.B0.byte == 0x00)
     {
      _pTmpDBase = (const unsigned char *)_db_pdo1_tx_comm;
      _tDBaseLen = sizeof(_db_pdo1_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
     }
     else
# 449 "CANopen/CO_DICT.c"
     {

      uDict.ret = E_OBJ_NOT_FOUND;
      return;
     }
     break;


    case 0x0A:
     if (_tMplex.index.bytes.B0.byte == 0x00)
     {
      _pTmpDBase = (const unsigned char *)_db_pdo1_tx_map;
      _tDBaseLen = sizeof(_db_pdo1_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
     }
     else
# 488 "CANopen/CO_DICT.c"
     {

      uDict.ret = E_OBJ_NOT_FOUND;
      return;
     }
     break;
# 504 "CANopen/CO_DICT.c"
    default:

     uDict.ret = E_OBJ_NOT_FOUND;
     return;
   }
   break;

  default:

   uDict.ret = E_OBJ_NOT_FOUND;
   return;
 }



 uDict.ret = E_OBJ_NOT_FOUND;


 *(_DATA4 *)(&(_uDictTemp[0])) = *(const _DATA4 *)_pTmpDBase;


 while(_tDBaseLen)
 {

  if ((_uDictTemp[1] == _tMplex.index.bytes.B1.byte) &&
   (_uDictTemp[0] == _tMplex.index.bytes.B0.byte))
  {

   uDict.ret = E_SUBINDEX_NOT_FOUND;


   if ((_uDictTemp[2] == _tMplex.sindex.byte) ||
     (_uDictTemp[3] & FSUB_BIT))
   {

       *((DICT_OBJECT_TEMPLATE *)(&(uDict.obj->index))) = *((const DICT_OBJECT_TEMPLATE *)(_pTmpDBase));


       if (_uDictTemp[3] & FSUB_BIT) uDict.obj->subindex = _tMplex.sindex.byte;



    if (_uDictTemp[3] & FDEF_BIT)
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


  _pTmpDBase += sizeof(DICT_OBJECT_TEMPLATE);

  _tDBaseLen--;


  *(_DATA4 *)(&(_uDictTemp[0])) = *(const _DATA4 *)_pTmpDBase;
 }
 return;
}
