
#include "config.h"

#include "basetype.h"
#include "comptype.h"
#include "constants.h"

#include "trace.h"
#include "fifo.h"
#include "lib_check.h"
#include "same_endian.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>


FILE *fptest = NULL;

//void UbxCheckSum(u8 *buff, u16 len, u8 *CheckA, u8 *CheckB)
void UbxCheckSum2(u8 *buff, u32 len, u8 *CheckA, u8 *CheckB)
{
  unsigned char cka=0,ckb=0;
  int i;

  for (i = 0; i < len; i++) 
  {
    cka += buff[i]; 
    ckb += cka;

    //if (i < 10) printf("i=%d, cka=%d, ckb=%d\n", i, cka, ckb);
    fprintf(fptest, "%d 16进制%02x 计算后值%d\n", i, buff[i], cka);
  }

  if (NULL != CheckA)
  {
    *CheckA = cka;
  }
  if (NULL != CheckB)
  {
    *CheckB = ckb;
  }
}

#if ENABLE_VEAPP_BIN_TEST

void main()
{
	unsigned char dat[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    char *file = "VeAppV0_0_2.bin";
    FILE *fp = NULL;
    int size;
    unsigned char buf[100*1024]; //注意文件的大小
    unsigned int crc;
    unsigned char check_a, check_b;

    fptest = fopen("test.txt", "wt");
    assert(NULL != fptest);
    
	  crc = crc32(dat, 10);

    fp = fopen(file, "rb");
    assert(NULL != fp);

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    fread(buf, 1, size, fp);

    crc = crc32(buf, size);

    fclose(fp);

    //UbxCheckSum(dat, 10,   &check_a, &check_b);
    UbxCheckSum(buf, size, &check_a, &check_b);

    fclose(fptest);
    
    while (1);
}

#endif

#if ENABLE_STRTOK_TEST

int main(void)
{
  char input[16] = "abc,d";
  char *p;

  p = strtok(input, ",");
  if (p)
    printf("%s\n", p);
  p = strtok(NULL, ",");
  if (p)
    printf("%s\n", p);

  while (1);

  return 0;
}

#endif

#if ENABLE_BASE64_TEST

static int Base64Encode(const char *OrgString, char *Base64String, int OrgStringLen) 
{
	const static char Base64Encode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int Base64StringLen = 0;

    /* base64 encoder (8*3-->6*4) */
	while( OrgStringLen > 0 )
	{
        *Base64String ++ = Base64Encode[(OrgString[0] >> 2 ) & 0x3f];
        if( OrgStringLen > 2 )
        {
            *Base64String ++ = Base64Encode[((OrgString[0] & 3) << 4) | (OrgString[1] >> 4)];
            *Base64String ++ = Base64Encode[((OrgString[1] & 0xF) << 2) | (OrgString[2] >> 6)];
            *Base64String ++ = Base64Encode[OrgString[2] & 0x3F];
        }
        else if (OrgStringLen > 1)
        {
            *Base64String ++ = Base64Encode[((OrgString[0] & 3) << 4) | (OrgString[1] >> 4)];
            *Base64String ++ = Base64Encode[((OrgString[1] & 0x0F) << 2)];
            *Base64String ++ = '=';
        }
        else 
        {
            *Base64String ++ = Base64Encode[(OrgString[0] & 3) << 4 ];
            *Base64String ++ = '=';
            *Base64String ++ = '=';
        }
        
        OrgString +=3;
        OrgStringLen -=3;
        Base64StringLen +=4;
	}

	*Base64String = 0; /* a string ends with '\0' */
	
	return Base64StringLen;
}

static char GetBase64Value(char ch)
{
	if ((ch >= 'A') && (ch <= 'Z'))  return ch - 'A';
	if ((ch >= 'a') && (ch <= 'z'))  return ch - 'a' + 26;
	if ((ch >= '0') && (ch <= '9'))  return ch - '0' + 52;
	if (ch == '+')  return 62;
	if (ch == '/')  return 63;
	if (ch == '=')  return 0;
	return 0;
}

static int Base64Decode(char *OrgString, char *Base64String) 
{
	unsigned char Base64Encode[4],tail;
	int Base64StringLen=strlen(Base64String);
    int i,num=0,OrgStringLen=0;
    
    /* add tail '=' if necessary (len=4*X) */
	if (Base64StringLen%4) {
        tail=4-Base64StringLen%4;
        memset(Base64String+Base64StringLen,'=',tail);
        Base64StringLen+=tail;
        Base64String[Base64StringLen]='\0';
	}
	
	/* count '=' number */
	for (i=Base64StringLen-1; i>=0; i--)
	{
		if (Base64String[i] == '=') num++;
		else break;
	}
	
    /* base64 decoder (6*4-->8*3) */
	while(Base64StringLen > 0)  
	{
		Base64Encode[0] = GetBase64Value(Base64String[0]);
		Base64Encode[1] = GetBase64Value(Base64String[1]);
		Base64Encode[2] = GetBase64Value(Base64String[2]);
		Base64Encode[3] = GetBase64Value(Base64String[3]);
		
		*OrgString ++ = (Base64Encode[0] << 2) | (Base64Encode[1] >> 4);
		*OrgString ++ = (Base64Encode[1] << 4) | (Base64Encode[2] >> 2);
		*OrgString ++ = (Base64Encode[2] << 6) | (Base64Encode[3]);
		
		Base64String += 4;
		Base64StringLen -= 4;
		OrgStringLen += 3;
	}

	return OrgStringLen-num;
}

void main(void)
{
//    char *str_origin = "0";
    char *str_origin = "2";
//    char *str_origin = "doorctrl";
//    char *str_origin = "energyctrl";
//    char *str_origin = "0000118050015";

	char str_encrypt[50];
    char str_decrypt[50];

    int len_origin = strlen(str_origin);
    int len_encrypt;
    int len_decrypt;

    memset(str_encrypt, 0, sizeof(str_encrypt));
    memset(str_decrypt, 0, sizeof(str_decrypt));
    
    len_encrypt = Base64Encode(str_origin, str_encrypt, len_origin);
    printf("len_encrypt: %d, str_encrypt: %s\r\n", len_encrypt, str_encrypt);

    len_decrypt = Base64Decode(str_decrypt, str_encrypt);
    printf("len_decrypt: %d, str_decrypt: %s\r\n", len_decrypt, str_decrypt);

    while (1);
}

#endif

#if ENABLE_LOG_IMU_GPS

#define MIN_LOG_MSG_LENGTH 19
#define MAX_LOG_MSG_LENGTH 1000

#define MAX_SVNUM_NAVSAT (40)

typedef struct
{
    u8 buf[MAX_LOG_MSG_LENGTH];
    u16 len;
}LogStruct;

typedef struct
{
    u32 tick;
    s16 iAccelX, iAccelY, iAccelZ;
    s16 iGyroX, iGyroY, iGyroZ;
    f64 AccelX, AccelY, AccelZ; // after filter
    f64 GyroX, GyroY, GyroZ;    
}ImuStruct;

typedef struct
{ 
  u32 tick;
  UtcStruct utc;
  u32 towms;
  u8 SvNum, TimeValid, FixType;

  f64 LatDeg, LonDeg;   // degree
  f64 hgt, msl;         // m/s
  f64 ve, vn, vd;
  f64 GroundSpeed;      // m/s
  f64 pdop;
  f64 hacc, vacc;       // hacc: horizontal accuracy estimate(m), vacc: vertical accuracy estimate(m)
  f64 sacc, cacc;       // sacc: speed accuracy estimate(m), cacc: course/heading accuracy estimate(deg)
  f64 HeadingMotionDeg;    // heading of motion, degree
  f64 HeadingVehichleDeg;  // heading of vehicle, degree

  bool valid; // only data updated, both for fix valid and invalid, set in 'ublox.c', cleared in 'drv_gnss.c'
}UbxNavPvtStruct;

/*
typedef struct
{
  u8 gnssid;
  u8 svid;
  u8 cn0;
  s8 elevation; // deg
  s16 azimuth; 
  f64 PrangeResidual;
  u32 flags;
}SatInfoStruct;

typedef struct
{
  u32 tick;
  u32 TowMs;
  u8 numsv;
  SatInfoStruct SatInfo[MAX_SVNUM_NAVSAT];

  bool valid; // set in 'ublox.c', cleared in 'drv_gnss.c'
}UbxNavSatStruct;
*/

typedef struct
{
    u32 tick;
    s8  on;
    f32 miles; // km
    f32 speed; // km/h 
}CarStruct;

ImuStruct g_ImuData;
UbxNavPvtStruct g_UbxNavPvtData;
//UbxNavSatStruct g_UbxNavSatData;
CarStruct g_CarData;

SearchFrameStatusEnum LogSearchFrame(FifoStruct *fifo, u8 *buf, u16 *len)
{
    u8 type;
    u16 FifoLen, FrameLen, len_gps;

    if ('$' != fifo->buf[fifo->ReadPos])
    {
        FifoUpdateReadPos(fifo, 1);
        trace(TEROR, "$ error\r\n");
        return FRAME_ERROR;
    }

    type = fifo->buf[IDX_READPOS(fifo->ReadPos + 1, fifo->size)];
    if (!(1 == type || 2 == type || 3 == type))
    {
        FifoUpdateReadPos(fifo, 1);
        trace(TEROR, "type error\r\n");
        return FRAME_ERROR;
    }
    
    if (1 == type)
    {
        FrameLen = 19;
    }
    else if (3 == type)
    {
        FrameLen = 16;
    }
    else if (2 == type || 4 == type)
    {
        u8 header1 = fifo->buf[IDX_READPOS(fifo->ReadPos + 6, fifo->size)];
        u8 header2 = fifo->buf[IDX_READPOS(fifo->ReadPos + 7, fifo->size)];
        u8 classid = fifo->buf[IDX_READPOS(fifo->ReadPos + 8, fifo->size)];
        u8 msgid   = fifo->buf[IDX_READPOS(fifo->ReadPos + 9, fifo->size)];
        u8 len1    = fifo->buf[IDX_READPOS(fifo->ReadPos + 10, fifo->size)];
        u8 len2    = fifo->buf[IDX_READPOS(fifo->ReadPos + 11, fifo->size)];
        
        if (!(0xB5 == header1 && 0x62 == header2))
        {
            FifoUpdateReadPos(fifo, 1);
            trace(TEROR, "header error\r\n");
            return FRAME_ERROR;
        }
        if (2 == type)
        {
            if (!(0x01 == classid && 0x07 == msgid))
            {
                FifoUpdateReadPos(fifo, 1);
                trace(TEROR, "id error\r\n");
                return FRAME_ERROR;
            }
            if (!(0x5C == len1 && 0x00 == len2))
            {
                FifoUpdateReadPos(fifo, 1);
                trace(TEROR, "len error\r\n");
                return FRAME_ERROR;
            }
            len_gps = 100;
            FrameLen = len_gps + 7;
        }
        else 
        {
            if (!(0x01 == classid && 0x35 == msgid))
            {
                FifoUpdateReadPos(fifo, 1);
                trace(TEROR, "id error\r\n");
                return FRAME_ERROR;
            }
            len_gps = (len1| len2 << 8) + 8;
            FrameLen = len_gps + 7;
        }
    }

    if (FrameLen > MAX_LOG_MSG_LENGTH)
    {
        FifoUpdateReadPos(fifo, 1);
        trace(TEROR, "FrameLen error");        
        return FRAME_ERROR;
    }
    
    FifoLen = FifoLength(fifo);
    if (FifoLen < FrameLen)
    {
        return FRAME_HALF;
    }    

    FifoReadOut(fifo, buf, FrameLen);

    u8 sum = ByteSumCheck(buf, FrameLen - 1);
    if (sum != buf[FrameLen-1])
    {
        FifoUpdateReadPos(fifo, 1);
        trace(TEROR, "sum error\r\n");
        return FRAME_ERROR;
    }

    if (2 == type || 4 == type)
    {
        u8 checka, checkb;
        UbxCheckSum(buf+8, len_gps-4, &checka, &checkb);
        if (!(checka == buf[FrameLen-3] && checkb == buf[FrameLen-2]))
        {
            FifoUpdateReadPos(fifo, 1);
            trace(TEROR, "ubx error\r\n");
            return FRAME_ERROR;
        }
    }

    if (NULL != len)
    {
        *len = FrameLen;
    }

    FifoUpdateReadPos(fifo, FrameLen);
    return FRAME_READY;
}

// note: sensitivity keep same with "drv_imu.c"
void decode_imu(LogStruct *log)
{
    ImuStruct *imu = &g_ImuData;
    const static f64 AccelSensitivity = 4.0f / 32768.0f;
    const static f64 GyroSensitivity  = 250.0f / 32768.0f;
    
    imu->tick = GET_U32(log->buf+2);
    imu->iAccelX = GET_S16(log->buf+6);
    imu->iAccelY = GET_S16(log->buf+8);
    imu->iAccelZ = GET_S16(log->buf+10);
    imu->iGyroX  = GET_S16(log->buf+12);
    imu->iGyroY  = GET_S16(log->buf+14);
    imu->iGyroZ  = GET_S16(log->buf+16);

    imu->AccelX = imu->iAccelX * AccelSensitivity;
    imu->AccelY = imu->iAccelY * AccelSensitivity;
    imu->AccelZ = imu->iAccelZ * AccelSensitivity;
    imu->GyroX = imu->iGyroX * GyroSensitivity;
    imu->GyroY = imu->iGyroY * GyroSensitivity;
    imu->GyroZ = imu->iGyroZ * GyroSensitivity;
    
    trace(TNOTE, "imu, %d, %.3f %.3f %.3f %.3f %.3f %.3f\r\n",
        imu->tick, imu->AccelX, imu->AccelY, imu->AccelZ, imu->GyroX, imu->GyroY, imu->GyroZ);
}

void decode_car(LogStruct *log)
{
    CarStruct *car = &g_CarData;

    car->tick  = GET_U32(log->buf+2);
    car->miles = GET_F32(log->buf+6);
    car->speed = GET_F32(log->buf+10);
    car->on    = GET_S08(log->buf+14);

    trace(TNOTE, "car, %d, %.3f, %.3f, %d\r\n", car->tick, car->miles, car->speed, car->on);
}

void decode_nav_pvt(LogStruct *log)
{
    UbxNavPvtStruct *pvt = &g_UbxNavPvtData;
    unsigned char *p = log->buf + 6 + 6;

    pvt->tick      = GET_U32(log->buf+2);
    pvt->towms     = GET_U32(p);
    pvt->utc.year  = GET_U16(p + 4);
    pvt->utc.month = GET_U08(p + 6);
    pvt->utc.day   = GET_U08(p + 7);
    pvt->utc.hour  = GET_U08(p + 8);
    pvt->utc.min   = GET_U08(p + 9);
    pvt->utc.isec  = GET_U08(p + 10);
    pvt->utc.msec  = pvt->towms % 1000;
    pvt->TimeValid = GET_U08(p + 11); 

    pvt->FixType   = GET_U08(p + 20);
    pvt->SvNum     = GET_U08(p + 23);
    pvt->LonDeg    = GET_S32(p + 24) * B10_N7;
    pvt->LatDeg    = GET_S32(p + 28) * B10_N7;
    pvt->hgt       = GET_S32(p + 32) * B10_N3;
    pvt->hacc      = GET_U32(p + 40) * B10_N3; 
    pvt->vacc      = GET_U32(p + 44) * B10_N3; 
    pvt->vn        = GET_S32(p + 48) * B10_N3; // mm/s --> m/s   
    pvt->ve        = GET_S32(p + 52) * B10_N3;
    pvt->vd        = GET_S32(p + 56) * B10_N3;

    pvt->GroundSpeed        = GET_S32(p + 60) * B10_N3;
    pvt->HeadingMotionDeg   = GET_S32(p + 64) * B10_N5;
    pvt->sacc               = GET_U32(p + 68) * B10_N3; 
    pvt->cacc               = GET_U32(p + 72) * B10_N5;         
    pvt->pdop               = GET_U16(p + 76) * B10_N2;
    pvt->HeadingVehichleDeg = GET_S32(p + 84) * B10_N5;

    trace(TNOTE, "pvt, tick:%d, time: %04d-%02d-%02d %02d:%02d:%02d %03d, timevalid: 0x%02x, pos: %.8f, %.8f, %.2f, type: 0x%02x, numsv: %d, pdop, %.2f, vel: %6.2f, %6.2f, %6.2f, heading: %6.2f, %6.2f\r\n",
        pvt->tick, pvt->utc.year,pvt->utc.month,pvt->utc.day, 
        pvt->utc.hour, pvt->utc.min, pvt->utc.isec, pvt->utc.msec,pvt->TimeValid,
        pvt->LatDeg, pvt->LonDeg, pvt->hgt, pvt->FixType, pvt->SvNum, pvt->pdop, 
        pvt->ve, pvt->vn, pvt->vd, pvt->HeadingMotionDeg, pvt->HeadingVehichleDeg);    
}

/*
void decode_nav_sat(LogStruct *log)
{
    UbxNavSatStruct *sat = &g_UbxNavSatData;
    unsigned char *p = log->buf + 6 + 6;
    u8 i;

    sat->tick  = GET_U32(log->buf+2);
    sat->TowMs = GET_U32(p);
    sat->numsv = GET_U08(p + 5);

    for (i = 0; (i < sat->numsv) && (i < MAX_SVNUM_NAVSAT); i++)
    {
        sat->SatInfo[i].gnssid         = GET_U08(p +  8 + 12 * i);
        sat->SatInfo[i].svid           = GET_U08(p +  9 + 12 * i);
        sat->SatInfo[i].cn0            = GET_U08(p + 10 + 12 * i);
        sat->SatInfo[i].elevation      = GET_S08(p + 11 + 12 * i);
        sat->SatInfo[i].azimuth        = GET_S16(p + 12 + 12 * i);
        sat->SatInfo[i].PrangeResidual = GET_S16(p + 14 + 12 * i) * 0.1;
        sat->SatInfo[i].flags          = GET_U32(p + 16 + 12 * i);
    }

    trace(TNOTE, "sat: %d\r\n", sat->tick);
    for (i = 0; i < sat->numsv; i++)
    {
        if ((sat->SatInfo[i].flags>>3) & 1)
        {
            trace(TNOTE, "%d, %3d, %2d, %2d, %3d, %10.2f\r\n", 
            sat->SatInfo[i].gnssid, sat->SatInfo[i].svid, sat->SatInfo[i].cn0, 
            sat->SatInfo[i].elevation, sat->SatInfo[i].azimuth, sat->SatInfo[i].PrangeResidual);
        }
    }
}
*/

void LogDecodeFrame(LogStruct *log)
{
    u8 *p = log->buf;
    u8 type = p[1];

    switch (type)
    {
        case 1 : decode_imu(log);     break;
        case 2 : decode_nav_pvt(log); break;
        case 3 : decode_car(log);     break;
        default : break;
    }
}

void main(void)
{
  //char filename_input[200] = "log0902_0002.txt";
  char filename_input[200] = "vctest-COM5-115200-log20181109-14_11_57.dat";
  char filename_trace[200];  
  char buf[128];
  u8 FifoBuf[4096];
  FifoStruct LogFifo,  *fifo = &LogFifo;
  LogStruct LogData,   *log  = &LogData;
  SearchFrameStatusEnum state;
  FILE *fp = NULL;
  
  tracefile(filename_input, filename_trace);
  traceopen(filename_trace);
  tracelevel(TNOTE);
  fp = fopen(filename_input, "rb");
  assert(NULL != fp);

  FifoInit(fifo, FifoBuf, sizeof(FifoBuf));
  memset(log, 0, sizeof(LogStruct));

  trace(TNOTE, "hello world\r\n");
  
  while (!feof(fp))
  {
    fread(buf, 1, 1, fp);
    FifoWriteIn(fifo, buf, 1);
    while (FifoLength(fifo) >= MIN_LOG_MSG_LENGTH)
    {
      state = LogSearchFrame(fifo, log->buf, &log->len);
      if (FRAME_READY == state)
      {
        LogDecodeFrame(log);
      }
      else if (FRAME_HALF == state)
      {
        break;
      }
    }
  }
  
  trace(TNOTE, "goodbye world\r\n");
  
  traceclose();
  fclose(fp);
  
  printf("process over");
  //getchar();
  //getchar();
}

#endif
