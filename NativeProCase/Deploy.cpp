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
int main()
{

	NetworkManager manager;
	manager.ConnectInit();
	manager.BbuDataInit();
	manager.AccessPointDataInit();
	manager.EstRruDataInit(1);
	manager.LinkDataInit();
	manager.Delete("LinkAccess2Rru");
	manager.Delete("SNRCount");
	manager.Delete("Last5PercentRate");
	manager.Delete("Efficiency");
	manager.Delete("ConsumeSum");

	LinkManager(manager.vLinkList, manager.vRruList, manager.vBbuList, manager.vAccessPointList, manager.vLinkAccess2RruList, manager.vLinkBbu2RruList);
	//LinkCount(manager.vRruList, manager.vBbuList, manager.vAccessPointList, manager.vLinkAccess2RruList, manager.vLinkBbu2RruList);
	manager.LinkPathDataSave(manager.vLinkAccess2RruList,"LinkAccess2Rru");
	manager.LinkPathDataSave(manager.vLinkBbu2RruList,"LinkBbu2Rru");
	manager.GetWorkType();
	manager.UeMoveModelInit();
	int vTt = 1;
	while (1){

		manager.UeDataInit();
		
		if (vTt == 200)
			break;
		ofstream SaveFile("output.txt", ios::app);
		SaveFile << "-------------------------当前TTI" << vTt << "----------------------------------" << endl;
		cout<< "-------------------------当前TTI" << vTt << "----------------------------------" << endl;

		BusinessGenerate(manager.vRequestList,manager.vUeList,manager.vRruList,1,0.5,0.5,0.5,0.5,20,50,10,vTt,1);//需要参数
		//system("pause");
		vTt++;
		SaveFile << "Id 距离     平均吞吐量     总比特数      速度      优先级" << endl;
		cout << "业务量生成成功" << endl;
		
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
			ResourseSchedual(*it,temp, manager.ResSchedualType, manager.vUeList,vTt);//需要参数
			SaveFile << "-------------------------当前BBU" << it->GetvBbuIdInfo() << "----------------------------------" << endl;
			cout << "-------------------------当前BBU" << it->GetvBbuIdInfo() << "----------------------------------" << endl;
			

		}
		SaveFile.close();
		AverageRate(manager.vRruList, manager.vUeList);
		manager.PrintUe();
		manager.PrintRru();
		
		UeMove(manager.vUeList, manager.vMoveKind, manager.vVType, manager.vVa, manager.vVb, manager.vM, manager.vS, vTt, manager.vVaMax, manager.vVbMin, manager.vDa, manager.vDb,manager.vBorderX,manager.vBorderY);//需要参数
		///UeMove(manager.vUeList, 0, 1, 20, 10, 5, 5, 1, 100, 50, 0, 0, 1500, 1000);//需要参数

		UeConnectRru(manager.vUeList, manager.vRruList, manager.WirlessLinkModelType);
		Efficiency(manager.vBbuList, manager.vUeList, 1);//计算频谱效率
		LoadConsume(manager.vBbuList);//计算能耗
		manager.Efficiency(manager.vUeList,manager.vBbuList,vTt,1);//计算单个Bbu频谱效率
		manager.ConsumeSum(manager.vBbuList,manager.vRruList,vTt);//计算单个Bbu的能耗
		manager.SNRCount(manager.vUeList, vTt);//计算SNR值得范围
		manager.Last5PercentRate(manager.vUeList, vTt);//计算最差5%的吞吐量
		manager.UeDataSave();
		manager.RruDataSave();
		manager.BbuDataSave();
		//system("pause");
		manager.EstRruDataInit(1);
		manager.BbuDataInit();
		manager.vUeList.clear();
	}
	manager.ConnectClose();
	vTt++;
	
}