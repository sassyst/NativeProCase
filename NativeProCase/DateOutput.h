#ifndef DateOutput_H
#define DateOutput_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Ue.h"
#include "Rru.h"
#include <cmath>
using namespace std;

void DateOutput(vector<Rru> &vRruList, vector<Ue> &vUeList)
{

}
void AverageRate(vector<Rru> &vRruList, vector<Ue> &vUeList)//平均吞吐量（每个Rru）
{
	vector<Ue>::iterator it;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		vector<Rru>::iterator it2;
		for (it2 = vRruList.begin(); it2 != vRruList.end(); it2++)
		{
			if (it->GetvServiceRruIdInfo() == it2->GetvRruIdInfo())
				it2->SetvAverageRateInfo(it2->GetvAverageRateInfo()+it->getvRate());
		}
	}
}

void Efficiency(vector<Bbu>&vBbuList, vector<Ue>&vUeList,int Time)//计算频谱效率（每个Bbu）
{
	vector<Bbu>::iterator it2;
	for (it2 = vBbuList.begin(); it2 != vBbuList.end(); it2++)
	{
		vector<Ue>::iterator it;
		double AllBit = 0;
		for (it = vUeList.begin(); it != vUeList.end(); it++)
		{
			if (it->GetvBbuIdInfo() == it2->GetvBbuIdInfo())
				AllBit = AllBit+it->getvTotalBit();
		}
		it2->SetvEfficiencyInfo(AllBit / (it2->GetvResInfo()*Time));
	}
}
void LoadConsume(vector<Bbu>&vBbuList)//计算小区动态负载能耗
{
	vector<Bbu>::iterator it2;
	double consume;
	for (it2 = vBbuList.begin(); it2 != vBbuList.end(); it2++)
	{
		if (it2->GetvResUtilizationRateInfo() != 0){
			consume = 10 * log10(it2->GetvResUtilizationRateInfo()*it2->GetvTransPowerInfo() * 5);
		}
		else
			consume = 0;
		it2->SetvConsumeInfo(consume);
	}
}

#endif