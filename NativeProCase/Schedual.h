// ��Դ��.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "SchedualEntity.h"
#include "SchedualOut.h"
#include "UserRequest.h"
#include "Bbu.h"
#include "RRSchedual.h"
#include "PFSchedual.h"
#include "CISchedual.h"
#include <map>

void ResourseSchedual(Bbu &bbu, vector<UserRequest> &temp, int AlType, vector<Ue> &vUeList, int vTTI)
{
	
	int length = 0;
	vector<UserRequest>::iterator it2;
	for (it2 = temp.begin(); it2 != temp.end(); it2++)
	{
		length++;
	}
	

	RRSchedual a;
	CISchedual b;
	PFSchedual c;

	if (AlType == 1)
	{
		bbu.SetvResUtilizationRateInfo(a.Schedual(temp, length, 1, vUeList,vTTI));			//����ֵ����Դռ��
		cout << bbu.GetvResUtilizationRateInfo() <<"��Դռ��UTL"<< endl;
	}
	else if (AlType == 2)
	{
		bbu.SetvResUtilizationRateInfo(b.Schedual(temp, length, 1, vUeList));
		cout << bbu.GetvResUtilizationRateInfo() << "��Դռ��UTL" << endl;
	}
	else if (AlType == 3)
	{
		bbu.SetvResUtilizationRateInfo(c.Schedual(temp, length, 1, vUeList));
		cout << bbu.GetvResUtilizationRateInfo() << "��Դռ��UTL" << endl;
	}
	vector<UserRequest>::iterator it;
	
	for (it = temp.begin(); it != temp.end(); it++)
	{
		//cout <<"XXXX"<< temp.size()<<endl;
		it->show2();
		//system("Pause");
	}
	temp.clear();
}

