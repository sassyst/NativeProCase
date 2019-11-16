#ifndef BbuPool_H
#define BbuPool_H

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class BbuPool
{
	private:
		int vBbuPoolId;
		double vX,vY,vZ;
		double vAllRes;				//总资源
		double vResLeft;			//剩余资源
		double vDynamicEnengy;		//动态能源
		double vStaticEnengy;		//静态能源
	public:
		int GetvBbuPoolIdInfo ();
		double GetvXInfo ();
		double GetvYInfo ();
		double GetvZInfo ();
		double GetvAllResInfo ();
		double GetvResLeftInfo ();
		double GetvDynamicEnengyInfo ();
		double GetvStaticEnengyInfo ();

		//vector<int> GetBbuArraylist ();     /*获取和当前BBU关联的RRU对象数链表*/ // xinjia
		bool SetvBbuPoolIdInfo (int BbuPoolId);
		bool SetvXInfo (double vX);
		bool SetvYInfo (double vY);
		bool SetvZInfo (double vZ);
		bool SetvAllResInfo (double AllRes);
		bool SetvResLeftInfo (double ResLeft);
		bool SetvDynamicEnengyInfo (double DynamicEnengy);
		bool SetvStaticEnengyInfo (double StaticEnengy);


		//bool AddBbu(int vBbuId);
		//bool RemoveBbu(int vBbuId);
};

int BbuPool::GetvBbuPoolIdInfo ()
{
	return vBbuPoolId; 
}
double BbuPool::GetvXInfo ()
{
	return vX;
}
double BbuPool::GetvYInfo ()
{
	return vY;
}
double BbuPool::GetvZInfo ()
{
	return vZ;
}
double BbuPool::GetvAllResInfo ()
{
	return vAllRes;
}
double BbuPool::GetvResLeftInfo ()
{
	return vResLeft;
}
double BbuPool::GetvDynamicEnengyInfo ()
{
	return vDynamicEnengy;
}
double BbuPool::GetvStaticEnengyInfo ()
{
	return vStaticEnengy;
}

bool BbuPool::SetvBbuPoolIdInfo(int BbuPoolId)
{
	vBbuPoolId = BbuPoolId;
	return 1;
}
bool BbuPool::SetvXInfo (double X)
{
	vX = X;
	return 1;
}
bool BbuPool::SetvYInfo (double Y)
{
	vY = Y;
	return 1;
}
bool BbuPool::SetvZInfo (double Z)
{
	vZ = Z;
	return 1;
}
bool BbuPool::SetvAllResInfo (double AllRes)
{
	vAllRes = AllRes;
	return 1;
}
bool BbuPool::SetvResLeftInfo (double ResLeft)
{
	vResLeft = ResLeft;
	return 1;
}
bool BbuPool::SetvDynamicEnengyInfo (double DynamicEnengy)
{
	vDynamicEnengy = DynamicEnengy;
	return 1;
}
bool BbuPool::SetvStaticEnengyInfo (double StaticEnengy)
{
	vStaticEnengy = StaticEnengy;
	return 1;
}



#endif