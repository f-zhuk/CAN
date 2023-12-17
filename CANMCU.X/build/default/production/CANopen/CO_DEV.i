# 1 "CANopen/CO_DEV.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.00/packs/Microchip/PIC18F-K_DFP/1.5.114/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "CANopen/CO_DEV.c" 2
# 45 "CANopen/CO_DEV.c"
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
# 45 "CANopen/CO_DEV.c" 2




const unsigned long rCO_DevType = 0x8934AL;


const unsigned char rCO_DevName[] = "Microchip CANopen Device";


const unsigned char rCO_DevHardwareVer[] = "V1.0";


const unsigned char rCO_DevSoftwareVer[] = "V1.0";


const unsigned char rCO_DevIdentityIndx = 0x4;
const unsigned long rCO_DevVendorID = 0x12345678L;
const unsigned long rCO_DevProductCode = 0x87654321L;
const unsigned long rCO_DevRevNo = 0x12345678L;
const unsigned long rCO_DevSerialNo = 0x87654321L;


unsigned char uCO_DevErrReg;


unsigned long uCO_DevManufacturerStatReg;
