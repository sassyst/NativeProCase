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
#include "NetworkManager.h"

void LinkManager(vector<Link> &vLinkList, vector<Rru> &vRruList, vector<Bbu> &vBbuList, vector<AccessPoint> &vAccessPointList, vector<LinkPath> &vLinkAccess2RruList, vector<LinkPath> &vLinkBbu2RruList)
{

	//通过Bbu中的vLinkId计算每个环的资源量，然后计算Rru接入哪一个AccessPoint或者Bbu，并判断能否接入，即是否资源满足，
	//最终输出LinkAccess2Rru中，LinkEnd1是AccessPointId,LinkEnd2是RruId，或者输出LinkBbu2Rru中
	//Vector的遍历方法可参考NetWorkManager中
	double rrux, rruy;
	double bbux, bbuy;
	double pointx, pointy;
	double vLength;
	vector<Rru>::iterator it1;
	vector<AccessPoint>::iterator it2;
	AccessPoint vAccess;
	vector<struct node>::iterator it4;
	vector<Bbu>::iterator it5;
	Bbu vBbu;
	vector<Link>::iterator it7;
	double vMaxLength = DBL_MAX;
	int vLinkPathNum = 0;
	int vFlag = -1;
	for (it5 = vBbuList.begin(); it5 != vBbuList.end(); it5++){
		if (it5->GetvLinkIdInfo() > 0){
			for (it7 = vLinkList.begin(); it7 != vLinkList.end(); it7++){
				if (it7->GetvLinkIdInfo() == it5->GetvLinkIdInfo()){
					it7->SetvRemainResInfo(it7->GetvRemainResInfo() + it5->GetvResInfo());
				}
			}
		}
	}

	for (it1 = vRruList.begin(); it1 != vRruList.end(); it1++){
		vMaxLength = DBL_MAX;
		vFlag = -1;
		rrux = it1->GetvXInfo();
		rruy = it1->GetvYInfo();
		//it3 = 0;//存入的结点个数
		Link vLink;
		for (it2 = vAccessPointList.begin(); it2 != vAccessPointList.end(); it2++){
			for (it7 = vLinkList.begin(); it7 != vLinkList.end(); it7++){
				if (it2->GetvLinkIdInfo() == it7->GetvLinkIdInfo())
					vLink = *it7;
			}
			if (it1->GetvEquipPowerInfo() < vLink.GetvRemainResInfo()){
				pointx = it2->GetvXInfo();
				pointy = it2->GetvYInfo();
				vLength = sqrt((rrux - pointx)*(rrux - pointx) + (rruy - pointy)*(rruy - pointy));
				if (vLength < vMaxLength)
				{
					vMaxLength = vLength;
					vAccess = *it2;
					vFlag = 0;
				}

			}
		}
		for (it5 = vBbuList.begin(); it5 != vBbuList.end(); it5++){
			if (it5->GetvLinkIdInfo() < 0 && it5->GetvResInfo() > it1->GetvEquipPowerInfo()){
				bbux = it5->GetvXInfo();
				bbuy = it5->GetvYInfo();
				vLength = sqrt((rrux - bbux)*(rrux - bbux) + (rruy - bbuy)*(rruy - bbuy));
				if (vLength < vMaxLength)
				{
					vMaxLength = vLength;
					vBbu = *it5;
					vFlag = 1;
				}
				
			}
		}
		if (vFlag == 1)
		{
			LinkPath *vLBR = new LinkPath();
			vLBR->SetvLinkPathIdInfo(vLinkPathNum);
			vLBR->SetvLinkEnd1Info(vBbu.GetvBbuIdInfo());
			vLBR->SetvLinkEnd2Info(it1->GetvRruIdInfo());
			vLBR->SetvLinkTypeInfo(-1);
			vLBR->SetvRealLengthInfo(vMaxLength);
			vLinkBbu2RruList.push_back(*vLBR);
			vLinkPathNum++;
			vBbu.SetvResInfo(vBbu.GetvResInfo() - it1->GetvEquipPowerInfo());
		}
		else if (vFlag == 0)
		{
			LinkPath *vLBR = new LinkPath();
			vLBR->SetvLinkPathIdInfo(vLinkPathNum);
			vLBR->SetvLinkEnd1Info(vAccess.GetvAccessPointIdInfo());
			vLBR->SetvLinkEnd2Info(it1->GetvRruIdInfo());
			vLBR->SetvLinkTypeInfo(3);
			vLBR->SetvRealLengthInfo(vMaxLength);
			vLinkAccess2RruList.push_back(*vLBR);
			vLinkPathNum++;
			vLink.SetvRemainResInfo(vLink.GetvRemainResInfo() - it1->GetvEquipPowerInfo());
		}

	}
	//全部有序插入，进行约束判断
};

