#ifndef UeConnectRru_H
#define UeConnectRru_H

#include "Cost231HataM.h"
#include "FreeSpaceModel.h"
#include "LeeModel.h"
#include "Ue.h"
#include "Rru.h"
#include <vector>
#include <cmath>
#include <iostream>
double GetMaxSNR(Ue it, Rru it2, Rru &vRru, int vModelType);
double GetDistance(Ue a, Rru b)
{
	return sqrt(pow((a.GetvXInfo() - b.GetvXInfo()), 2) + pow((a.GetvYInfo() - b.GetvYInfo()), 2));
}

void UeConnectRru(vector<Ue> &vUeList, vector<Rru> &vRruList,int vModelType)
{

	vector<Ue>::iterator it;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		double vMaxSNR = -100;
		vector<Rru>::iterator it2;
		Rru vRru;
		for (it2 = vRruList.begin(); it2 != vRruList.end(); it2++)
		{
			double vDis = GetDistance(*it, *it2);
			if (vDis < it2->GetvRadiusInfo())
			{
				double SNR = GetMaxSNR(*it, *it2, vRru, vModelType);
				if (SNR > vMaxSNR)
				{
					vMaxSNR = SNR;

				}
			}
		}
		if (vMaxSNR > -100)			//connected
		{
			if (it->GetvServiceRruIdInfo() != -1)
			{
				vector<Rru>::iterator it3;
				for (it3 = vRruList.begin(); it3 != vRruList.end(); it3++)
				{
					if (it3->GetvRruIdInfo() == it->GetvServiceRruIdInfo())
						it3->SetvUeNumInfo(it3->GetvUeNumInfo() - 1);
				}
			}
			it->SetvServiceRruIdInfo(vRru.GetvRruIdInfo());
			it->SetvSNRInfo(vMaxSNR);
			if (it->GetvBbuIdInfo() != vRru.GetvServiceBbuIdInfo())
			{
				it->SetvBbuIdInfo(vRru.GetvServiceBbuIdInfo());
				it->setvPriority(0);
			}
			it->setvDis(GetDistance(*it, vRru));
			vector<Rru>::iterator it3;
			for (it3 = vRruList.begin(); it3 != vRruList.end(); it3++)
			{
				if (it3->GetvRruIdInfo() == vRru.GetvRruIdInfo())
					it3->SetvUeNumInfo(it3->GetvUeNumInfo() + 1);
			}
			
			//cout << "Ue" << it->GetvUeIdInfo() << "Rru" << vRru.GetvRruIdInfo();
		}
		else if (vMaxSNR == -100)			//not connect
		{
			if (it->GetvServiceRruIdInfo() != -1)
			{
				vector<Rru>::iterator it3;
				for (it3 = vRruList.begin(); it3 != vRruList.end(); it3++)
				{
					if (it3->GetvRruIdInfo() == it->GetvServiceRruIdInfo() && GetDistance(*it, *it3) > it3->GetvRadiusInfo())
					{
						it->SetvServiceRruIdInfo(-1);
						it3->SetvUeNumInfo(it3->GetvUeNumInfo() - 1);
						
					}
				}
			}
		}

	}
	
};

double GetMaxSNR(Ue it, Rru it2, Rru &vRru, int vModelType)
{
	double vN = -54;    //高斯白噪声
	double vMaxSNR = -100, vSNR = 0;
	double vDis = GetDistance(it, it2)/100;
	//cout << vDis << "DISTANCE" << endl;
	if (vModelType == 0)				//自由空间模型
	{
		FreeSpaceModel vF1;
		vF1.SetvFreeSpaceModelD(vDis);
		vF1.SetvFreeSpaceModelF(it2.GetvCarrierFrequentInfo());
		vSNR = (it2.GetvRruTransPowerInfo() - vF1.GetFreeSpaceModelPl()) - vN;
		//cout << "vSNR" << vSNR << endl;
		//cout << vF1.GetFreeSpaceModelPl() << "@@111111111111111111111" << endl;
		if (vSNR > vMaxSNR)
		{
			vMaxSNR = vSNR;
			vRru = it2;
			//cout << "vMaxSNR" << vMaxSNR << endl;
		}
	}
	else if (vModelType == 1)			//Lee模型
	{
		LeeModel vL1;
		vL1.SetvLeeModelD(vDis);
		vL1.SetvLeeModelH(it2.GetvZInfo() - it.GetvZInfo());
		vSNR = (it2.GetvRruTransPowerInfo() - vL1.GetLeeModelPl()) - vN;
		//cout << "vSNR" << vSNR<<endl;
		if (vSNR > vMaxSNR)
		{
			vMaxSNR = vSNR;
			vRru = it2;
		}
	}
	else if (vModelType == 2)			//Hata231模型
	{
		Cost231Hata vC1;
		vC1.SetvCost231HataD(vDis);
		vC1.SetvCost231HataF(it2.GetvCarrierFrequentInfo());
		vC1.SetvCost231HataHb(it2.GetvZInfo() - it.GetvZInfo());
		vC1.SetvCost231HataHm(it2.GetvZInfo() - it.GetvZInfo());
		vSNR = (it2.GetvRruTransPowerInfo() - vC1.GetCost231HataPl1()) - vN;
		//cout << vC1.GetCost231HataPl1() <<"@@111111111111111111111"<< endl;
		//cout << "vSNR = " << vSNR << endl;
		if (vSNR > vMaxSNR)
		{
			vMaxSNR = vSNR;
			vRru = it2;
		}

	}
	else if (vModelType == 3)			//Hata231修正模型
	{
		Cost231HataM vC1;
		vC1.SetvCost231HataD(vDis);
		vC1.SetvCost231HataF(it2.GetvCarrierFrequentInfo());
		vC1.SetvCost231HataHb(it2.GetvZInfo() - it.GetvZInfo());
		vC1.SetvCost231HataHm(it2.GetvZInfo() - it.GetvZInfo());
		vSNR = (it2.GetvRruTransPowerInfo() - vC1.GetCost231HataPl1()) - vN;
		//cout << vC1.GetCost231HataPl1() << "@@!!!!!!!!!!!!!!!!!" << endl;
		//cout << "vSNR" << vSNR<<endl;
		if (vSNR > vMaxSNR)
		{
			vMaxSNR = vSNR;
			vRru = it2;
		}
	}
	return vMaxSNR;
}
#endif
