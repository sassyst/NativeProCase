#ifndef RRSchedual_H
#define RRSchedual_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "UserRequest.h"
#include "SchedualOut.h"
#include<map>

using namespace std;


class RRSchedual
{
private:
	int vRbNum;                                /*���ȵ���RB��Ŀ*/
	int vRbLeft;                               /*ʣ��RB��Ŀ*/
	//SchedualOut vSchedualResult;		       /*�����û���������*/
	int vBbuId;		 	                       /*��վ��Id*/
	int vTti;		                           /*��ʾ��ǰ��TTI��־*/


public:
	double i=10000;
	bool Addrequest(UserRequest temp);       /*���û��������ӵ�������*/                                           //δʵ�֣�����
	double Schedual(vector<UserRequest> &vRequstList, int length, int type, vector<Ue> &vUeList,int vTTI);/*���Ⱥ���������˳����е���*/
	void Update(int vTTI);                   /*����ˢ��TTI������ʣ�����Դ,�������û���ƽ������*/               //δʵ�֣�����
	bool Remove(int vUeId);                  /*�Ƴ������е���Ӧ�û�*/                                           //δʵ��
	bool RefreshQueue();                     /*ˢ�¶���*/                                                       //δʵ��
	int CountRb(UserRequest maxRequest, int type);         /*�����û�����Rb��������Ϊ�����ͺ�ʵ����*/
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


bool  RRSchedual::Addrequest(UserRequest temp)
{
	/*   map<UserRequest, double> Queue = getvQueue();
	Queue.insert(pair<UserRequest, double>(temp, i));
	i--;   */
	return 1;
}
double  RRSchedual::Schedual(vector<UserRequest> &temp, int length, int type, vector<Ue> &vUeList,int vTTI)
{
	int i;
	int useRb;
	setvRbNum(500);
	setvRbLeft(500);
	int maxP = 0;             //�������ȼ�
	for (i = 0; i < length; i++)   //�õ��������ȼ�
	{
		if (temp[i].getPriority() >maxP)
		{
			maxP = temp[i].getPriority();
		}
	}
	if (maxP == 0)       
	{
		int m = 10000;
		for (i = 0; i < length; i++)   //�õ��������ȼ�
		{
			temp[i].setPriority(m);
			m--;
		}
	}
	else
	{
		int m = 10001 - length;
		for (i = 0; i < length; i++)
		{
			if (temp[i].getPriority() == 0)
			{
				temp[i].setPriority(m);
				m++;
			}
		}
	}    //����Ϊ���ȼ���ʼ��
	maxP = 10000;
	
	while (getvRbLeft()>0)                                  //������ʣ��Rbʱ��ִ�е���
	{
		int check=0;
		for (i = 0; i < length; i++)   
		{
			if (temp[i].getPriority() == maxP)
			{
				check++;
			}
		}
		
		if (check == 0)
			break;                          //�ж����ȫ���û������ȹ�һ�飬������ʣ��RbҲ����ѭ��
		//<< length <<"len"<< endl;
		for (i = 0; i < length; i++) //�õ�������ȼ���Ӧ������
		{
			if (temp[i].getPriority() == maxP)
			{
				useRb = CountRb(temp[i], type);                  //����������������Rb����,typeΪ��������
			//	SaveFile << i << "i" << temp[i].getPriority() << "P" << useRb << "Rb" << getvRbLeft() << "Left" << endl;

				if (useRb > getvRbLeft())                              //���ʣ��Rb�Ѳ����Է�����û�
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + getvRbLeft());
					temp[i].setvTotalBit((temp[i].getvTotalBit() + ((double)getvRbLeft() / useRb / 1000 * (double)temp[i].getvTransSpeed())));   //�����û����ͱ�������һ��TTI��1ms��
					
					setvRbLeft(0);              //��ʣ��Rb����
				}
				else
				{
					temp[i].setvTotalRb(temp[i].getvTotalRb() + useRb);
					temp[i].setvTotalBit((temp[i].getvTotalBit() + ((double)temp[i].getvTransSpeed() / 1000)));   //�����û����ͱ�����
					setvRbLeft(getvRbLeft()-useRb);              //��ʣ��Rb����
				}
				temp[i].setPriority(0);
				for (int p = 0; p < length; p++)
				{
					if (temp[p].getPriority() != 0)
						temp[p].setPriority(temp[p].getPriority() + 1);
				}
			}
		}
		
	}
	int m = 10001 - length;
	for (i = 0; i < length; i++)
	{
		if (temp[i].getPriority() == 0)                           
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*0.9 + temp[i].getvTransSpeed()*0.1));           //�޷�����key�в���  �������
			temp[i].setvSpeed(temp[i].getvTransSpeed());
			temp[i].setPriority(m);
			m++;
		}
		else
		{
			temp[i].setvAverageRate((temp[i].getvAverageRate()*0.9));
		}
	}

	schedualOut(temp, vUeList);
//	Result.setvAllQ(temp);    //������ȼ����䣬��η�����Դ���������󣿣�����������������������    ���ȼ���Ϊ0���ѽ����

	double result = ((double)(getvRbNum() - getvRbLeft()) / getvRbNum());

	return  result;
//	return Result;


	
}
int RRSchedual::CountRb(UserRequest maxRequest, int type)         //1Ϊ�����ͣ�2Ϊʵ����
{
	double useRb=0;
	double vTTI = 0.001;
	double TTI = 0.001;
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
			useRb = TTIlength*maxRequest.getvTransSpeed()*1000000 / (2 * 78 * 7 * 12 * 2 * (vTTI / TTI) / 1024);
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
void  RRSchedual::Update(int vTTI)
{
	
}
bool  RRSchedual::Remove(int vUeId)
{
	
	return 1;
}
bool RRSchedual::RefreshQueue()
{

	return 1;
}

int  RRSchedual::getvRbNum()
{
	return vRbNum;
}
int  RRSchedual::getvRbLeft()
{
	return vRbLeft;
}
/*SchedualOut  RRSchedual::getvSchedualResult()
{
return vSchedualResult;
}*/
int  RRSchedual::getvBbuId()
{
	return vBbuId;
}
int  RRSchedual::getvTti()
{
	return vTti;
}



bool  RRSchedual::setvRbNum(int RbNum)
{
	vRbNum = RbNum;
	return 1;
}
bool  RRSchedual::setvRbLeft(int RbLeft)
{
	vRbLeft = RbLeft;
	return 1;
}
bool  RRSchedual::setvBbuId(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool  RRSchedual::setvTti(int Tti)
{
	vTti = Tti;
	return 1;
}



#endif