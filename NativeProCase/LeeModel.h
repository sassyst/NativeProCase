#ifndef LeeModel_H
#define LeeModel_H

#include <cmath>


class LeeModel
{
private:
	double	vLeeModelPl;
	double	vLeeModelD;
	double	vLeeModelH;
public:
	//Get
	double GetvLeeModelPl();
	double GetvLeeModelD();
	double GetvLeeModelH();
	//Set
	bool SetvLeeModelPl(double vLeeModelPl);
	bool SetvLeeModelD(double vLeeModelD);
	bool SetvLeeModelH(double vLeeModelH);

	double	GetLeeModelPl();

};


double LeeModel::GetvLeeModelPl()
{
	return vLeeModelPl;
};
double LeeModel::GetvLeeModelD()
{
	return vLeeModelD;
};
double LeeModel::GetvLeeModelH()
{
	return vLeeModelH;
};

bool LeeModel::SetvLeeModelPl(double LeeModelPl)
{
	vLeeModelPl = LeeModelPl;
	return 1;
};
bool LeeModel::SetvLeeModelD(double LeeModelD)
{
	vLeeModelD = LeeModelD;
	return 1;
};
bool LeeModel::SetvLeeModelH(double LeeModelH)
{
	vLeeModelH = LeeModelH;
	return 1;
};

double	LeeModel::GetLeeModelPl()
{
	vLeeModelPl = 129.45 + 38.4*log10(vLeeModelD) - 20 * log10(vLeeModelH);
	return vLeeModelPl;
};

#endif