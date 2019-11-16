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
	int vRruId;                  /*RRU的编号*/
	int vServiceBbuId;           /*服务的BBU的ID*/
	double vRadius;              /*覆盖半径*/
	double vX, vY, vZ;             /*地理坐标*/
	int vRruTransPower;          /*RRU 发射功率*/
	int vRruBandwidth;           /*RRU的带宽资源*/
	int vUeNum;                  /*RRU覆盖范围内的用户数量*/
	int vIsActivity;             /*表示RRU的状态*/
	double vCarrierFrequent;     /*载频*/
	int vRruAntennaId;           /*天线Id*/
	double vEquipPower;			 /*设备能耗*/
	double vBusiness;				 /*既定业务量*/
	double vOpTime;               //处理时延
	double vAverageRate;          //平均吞吐量

public:

	//Rru (){};                    /*Rru构造函数*/
	//		vector<int> GetUeArraylist ();     /*获取和当前BBU关联的RRU对象数链表*/
	void SetBasicInfo();        /*初始化相应的对象的基本信息*/
	/*获取Rru各项基本信息*/
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
	/*设置Rru各项基本信息*/
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
	bool AddUe(int UeId);         /*向此RRU中关联的UE列表中增加用户*/
	bool RemoveUe(int UeId);          /*向此RRU中关联的UE列表中删除用户*/
	bool TransData2Bbu(int BbuId, string vMsg);      /*实现由RRU向BBU发送信息*/
	bool ReciDataFromBbu(int BbuId, string vMsg);      /*实现RRU接收到的信息*/
	bool TransData2Ue(int UeId, string vMsg);         /*实现由RRU向Ue发送信息*/
	bool ReciDataFromUe(int UeId, string vMsg);       /*实现RRU接收到的信息*/

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