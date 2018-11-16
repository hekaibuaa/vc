
#ifndef LIB_BYTES_H
#define LIB_BYTES_H

/* same endian */

extern char               get_s08_same(const unsigned char *buf);
extern unsigned char      get_u08_same(const unsigned char *buf);
extern short              get_s16_same(const unsigned char *buf);
extern unsigned short     get_u16_same(const unsigned char *buf);
extern int                get_s32_same(const unsigned char *buf);
extern unsigned int       get_u32_same(const unsigned char *buf);
extern long long          get_s64_same(const unsigned char *buf);
extern unsigned long long get_u64_same(const unsigned char *buf);
extern float              get_f32_same(const unsigned char *buf);
extern double             get_f64_same(const unsigned char *buf);

extern unsigned int set_s08_same(unsigned char *buf, char dat);
extern unsigned int set_u08_same(unsigned char *buf, unsigned char dat);
extern unsigned int set_s16_same(unsigned char *buf, short dat);
extern unsigned int set_u16_same(unsigned char *buf, unsigned short dat);
extern unsigned int set_s32_same(unsigned char *buf, int dat);
extern unsigned int set_u32_same(unsigned char *buf, unsigned int dat);
extern unsigned int set_s64_same(unsigned char *buf, long long dat);
extern unsigned int set_u64_same(unsigned char *buf, unsigned long long dat);
extern unsigned int set_f32_same(unsigned char *buf, float dat);
extern unsigned int set_f64_same(unsigned char *buf, double dat);

/* different endian */

extern char               get_s08_diff(const unsigned char *buf);
extern unsigned char      get_u08_diff(const unsigned char *buf);
extern short              get_s16_diff(const unsigned char *buf);
extern unsigned short     get_u16_diff(const unsigned char *buf);
extern int                get_s32_diff(const unsigned char *buf);
extern unsigned int       get_u32_diff(const unsigned char *buf);
extern long long          get_s64_diff(const unsigned char *buf);
extern unsigned long long get_u64_diff(const unsigned char *buf);
extern float              get_f32_diff(const unsigned char *buf);
extern double             get_f64_diff(const unsigned char *buf);

extern unsigned int set_s08_diff(unsigned char *buf, char dat);
extern unsigned int set_u08_diff(unsigned char *buf, unsigned char dat);
extern unsigned int set_s16_diff(unsigned char *buf, short dat);
extern unsigned int set_u16_diff(unsigned char *buf, unsigned short dat);
extern unsigned int set_s32_diff(unsigned char *buf, int dat);
extern unsigned int set_u32_diff(unsigned char *buf, unsigned int dat);
extern unsigned int set_s64_diff(unsigned char *buf, long long dat);
extern unsigned int set_u64_diff(unsigned char *buf, unsigned long long dat);
extern unsigned int set_f32_diff(unsigned char *buf, float dat);
extern unsigned int set_f64_diff(unsigned char *buf, double dat);

#endif // #ifndef LIB_BYTES_H

