#ifndef Business_H
#define Business_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Ue.h"
#include "Rru.h"
#include "RandomWalkModel.h"
#include <vector>
#include "UserRequest.h"
#include "UeConnectRru.h"
using namespace std;

void Swap(int &a, int &b){// �п���swapͬһ���������������汾
	int t = a;
	a = b;
	b = t;
};

void BusinessGenerate(vector<UserRequest> &vRequestList, vector<Ue> &vUeList, vector<Rru> &vRruList, int vWorkType, double vActiveRatio, double vFileRatio, double vWorkRatio, double vVoIPRate, double vNVoIPMin, double vNVoIPMiu, double vNVoIPSigma, double vTt, int vModelType)
{

	/*  	vActiveRatio	��Ծ�û�ռ�ȣ���ʾ��Ծ�û���ռ�İٷֱȣ�С��������Ծ�û��ͷǻ�Ծ�û��ı���ΪvActiveRatio : (1 - vActiveRatio)
			vFileRatio	VoIpҵ��ռ�ȣ���ʾVoIPҵ����ռ�İٷֱȣ�С������VoIP�û��ͷ�VoIpҵ���û��ı���ΪvFileRatio : (1 - vFileRatio)
			vVoIPRatio	VoIPҵ���û���Ҫ�����ʣ���λ��k / bps��
			vNVoIPMin	��VoIPҵ���û�Ҫ���������ʣ���λ��k / bps��
			vNVoIPMiu	��VoIPҵ���û�Ҫ������ʾ�ֵ����λ��k / bps��
			vNVoIPSigma	��VoIPҵ���û�Ҫ������ʷ���
			vTt	����TTI��ʱ�䣨��λ��s��
			vUeNumber	UE���ܸ���
			*/

	while (!vRequestList.empty())
	{
		vRequestList.pop_back();
	}//���vRequest


	if (vWorkType == 0)//�Ǽȶ�ҵ����
	{
		vector<Ue> vNewUeList;
		vector<Ue>::iterator it;
		for (it = vUeList.begin(); it != vUeList.end(); it++)
		{
			if (it->GetvServiceRruIdInfo() != -1)
			{
				vNewUeList.push_back(*it);
			}
		}

		int length = vNewUeList.size();
		int *a = new int[length];
		int vAcNum = length*vActiveRatio;
		int *b = new int[vAcNum];
		for (int i = 0; i < length; i++)
			a[i] = i;
		if (vActiveRatio > 0)
		{
			for (int i = 0; i < vAcNum; i++)
			{
				int j = rand() % (length - i) + i;// ����i��n-1��������
				Swap(a[i], a[j]);
			}
			for (int i = 0; i < vAcNum; i++)
			{
				b[i] = a[i];
				vNewUeList[b[i]].SetvIsActivityInfo(1);
			}

		}
		if (vFileRatio > 0)
		{
			int vVNum = vAcNum * vFileRatio;
			for (int i = 0; i < vVNum; i++)
			{
				srand(time(0));
				int j = rand() % (vAcNum - i) + i;// ����i��n-1��������
				Swap(b[i], b[j]);
			}
			for (int i = 0; i < vVNum; i++)
			{
				UserRequest *vRequest = new UserRequest(vNewUeList[b[i]].GetvUeIdInfo(), vVoIPRate, 1, vNewUeList[b[i]].GetvSNRInfo(), vNewUeList[b[i]].getvTotalBit(), vNewUeList[b[i]].getvTTISent(), vNewUeList[b[i]].getvAverageRate(), vNewUeList[b[i]].GetvBbuIdInfo(), vNewUeList[b[i]].getvTotalRb(), vNewUeList[b[i]].getvDis(), 0);//vNewUeList[b[i]].getvPriority());
				vRequestList.push_back(*vRequest);
			}
			for (int i = vVNum; i < vAcNum; i++)
			{
				RandomWalkModel m2;//����ȫ���ģ�Ͷ���m2 
				UserRequest *vRequest = new UserRequest(vNewUeList[b[i]].GetvUeIdInfo(), m2.GetNormalVx_RandomWalkModel(vNVoIPMiu, vNVoIPSigma), 1, vNewUeList[b[i]].GetvSNRInfo(), vNewUeList[b[i]].getvTotalBit(), vNewUeList[b[i]].getvTTISent(), vNewUeList[b[i]].getvAverageRate(), vNewUeList[b[i]].GetvBbuIdInfo(), vNewUeList[b[i]].getvTotalRb(), vNewUeList[b[i]].getvDis(), 0);// vNewUeList[b[i]].getvPriority());
				vRequestList.push_back(*vRequest);
			}
		}
		delete[]a;
		delete[]b;

	}
	else if (vWorkType == 1)
	{
		vector<Rru>::iterator it;
		for (it = vRruList.begin(); it != vRruList.end(); it++)
		{
			if (it->GetvUeNumInfo() == 0)
			{
				double vBusiness = it->GetvBusinessInfo();
				int Id = 0;
				if (vUeList.size() > 0)
				{
					Id = vUeList.back().GetvUeIdInfo();
				}
				else
				{
					Id = 0;
				}
				while (vBusiness > 0)
				{
					Ue *vUe = new Ue();
					//cout << vBusiness << "aaaaaaaaaaa" << endl;
					Rru rru;
					vUe->SetvUeIdInfo(Id + 1);
					Id++;
					vUe->SetvXInfo(it->GetvXInfo() + 0.7*(rand() % (2 * int(it->GetvRadiusInfo())) - it->GetvRadiusInfo()));
					vUe->SetvYInfo(it->GetvYInfo() + 0.7*(rand() % (2 * int(it->GetvRadiusInfo())) - it->GetvRadiusInfo()));
					vUe->SetvServiceRruIdInfo(it->GetvRruIdInfo());
					vUe->setvDis(GetDistance(*vUe, *it));
					vUe->setvWorkType(-1);
					it->SetvUeNumInfo(it->GetvUeNumInfo() + 1);
					
					double SNR = GetMaxSNR(*vUe, *it, rru, vModelType);
					RandomWalkModel m2;//����ȫ���ģ�Ͷ���m2 
					double vV = m2.GetNormalVx_RandomWalkModel(vNVoIPMiu, vNVoIPSigma);
					vUe->SetvBbuIdInfo(it->GetvServiceBbuIdInfo());
					vUe->SetvSNRInfo(SNR);
					if (vV < vNVoIPMin) vV = vNVoIPMin;
					vUeList.push_back(*vUe);
					if (vV >= vBusiness)
					{
						UserRequest *vRequest = new UserRequest(vUe->GetvUeIdInfo(), vBusiness, 1, SNR, vUe->getvTotalBit(), vUe->getvTTISent(), vUe->getvAverageRate(), vUe->GetvBbuIdInfo(), vUe->getvTotalRb(), vUe->getvDis(),0);
						vRequestList.push_back(*vRequest);
						vBusiness = 0;
					}
					else
					{
						UserRequest *vRequest = new UserRequest(vUe->GetvUeIdInfo(), vV, 1, SNR, vUe->getvTotalBit(), vUe->getvTTISent(), vUe->getvAverageRate(), vUe->GetvBbuIdInfo(), vUe->getvTotalRb(), vUe->getvDis(), 0);
						vRequestList.push_back(*vRequest);
						vBusiness = vBusiness - vV;
					}
				}
			}//Ϊ�ȶ�ҵ���������û���
			else if (it->GetvUeNumInfo() > 0)
			{
				vector<Ue>::iterator it2;
				double vBusiness = it->GetvBusinessInfo();
				int vNum = it->GetvUeNumInfo();
				double vAvgBusiness = it->GetvBusinessInfo() / vNum;
				for (it2 = vUeList.begin(); it2 != vUeList.end(); it2++)
				{
					if (it2->GetvServiceRruIdInfo() == it->GetvRruIdInfo())
					{
						vNum--;
						if (vBusiness > 0)
						{
							RandomWalkModel m2;//����ȫ���ģ�Ͷ���m2 
							double vV = m2.GetNormalVx_RandomWalkModel(vAvgBusiness, vNVoIPSigma);
							if (vV < vNVoIPMin) vV = vNVoIPMin;
							if (vV < vBusiness)
							{
								vBusiness = vBusiness - vV;
								UserRequest *vRequest = new UserRequest(it2->GetvUeIdInfo(), vV, 1, it2->GetvSNRInfo(), it2->getvTotalBit(), it2->getvTTISent(), it2->getvAverageRate(), it2->GetvBbuIdInfo(), it2->getvTotalRb(), it2->getvDis(),0);
								vRequestList.push_back(*vRequest);
							}
							else if (vV > vBusiness)
							{
								UserRequest *vRequest = new UserRequest(it2->GetvUeIdInfo(), vBusiness, 1, it2->GetvSNRInfo(), it2->getvTotalBit(), it2->getvTTISent(), it2->getvAverageRate(), it2->GetvBbuIdInfo(), it2->getvTotalRb(), it2->getvDis(),0);
								vRequestList.push_back(*vRequest);
								vBusiness = 0;
							}
						}
						else if (vBusiness == 0)
						{
							UserRequest *vRequest = new UserRequest(it2->GetvUeIdInfo(), 0, 1, it2->GetvSNRInfo(), it2->getvTotalBit(), it2->getvTTISent(), it2->getvAverageRate(), it2->GetvBbuIdInfo(), it2->getvTotalRb(), it2->getvDis(), 0);
							vRequestList.push_back(*vRequest);
						}
					}
				}
			}//Ϊ�Ѵ��ڵ��û�����ȶ�ҵ����
		}

	}
}
#endif
