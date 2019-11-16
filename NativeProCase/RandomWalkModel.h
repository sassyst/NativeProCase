#ifndef RandomWalkModel_H
#define RandomWalkModel_H
/*
----------------------------------------------------------------------------------------------------------------------
�ƶ�ģ�������
*/
#include <iostream>
#include   <stdlib.h>
#include   <time.h>
#include <math.h>
#define pi 3.1415926
using namespace std;
class RandomWalkModel
{
private:
	int kind;//�ٶȷֲ��Ǿ��ȷֲ�������̫�ֲ�
	double Vmax;//�ٶ��Ǿ���ֲ�ʱ������ٶ�
	double Vmin;//�ٶ��Ǿ��ȷֲ�ʱ����С�ٶ�
	double Miu;//�ٶ�����̫�ֲ�ʱ�ľ�ֵ
	double Sigma;//�ٶ�����̫�ֲ�ʱ�ķ���
	double V;//�����˶����ٶ�
	double D;//�����˶��ķ���
	double T;//�����˶���ʱ��
	//double S;//����õ��ı����˶��ľ���
	double X;//UE��X����ֵ
	double Y;//UE��Y����ֵ
public:
	//

	//����set get����
	/*void setkind(int temp)
	{
		kind=temp;
	}
	int getkind()
	{
		return kind;
	}*/
	/*void setVmax(double temp)
	{
		Vmax=temp;
	}
	double getVmax()
	{
		return Vmax;
	}
	void setVmin(double temp)
	{
		Vmin=temp;
	}
	double getVmin()
	{
		return Vmin;
	}
	void setMiu(double temp)
	{
		Miu=temp;
	}
	double getMiu()
	{
		return Miu;
	}
	void setSigma(double temp)
	{
		Sigma=temp;
	}
	double getSigma()
	{
		return Sigma;
	}*/
	/*void setV(double temp)
	{
		V=temp;
	}
	double getV()
	{
		return V;
	}*/
	/*void setT(double temp)
	{
		T=temp;
	}
	double getT()
	{
		return T;
	}*/
	/*void setS(double temp)
	{
		S=temp;
	}
	double getS()
	{
		return S;
	}*/
	/*void setX(double temp)
	{
		X=temp;
	}
	double getX()
	{
		return X;
	}
	void setY(double temp)
	{
		Y=temp;
	}
	double getY()
	{
		return Y;
	}*/
	double GetD()//��[0,360]���������Ƕ�  ע��srand((unsigned)time(NULL));
	{
		
		D=rand()%360;
		//cout<<"����Ƕ�D="<<D<<endl;
		D=D/360.0*2.0*pi;
		//cout<<"�����D="<<D<<endl;
		return D;
	}
	//�ٶ�Ϊ���ȷֲ�ʱ��������µ�λ��X
	double GetSRandomX(double Vx,double T, double D,double X)
	{
		
		double Z;
		/*int num;
		num=(int)(Vmax-Vmin);
		srand((unsigned)time(NULL));
		Vx=rand()%num+Vmin;
		cout<<"Vx="<<Vx<<endl;*/
		Z=Vx*T;
		//cout<<"Z="<<Z<<endl;
		//cout<<"cos(D):"<<cos(D)<<endl;
		X=X+Z*cos(D);
		cout<<"X="<<X<<endl;
		return X;
	}
	//�ٶ�Ϊ���ȷֲ�ʱ��������µ�λ��Y
	double GetSRandomY(double Vx,double T, double D,double Y)
	{
		
		double Z;
		/*int num;
		num=(int)(Vmax-Vmin);
		srand((unsigned)time(NULL));
		Vx=rand()%num+Vmin;*/
		//cout<<"Vx="<<Vx<<endl;
		Z=Vx*T;
		//cout<<"Z="<<Z<<endl;
		Y=Y+Z*sin(D);
		//cout<<"Y="<<Y<<endl;
		return Y;
	}
	double AverageRandom(double Vmin,double Vmax)//����һ����һ������֮�ڵ�ƽ���ֲ����������������4λС����
	{
		//srand((unsigned)time(NULL));
		int num;
		double Vx;		
		int minInteger=(int)(Vmin*10000);
		int maxInteger=(int)(Vmax*10000);
		int randInteger=rand()*rand();
		num=maxInteger-minInteger;
		Vx=randInteger%num+minInteger;
		//cout<<"����ٶ�Vx/10000.0 :"<<Vx/10000.0<<endl;
		return Vx/10000.0;
		
		/*srand((unsigned)time(NULL));
		int num;
		double Vx;	
		num=(int)(Vmax-Vmin);
		Vx=rand()%num+Vmin;
		return Vx;*/
	}
	double LogNormal(double Vx,double Miu,double Sigma)//��̫�ֲ�����
	{
		return (1.0/(sqrt(2*pi)*Sigma))*exp((-1)*((Vx-Miu)*(Vx-Miu))/(2*Sigma*Sigma));
	}
	double GetNormalVx_RandomWalkModel(double Miu,double Sigma)//��̫�ֲ�����ٶ�
	{
		double dScope;
		double Vx;
		double Fx;
		//srand((unsigned)time(NULL));
		do{
		Vx=AverageRandom(Miu-3*Sigma, Miu+3*Sigma);
		//cout<<"��������ٶ�Vx="<<Vx<<endl;
		Fx=LogNormal( Vx, Miu, Sigma);
		//cout<<"�����ܶ�Fx="<<Fx<<endl;
		dScope=AverageRandom(0,LogNormal( Miu, Miu, Sigma));
		//cout<<"dScope="<<dScope<<endl;
		//if (dScope>Fx) cout<<"--------dScope>Fx"<<endl;
		//else cout<<"--------dScope<=Fx"<<endl;
		}while(dScope>Fx);//xԽ����miu����Ӧ��Fx��ֵԽ��dScope<=Fx�ĸ���Խ������ȡ��x����miu�ĸ��ʴ�ԽԶ��miu����ԽС��
		//cout<<"��dScope<=Fxʱ������̫�ֲ��õ�����Vx="<<Vx<<endl;
		return Vx;
	}
	//�ٶ�Ϊ��̫�ֲ�ʱ��������µ�λ��
	double GetSNormalX(double V,double T, double D,double X)
	{
		//cout<<"�ٶ�Ϊ��̫�ֲ�ʱ��������µ�λ��"<<endl;
		double Z;
		Z=V*T;
		//cout<<"Z="<<Z<<endl;
		X=X+Z*cos(D);
		//cout<<"X="<<X<<endl;
		return X;
	}
	//�ٶ�Ϊ��̫�ֲ�ʱ��������µ�λ��
	double GetSNormalY(double V, double T, double D,double Y)
	{
		double Z;
		Z=V*T;
		//cout<<"Z="<<Z<<endl;
		Y=Y+Z*sin(D);
		//cout<<"Y="<<Y<<endl;
		return Y;
	}


};
class PartRandomWalkModel:public RandomWalkModel//�������ģ��
{
private:
	//double Vnmax;//�ٶ�����̫�ֲ�ʱ�����ֵ
	//double Vnmin;//�ٶ�����̫�ֲ�ʱ����Сֵ
	//double Dmax;//�˹�����ĽǶ����ֵ
	//double Dmin;//�˶�����ĽǶ���Сֵ
public:
	/*void setVnmax(double temp)
	{
		Vnmax=temp;
	}
	double getVnmax()
	{
		return Vnmax;
	}
	void setVnmin(double temp)
	{
		Vnmin=temp;
	}
	double getVnmin()
	{
		return Vnmin;
	}*/
	/*void setDmax(double temp)
	{
		Dmax=temp;
	}
	double getDmax()
	{
		return Dmax;
	}
	void setDmin(double temp)
	{
		Dmin=temp;
	}
	double getDmin()
	{
		return Dmin;
	}*/
	double GetD_PartRandomWalkModel(double Dmax,double Dmin)//��[0,2��]���������Ƕ�
	{
		double Dx;
		do{
		//D=rand()/RAND_MAX*2*pi;
		
		Dx=rand()%360;
		//cout<<"�Ƕ�D="<<Dx<<endl;
		Dx=Dx/360.0*2.0*pi;
		//cout<<"�����D="<<Dx<<endl;
		}while(Dx<Dmin || Dx>Dmax);
		//cout<<"��������Ƕ�ΪD="<<Dx<<endl;
		return Dx;
	}
	double GetNormalVx_PartRandomWalkModel(double Vnmin, double Vnmax,double Miu,double Sigma)//��̫�ֲ���������ٶ�
	{
		double dScope;
		double Vx;
		double Fx;
		//srand((unsigned)time(NULL));
		do{
		Vx=AverageRandom(Miu-4*Sigma, Miu+4*Sigma);
		//cout<<"��������ٶ�Vx="<<Vx<<endl;
		Fx=LogNormal( Vx, Miu, Sigma);
		//cout<<"�����ܶ�Fx="<<Fx<<endl;
		dScope=AverageRandom(0,LogNormal( Miu, Miu, Sigma));
		}while((dScope>Fx) ||(Vx<Vnmin)||(Vx>Vnmax));
		//cout<<"��dScope<=Fxʱ���ٶ���Vnmin��Vnmax֮��ʱ��������̫�ֲ��õ�����Vx="<<Vx<<endl;
		return Vx;
	}
	////�������ģ��:�ٶ�Ϊ��̫�ֲ�ʱ��������µ�λ��
	//double GetSNormalX(double Miu,double Sigma, double T, double D,double X)
	//{
	//	double Vx;
	//	double Z;
	//	do
	//	{
	//	Vx=(1/(sqrt(2*pi)*Sigma))*exp(pow((rand()-Miu),2)/(2*pow(Sigma,2)));
	//	}while(Vx>Vnmin && Vx<Vnmax);		
	//	Z=Vx*T;
	//	X=X+Z*cos(D);
	//	//Y=Y+Z*sin(D);
	//	return X;
	//}
	////�������ģ��:�ٶ�Ϊ��̫�ֲ�ʱ��������µ�λ��
	//double GetSNormalY(double Miu,double Sigma, double T, double D,double Y)
	//{
	//	double Vx;
	//	double Z;
	//	do
	//	{
	//	Vx=(1/(sqrt(2*pi)*Sigma))*exp(pow((rand()-Miu),2)/(2*pow(Sigma,2)));
	//	}while(Vx>Vnmin && Vx<Vnmax);		
	//	Z=Vx*T;
	//	Y=Y+Z*sin(D);
	//	return Y;
	//}
};
#endif;