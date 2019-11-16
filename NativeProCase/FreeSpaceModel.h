#ifndef FreeSpaceModel_H
#define FreeSpaceModel_H
#include<cmath>
#include<iostream>

class FreeSpaceModel
{
private:
	double	vFreeSpaceModelPl;			//自由空间模型路径损耗（dB）
	double	vFreeSpaceModelD;			//自由空间模型传播距离（km）
	double	vFreeSpaceModelF;			//自由空间模型频率（MHz）
public:

	//Get
	double GetvFreeSpaceModelPl();
	double GetvFreeSpaceModelD();
	double GetvFreeSpaceModelF();
	//Set
	bool SetvFreeSpaceModelPl(double vFreeSpaceModelPl);
	bool SetvFreeSpaceModelD(double vFreeSpaceModelD);
	bool SetvFreeSpaceModelF(double vFreeSpaceModelF);
	//
	double	GetFreeSpaceModelPl();		//计算自由空间模型下的路径损耗

};

double FreeSpaceModel::GetvFreeSpaceModelPl()
{
	return vFreeSpaceModelPl;
};
double FreeSpaceModel::GetvFreeSpaceModelD()
{
	return vFreeSpaceModelD;
};
double FreeSpaceModel::GetvFreeSpaceModelF()
{
	return vFreeSpaceModelF;
};

bool FreeSpaceModel::SetvFreeSpaceModelPl(double FreeSpaceModelPl)
{
	vFreeSpaceModelPl = FreeSpaceModelPl;
	return 1;
};
bool FreeSpaceModel::SetvFreeSpaceModelD(double FreeSpaceModelD)
{
	vFreeSpaceModelD = FreeSpaceModelD;
	return 1;
};
bool FreeSpaceModel::SetvFreeSpaceModelF(double FreeSpaceModelF)
{
	vFreeSpaceModelF = FreeSpaceModelF;
	return 1;
};


double	FreeSpaceModel::GetFreeSpaceModelPl()
{
	vFreeSpaceModelPl = 32.45 + 20*log10(vFreeSpaceModelD)+20*log10(vFreeSpaceModelF);
	return vFreeSpaceModelPl;
};

#endif