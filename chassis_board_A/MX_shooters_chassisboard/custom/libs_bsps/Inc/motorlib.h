#ifndef ctrltask_H
#define ctrltask_H

#include "pid.h"
#include "stm32f4xx.h"

#define PIDoutercyclerate 2

#define asinwave 0x01
#define atriwave 0x02
#define stepwave 0x03

#define speedupcps 0

float kictrl(PID_regulator *pid,float effctarea);



typedef struct _Motor_Info
{
	struct
	{
		
		float angle_limit[2];//�Ƕ����ƣ���������Ϊ{-180��180}��������ʹ�õ�λ��
		float speed_limit[2];//�ٶ����ƣ���ѯ��������װ�ֲᣬ������ʹ�õ�λrpm
		float current_limit[2];//�������ƣ���ѯ��������װ�ֲᣬ������ʹ�õ�λA
		float reductiongearratio;//����������ڻ������ɵļ��ٱ��ʣ�����ʱ�����ڴ�ֵӦ����һ
		float inpositioncurrent;//ײ��λ�ĵ���ֵ��ʹ�õ�λA
		float installationangle;//��װ�Ƕȣ����������ʱ�ĽǶȣ��������ʽ��������3508/2006���;���ֵ��������6020���в�ͬ��ʹ�÷���
		int16_t pidoutcycrate;
	}parameter;
	
	struct
	{
		float angle;
		float speed;
		float currentsum;
		float pidcount;
		float anglechanged;
		float temp_angle[2];

	}tempdata;//���ڽ���Ƕȵ���ʱ����
	
	struct
	{
		float angle;
		float speed;
		float current;//2006ֱ�ӷ���ת�س�ϵ��Ϊһ��3508����ת�ص���
	}tarmotorinfo;//��¼���Ŀ�����
	
	struct
	{
		float angle;
		float speed;
		float current[5];
	}curmotorinfo;//��¼���Ŀ��Ƕ�
	
}MotorInfo;

typedef struct _wave_HandleTypeDef
{
	uint8_t wavetpye;
	float waveperiod;
	float taskperiod;
	float amplitude;
}wave_HandleTypeDef;

typedef struct
{
	float data;   									//��������
	float lastdata;   									//��¼�ϴ�����
	float k;								//����k��/ms��
	float sampleperi;//ms
	float outdata;
}kshaper_handle;

void gearmotor_angledecoder(MotorInfo *Motor);
void gearmotor_angledecoder_sum(MotorInfo *Motor);
void motaspid_calc(MotorInfo *minfo,PID_regulator *anglepid,PID_regulator *speedpid);
void canrxtomotinfo(MotorInfo *minfo,uint8_t rx[8]);
void motcurrentsensor(MotorInfo *minfo);
void k_shaper(kshaper_handle *kdata);
float anglecircle(float angle);
float anglelimit(float angle,float anglemax,float anglemin);

#define Defaul_3508_Parameter \
{\
		{-180.f,180.f},\
		{-450.f,450.f},\
		{-10.f,10.f},\
		0,\
		19.2,\
		0,\
		0,\
}\



#define Defaul_TempData \
{\
		0,\
		0,\
		0,\
		0,\
		0,\
		{0,0},\
		0,\
}\

#define Defaul_TarMotorCtrlInfo \
{\
		0,\
		0,\
		0,\
}\

#define Defaul_CurMotorCtrlInfo \
{\
		0,\
		0,\
		0,\
}\

#define Default_2006_Config \
{\
	Defaul_2006_Parameter,\
	Defaul_TempData,\
	Defaul_TarMotorCtrlInfo,\
	Defaul_CurMotorCtrlInfo,\
}\

#endif
