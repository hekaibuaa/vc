
/*--------------------------- same endian ------------------------------------*/

char get_s08_same(const unsigned char *buf)
{
  return buf[0];
}

unsigned char get_u08_same(const unsigned char *buf)
{
  return (unsigned char)(buf[0]);
}

short get_s16_same(const unsigned char *buf)
{
  short dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  
  return dat;
}

unsigned short get_u16_same(const unsigned char *buf)
{
  unsigned short dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  
  return dat;
}

int get_s32_same(const unsigned char *buf)
{
  int dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  p[2] = buf[2];
  p[3] = buf[3];
  
  return dat;
}

unsigned int get_u32_same(const unsigned char *buf)
{
  unsigned int dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  p[2] = buf[2];
  p[3] = buf[3];
  
  return dat;
}

long long get_s64_same(const unsigned char *buf)
{
  long long dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  p[2] = buf[2];
  p[3] = buf[3];
  p[4] = buf[4];
  p[5] = buf[5];
  p[6] = buf[6];
  p[7] = buf[7];
  
  return dat;
}

unsigned long long get_u64_same(const unsigned char *buf)
{
  unsigned long long dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  p[2] = buf[2];
  p[3] = buf[3];
  p[4] = buf[4];
  p[5] = buf[5];
  p[6] = buf[6];
  p[7] = buf[7];
  
  return dat;
}

float get_f32_same(const unsigned char *buf)
{
  float dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  p[2] = buf[2];
  p[3] = buf[3];
  
  return dat;
}

double get_f64_same(const unsigned char *buf)
{
  double dat;
  unsigned char *p = (unsigned char *)&dat;

  p[0] = buf[0];
  p[1] = buf[1];
  p[2] = buf[2];
  p[3] = buf[3];
  p[4] = buf[4];
  p[5] = buf[5];
  p[6] = buf[6];
  p[7] = buf[7];

  return dat;
}

unsigned int set_s08_same(unsigned char *buf, char dat)
{
  buf[0] = dat;

  return 1u;
}

unsigned int set_u08_same(unsigned char *buf, unsigned char dat)
{
  buf[0] = (char )dat;

  return 1u;
}

unsigned int set_s16_same(unsigned char *buf, short dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];

  return 2u;
}

unsigned int set_u16_same(unsigned char *buf, unsigned short dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];

  return 2u;
}

unsigned int set_s32_same(unsigned char *buf, int dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];
  buf[2] = p[2];
  buf[3] = p[3];

  return 4u;
}

unsigned int set_u32_same(unsigned char *buf, unsigned int dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];
  buf[2] = p[2];
  buf[3] = p[3];

  return 4u;
}

unsigned int set_s64_same(unsigned char *buf, long long dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];
  buf[2] = p[2];
  buf[3] = p[3];
  buf[4] = p[4];
  buf[5] = p[5];
  buf[6] = p[6];
  buf[7] = p[7];
  
  return 8u;
}

unsigned int set_u64_same(unsigned char *buf, unsigned long long dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];
  buf[2] = p[2];
  buf[3] = p[3];
  buf[4] = p[4];
  buf[5] = p[5];
  buf[6] = p[6];
  buf[7] = p[7];
  
  return 8u;
}

unsigned int set_f32_same(unsigned char *buf, float dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];
  buf[2] = p[2];
  buf[3] = p[3];

  return 4u;
}

unsigned int set_f64_same(unsigned char *buf, double dat)
{
  unsigned char *p = (unsigned char *)&dat;
  
  buf[0] = p[0];
  buf[1] = p[1];
  buf[2] = p[2];
  buf[3] = p[3];
  buf[4] = p[4];
  buf[5] = p[5];
  buf[6] = p[6];
  buf[7] = p[7];

  return 8u;
}

/*--------------------------- same endian ------------------------------------*/

char get_s08_diff(const unsigned char *buf)
{
  return buf[0];
}
unsigned char get_u08_diff(const unsigned char *buf)
{
  return (unsigned char)(buf[0]);
}

