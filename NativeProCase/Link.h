#ifndef Link_H
#define Link_H

class Link
{
private:
	int vLinkId;			//Id
	int vLinkType;			//值1为环型，0为总线型
	double vX1;				
	double vY1;
	double vZ1;
	double vX2;
	double vY2;
	double vZ2;
	double vLongRadius;		//长半径
	double vShortRadius;	//短半径
	int vAccessPointNum;	//接入点数目
	double vCost;			//造价
	double vRemainRes;		//剩余资源量
public:
	int GetvLinkIdInfo();
	int GetvLinkTypeInfo();
	double GetvX1Info();
	double GetvY1Info();
	double GetvZ1Info();
	double GetvX2Info();
	double GetvY2Info();
	double GetvZ2Info();
	double GetvLongRadiusInfo();
	double GetvShortRadiusInfo();
	int GetvAccessPointNumInfo();
	double GetvCostInfo();
	double GetvRemainResInfo();

	bool SetvLinkIdInfo(int LinkId);
	bool SetvLinkTypeInfo(int LinkType);
	bool SetvX1Info(double X1);
	bool SetvY1Info(double Y1);
	bool SetvZ1Info(double Z1);
	bool SetvX2Info(double X);
	bool SetvY2Info(double Y);
	bool SetvZ2Info(double Z);
	bool SetvLongRadiusInfo(double LongRadius);
	bool SetvShortRadiusInfo(double ShortRadius);
	bool SetvAccessPointNumInfo(int AccessPointNum);
	bool SetvCostInfo(double Cost);
	bool SetvRemainResInfo(double RemainRes);
};

int Link::GetvLinkIdInfo()
{
	return vLinkId;
}
int Link::GetvLinkTypeInfo()
{
	return vLinkType;
}
double Link::GetvX1Info()
{
	return vX1;
}
double Link::GetvY1Info()
{
	return vY1;
}
double Link::GetvZ1Info()
{
	return vZ1;
}
double Link::GetvX2Info()
{
	return vX2;
}
double Link::GetvY2Info()
{
	return vY2;
}
double Link::GetvZ2Info()
{
	return vZ2;
}
double Link::GetvLongRadiusInfo()
{
	return vLongRadius;
}
double Link::GetvShortRadiusInfo()
{
	return vShortRadius;
}
int Link::GetvAccessPointNumInfo()
{
	return vAccessPointNum;
}
double Link::GetvCostInfo()
{
	return vCost;
}
double Link::GetvRemainResInfo()
{
	return vRemainRes;
}

bool Link::SetvLinkIdInfo(int LinkId)
{
	vLinkId = LinkId;
	return 1;
}
bool Link::SetvLinkTypeInfo(int LinkType)
{
	vLinkType = LinkType;
	return 1;
}
bool Link::SetvX1Info(double X)
{
	vX1 = X;

	return 1;
}
bool Link::SetvY1Info(double Y)
{
	vY1 = Y;
	return 1;
}
bool Link::SetvZ1Info(double Z)
{
	vZ1 = Z;
	return 1;
}
bool Link::SetvX2Info(double X)
{
	vX2 = X;

	return 1;
}
bool Link::SetvY2Info(double Y)
{
	vY2 = Y;
	return 1;
}
bool Link::SetvZ2Info(double Z)
{
	vZ2 = Z;
	return 1;
}
bool Link::SetvLongRadiusInfo(double LongRadius)
{
	vLongRadius = LongRadius;
	return 1;
}
bool Link::SetvShortRadiusInfo(double ShortRadius)
{
	vShortRadius = ShortRadius;
	return 1;
}
bool Link::SetvAccessPointNumInfo(int AccessPointNum)
{
	vAccessPointNum = AccessPointNum;
	return 1;
}
bool Link::SetvCostInfo(double Cost)
{
	vCost = Cost;
	return 1;
}
bool Link::SetvRemainResInfo(double RemainRes)
{
	vRemainRes = RemainRes;
	return 1;
}
#endif