#include "main.h"

/*-------------------------------------
* �������������ò��η�����
* ����  �����η�����
* ����  ��dddd
* ���  ��dddd
���ߣ�LPGUAIA
���ڣ�2021.7.7
-----------------------------------------*/
wave_HandleTypeDef sinwave={0x01,\
														1000,\
														5,\
														90};

float wavegenerator (wave_HandleTypeDef *SinWave)
{
	uint16_t samplenum = SinWave->waveperiod/SinWave->taskperiod;
	static uint16_t count;
	float output;
	
	if(count<samplenum)
		count++;
	else
		count=0;
	
	switch(SinWave->wavetpye)
	{
		case asinwave:
			output=SinWave->amplitude*sin(2*PI*count/samplenum);break;
		case atriwave:
			output=SinWave->amplitude*count/samplenum;break;
		case stepwave:
			output=SinWave->amplitude*((int)((2*count-1)/samplenum));break;
		default:
			output=SinWave->amplitude*sin(2*PI*count/samplenum);break;
	}
	
	return output;
}



/*-------------------------------------
* �����������ٵ���ǶȽ���
* ����  ��������ٺ�ĽǶ�
* ����  ������ṹ��
* ���  ����

���ߣ�LPGUAIA
���ڣ�2021.4.27
-----------------------------------------*/ 

void gearmotor_angledecoder(MotorInfo *Motor)
{
	
	Motor->tempdata.anglechanged=Motor->tempdata.temp_angle[1] - Motor->tempdata.temp_angle[0];
	Motor->tempdata.temp_angle[0]=Motor->tempdata.temp_angle[1];
	
	
	if(ABS(Motor->tempdata.anglechanged)<=300)
		Motor->tempdata.anglechanged=Motor->tempdata.anglechanged/Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged>300)
		Motor->tempdata.anglechanged = (Motor->tempdata.anglechanged-360) / Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged<-300)
		Motor->tempdata.anglechanged = (360 + Motor->tempdata.anglechanged) / Motor->parameter.reductiongearratio;
	
	
	if(ABS(Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle)<180)
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle;
	else if(Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle<=-180)
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle + 360;
	else if(Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle>=180)
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle - 360;
}
/*-------------------------------------
* �����������ٵ���ǶȽ���
* ����  ��������ٺ���ۼƽǶ�
* ����  ������ṹ��
* ���  ����

���ߣ�LPGUAIA
���ڣ�2021.4.27
-----------------------------------------*/ 
void gearmotor_angledecoder_sum(MotorInfo *Motor)
{
	
	Motor->tempdata.anglechanged=Motor->tempdata.temp_angle[1] - Motor->tempdata.temp_angle[0];
	Motor->tempdata.temp_angle[0]=Motor->tempdata.temp_angle[1];
	
	
	if(ABS(Motor->tempdata.anglechanged)<=300)
		Motor->tempdata.anglechanged=Motor->tempdata.anglechanged/Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged>300)
		Motor->tempdata.anglechanged = (Motor->tempdata.anglechanged-360) / Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged<-300)
		Motor->tempdata.anglechanged = (360 + Motor->tempdata.anglechanged) / Motor->parameter.reductiongearratio;
	
		Motor->curmotorctrlinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorctrlinfo.angle;

}

/*-------------------------------------
* ������������б�¼�������
* ����  �������Կ������Ӻ���������ֵֹĶ�������������η�ֹ�򻬵�
* ����  �����ݽṹ��
* ���  ����

���ߣ�LPGUAIA
���ڣ�2021.4.27
-----------------------------------------*/ 
void k_shaper(kshaper_handle *kdata)
{
	if(ABS((kdata->data-kdata->lastdata)/kdata->sampleperi)<=kdata->k)
	{
		kdata->outdata=kdata->data;
		kdata->lastdata=kdata->data;
	}
	else if ((kdata->data-kdata->lastdata)/kdata->sampleperi<-kdata->k)
	{
		kdata->outdata=kdata->lastdata-kdata->k*kdata->sampleperi;
		kdata->lastdata=kdata->outdata;
	}
	else if ((kdata->data-kdata->lastdata)/kdata->sampleperi>kdata->k)
	{
		kdata->outdata=kdata->lastdata+kdata->k*kdata->sampleperi;
		kdata->lastdata=kdata->data;
	}
	
}

float anglecircle(float angle)
{
	if(angle>180.f)
		angle=angle-360.f;
	else if(angle<-180.f)
		angle=angle+360.f;

	return angle;
}

float anglelimit(float angle,float anglemax,float anglemin)
{
	if(angle>anglemax)
		angle=anglemax;
	else if(angle<anglemin)
		angle=anglemin;

	return angle;
}
