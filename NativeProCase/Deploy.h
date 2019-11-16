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
	NetworkManager manager;			//声明manager管理对象
		//初始化操作
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
		//对TTI为0时，需先进行有线链路的部署
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
		//用户移动模型初始化
		manager.UeMoveModelInit();
		
		manager.UeDataInit();

		
		SaveFile << "-------------------------当前TTI" << vTt << "----------------------------------" << endl;
		cout << "-------------------------当前TTI" << vTt << "----------------------------------" << endl;
		SaveFile << manager.vRruList[0].GetvServiceBbuIdInfo() << "guanjian2" << endl;
		//调用业务量模型
		BusinessGenerate(manager.vRequestList, manager.vUeList, manager.vRruList, manager.BusinessType, 1, 0.8, 0.8, 25, 20, 50, 10, vTt, 1);//需要参数
		//system("pause");
		
		SaveFile << "Id 距离     平均吞吐量     总比特数      速度      优先级" << endl;
		cout << "业务量生成成功" << endl;
		//Ue关联Rru
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
			ResourseSchedual(*it, temp, manager.ResSchedualType, manager.vUeList, vTt);//资源调度模型
			//SaveFile << it->GetvResUtilizationRateInfo() << "UTL" << endl;
			SaveFile << "-------------------------当前BBU" << it->GetvBbuIdInfo() << "----------------------------------" << endl;
			cout << "-------------------------当前BBU" << it->GetvBbuIdInfo() << "----------------------------------" << endl;

		}
	
		UeMove(manager.vUeList, manager.vMoveKind, manager.vVType, manager.vVa, manager.vVb, manager.vM, manager.vS, vTt, manager.vVaMax, manager.vVbMin, manager.vDa, manager.vDb, manager.vBorderX, manager.vBorderY);//需要参数
		///UeMove(manager.vUeList, 0, 1, 20, 10, 5, 5, 1, 100, 50, 0, 0, 1500, 1000);//需要参数
		vector<Ue>::iterator it2;
		for (it2 = manager.vUeList.begin(); it2 != manager.vUeList.end(); it2++)
		{
			SaveFile << it2->getvRate() << endl;
		}
		//求平均速率
		AverageRate(manager.vRruList, manager.vUeList);
		//BBU池调度
		BbuPoolResSchedule(manager.vBbuPoolList, manager.vBbuList, manager.vRruList);

		
		Efficiency(manager.vBbuList, manager.vUeList, 1);//计算频谱效率
		LoadConsume(manager.vBbuList);//计算能耗
	
		manager.Efficiency(manager.vUeList, manager.vBbuList, vTt, 1);//计算单个Bbu频谱效率
		manager.ConsumeSum(manager.vBbuList, manager.vRruList, vTt);//计算单个Bbu的能耗
		manager.SNRCount(manager.vUeList, vTt);//计算SNR值得范围
		manager.Last5PercentRate(manager.vUeList, vTt);//计算最差5%的吞吐量
		//保存数据
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