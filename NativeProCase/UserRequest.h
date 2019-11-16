#ifndef UserRequest_H
#define UserRequest_H

#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;



class UserRequest
{
private:

	long int vTransSpeed;         /*�û�����������*/
	double vSpeed;
	double vServiceType;           /*ҵ�����ͣ�0Ĭ��Ϊ��ʵʱҵ��,1Ϊʵʱҵ��ģ��*/
	double vTurboCodeRate;      /*��Դ���ʣ�Turbo��Ϊ����*/
	int vModulationRate;        /*QPSK=2, 16QAM=4,64QAM=6*/
	double vSinr;		        /*�û�����Ϣ*/
	double vTotalBit;	    	/*�û������������bit�����û�Ҫ������ʣ���λ����bitÿ��*/
	int vTTISent;		 	    /*���͵�TTI��ʼʱ��,ÿ��ʱ���ж��TTI��TTI�ı�ʶ������Ψһ�ģ�ÿ��ʱ��Ҫ�ظ�*/
	double vAverageRate;		/*�û�֮ǰN��ʱ�̵��������ʵ�ƽ��ֵ����λ����bitÿ��*/               //��ô���£�����������������������������
	long int Priority;               /*�û������ȼ�*/
	long int Priority2;               /*�û������ȼ�*/
	int vTime;                  /*����ʱ�̣�����Ψһȷ��TTI*/
	int vBbuId;					/*����BBuId*/
	int vTotalRb;                /*�����ѷ����Rb����*/
	double vDis;

	//map<int, int> vTTIRb;


public:
	int vRbcurrent;               //���������rb����
	int vUserId;                /*�û�Id*/
	UserRequest()
	{
		vTotalBit = 0;
		vServiceType = 0;
		vAverageRate = 1;
		vRbcurrent = 0;
	};
	UserRequest(int UserId, long TransSpeed, int ServiceType, int Sinr, double TotalBit,int TTISent,double AverageRate,int BbuId,int totalRb,double Dis,int vPriority)
	{
		Priority = vPriority;
		vUserId = UserId;
		vTransSpeed = TransSpeed;
		vServiceType = ServiceType;
		vSinr = Sinr;
		vTotalBit = TotalBit;
		vTTISent = TTISent;
		vAverageRate = AverageRate;
		vBbuId = BbuId;
		vTotalRb = totalRb;
		vDis = Dis;
		vSpeed = 0;
	};
	void RefreshInfo(int TTISent);
	bool UpdateAverateRate(double vRatio, long vPresentRate);
	int getvUserId();
	double getvTransSpeed();
	double getvSpeed();
	int getvServiceType();
	double getvTurboCodeRate();
	int getvModulationRate();
	double getvSinr();
	double getvTotalBit();
	int getvTTISent();
	double getvAverageRate();
	int GetvBbuIdInfo();
	long int getPriority();             //�¼ӵ�  ��ѯ���ȼ�
	long int getPriority2();             //�¼ӵ�  ��ѯ���ȼ�2(�������Priority)
	double getvDis();
	/*����UserRequest���������Ϣ*/
	bool setvUserId(int UserId);
	bool setvTransSpeed(double TransSpeed);
	bool setvSpeed(double Speed);
	bool setvServiceType(int ServiceType);
	bool setvTurboCodeRate(double TurboCodeRate);
	bool setvModulationRate(int ModulationRate);
	bool setvSinr(double Sinr);
	bool setvTotalBit(double TotalBit);
	bool setvTTISent(int TTISent);
	bool setvAverageRate(double AverageRate);
	bool SetvBbuIdInfo(int BbuId);
	bool setPriority(long int priority);
	bool setPriority2(long int priority2);
	int getvTotalRb();             //�¼ӵ�  ����Rb����
	bool setvTotalRb(int TotalRb);
	void show();
	void show2();
	bool setvDis(double vDis);

};

double UserRequest::getvDis()
{
	return vDis;
}
void UserRequest::RefreshInfo(int TTISent)
{
	vTTISent = TTISent;
}
bool UserRequest::UpdateAverateRate(double vRatio, long vPresentRate)
{
	vAverageRate = (1 - vRatio)*vAverageRate + vRatio*vPresentRate;
	return 1;
}

