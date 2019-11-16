#ifndef LinkPath_H
#define LinkPath_H
#include<stdlib.h>

class LinkPath
{
private:
	int vLinkPathId;
	int vLinkEnd1;		//端点1
	int vLinkEnd2;		//端点2
	double vRealLength;
	int vLinkType;
	double vMaxTransRate;
	double vAttenuation;
	double vDelay;
	double vErrorRate;
	double vCost;
	int vLinkCircleId;	//所属环或总线的Id
	int vFibersNum;
	double vNs;//噪声功率
	double vLoss;//损耗系数
public:
	int GetvLinkPathIdInfo();
	int GetvLinkEnd1Info();
	int GetvLinkEnd2Info();
	double GetvRealLengthInfo();
	int GetvLinkTypeInfo();
	double GetvMaxTransRateInfo();
	double GetvAttenuationInfo();
	double GetvDelayInfo();
	double GetvErrorRateInfo();
	double GetvCostInfo();
	int GetvLinkCircleIdInfo();
	int GetvFibersNumInfo();
	double GetvNsInfo();
	double GetvLossInfo();

	bool SetvLinkPathIdInfo(int LinkPathId);
	bool SetvLinkEnd1Info(int LinkEnd1);
	bool SetvLinkEnd2Info(int LinkEnd2);
	bool SetvRealLengthInfo(double RealLength);
	bool SetvLinkTypeInfo(int LinkType);
	bool SetvMaxTransRateInfo(double MaxTransRate);
	bool SetvAttenuationInfo(double Attenuation);
	bool SetvDelayInfo(double Delay);
	bool SetvErrorRateInfo(double ErrorRate);
	bool SetvCostInfo(double Cost);
	bool SetvLinkCircleIdInfo(int LinkCircleId);
	bool SetvFibersNumInfo(int FibersNum);
	bool SetvNsInfo(double vNs);
	bool SetvLossInfo(double vLoss);

};			//LinkPath基类
//三个继承类
class LinkBbuPool2BbuPool :public LinkPath
{};
class LinkBbu2Bbu :public LinkPath
{};
class LinkBbu2Rru :public LinkPath
{};
class LinkAccess2Rru :public LinkPath
{};
int LinkPath::GetvLinkPathIdInfo()
{
	return vLinkPathId;
}
int LinkPath::GetvLinkEnd1Info()
{
	return vLinkEnd1;
}
int LinkPath::GetvLinkEnd2Info()
{
	return vLinkEnd2;
}
double LinkPath::GetvRealLengthInfo()
{
	return vRealLength;
}
int LinkPath::GetvLinkTypeInfo()
{
	return vLinkType;
}
double LinkPath::GetvMaxTransRateInfo()
{
	return vMaxTransRate;
}
double LinkPath::GetvAttenuationInfo()
{
	return vAttenuation;
}
double LinkPath::GetvDelayInfo()
{
	return vDelay;
}
double LinkPath::GetvErrorRateInfo()
{
	return vErrorRate;
}
double LinkPath::GetvCostInfo()
{
	return vCost;
}
int LinkPath::GetvLinkCircleIdInfo()
{
	return vLinkCircleId;
}
int LinkPath::GetvFibersNumInfo()
{
	return vFibersNum;
}
double LinkPath::GetvNsInfo()
{
	return vNs;
}
double LinkPath::GetvLossInfo()
{
	return vLoss;
}

bool LinkPath::SetvLinkPathIdInfo(int LinkPathId)
{
	vLinkPathId = LinkPathId;
	return 1;
}
bool LinkPath::SetvLinkEnd1Info(int LinkEnd1)
{
	vLinkEnd1 = LinkEnd1;
	return 1;
}
bool LinkPath::SetvLinkEnd2Info(int LinkEnd2)
{
	vLinkEnd2 = LinkEnd2;
	return 1;
}
bool LinkPath::SetvRealLengthInfo(double RealLength)
{
	vRealLength = RealLength;
	return 1;
}
bool LinkPath::SetvLinkTypeInfo(int LinkType)
{
	vLinkType = LinkType;
	return 1;
}
bool LinkPath::SetvMaxTransRateInfo(double MaxTransRate)
{
	vMaxTransRate = MaxTransRate;
	return 1;
}
bool LinkPath::SetvAttenuationInfo(double Attenuation)
{
	vAttenuation = Attenuation;
	return 1;
}
bool LinkPath::SetvDelayInfo(double Delay)
{
	vDelay = Delay;
	return 1;
}
bool LinkPath::SetvErrorRateInfo(double ErrorRate)
{
	vErrorRate = ErrorRate;
	return 1;
}
bool LinkPath::SetvCostInfo(double Cost)
{
	vCost = Cost;
	return 1;
}
bool LinkPath::SetvLinkCircleIdInfo(int LinkCircleId)
{
	vLinkCircleId = LinkCircleId;
	return 1;
}
bool LinkPath::SetvFibersNumInfo(int FibersNum)
{
	vFibersNum = FibersNum;
	return 1;
}
bool LinkPath::SetvNsInfo(double Ns)
{
	vNs = Ns;
	return 1;
}
bool LinkPath::SetvLossInfo(double Loss)
{
	vLoss = Loss;
	return 1;
}

#endif