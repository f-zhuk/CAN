# 1 "CANopen/CO_MEMIO.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.00/packs/Microchip/PIC18F-K_DFP/1.5.114/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "CANopen/CO_MEMIO.c" 2
# 48 "CANopen/CO_MEMIO.c"
# 1 "CANopen/CO_DEFS.def" 1
# 48 "CANopen/CO_MEMIO.c" 2

# 1 "CANopen/CO_MEMIO.h" 1
# 75 "CANopen/CO_MEMIO.h"
void CO_MEMIO_CopySram(unsigned char *pIn, unsigned char *pOut, unsigned int len);
# 98 "CANopen/CO_MEMIO.h"
void CO_MEMIO_CopyRomToRam(const unsigned char *pIn, unsigned char *pOut, unsigned int len);
# 49 "CANopen/CO_MEMIO.c" 2




typedef struct _DATA_BLOCK_16
{
 unsigned char bytes[16];
}_DATA16;

typedef struct _DATA_BLOCK_8
{
 unsigned char bytes[8];
}_DATA8;

typedef struct _DATA_BLOCK_4
{
 unsigned char bytes[4];
}_DATA4;
# 91 "CANopen/CO_MEMIO.c"
void CO_MEMIO_CopySram(unsigned char *pIn, unsigned char *pOut, unsigned int len)
{
 while (len)
 {
  if (len < 4)
  {
   *pOut = *pIn;

   pOut++;
   pIn++;
   len--;
  }
  else
  if (len < 8)
  {
   *((_DATA4 *)pOut) = *((_DATA4 *)(pIn));

   pOut += 4;
   pIn += 4;
   len -= 4;
  }
  else
  if (len < 16)
  {
   *((_DATA8 *)pOut) = *((_DATA8 *)(pIn));

   pOut += 8;
   pIn += 8;
   len -= 8;
  }
  else
  {
   *((_DATA16 *)pOut) = *((_DATA16 *)(pIn));

   pOut += 16;
   pIn += 16;
   len -= 16;
  }
 }
}
# 153 "CANopen/CO_MEMIO.c"
void CO_MEMIO_CopyRomToRam(const unsigned char *pIn, unsigned char *pOut, unsigned int len)
{
# 214 "CANopen/CO_MEMIO.c"
 while (len)
 {
  if (len < 4)
  {
   *pOut = *pIn;

   pOut++;
   pIn++;
   len--;
  }
  else
  if (len < 8)
  {
   *((_DATA4 *)(pOut)) = *((const _DATA4 *)pIn);

   pOut += 4;
   pIn += 4;
   len -= 4;
  }
  else
  {
   *((_DATA8 *)(pOut)) = *((const _DATA8 *)pIn);

   pOut += 8;
   pIn += 8;
   len -= 8;
  }
 }

}
