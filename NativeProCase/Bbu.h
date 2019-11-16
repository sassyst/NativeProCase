#ifndef Bbu_H
#define Bbu_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;


class Bbu
{
private:
	int vBbuId;                 /*BBU�ı��*/
	int vBbuPoolId;             /*BBU Pool��Id*/
	double vX, vY, vZ;            /*��������*/
	int vRruNum;                /*�����RRU����*/
	int vSchedualRruMode;       /*RRU��Դ���ȵķ�ʽ*/
	double vTransPower;         /*���书��dbm��ʽ*/
	double vEquipPower;			/*�豸�ܺ�*/
	int vIsActivity;				/*״̬*/
	double vRes;					/*��Դ��*/
	int vLinkId;					/*��·Id*/
	double vOpTime;				//����ʱ��
	double vEfficiency;			//Ƶ��Ч��
	double vResUtilizationRate;	//��Դռ��
	double vConsume;				//��̬����
public:
	//Bbu (){};/*Bbu���캯��*/
	//		vector<int> GetRruArraylist ();     /*��ȡ�͵�ǰBBU������RRU����������*/
	void SetBasicInfo();        /*��ʼ����Ӧ�Ķ���Ļ�����Ϣ*/
	/*��ȡBbu���������Ϣ*/
	int GetvBbuIdInfo();      //xuyaogenggai
	int GetvBbuPoolIdInfo();
	double GetvXInfo();
	double GetvYInfo();
	double GetvZInfo();
	int GetvRruNumInfo();
	int GetvSchedualRruModeInfo();
	double GetvTransPowerInfo();
	double GetvEquipPowerInfo();
	int GetvIsActivityInfo();
	double GetvResInfo();
	int GetvLinkIdInfo();
	double GetvOpTimeInfo();
	double GetvEfficiencyInfo();
	double GetvResUtilizationRateInfo();
	double GetvConsumeInfo();
	/*����Bbu���������Ϣ*/
	bool SetvBbuIdInfo(int Bbuld);
	bool SetvBbuPoolIdInfo(int BbuPoolId);
	bool SetvXInfo(double X);
	bool SetvYInfo(double Y);
	bool SetvZInfo(double Z);
	bool SetvRruNumInfo(int RruNum);
	bool SetvSchedualRruModeInfo(int SchedualRruMode);
	bool SetvTransPowerInfo(double TransPower);
	bool SetvEquipPowerInfo(double EquipPower);
	bool SetvIsActivityInfo(int IsActivity);
	bool SetvResInfo(double Res);
	bool SetvLinkIdInfo(int LinkId);
	bool SetvOptimeInfo(double Optime);
	bool SetvEfficiencyInfo(double Efficiency);
	bool SetvResUtilizationRateInfo(double ResUtilizationRate);
	bool SetvConsumeInfo(double Consume);
	//bool AddRru(int vRruId);         /*���BBU�й�����RRU�б�������RRU����*/
	//bool RemoveRru(int vRruId);          /*���BBU�й�����RRU�б���ɾ��ָ��ID��RRU*/
	//bool TransData2Rru(int vRruId ,string vMsg);      /*ʵ����BBU��RRU������Ϣ*/
	//bool ReciDataFromRru(int vRruId ,string vMsg);      /*ʵ��BBU���յ�����Ϣ*/

};

int Bbu::GetvLinkIdInfo()
{
	return vLinkId;
}
int Bbu::GetvBbuIdInfo()
{
	return vBbuId;
}
int Bbu::GetvBbuPoolIdInfo()
{
	return vBbuPoolId;
}
double Bbu::GetvXInfo()
{
	return vX;
}
double Bbu::GetvYInfo()
{
	return vY;
}
double Bbu::GetvZInfo()
{
	return vZ;
}
int Bbu::GetvRruNumInfo()
{
	return vRruNum;
}
int Bbu::GetvSchedualRruModeInfo()
{
	return vSchedualRruMode;
}
double Bbu::GetvTransPowerInfo()
{
	return vTransPower;
}
double Bbu::GetvEquipPowerInfo()
{
	return vEquipPower;
}
int Bbu::GetvIsActivityInfo()
{
	return vIsActivity;
}
double Bbu::GetvResInfo()
{
	return vRes;
}
double Bbu::GetvOpTimeInfo()
{
	return vOpTime;
}
double Bbu::GetvEfficiencyInfo()
{
	return vEfficiency;
}
double Bbu::GetvResUtilizationRateInfo()
{
	return vResUtilizationRate;
}
double Bbu::GetvConsumeInfo()
{
	return vConsume;
}
bool Bbu::SetvLinkIdInfo(int LinkId)
{
	vLinkId = LinkId;
	return 1;
}
bool Bbu::SetvBbuIdInfo(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool Bbu::SetvBbuPoolIdInfo(int BbuPoolId)
{
	vBbuPoolId = BbuPoolId;
	return 1;
}
bool Bbu::SetvXInfo(double X)
{
	vX = X;
	return 1;
}
bool Bbu::SetvYInfo(double Y)
{
	vY = Y;
	return 1;
}
bool Bbu::SetvZInfo(double Z)
{
	vZ = Z;
	return 1;
}
bool Bbu::SetvRruNumInfo(int RruNum)
{
	vRruNum = RruNum;
	return 1;
}
bool Bbu::SetvSchedualRruModeInfo(int SchedualRruMode)
{
	vSchedualRruMode = SchedualRruMode;
	return 1;
}
bool Bbu::SetvTransPowerInfo(double TransPower)
{
	vTransPower = TransPower;
	return 1;
}
bool Bbu::SetvEquipPowerInfo(double EquipPower)
{
	vEquipPower = EquipPower;
	return 1;
}
bool Bbu::SetvIsActivityInfo(int IsActivity)
{
	vIsActivity = IsActivity;
	return 1;
}
bool Bbu::SetvResInfo(double Res)
{
	vRes = Res;
	return 1;
}
bool Bbu::SetvOptimeInfo(double Optime)
{
	vOpTime = Optime;
	return 1;
}
bool Bbu::SetvEfficiencyInfo(double Efficiency)
{
	vEfficiency = Efficiency;
	return 1;
}
bool Bbu::SetvResUtilizationRateInfo(double ResUtilizationRate)
{
	vResUtilizationRate = ResUtilizationRate;
	return 1;
}
bool Bbu::SetvConsumeInfo(double Consume)
{
	vConsume = Consume;
	return 1;
}
#endif