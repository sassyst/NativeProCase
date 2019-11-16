#ifndef Ue_H
#define Ue_H

#include <iostream>
#include <string>

using namespace std;

class Ue
{
	private:
		int vUeId;					/*�û�Id*/
		int vUeType;				/*��ʾ���ڻ�������*/
		double vX,vY,vZ;			/*�û��ľ���λ��*/
		int vServiceRruId;			/*����RRu�ı��*/
		int vRbNum;					/*�����RB��Ŀ*/
		int vUeTransPower;			/*���书��*/
		int vUeAntennaId;			/*�û��ķ�������*/
		int vIsActivity;			/*��ʾ�û��Ƿ��ڻ�Ծ״̬*/
		int vUeGroupId;				/*Ue��*/
		int vModelType;				/*�û�ѡ���ģ��*/
		int vUeDistrict;			/*��������*/
		double vSNR;				/*SNR*/
		double vTotalBit;	    	/*�û������������bit�����û�Ҫ�������*/
		int vTTISent;		 	    /*���͵�TTI��ʼʱ��*/
		double vAverageRate;		/*�û�֮ǰN��ʱ�̵��������ʵ�ƽ��ֵ*/
		int vBbuId;					/*����BBuId*/
		int vTotalRb;                /*�����ѷ����Rb����*/
		int vPriority;				
		double vDis;				/*���վ����*/
		double vRate;				//��ʱ����
		int vWorkType;				//���ּȶ�ҵ�����ͷǼȶ�ҵ����
	public:
		//Ue ();
		void SetBasicInfo ();
		/*��ȡUe���������Ϣ*/
		int GetvUeIdInfo ();
		int GetvUeTypeInfo ();
		double GetvXInfo ();
		double GetvYInfo ();
		double GetvZInfo ();
		int GetvServiceRruIdInfo ();
		int GetvRbNumInfo ();
		int GetvUeTransPowerInfo ();
		int GetvUeAntennaIdInfo ();
		int GetvIsActivityInfo ();
		int GetvUeGroupIdInfo ();
		int GetvModelTypeInfo();
		double GetvSNRInfo();
		int GetvBbuIdInfo();
		double getvTotalBit();
		int getvTTISent();
		double getvAverageRate();
		double getvRate();
		double getvDis();
		int getvPriority();
		int getvWorkType();
		/*����Ue���������Ϣ*/
		bool SetvUeIdInfo (int UeId);
		bool SetvUeTypeInfo (int UeType);
		bool SetvXInfo (double X);
		bool SetvYInfo (double Y);
		bool SetvZInfo (double Z);
		bool SetvServiceRruIdInfo (int ServiceRruId);
		bool SetvRbNumInfo (int RbNum);
		bool SetvUeTransPowerInfo (int UeTransPower);
		bool SetvUeAntennaIdInfo (int UeAntennaId);
		bool SetvIsActivityInfo (int IsActivity);
		bool SetvUeGroupIdInfo (int UeGroupId);
		bool SetvModelTypeInfo(int vModelType);
		bool SetvSNRInfo(double SNR);
		void UpdateLocation(double X,double Y ,double Z);/*�����û��ĵ���λ��*/
		bool SetvBbuIdInfo(int BbuId);
		bool setvTotalBit(double TotalBit);
		bool setvTTISent(int TTISent);
		bool setvAverageRate(double AverageRate);
		bool setvRate(double Rate);
		int  getvTotalRb();             //�¼ӵ�  ����Rb����
		bool setvTotalRb(int TotalRb);
		bool setvDis(double vDis);
		bool setvPriority(int Priority);
		bool setvWorkType(int Worktype);
};
int Ue::getvWorkType()
{
	return vWorkType;
}
double Ue::GetvSNRInfo()
{
	return vSNR;
}
int Ue::getvPriority()
{
	return vPriority;
}
double Ue::getvDis()
{
	return vDis;
}

int Ue::GetvModelTypeInfo()
{
	return vModelType;
}
int Ue::GetvUeIdInfo ()
{
	return vUeId;
}
int Ue::GetvUeTypeInfo ()
{
	return vUeType;
}
int Ue::GetvServiceRruIdInfo ()
{
	return vServiceRruId;
}
int Ue::GetvBbuIdInfo()
{
	return vBbuId;
}
double Ue::GetvXInfo ()
{
	return vX;
}
double Ue::GetvYInfo ()
{
	return vY;
}
double Ue::GetvZInfo ()
{
	return vZ;
}
int Ue::GetvRbNumInfo ()
{
	return vRbNum;
}
int Ue::GetvUeTransPowerInfo ()
{
	return vUeTransPower;
}
int Ue::GetvUeAntennaIdInfo ()
{
	return vUeAntennaId;
}
int Ue::GetvIsActivityInfo ()
{
	return vIsActivity;
}
int Ue::GetvUeGroupIdInfo ()
{
	return vUeGroupId;
}
double  Ue::getvTotalBit()
{
	return vTotalBit;
}
int  Ue::getvTTISent()
{
	return vTTISent;
}
double  Ue::getvAverageRate()
{
	return vAverageRate;
}
double  Ue::getvRate()
{
	return vRate;
}
bool  Ue::setvTotalBit(double TotalBit)
{
	vTotalBit = TotalBit;
	return 1;
}
bool  Ue::setvTTISent(int TTISent)
{
	vTTISent = TTISent;
	return 1;
}
bool  Ue::setvDis(double Dis)
{
	vDis = Dis;
	return 1;
}
bool  Ue::setvAverageRate(double AverageRate)
{
	vAverageRate = AverageRate;
	return 1;
}
bool  Ue::setvRate(double Rate)
{
	vRate = Rate;
	return 1;
}
bool Ue::SetvSNRInfo(double SNR)
{
	vSNR = SNR;
	return 1;
}
bool Ue::SetvUeIdInfo (int UeId)
{
	vUeId = UeId;
	return 1;
}
bool Ue::SetvBbuIdInfo(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool Ue::SetvUeTypeInfo (int UeType)
{
	vUeType = UeType;
	return 1;
}
bool Ue::SetvServiceRruIdInfo (int ServiceRruId)
{
	vServiceRruId = ServiceRruId;
	return 1;
}
bool Ue::SetvXInfo (double X)
{
	vX = X;
	return 1;
}
bool Ue::SetvYInfo (double Y)
{
	vY = Y;
	return 1;
}
bool Ue::SetvZInfo (double Z)
{
	vZ = Z;
	return 1;
}
bool Ue::SetvRbNumInfo (int RbNum)
{
	vRbNum = RbNum;
	return 1;
}
bool Ue::SetvUeTransPowerInfo (int UeTransPower)
{
	vUeTransPower = UeTransPower;
	return 1;
}
bool Ue::SetvUeAntennaIdInfo (int UeAntennaId)
{
	vUeAntennaId = UeAntennaId;
	return 1;
}
bool Ue::SetvIsActivityInfo (int IsActivity)
{
	vIsActivity = IsActivity;
	return 1;
}
bool Ue::SetvUeGroupIdInfo (int UeGroupId)
{
	vUeGroupId = UeGroupId;
	return 1;
}
bool Ue::SetvModelTypeInfo(int ModelType)
{
	vModelType = ModelType;
	return 1;
}
int Ue::getvTotalRb()
{
	return vTotalRb;
}
bool Ue::setvTotalRb(int TotalRb)
{
	vTotalRb = TotalRb;
	return 1;
}
bool Ue::setvPriority(int Priority)
{
	vPriority = Priority;
	return 1;
}
bool Ue::setvWorkType(int WorkType)
{
	vWorkType = WorkType;
	return 1;
}

#endif