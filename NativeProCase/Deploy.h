#include "NetworkManager.h"
#include <iostream>
#include <vector>
#include "UeConnectRru.h"
#include "UeWalkModel.h"
#include <windows.h>
#include<stdio.h>
#include "LinkManage.h"
#include "Business.h"
#include "Schedual.h"
#include "Output.h"
#include "DateOutput.h"
#include "BbuPoolResSchedule.h"

int Deploy1()
{
	NetworkManager manager;			//����manager�������
		//��ʼ������
		manager.ConnectInit();
		long vTt = 0;
		manager.GetTTI();
		vTt = manager.vTTI;
		cout << vTt << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		manager.BbuDataInit();
		manager.BbuPoolDataInit();
		manager.AccessPointDataInit();
		manager.GetWorkType();
		manager.GetWorkType2();
		manager.GetBusinessType();
		if (manager.BusinessType == 1)
		{
			manager.EstRruDataInit(1);
		}
		else if (manager.BusinessType == 0)
		{
			manager.RruDataInit();
		}
		manager.LinkDataInit();
		ofstream SaveFile("output.txt", ios::app);
		//��TTIΪ0ʱ�����Ƚ���������·�Ĳ���
		if (vTt == 0)
		{
			manager.Delete("LinkAccess2Rru");
			manager.Delete("SNRCount");
			manager.Delete("Last5PercentRate");
			manager.Delete("Efficiency");
			manager.Delete("ConsumeSum");
			LinkManager(manager.vLinkList, manager.vRruList, manager.vBbuList, manager.vAccessPointList, manager.vLinkAccess2RruList, manager.vLinkBbu2RruList);
			//LinkCount(manager.vRruList, manager.vBbuList, manager.vAccessPointList, manager.vLinkAccess2RruList, manager.vLinkBbu2RruList);
			manager.LinkPathDataSave(manager.vLinkAccess2RruList, "LinkAccess2Rru");
			manager.LinkPathDataSave(manager.vLinkBbu2RruList, "LinkBbu2Rru");
		}
		//�û��ƶ�ģ�ͳ�ʼ��
		manager.UeMoveModelInit();
		
		manager.UeDataInit();

		
		SaveFile << "-------------------------��ǰTTI" << vTt << "----------------------------------" << endl;
		cout << "-------------------------��ǰTTI" << vTt << "----------------------------------" << endl;
		SaveFile << manager.vRruList[0].GetvServiceBbuIdInfo() << "guanjian2" << endl;
		//����ҵ����ģ��
		BusinessGenerate(manager.vRequestList, manager.vUeList, manager.vRruList, manager.BusinessType, 1, 0.8, 0.8, 25, 20, 50, 10, vTt, 1);//��Ҫ����
		//system("pause");
		
		SaveFile << "Id ����     ƽ��������     �ܱ�����      �ٶ�      ���ȼ�" << endl;
		cout << "ҵ�������ɳɹ�" << endl;
		//Ue����Rru
		UeConnectRru(manager.vUeList, manager.vRruList, manager.WirlessLinkModelType);
	
		vector<Bbu>::iterator it;
		for (it = manager.vBbuList.begin(); it != manager.vBbuList.end(); it++)
		{
			vector<UserRequest> temp;
			vector<UserRequest>::iterator it2;
			for (it2 = manager.vRequestList.begin(); it2 != manager.vRequestList.end(); it2++)
			{
				if (it2->GetvBbuIdInfo() == it->GetvBbuIdInfo())
					temp.push_back(*it2);
			}
			ResourseSchedual(*it, temp, manager.ResSchedualType, manager.vUeList, vTt);//��Դ����ģ��
			//SaveFile << it->GetvResUtilizationRateInfo() << "UTL" << endl;
			SaveFile << "-------------------------��ǰBBU" << it->GetvBbuIdInfo() << "----------------------------------" << endl;
			cout << "-------------------------��ǰBBU" << it->GetvBbuIdInfo() << "----------------------------------" << endl;

		}
	
		UeMove(manager.vUeList, manager.vMoveKind, manager.vVType, manager.vVa, manager.vVb, manager.vM, manager.vS, vTt, manager.vVaMax, manager.vVbMin, manager.vDa, manager.vDb, manager.vBorderX, manager.vBorderY);//��Ҫ����
		///UeMove(manager.vUeList, 0, 1, 20, 10, 5, 5, 1, 100, 50, 0, 0, 1500, 1000);//��Ҫ����
		vector<Ue>::iterator it2;
		for (it2 = manager.vUeList.begin(); it2 != manager.vUeList.end(); it2++)
		{
			SaveFile << it2->getvRate() << endl;
		}
		//��ƽ������
		AverageRate(manager.vRruList, manager.vUeList);
		//BBU�ص���
		BbuPoolResSchedule(manager.vBbuPoolList, manager.vBbuList, manager.vRruList);

		
		Efficiency(manager.vBbuList, manager.vUeList, 1);//����Ƶ��Ч��
		LoadConsume(manager.vBbuList);//�����ܺ�
	
		manager.Efficiency(manager.vUeList, manager.vBbuList, vTt, 1);//���㵥��BbuƵ��Ч��
		manager.ConsumeSum(manager.vBbuList, manager.vRruList, vTt);//���㵥��Bbu���ܺ�
		manager.SNRCount(manager.vUeList, vTt);//����SNRֵ�÷�Χ
		manager.Last5PercentRate(manager.vUeList, vTt);//�������5%��������
		//��������
		manager.UeDataSave();
		manager.RruDataSave();
		manager.BbuDataSave();

		manager.EstRruDataInit(1);
		manager.BbuDataInit();
		manager.vUeList.clear();
		manager.AddTTI(vTt);
		manager.ConnectClose();
		SaveFile.close();
	return 0;
}