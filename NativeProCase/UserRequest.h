#ifndef UserRequest_H
#define UserRequest_H

#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;



class UserRequest
{
private:

	long int vTransSpeed;         /*用户需求传输速率*/
	double vSpeed;
	double vServiceType;           /*业务类型，0默认为非实时业务,1为实时业务模型*/
	double vTurboCodeRate;      /*信源码率（Turbo码为主）*/
	int vModulationRate;        /*QPSK=2, 16QAM=4,64QAM=6*/
	double vSinr;		        /*用户的信息*/
	double vTotalBit;	    	/*用户被传输的所有bit数，用户要求的速率，单位是兆bit每秒*/
	int vTTISent;		 	    /*发送的TTI起始时刻,每个时刻有多个TTI，TTI的标识符不是唯一的，每个时刻要重复*/
	double vAverageRate;		/*用户之前N个时刻的数据速率的平均值，单位是兆bit每秒*/               //怎么更新？？？？？？？？？？？？？？？
	long int Priority;               /*用户的优先级*/
	long int Priority2;               /*用户的优先级*/
	int vTime;                  /*定义时刻，用于唯一确定TTI*/
	int vBbuId;					/*所属BBuId*/
	int vTotalRb;                /*定义已分配的Rb数量*/
	double vDis;

	//map<int, int> vTTIRb;


public:
	int vRbcurrent;               //新增分配的rb数量
	int vUserId;                /*用户Id*/
	UserRequest()
	{
		vTotalBit = 0;
		vServiceType = 0;
		vAverageRate = 1;
		vRbcurrent = 0;
	};
	UserRequest(int UserId, long TransSpeed, int ServiceType, int Sinr, double TotalBit,int TTISent,double AverageRate,int BbuId,int totalRb,double Dis,int vPriority)
	{
		Priority = vPriority;
		vUserId = UserId;
		vTransSpeed = TransSpeed;
		vServiceType = ServiceType;
		vSinr = Sinr;
		vTotalBit = TotalBit;
		vTTISent = TTISent;
		vAverageRate = AverageRate;
		vBbuId = BbuId;
		vTotalRb = totalRb;
		vDis = Dis;
		vSpeed = 0;
	};
	void RefreshInfo(int TTISent);
	bool UpdateAverateRate(double vRatio, long vPresentRate);
	int getvUserId();
	double getvTransSpeed();
	double getvSpeed();
	int getvServiceType();
	double getvTurboCodeRate();
	int getvModulationRate();
	double getvSinr();
	double getvTotalBit();
	int getvTTISent();
	double getvAverageRate();
	int GetvBbuIdInfo();
	long int getPriority();             //新加的  轮询优先级
	long int getPriority2();             //新加的  轮询优先级2(用来输出Priority)
	double getvDis();
	/*设置UserRequest各项基本信息*/
	bool setvUserId(int UserId);
	bool setvTransSpeed(double TransSpeed);
	bool setvSpeed(double Speed);
	bool setvServiceType(int ServiceType);
	bool setvTurboCodeRate(double TurboCodeRate);
	bool setvModulationRate(int ModulationRate);
	bool setvSinr(double Sinr);
	bool setvTotalBit(double TotalBit);
	bool setvTTISent(int TTISent);
	bool setvAverageRate(double AverageRate);
	bool SetvBbuIdInfo(int BbuId);
	bool setPriority(long int priority);
	bool setPriority2(long int priority2);
	int getvTotalRb();             //新加的  分配Rb数量
	bool setvTotalRb(int TotalRb);
	void show();
	void show2();
	bool setvDis(double vDis);

};

double UserRequest::getvDis()
{
	return vDis;
}
void UserRequest::RefreshInfo(int TTISent)
{
	vTTISent = TTISent;
}
bool UserRequest::UpdateAverateRate(double vRatio, long vPresentRate)
{
	vAverageRate = (1 - vRatio)*vAverageRate + vRatio*vPresentRate;
	return 1;
}