int  UserRequest::getvUserId()
{
	return vUserId;
}
double  UserRequest::getvTransSpeed()
{
	return vTransSpeed;
}
double  UserRequest::getvSpeed()
{
	return vSpeed;
}
int  UserRequest::getvServiceType()
{
	return vServiceType;
}
double  UserRequest::getvTurboCodeRate()
{
	return vTurboCodeRate;
}
int  UserRequest::getvModulationRate()
{
	return vModulationRate;
}
double  UserRequest::getvSinr()
{
	return vSinr;
}
double  UserRequest::getvTotalBit()
{
	return vTotalBit;
}
int  UserRequest::getvTTISent()
{
	return vTTISent;
}
double  UserRequest::getvAverageRate()
{
	return vAverageRate;
}
int  UserRequest::GetvBbuIdInfo()
{
	return vBbuId;
}

bool  UserRequest::SetvBbuIdInfo(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool  UserRequest::setvUserId(int UserId)
{
	vUserId = UserId;
	return 1;
}
bool  UserRequest::setvTransSpeed(double TransSpeed)
{
	vTransSpeed = TransSpeed;
	return 1;
}
bool  UserRequest::setvSpeed(double Speed)
{
	vSpeed = Speed;
	return 1;
}
bool  UserRequest::setvServiceType(int ServiceType)
{
	vServiceType = ServiceType;
	return 1;
}
bool  UserRequest::setvTurboCodeRate(double TurboCodeRate)
{
	vTurboCodeRate = TurboCodeRate;
	return 1;
}
bool  UserRequest::setvModulationRate(int ModulationRate)
{
	vModulationRate = ModulationRate;
	return 1;
}
bool  UserRequest::setvSinr(double Sinr)
{
	vSinr = Sinr;
	return 1;
}
bool  UserRequest::setvTotalBit(double TotalBit)
{
	vTotalBit = TotalBit;
	return 1;
}
bool  UserRequest::setvTTISent(int TTISent)
{
	vTTISent = TTISent;
	return 1;
}
bool  UserRequest::setvAverageRate(double AverageRate)
{
	vAverageRate = AverageRate;
	return 1;
}

long int UserRequest::getPriority2()
{
	return Priority2;
}
long int UserRequest::getPriority()
{
	return Priority;
}
bool UserRequest::setPriority(long int priority)
{
	Priority = priority;
	return 1;
}
bool UserRequest::setPriority2(long int priority)
{
	Priority2 = priority;
	return 1;
}
int UserRequest::getvTotalRb()
{
	return vTotalRb;
}
bool UserRequest::setvTotalRb(int TotalRb)
{
	vTotalRb = TotalRb;
	return 1;
}
bool  UserRequest::setvDis(double Dis)
{
	vDis = Dis;
	return 1;
}
void UserRequest::show()
{
	ofstream SaveFile("output.txt",ios::app);
	SaveFile << "�û���UserId��" << this->getvUserId() << endl;
	SaveFile << "�û������ȼ���" << this->getPriority() << endl;
	SaveFile << "�û����������ʣ�" << this->getvTransSpeed() << endl;
	SaveFile << "�û���ǰNʱ��ƽ����������" << this->getvAverageRate() << endl;
	SaveFile << "�û��ѷ��͵���bit��:" << this->getvTotalBit() << endl;
	SaveFile << "�Ѹ��û��������Rb����" << this->getvTotalRb() << endl;
	cout << "�û���UserId��" << this->getvUserId() << endl;
	cout << "�û������ȼ���" << this->getPriority() << endl;
	cout << "�û���PF���ȼ���" << this->getPriority2() << endl;
	cout << "�û����������ʣ�" << this->getvTransSpeed()<<" M/s"<< endl;
	cout << "�û���ǰNʱ��ƽ����������" << this->getvAverageRate()<<"M/s"<< endl;
	cout << "�û��ѷ��͵���bit��:" << this->getvTotalBit() <<" MB"<< endl;
	cout << "�Ѹ��û��������Rb����" << this->getvTotalRb() <<" ��"<<endl;
	SaveFile.close();
}
void UserRequest::show2()
{
	ofstream SaveFile("output.txt", ios::app);
	SaveFile << this->getvUserId();
	SaveFile << "   " << this->getvDis();
	SaveFile << "    " << this->getvAverageRate() ;
	SaveFile << "      " << this->getvTotalBit() ;
	SaveFile << "      " << this->getvTransSpeed() ;
	SaveFile << "      " << this->getPriority() << endl;
	/*cout << this->getvUserId();
	cout << "   " << this->getvDis();
	cout << "    " << this->getvAverageRate();
	cout << "      " << this->getvTotalBit();
	cout << "      " << this->getvTransSpeed();
	cout << "      " << this->getPriority() << endl;*/
}


#endif