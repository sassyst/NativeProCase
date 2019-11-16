#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<math.h>
#include <vector>
#include "Rru.h"
#include "Bbu.h"
#include "Link.h"
#include "LinkPath.h"
#include "AccessPoint.h"
#include "odbcoperate.h"

using namespace std;

void LinkCount(vector<Rru> &vRruList, vector<Bbu> &vBbuList, vector<AccessPoint> &vAcceePointList, vector<LinkPath> &vLinkAccess2RruList, vector<LinkPath> &vLinkBbu2RruList){
	double vWireCost = 0, vTotalCost1 = 0, vTotalCost2 = 0, vTotalCost = 0;
	double vWireLength;
	double vNs;//噪声功率
	double vPs;
	double vSnr;//信噪比
	int vRruId;
	int vPointId;
	int vLinkPathId;
	int vBbuId;
	double vRruTransPower;//发射功率
	double vLoss;//损耗系数
	double vSe;//传输效率
	double vPointx = 0;
	double vPointy = 0;
	double vBbux = 0;
	double vBbuy = 0;
	double vTransTime;//传输时间
	double vRruOpTime;//rru处理时间
	double vBbuOpTime;//bbu处理时间
	double vOpTime;//总处理时间
	long vLightrate = 300000000;//光速

	vector<LinkPath>::iterator it1, it5;
	vector<Rru>::iterator it2, it6;
	vector<AccessPoint>::iterator it3;
	vector<Bbu>::iterator it4, it7;

	for (it1 = vLinkAccess2RruList.begin(); it1 != vLinkAccess2RruList.end(); it1++){
		vWireCost = it1->GetvCostInfo();
		vWireLength = it1->GetvRealLengthInfo();
		vNs = it1->GetvNsInfo();
		vLoss = it1->GetvLossInfo();
		vRruId = it1->GetvLinkEnd2Info();
		vPointId = it1->GetvLinkEnd1Info();
		vLinkPathId = it1->GetvLinkPathIdInfo();

		for (it2 = vRruList.begin(); it2 != vRruList.end(); it2++){
			if (vRruId == it2->GetvRruIdInfo()){
				vRruTransPower = it2->GetvRruTransPowerInfo();
				vRruOpTime = it2->GetvOpTimeInfo();
				vBbuId = it2->GetvServiceBbuIdInfo();
				break;
			}
		}

		for (it3 = vAcceePointList.begin(); it3 != vAcceePointList.end(); it3++){
			if (vPointId == it3->GetvAccessPointIdInfo() && vLinkPathId == it3->GetvLinkIdInfo()){
				vPointx = it3->GetvXInfo();
				vPointId = it3->GetvYInfo();
				break;
			}
		}

		for (it4 = vBbuList.begin(); it4 != vBbuList.end(); it4++){
			if (vBbuId = it4->GetvBbuIdInfo()){
				vBbux = it4->GetvXInfo();
				vBbuy = it4->GetvYInfo();
				vBbuOpTime = it4->GetvOpTimeInfo();
				break;
			}
		}
		vOpTime = vRruOpTime + vBbuOpTime;
		vTransTime = (vWireLength + sqrt((vPointx - vBbux)*(vPointx - vBbux) + (vPointy - vBbuy)*(vPointy - vBbuy))) / vLightrate;
		cout << vOpTime << vTransTime;

		vPs = (2 * vRruTransPower - vLoss*vWireLength) / 2;
		vSnr = vPs / vNs;
		vSe = 1.44*(vSnr - (vSnr*vSnr) / 2);
		cout << vSe;//第linkpathid条链路的传输效率

		vTotalCost1 = vTotalCost1 + vWireCost*vWireLength;

	}

	for (it5 = vLinkBbu2RruList.begin(); it5 != vLinkBbu2RruList.end(); it5++){
		vWireCost = it5->GetvCostInfo();
		vWireLength = it5->GetvRealLengthInfo();
		vNs = it1->GetvNsInfo();
		vLoss = it1->GetvLossInfo();
		vRruId = it1->GetvLinkEnd2Info();
		vLinkPathId = it1->GetvLinkPathIdInfo();

		for (it6 = vRruList.begin(); it6 != vRruList.end(); it6++){
			if (vRruId == it6->GetvRruIdInfo()){
				vRruTransPower = it6->GetvRruTransPowerInfo();
				vRruOpTime = it6->GetvOpTimeInfo();
				vBbuId = it6->GetvServiceBbuIdInfo();
				break;
			}
		}

		for (it7 = vBbuList.begin(); it7 != vBbuList.end(); it7++){
			if (vBbuId = it7->GetvBbuIdInfo()){
				vBbuOpTime = it7->GetvOpTimeInfo();
				break;
			}
		}
		vOpTime = vRruOpTime + vBbuOpTime;
		vTransTime = vWireLength / vLightrate;
		cout << vOpTime << vTransTime;

		vPs = (2 * vRruTransPower - vLoss*vWireLength) / 2;
		vSnr = vPs / vNs;
		vSe = 1.44*(vSnr - (vSnr*vSnr) / 2);
		cout << vSe;//第linkpathid条链路的传输效率

		vTotalCost2 = vTotalCost2 + vWireCost*vWireLength;
	}
	vTotalCost = vTotalCost1 + vTotalCost2;
	system("pause");
}

