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
	 int vRealFactor; /*ʵʱҵ���Ӱ������*/
	 int vDataFactor; /*����ҵ���Ӱ������*/
	double vWindow;  /*ʱ�䴰���Ӧ�*/
	int vRbNum;                                /*���ȵ���RB��Ŀ*/
	int vRbLeft;                               /*ʣ��RB��Ŀ*/
	//SchedualOut vSchedualResult;		       /*�����û���������*/
	int vBbuId;		 	                       /*��վ��Id*/
	int vTti;		                           /*��ʾ��ǰ��TTI��־*/



public:
	PFSchedual()
	{
		vRealFactor = 100;
		vDataFactor = 1;
		vWindow = 0.1; 
	};
	bool Addrequest(UserRequest temp);          /*���û��������ӵ�������*/
	double Schedual(vector<UserRequest> &temp, int length, int type, vector<Ue> &vUeList);   /*���Ⱥ���������˳����е���*/
	double GetPriprotyFactor(UserRequest input); /*�����û������ȼ�����*/
	void Update(int vTTI);                   /*����ˢ��TTI������ʣ�����Դ,�������û���ƽ������*/             //δʵ�֣�����
	int CountRb(UserRequest maxRequest, int type);            /*�����û�����Rb��������Ϊ�����ͺ�ʵ����*/


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
	/*����Bbu���������Ϣ*/
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
	for (i = 0; i < length; i++)                          //�õ�ÿ����������ȼ�����ѹ��queue��
	{
		long P = GetPriprotyFactor(temp[i]);
		temp[i].setPriority(P);
		temp[i].setPriority2(P);
	}
	while (getvRbLeft() >0)                                  //������ʣ��Rbʱ��ִ�е���
	{
		double maxP = 0;
		for (i = 0; i < length; i++)   //�õ��������ȼ�
		{
			if (temp[i].getPriority() > maxP)
			{
				maxP = temp[i].getPriority();
			}
		}
		if (maxP == 0)               //�����������һ�飬������ʣ��RbҲ����ѭ��
			break;
		for (i = 0; i < length; i++) //�õ�������ȼ���Ӧ������
		{
			if (temp[i].getPriority() == maxP)
			{


				
				useRb = CountRb(temp[i], type);                  //����������������Rb����,typeΪ��������

				//////////////////


				if (useRb > getvRbLeft())                              //���ʣ��Rb�Ѳ����Է�����û�
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + getvRbLeft());
					temp[i].setvTotalBit((temp[i].getvTotalBit() + ((double)getvRbLeft() / useRb / 1000 * (double)temp[i].getvTransSpeed())) );   //�����û����ͱ�����
					setvRbLeft(0);              //��ʣ��Rb����
				}
				else
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + useRb);
					temp[i].setvTotalBit((temp[i].getvTotalBit() + ((double)temp[i].getvTransSpeed() / 1000)));   //�����û����ͱ�����
					setvRbLeft(getvRbLeft() - useRb);              //����Rb
				}
				temp[i].setPriority(0);
			}
		}
		
	}
	for (i = 0; i < length; i++)
	{
		if (temp[i].getPriority() == 0)
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*(1-vWindow) + temp[i].getvTransSpeed()*vWindow));           //�޷�����key�в���  �������
			temp[i].setvSpeed(temp[i].getvTransSpeed());
		}
		else
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*(1-vWindow)));
		}

	}
	schedualOut(temp,vUeList);
//	Result.setvAllQ(temp);    //������ȼ����䣬��η�����Դ���������󣿣�����������������������    ���ȼ���Ϊ0���ѽ����
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
			cout << "�û�sinrֵ���ͣ�" << endl;
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
		cout << "���ȼ�����!" << endl;
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
		PriprotyFactor = PriprotyFactor * 100;                //�������ȼ��������ʵʱҵ�����ͣ������ȼ�����100,ƽ������������userrequest�Ĺ��캯�����ʼ��Ϊ0.001
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