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
	int vBbuId;                 /*BBU的编号*/
	int vBbuPoolId;             /*BBU Pool的Id*/
	double vX, vY, vZ;            /*地理坐标*/
	int vRruNum;                /*服务的RRU数量*/
	int vSchedualRruMode;       /*RRU资源调度的方式*/
	double vTransPower;         /*传输功率dbm形式*/
	double vEquipPower;			/*设备能耗*/
	int vIsActivity;				/*状态*/
	double vRes;					/*资源量*/
	int vLinkId;					/*链路Id*/
	double vOpTime;				//处理时延
	double vEfficiency;			//频谱效率
	double vResUtilizationRate;	//资源占比
	double vConsume;				//动态负载
public:
	//Bbu (){};/*Bbu构造函数*/
	//		vector<int> GetRruArraylist ();     /*获取和当前BBU关联的RRU对象数链表*/
	void SetBasicInfo();        /*初始化相应的对象的基本信息*/
	/*获取Bbu各项基本信息*/
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
	/*设置Bbu各项基本信息*/
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
	//bool AddRru(int vRruId);         /*向此BBU中关联的RRU列表中增加RRU对象*/
	//bool RemoveRru(int vRruId);          /*向此BBU中关联的RRU列表中删除指定ID的RRU*/
	//bool TransData2Rru(int vRruId ,string vMsg);      /*实现由BBU向RRU发送信息*/
	//bool ReciDataFromRru(int vRruId ,string vMsg);      /*实现BBU接收到的信息*/

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