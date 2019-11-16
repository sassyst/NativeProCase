#ifndef Rru_H
#define Rru_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

class Rru
{
private:
	int vRruId;                  /*RRU�ı��*/
	int vServiceBbuId;           /*�����BBU��ID*/
	double vRadius;              /*���ǰ뾶*/
	double vX, vY, vZ;             /*��������*/
	int vRruTransPower;          /*RRU ���书��*/
	int vRruBandwidth;           /*RRU�Ĵ�����Դ*/
	int vUeNum;                  /*RRU���Ƿ�Χ�ڵ��û�����*/
	int vIsActivity;             /*��ʾRRU��״̬*/
	double vCarrierFrequent;     /*��Ƶ*/
	int vRruAntennaId;           /*����Id*/
	double vEquipPower;			 /*�豸�ܺ�*/
	double vBusiness;				 /*�ȶ�ҵ����*/
	double vOpTime;               //����ʱ��
	double vAverageRate;          //ƽ��������

public:

	//Rru (){};                    /*Rru���캯��*/
	//		vector<int> GetUeArraylist ();     /*��ȡ�͵�ǰBBU������RRU����������*/
	void SetBasicInfo();        /*��ʼ����Ӧ�Ķ���Ļ�����Ϣ*/
	/*��ȡRru���������Ϣ*/
	int GetvRruIdInfo();
	int GetvServiceBbuIdInfo();
	double GetvRadiusInfo();
	double GetvXInfo();
	double GetvYInfo();
	double GetvZInfo();
	int GetvRruTransPowerInfo();
	int GetvRruBandwidthInfo();
	int GetvUeNumInfo();
	int GetvIsActivityInfo();
	double GetvCarrierFrequentInfo();
	int GetvRruAntennaIdInfo();
	double GetvEquipPowerInfo();
	double GetvBusinessInfo();
	double GetvOpTimeInfo();
	double GetvAverageRateInfo();
	/*����Rru���������Ϣ*/
	bool SetvRruIdInfo(int Rruld);
	bool SetvServiceBbuIdInfo(int ServiceBbuId);
	bool SetvRadiusInfo(double Radius);
	bool SetvXInfo(double X);
	bool SetvYInfo(double Y);
	bool SetvZInfo(double Z);
	bool SetvUeNumInfo(int UeNum);
	bool SetvRruTransPowerInfo(int RruTransPower);
	bool SetvRruBandwidthInfo(int RruBandwidth);
	bool SetvIsActivityInfo(int IsActivity);
	bool SetvCarrierFrequentInfo(double CarrierFrequent);
	bool SetvRruAntennaIdInfo(int RruAntennaId);
	bool SetvEquipPowerInfo(double EquipPower);
	bool SetvBusinessInfo(double Business);
	bool SetvOptimeInfo(double Optime);
	bool SetvAverageRateInfo(double AverageRate);
	bool AddUe(int UeId);         /*���RRU�й�����UE�б��������û�*/
	bool RemoveUe(int UeId);          /*���RRU�й�����UE�б���ɾ���û�*/
	bool TransData2Bbu(int BbuId, string vMsg);      /*ʵ����RRU��BBU������Ϣ*/
	bool ReciDataFromBbu(int BbuId, string vMsg);      /*ʵ��RRU���յ�����Ϣ*/
	bool TransData2Ue(int UeId, string vMsg);         /*ʵ����RRU��Ue������Ϣ*/
	bool ReciDataFromUe(int UeId, string vMsg);       /*ʵ��RRU���յ�����Ϣ*/

};


int Rru::GetvRruIdInfo()
{
	return vRruId;
}
int Rru::GetvServiceBbuIdInfo()
{
	return vServiceBbuId;
}
double Rru::GetvRadiusInfo()
{
	return vRadius;
}
double Rru::GetvXInfo()
{
	return vX;
}
double Rru::GetvYInfo()
{
	return vY;
}
double Rru::GetvZInfo()
{
	return vZ;
}
int Rru::GetvRruTransPowerInfo()
{
	return vRruTransPower;
}
int Rru::GetvRruBandwidthInfo()
{
	return vRruBandwidth;
}
int Rru::GetvUeNumInfo()
{
	return vUeNum;
}
int Rru::GetvIsActivityInfo()
{
	return vIsActivity;
}
double Rru::GetvCarrierFrequentInfo()
{
	return vCarrierFrequent;
}
int Rru::GetvRruAntennaIdInfo()
{
	return vRruAntennaId;
}
double Rru::GetvEquipPowerInfo()
{
	return vEquipPower;
}
double Rru::GetvBusinessInfo()
{
	return vBusiness;
}
double Rru::GetvOpTimeInfo()
{
	return vOpTime;
}
double Rru::GetvAverageRateInfo()
{
	return vAverageRate;
}

bool Rru::SetvRruIdInfo(int RruId)
{
	vRruId = RruId;
	return 1;
}
bool Rru::SetvServiceBbuIdInfo(int ServiceBbuId)
{
	vServiceBbuId = ServiceBbuId;
	return 1;
}
bool Rru::SetvRadiusInfo(double Radius)
{
	vRadius = Radius;
	return 1;
}
bool Rru::SetvXInfo(double X)
{
	vX = X;
	return 1;
}
bool Rru::SetvYInfo(double Y)
{
	vY = Y;
	return 1;
}
bool Rru::SetvZInfo(double Z)
{
	vZ = Z;
	return 1;
}
bool Rru::SetvUeNumInfo(int UeNum)
{
	vUeNum = UeNum;
	return 1;
}
bool Rru::SetvRruTransPowerInfo(int RruTransPower)
{
	vRruTransPower = RruTransPower;
	return 1;
}
bool Rru::SetvRruBandwidthInfo(int RruBandwidth)
{
	vRruBandwidth = RruBandwidth;
	return 1;
}
bool Rru::SetvIsActivityInfo(int IsActivity)
{
	vIsActivity = IsActivity;
	return 1;
}
bool Rru::SetvCarrierFrequentInfo(double CarrierFrequent)
{
	vCarrierFrequent = CarrierFrequent;
	return 1;
}
bool Rru::SetvRruAntennaIdInfo(int RruAntennaId)
{
	vRruAntennaId = RruAntennaId;
	return 1;
}
bool Rru::SetvEquipPowerInfo(double EquipPower)
{
	vEquipPower = EquipPower;
	return 1;
}
bool Rru::SetvBusinessInfo(double Business)
{
	vBusiness = Business;
	return 1;
}
bool Rru::SetvOptimeInfo(double Optime)
{
	vOpTime = Optime;
	return 1;
}
bool Rru::SetvAverageRateInfo(double AverageRate)
{
	vAverageRate = AverageRate;
	return 1;
}
#endif