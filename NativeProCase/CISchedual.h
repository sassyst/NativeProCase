#ifndef CISchedual_H
#define CISchedual_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "UserRequest.h"
#include "SchedualOut.h"
#include<map>
#include<math.h>
using namespace std;


class CISchedual 
{
private:
	int vRbNum;                                /*调度的总RB数目*/
	int vRbLeft;                               /*剩余RB数目*/
	//SchedualOut vSchedualResult;		       /*返回用户的输入结果*/
	int vBbuId;		 	                       /*基站的Id*/
	int vTti;		                           /*表示当前的TTI标志*/


public:
	bool Addrequest(UserRequest temp);           /*将用户请求增加到队列中*/               //未实现，多余
	double Schedual(vector<UserRequest> &temp, int length, int type, vector<Ue> &vUeList);    /*调度函数，按照顺序进行调度*/
	double GetPriprotyFactor(UserRequest input); /*计算用户的优先级因子*/
	void Update(int vTTI);                       /*根据刷新TTI并更新剩余的资源,并更新用户的平均速率*/    //未实现，多余成员函数
	bool Remove(int vUeId);                      /*移除队列中的相应用户*/               //调度后移除？？？？如果移除还怎么返回给上层？？？？？？？未实现，多余
	bool RefreshQueue();                         /*刷新队列*/        //未实现，多余
	int CountRb(UserRequest maxRequest,int type);           /*计算用户所需Rb数量，分为理想型和实际型*/
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


bool  CISchedual::Addrequest(UserRequest temp)
{
	/*    map<UserRequest, double> Queue = getvQueue();
	Queue.insert(pair<UserRequest, double>(temp, i));
	i--;     */
	return 1;
}
double CISchedual::Schedual(vector<UserRequest> &temp, int length, int type, vector<Ue> &vUeList)
{
	int useRb;

	int i;
	setvRbNum(500);
	setvRbLeft(500);
	for (i = 0; i < length; i++)                          //得到每个请求的优先级
	{
		long int P = GetPriprotyFactor(temp[i]);

		temp[i].setPriority(P);
	}
	while (getvRbLeft() >0)                                  //当还有剩余Rb时，执行调度
	{
		long int maxP = 0;
		for (i = 0; i < length; i++)   //得到最大的优先级
		{
			if (temp[i].getPriority() > maxP)
			{
				maxP = temp[i].getPriority();
			}
		}
		if (maxP == 0)                   //如果都调度了一遍，就算有剩余Rb也跳出循环
			break;
		for (i = 0; i < length; i++) //得到最大优先级对应的请求
		{
			if (temp[i].getPriority() == maxP)
			{
				
				useRb = CountRb(temp[i], type);                  //计算出此请求所需的Rb数量,type为计算类型


				if (useRb > getvRbLeft())                              //如果剩余Rb已不足以分配给用户
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + getvRbLeft());
					temp[i].setvTotalBit((temp[i].getvTotalBit() + (getvRbLeft() / useRb / 1000 * (double)temp[i].getvTransSpeed())));   //更新用户发送比特数
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
			temp[i].setvAverageRate((temp[i].getvAverageRate()*0.9 + temp[i].getvTransSpeed()*0.1));           //无法更改key中参数  待解决。
			temp[i].setvSpeed(temp[i].getvTransSpeed());
		}
		else
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*0.9));
		}
	}
	schedualOut(temp, vUeList);
//	Result.setvAllQ(temp);    //如果优先级不变，如何分配资源给其他请求？？？？？？？？？？？？？    优先级置为0，已解决。
    return (double)(getvRbNum() - getvRbLeft() )/ getvRbNum();
	//return Result;



}
int CISchedual::CountRb(UserRequest maxRequest,int type)
{
	double useRb;
	int vTTI = 1;
	int TTI = 1;
	double TTIlength = 0.001;
	if(type = 1)
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
double CISchedual::GetPriprotyFactor(UserRequest input)
{
	double PriprotyFactor;
	PriprotyFactor = input.getvSinr();
	PriprotyFactor = log(PriprotyFactor+1) / log(2);
	if (input.getvServiceType() == 1)
	{
		PriprotyFactor = PriprotyFactor * 100;                //计算优先级，如果是实时业务类型，则将优先级乘以100
	}
	return PriprotyFactor;

}
void  CISchedual::Update(int vTTI)
{

}
bool  CISchedual::Remove(int vUeId)
{

	return 1;
}
bool CISchedual::RefreshQueue()
{

	return 1;
}


int  CISchedual::getvRbNum()
{
	return vRbNum;
}
int  CISchedual::getvRbLeft()
{
	return vRbLeft;
}
/*SchedualOut  CISchedual::getvSchedualResult()
{
return vSchedualResult;
}*/
int  CISchedual::getvBbuId()
{
	return vBbuId;
}
int  CISchedual::getvTti()
{
	return vTti;
}



bool  CISchedual::setvRbNum(int RbNum)
{
	vRbNum = RbNum;
	return 1;
}
bool  CISchedual::setvRbLeft(int RbLeft)
{
	vRbLeft = RbLeft;
	return 1;
}
bool  CISchedual::setvBbuId(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool  CISchedual::setvTti(int Tti)
{
	vTti = Tti;
	return 1;
}


#endif