short get_s16_diff(const unsigned char *buf)
{
  short dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[1];
  p[1] = buf[0];    
    
  return dat;
}

unsigned short get_u16_diff(const unsigned char *buf)
{
  unsigned short dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[1];
  p[1] = buf[0];  
          
  return dat;
}

int get_s32_diff(const unsigned char *buf)
{
  int dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[3];
  p[1] = buf[2];  
  p[2] = buf[1];
  p[3] = buf[0];  
      
  return dat;
}

unsigned int get_u32_diff(const unsigned char *buf)
{
  unsigned int dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[3];
  p[1] = buf[2];  
  p[2] = buf[1];
  p[3] = buf[0];  
      
  return dat;
}

long long get_s64_diff(const unsigned char *buf)
{
  long long dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[7];
  p[1] = buf[6];  
  p[2] = buf[5];
  p[3] = buf[4];  
  p[4] = buf[3];
  p[5] = buf[2];  
  p[6] = buf[1];
  p[7] = buf[0];  
  
  return dat;
}

unsigned long long get_u64_diff(const unsigned char *buf)
{
  unsigned long long dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[7];
  p[1] = buf[6];  
  p[2] = buf[5];
  p[3] = buf[4];  
  p[4] = buf[3];
  p[5] = buf[2];  
  p[6] = buf[1];
  p[7] = buf[0];   
      
  return dat;
}

float get_f32_diff(const unsigned char *buf)
{
  float dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[3];
  p[1] = buf[2];  
  p[2] = buf[1];
  p[3] = buf[0];  
      
  return dat;
}

double get_f64_diff(const unsigned char *buf)
{
  double dat;
  unsigned char *p=(unsigned char *)&dat;

  p[0] = buf[7];
  p[1] = buf[6];  
  p[2] = buf[5];
  p[3] = buf[4]; 
  p[4] = buf[3];
  p[5] = buf[2];  
  p[6] = buf[1];
  p[7] = buf[0]; 
  
  return dat;
}

unsigned int set_s08_diff(unsigned char *buf, char dat)
{
  buf[0] = (unsigned char)dat;

  return 1u;
}

unsigned int set_u08_diff(unsigned char *buf, unsigned char dat)
{
  buf[0] = dat;

  return 1u;
}

unsigned int set_s16_diff(unsigned char *buf, short dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[1];
  buf[1] = p[0];

  return 2u;
}

unsigned int set_u16_diff(unsigned char *buf, unsigned short dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[1];
  buf[1] = p[0];

  return 2u;
}
  
unsigned int set_s32_diff(unsigned char *buf, int dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[3];
  buf[1] = p[2];
  buf[2] = p[1];
  buf[3] = p[0];

  return 4u;
}

unsigned int set_u32_diff(unsigned char *buf, unsigned int dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[3];
  buf[1] = p[2];
  buf[2] = p[1];
  buf[3] = p[0];

  return 4u;
}

unsigned int set_s64_diff(unsigned char *buf, long long dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[7];
  buf[1] = p[6];
  buf[2] = p[5];
  buf[3] = p[4];
  buf[4] = p[3];
  buf[5] = p[2];
  buf[6] = p[1];
  buf[7] = p[0];
  
  return 8u;
}

unsigned int set_u64_diff(unsigned char *buf, unsigned long long dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[7];
  buf[1] = p[6];
  buf[2] = p[5];
  buf[3] = p[4];
  buf[4] = p[3];
  buf[5] = p[2];
  buf[6] = p[1];
  buf[7] = p[0];

  return 8u;
}

unsigned int set_f32_diff(unsigned char *buf, float dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[3];
  buf[1] = p[2];
  buf[2] = p[1];
  buf[3] = p[0];

  return 4u;
}

unsigned int set_f64_diff(unsigned char *buf, double dat)
{
  unsigned char *p = (unsigned char *)&dat;

  buf[0] = p[7];
  buf[1] = p[6];
  buf[2] = p[5];
  buf[3] = p[4];
  buf[4] = p[3];
  buf[5] = p[2];
  buf[6] = p[1];
  buf[7] = p[0];

  return 8u;
}

