#ifndef PFSchedual_H
#define PFSchedual_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "UserRequest.h"
#include "SchedualOut.h"
#include<map>
#include<math.h>
using namespace std;


class PFSchedual 
{
private:
	 int vRealFactor; /*实时业务的影响因子*/
	 int vDataFactor; /*数据业务的影响因子*/
	double vWindow;  /*时间窗因子τ*/
	int vRbNum;                                /*调度的总RB数目*/
	int vRbLeft;                               /*剩余RB数目*/
	//SchedualOut vSchedualResult;		       /*返回用户的输入结果*/
	int vBbuId;		 	                       /*基站的Id*/
	int vTti;		                           /*表示当前的TTI标志*/



public:
	PFSchedual()
	{
		vRealFactor = 100;
		vDataFactor = 1;
		vWindow = 0.1; 
	};
	bool Addrequest(UserRequest temp);          /*将用户请求增加到队列中*/
	double Schedual(vector<UserRequest> &temp, int length, int type, vector<Ue> &vUeList);   /*调度函数，按照顺序进行调度*/
	double GetPriprotyFactor(UserRequest input); /*计算用户的优先级因子*/
	void Update(int vTTI);                   /*根据刷新TTI并更新剩余的资源,并更新用户的平均速率*/             //未实现，多余
	int CountRb(UserRequest maxRequest, int type);            /*计算用户所需Rb数量，分为理想型和实际型*/


	double getvServiceWeight();
	int getvRealFactor();
	int getvDataFactor();
	double getvWindow();
	bool setvServiceWeight(double ServiceWeight);
	int getvRbNum();
	int getvRbLeft();
	//SchedualOut getvSchedualResult();
	int getvBbuId();
	int getvTti();
	/*设置Bbu各项基本信息*/
	bool setvRbNum(int RbNum);
	bool setvRbLeft(int RbLeft);
	bool setvBbuId(int BbuId);
	bool setvTti(int Tti);
};


bool  PFSchedual::Addrequest(UserRequest temp)
{
	/*   map<UserRequest, double> Queue = getvQueue();
	Queue.insert(pair<UserRequest, double>(temp, i));                //?????????????????
	i--;   */
	return 1;
}
double PFSchedual::Schedual(vector<UserRequest> &temp, int length, int type, vector<Ue> &vUeList)
{
	int i;
	int useRb;
	//SchedualOut Result;
	setvRbNum(500);
	setvRbLeft(500);
	for (i = 0; i < length; i++)                          //得到每个请求的优先级，并压入queue中
	{
		long P = GetPriprotyFactor(temp[i]);
		temp[i].setPriority(P);
		temp[i].setPriority2(P);
	}
	while (getvRbLeft() >0)                                  //当还有剩余Rb时，执行调度
	{
		double maxP = 0;
		for (i = 0; i < length; i++)   //得到最大的优先级
		{
			if (temp[i].getPriority() > maxP)
			{
				maxP = temp[i].getPriority();
			}
		}
		if (maxP == 0)               //如果都调度了一遍，就算有剩余Rb也跳出循环
			break;
		for (i = 0; i < length; i++) //得到最大优先级对应的请求
		{
			if (temp[i].getPriority() == maxP)
			{


				
				useRb = CountRb(temp[i], type);                  //计算出此请求所需的Rb数量,type为计算类型

				//////////////////


				if (useRb > getvRbLeft())                              //如果剩余Rb已不足以分配给用户
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + getvRbLeft());
					temp[i].setvTotalBit((temp[i].getvTotalBit() + ((double)getvRbLeft() / useRb / 1000 * (double)temp[i].getvTransSpeed())) );   //更新用户发送比特数
					setvRbLeft(0);              //将剩余Rb分配
				}
				else
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + useRb);
					temp[i].setvTotalBit((temp[i].getvTotalBit() + ((double)temp[i].getvTransSpeed() / 1000)));   //更新用户发送比特数
					setvRbLeft(getvRbLeft() - useRb);              //分配Rb
				}
				temp[i].setPriority(0);
			}
		}
		
	}
	for (i = 0; i < length; i++)
	{
		if (temp[i].getPriority() == 0)
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*(1-vWindow) + temp[i].getvTransSpeed()*vWindow));           //无法更改key中参数  待解决。
			temp[i].setvSpeed(temp[i].getvTransSpeed());
		}
		else
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*(1-vWindow)));
		}

	}
	schedualOut(temp,vUeList);
