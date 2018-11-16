
/**
* @file     lib_check.h
* @brief    library of check calculation
* @version  
* @author   hekai
* @date     2017-5-24
* @note     
*/

#ifndef LIB_CHECK_H
#define LIB_CHECK_H

/*============================ INCLUDES ======================================*/

#include "basetype.h"

/*============================ PROTOTYPES ====================================*/

extern u16 crc16(const u8 *pBytes, u32 Length);
extern unsigned int crc24q(const unsigned char *buff, int len);
extern unsigned int crc32(const unsigned char *buff, int len);
extern void UbxCheckSum(u8 *buff, u32 len, u8 *CheckA, u8 *CheckB);
extern void ZeroCheckSum(u8 *buff, u16 len, u8 *CheckA, u8 *CheckB);
extern u8 ByteSumCheck(u8 *buf, u16 len);
extern u8 ByteXorCheck(u8 *pStart, u8 *pEnd);

#endif

