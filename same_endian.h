
#ifndef SAME_ENDIAN_H
#define SAME_ENDIAN_H

#ifdef DIFF_ENDIAN_H

//#error "diff_endian.h has been included, please select only one endian mode"

#undef GET_S08
#undef GET_U08
#undef GET_S16
#undef GET_U16
#undef GET_S32
#undef GET_U32
#undef GET_S64
#undef GET_U64
#undef GET_F32
#undef GET_F64

#undef SET_S08
#undef SET_U08
#undef SET_S16
#undef SET_U16
#undef SET_S32
#undef SET_U32
#undef SET_S64
#undef SET_U64
#undef SET_F32
#undef SET_F64

#endif // #ifdef DIFF_ENDIAN_H

#include "lib_bytes.h"

#define GET_S08(buf)      get_s08_same((unsigned char *)buf)
#define GET_U08(buf)      get_u08_same((unsigned char *)buf)
#define GET_S16(buf)      get_s16_same((unsigned char *)buf)
#define GET_U16(buf)      get_u16_same((unsigned char *)buf)
#define GET_S32(buf)      get_s32_same((unsigned char *)buf)
#define GET_U32(buf)      get_u32_same((unsigned char *)buf)
#define GET_S64(buf)      get_s64_same((unsigned char *)buf)
#define GET_U64(buf)      get_u64_same((unsigned char *)buf)
#define GET_F32(buf)      get_f32_same((unsigned char *)buf)
#define GET_F64(buf)      get_f64_same((unsigned char *)buf)

#define SET_S08(buf, dat) set_s08_same((unsigned char *)buf, (char)dat)
#define SET_U08(buf, dat) set_u08_same((unsigned char *)buf, (unsigned char)dat)
#define SET_S16(buf, dat) set_s16_same((unsigned char *)buf, (short)dat)
#define SET_U16(buf, dat) set_u16_same((unsigned char *)buf, (unsigned short)dat)
#define SET_S32(buf, dat) set_s32_same((unsigned char *)buf, (int)dat)
#define SET_U32(buf, dat) set_u32_same((unsigned char *)buf, (unsigned int)dat)
#define SET_S64(buf, dat) set_s64_same((unsigned char *)buf, (long long)dat)
#define SET_U64(buf, dat) set_u64_same((unsigned char *)buf, (unsigned long long)dat)
#define SET_F32(buf, dat) set_f32_same((unsigned char *)buf, (float)dat)
#define SET_F64(buf, dat) set_f64_same((unsigned char *)buf, (double)dat)

#endif // #ifndef SAME_ENDIAN_H

