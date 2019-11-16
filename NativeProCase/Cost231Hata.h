#ifndef Cost231Hata_H
#define Cost231Hata_H
#include <cmath>

class Cost231Hata
{
private:
	int	vEnvirKind;				//代表区域类型，分别是中小城市、f>400MHz大城市、f<200MHz大城市
	double	vCost231HataF;		//工作频率（MHz）
	double	vCost231HataHb;		//基站天线有效高度（m）
	double	vCost231HataHm;		//移动台天线高度（m）
	double	vCost231HataD;		//传播距离（km）
public:
	//Get
	int GetvEnvirKind();
	double GetvCost231HataF();
	double GetvCost231HataHb();
	double GetvCost231HataHm();
	double GetvCost231HataD();
	//Set
	bool SetvEnvirKind(int vEnvirKind);
	bool SetvCost231HataF(double vCost231HataF);
	bool SetvCost231HataHb(double vCost231HataHb);
	bool SetvCost231HataHm(double vCost231HataHm);
	bool SetvCost231HataD(double vCost231HataD);
	//
	double	GetCost231HataPl1();	//中小城市情况的路径损耗
	double	GetCost231HataPl2();	//f>400MHz大城市情况的路径损耗
};

int Cost231Hata::GetvEnvirKind()
{
	return vEnvirKind;
};
double Cost231Hata::GetvCost231HataF()
{
	return vCost231HataF;
};
double Cost231Hata::GetvCost231HataHb()
{
	return vCost231HataHb;
};
double Cost231Hata::GetvCost231HataHm()
{
	return vCost231HataHm;
};
double Cost231Hata::GetvCost231HataD()
{
	return vCost231HataD;
};


bool Cost231Hata::SetvEnvirKind(int EnvirKind)
{
	vEnvirKind = EnvirKind;
	return 1;
};
bool Cost231Hata::SetvCost231HataF(double Cost231HataF)
{
	vCost231HataF = Cost231HataF;
	return 1;
};
bool Cost231Hata::SetvCost231HataHb(double Cost231HataHb)
{
	vCost231HataHb = Cost231HataHb;
	return 1;
};
bool Cost231Hata::SetvCost231HataHm(double Cost231HataHm)
{
	vCost231HataHm = Cost231HataHm;
	return 1;
};
bool Cost231Hata::SetvCost231HataD(double Cost231HataD)
{
	vCost231HataD = Cost231HataD;
	return 1;
};


double	Cost231Hata::GetCost231HataPl1()
{
	if (vCost231HataF >= 200 && vCost231HataF <= 400 )
		return 46.3 + 35.46*log10(vCost231HataF)-13.82*log10(vCost231HataHb)-(1.1*log10(vCost231HataF)-0.7)* vCost231HataHm + (44.9 - 6.55*log10(vCost231HataHb))*log10(vCost231HataD) - 0.8;
	else if (vCost231HataF > 400)
		return 46.3 + 33.9 *log10(vCost231HataF)-13.82*log10(vCost231HataHb)-3.2*pow((log10(11.75*vCost231HataHm)),2) + (44.9 - 6.55*log10(vCost231HataHb))*log10(vCost231HataD) + 7.97;
	else if (vCost231HataF < 200)
		return 46.3 + 33.9*log10(vCost231HataF) - 13.82*log10(vCost231HataHb) - 8.29*pow((log10(1.54*vCost231HataHm)), 2) + (44.9 - 6.55*log10(vCost231HataHb))*log10(vCost231HataD) + 4.1;
	else
		return 0;
};
#endif