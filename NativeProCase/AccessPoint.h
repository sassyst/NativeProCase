#ifndef AccessPoint_H
#define AccessPoint_H

class AccessPoint{

private:
	int vAccessPointId;		//Id
	int vLinkId;			//Á´Â·Id
	float vX;
	float vY;
	float vZ;
public:
	int GetvAccessPointIdInfo();
	int GetvLinkIdInfo();
	double GetvXInfo();
	double GetvYInfo();
	double GetvZInfo();
	bool SetvAccessPointIdInfo(int AccessPointId);
	bool SetvLinkIdInfo(int LinkId);
	bool SetvXInfo(double X1);
	bool SetvYInfo(double Y1);
	bool SetvZInfo(double Z1);
};

int AccessPoint::GetvAccessPointIdInfo()
{
	return vAccessPointId;
}
int AccessPoint::GetvLinkIdInfo()
{
	return vLinkId;
}

double AccessPoint::GetvXInfo()
{
	return vX;
}
double AccessPoint::GetvYInfo()
{
	return vY;
}
double AccessPoint::GetvZInfo()
{
	return vZ;
}
bool AccessPoint::SetvAccessPointIdInfo(int AccessPointId)
{
	vAccessPointId = AccessPointId;
	return 1;
}
bool AccessPoint::SetvLinkIdInfo(int LinkId)
{
	vLinkId = LinkId;
	return 1;
}
bool AccessPoint::SetvXInfo(double X)
{
	vX = X;

	return 1;
}
bool AccessPoint::SetvYInfo(double Y)
{
	vY = Y;
	return 1;
}
bool AccessPoint::SetvZInfo(double Z)
{
	vZ = Z;
	return 1;
}
#endif