//	Result.setvAllQ(temp);    //如果优先级不变，如何分配资源给其他请求？？？？？？？？？？？？？    优先级置为0，已解决。
    return (double)(getvRbNum() - getvRbLeft()) / getvRbNum();
//	return Result;



}
int PFSchedual::CountRb(UserRequest maxRequest, int type)
{
	double useRb;
	int vTTI = 1;
	int TTI = 1;
	double TTIlength = 0.001;
	if (type = 1)
	{
		useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (TTIlength * 15000 * 12 * log(1 + pow(10, (maxRequest.getvSinr() / 10))) / log(2));
	}
	else if (type = 2)
	{

		if (maxRequest.getvSinr() < -6.71)
			cout << "用户sinr值过低！" << endl;
		else if (maxRequest.getvSinr() >= -6.71 && maxRequest.getvSinr() < -5.11)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (2 * 78 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= -5.11 && maxRequest.getvSinr() < -3.15)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (2 * 120 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= -3.15 && maxRequest.getvSinr() < -0.87)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (2 * 193 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= -0.87 && maxRequest.getvSinr() < 0.71)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (2 * 308 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 0.71 && maxRequest.getvSinr() < 2.529)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (2 * 449 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 2.529 && maxRequest.getvSinr() < 4.606)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (2 * 602 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 4.606 && maxRequest.getvSinr() < 6.431)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (4 * 378 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 6.431 && maxRequest.getvSinr() < 8.326)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (4 * 490 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 8.326 && maxRequest.getvSinr() < 10.3)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (4 * 616 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 10.3 && maxRequest.getvSinr() < 12.22)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (6 * 456 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 12.22 && maxRequest.getvSinr() < 14.01)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (6 * 587 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 14.01 && maxRequest.getvSinr() < 15.81)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (6 * 666 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 15.81 && maxRequest.getvSinr() < 17.68)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (6 * 772 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else if (maxRequest.getvSinr() >= 17.68 && maxRequest.getvSinr() < 19.61)
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (6 * 873 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
		else
			useRb = TTIlength*maxRequest.getvTransSpeed() * 1000000 / (6 * 948 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
	}
	else
	{
		cout << "优先级有误!" << endl;
	}
	if ((useRb - (int)useRb) > 0)
	{
		useRb++;
	}
	return (int)useRb;
}

double PFSchedual::GetPriprotyFactor(UserRequest input)
{
	double PriprotyFactor;
	if (input.getvAverageRate() == 0)
	{
		PriprotyFactor = input.getvTransSpeed() / 1;
	}
	else
	{
		PriprotyFactor = input.getvTransSpeed() / input.getvAverageRate();
	}
	if (input.getvServiceType() == 1)
	{
		PriprotyFactor = PriprotyFactor * 100;                //计算优先级，如果是实时业务类型，则将优先级乘以100,平均传输速率在userrequest的构造函数里初始化为0.001
	}
	
	return PriprotyFactor;
}
void  PFSchedual::Update(int vTTI)
{

}

int PFSchedual::getvRealFactor()
{
	return vRealFactor;
}
int PFSchedual::getvDataFactor()
{
	return vDataFactor;
}
double PFSchedual::getvWindow()
{
	return vWindow;
}


int  PFSchedual::getvRbNum()
{
	return vRbNum;
}
int  PFSchedual::getvRbLeft()
{
	return vRbLeft;
}
/*SchedualOut  PFSchedual::getvSchedualResult()
{
return vSchedualResult;
}*/
int  PFSchedual::getvBbuId()
{
	return vBbuId;
}
int  PFSchedual::getvTti()
{
	return vTti;
}



bool  PFSchedual::setvRbNum(int RbNum)
{
	vRbNum = RbNum;
	return 1;
}
bool  PFSchedual::setvRbLeft(int RbLeft)
{
	vRbLeft = RbLeft;
	return 1;
}
bool  PFSchedual::setvBbuId(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool  PFSchedual::setvTti(int Tti)
{
	vTti = Tti;
	return 1;
}

#endif