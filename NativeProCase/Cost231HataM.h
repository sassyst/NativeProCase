#ifndef Cost231HataM_H
#define Cost231HataM_H

#include<cmath>
#include "Cost231Hata.h"
class Cost231HataM :public Cost231Hata
{
public :
	double	GetCost231HataPl1();	//����Cost231Hataģ���������������·�����
	double	GetCost231HataPl2();	//Cost231Hataģ����������¿�����/ũ���·�����
	double	GetCost231HataPl3();	//
};

double	Cost231HataM::GetCost231HataPl1()
{
	return 46.3 + 35.46*log10(GetvCost231HataF()) - 13.82*log10(GetvCost231HataHb()) - (1.1*log10(GetvCost231HataF()) - 0.7)* GetvCost231HataHm() + (44.9 - 6.55*log10(GetvCost231HataHb()))*log10(GetvCost231HataD()) - 13.08;
};
double	Cost231HataM::GetCost231HataPl2()
{
	return 46.3 + 35.46*log10(GetvCost231HataF()) - 13.82*log10(GetvCost231HataHb()) - (1.1*log10(GetvCost231HataF()) - 0.7)* GetvCost231HataHm() + (44.9 - 6.55*log10(GetvCost231HataHb()))*log10(GetvCost231HataD()) - 23.32;
};
double	Cost231HataM::GetCost231HataPl3()//����ģ�����޸���˺���������Ϊ0
{
	return 0;
};

#endif