int  UserRequest::getvUserId()
{
	return vUserId;
}
double  UserRequest::getvTransSpeed()
{
	return vTransSpeed;
}
double  UserRequest::getvSpeed()
{
	return vSpeed;
}
int  UserRequest::getvServiceType()
{
	return vServiceType;
}
double  UserRequest::getvTurboCodeRate()
{
	return vTurboCodeRate;
}
int  UserRequest::getvModulationRate()
{
	return vModulationRate;
}
double  UserRequest::getvSinr()
{
	return vSinr;
}
double  UserRequest::getvTotalBit()
{
	return vTotalBit;
}
int  UserRequest::getvTTISent()
{
	return vTTISent;
}
double  UserRequest::getvAverageRate()
{
	return vAverageRate;
}
int  UserRequest::GetvBbuIdInfo()
{
	return vBbuId;
}

bool  UserRequest::SetvBbuIdInfo(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool  UserRequest::setvUserId(int UserId)
{
	vUserId = UserId;
	return 1;
}
bool  UserRequest::setvTransSpeed(double TransSpeed)
{
	vTransSpeed = TransSpeed;
	return 1;
}
bool  UserRequest::setvSpeed(double Speed)
{
	vSpeed = Speed;
	return 1;
}
bool  UserRequest::setvServiceType(int ServiceType)
{
	vServiceType = ServiceType;
	return 1;
}
bool  UserRequest::setvTurboCodeRate(double TurboCodeRate)
{
	vTurboCodeRate = TurboCodeRate;
	return 1;
}
bool  UserRequest::setvModulationRate(int ModulationRate)
{
	vModulationRate = ModulationRate;
	return 1;
}
bool  UserRequest::setvSinr(double Sinr)
{
	vSinr = Sinr;
	return 1;
}
bool  UserRequest::setvTotalBit(double TotalBit)
{
	vTotalBit = TotalBit;
	return 1;
}
bool  UserRequest::setvTTISent(int TTISent)
{
	vTTISent = TTISent;
	return 1;
}
bool  UserRequest::setvAverageRate(double AverageRate)
{
	vAverageRate = AverageRate;
	return 1;
}

long int UserRequest::getPriority2()
{
	return Priority2;
}
long int UserRequest::getPriority()
{
	return Priority;
}
bool UserRequest::setPriority(long int priority)
{
	Priority = priority;
	return 1;
}
bool UserRequest::setPriority2(long int priority)
{
	Priority2 = priority;
	return 1;
}
int UserRequest::getvTotalRb()
{
	return vTotalRb;
}
bool UserRequest::setvTotalRb(int TotalRb)
{
	vTotalRb = TotalRb;
	return 1;
}
bool  UserRequest::setvDis(double Dis)
{
	vDis = Dis;
	return 1;
}
void UserRequest::show()
{
	ofstream SaveFile("output.txt",ios::app);
	SaveFile << "用户的UserId：" << this->getvUserId() << endl;
	SaveFile << "用户的优先级：" << this->getPriority() << endl;
	SaveFile << "用户的请求速率：" << this->getvTransSpeed() << endl;
	SaveFile << "用户的前N时刻平均吞吐量：" << this->getvAverageRate() << endl;
	SaveFile << "用户已发送的总bit数:" << this->getvTotalBit() << endl;
	SaveFile << "已给用户分配的总Rb数：" << this->getvTotalRb() << endl;
	cout << "用户的UserId：" << this->getvUserId() << endl;
	cout << "用户的优先级：" << this->getPriority() << endl;
	cout << "用户的PF优先级：" << this->getPriority2() << endl;
	cout << "用户的请求速率：" << this->getvTransSpeed()<<" M/s"<< endl;
	cout << "用户的前N时刻平均吞吐量：" << this->getvAverageRate()<<"M/s"<< endl;
	cout << "用户已发送的总bit数:" << this->getvTotalBit() <<" MB"<< endl;
	cout << "已给用户分配的总Rb数：" << this->getvTotalRb() <<" 个"<<endl;
	SaveFile.close();
}
void UserRequest::show2()
{
	ofstream SaveFile("output.txt", ios::app);
	SaveFile << this->getvUserId();
	SaveFile << "   " << this->getvDis();
	SaveFile << "    " << this->getvAverageRate() ;
	SaveFile << "      " << this->getvTotalBit() ;
	SaveFile << "      " << this->getvTransSpeed() ;
	SaveFile << "      " << this->getPriority() << endl;
	/*cout << this->getvUserId();
	cout << "   " << this->getvDis();
	cout << "    " << this->getvAverageRate();
	cout << "      " << this->getvTotalBit();
	cout << "      " << this->getvTransSpeed();
	cout << "      " << this->getPriority() << endl;*/
}


#endif