#ifndef RandomWalkModel_H
#define RandomWalkModel_H
/*
----------------------------------------------------------------------------------------------------------------------
移动模型设计类
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
	int kind;//速度分布是均匀分布还是正太分布
	double Vmax;//速度是均与分布时的最大速度
	double Vmin;//速度是均匀分布时的最小速度
	double Miu;//速度是正太分布时的均值
	double Sigma;//速度是正太分布时的方差
	double V;//本次运动的速度
	double D;//本次运动的方向
	double T;//本次运动的时间
	//double S;//计算得到的本次运动的距离
	double X;//UE的X坐标值
	double Y;//UE的Y坐标值
public:
	//

	//生成set get方法
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
	double GetD()//在[0,360]间产生随机角度  注：srand((unsigned)time(NULL));
	{
		
		D=rand()%360;
		//cout<<"随机角度D="<<D<<endl;
		D=D/360.0*2.0*pi;
		//cout<<"换算后D="<<D<<endl;
		return D;
	}
	//速度为均匀分布时，计算出新的位置X
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
	//速度为均匀分布时，计算出新的位置Y
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
	double AverageRandom(double Vmin,double Vmax)//产生一个在一个区间之内的平均分布的随机数，精度是4位小数。
	{
		//srand((unsigned)time(NULL));
		int num;
		double Vx;		
		int minInteger=(int)(Vmin*10000);
		int maxInteger=(int)(Vmax*10000);
		int randInteger=rand()*rand();
		num=maxInteger-minInteger;
		Vx=randInteger%num+minInteger;
		//cout<<"随机速度Vx/10000.0 :"<<Vx/10000.0<<endl;
		return Vx/10000.0;
		
		/*srand((unsigned)time(NULL));
		int num;
		double Vx;	
		num=(int)(Vmax-Vmin);
		Vx=rand()%num+Vmin;
		return Vx;*/
	}
	double LogNormal(double Vx,double Miu,double Sigma)//正太分布函数
	{
		return (1.0/(sqrt(2*pi)*Sigma))*exp((-1)*((Vx-Miu)*(Vx-Miu))/(2*Sigma*Sigma));
	}
	double GetNormalVx_RandomWalkModel(double Miu,double Sigma)//正太分布随机速度
	{
		double dScope;
		double Vx;
		double Fx;
		//srand((unsigned)time(NULL));
		do{
		Vx=AverageRandom(Miu-3*Sigma, Miu+3*Sigma);
		//cout<<"随机出的速度Vx="<<Vx<<endl;
		Fx=LogNormal( Vx, Miu, Sigma);
		//cout<<"概率密度Fx="<<Fx<<endl;
		dScope=AverageRandom(0,LogNormal( Miu, Miu, Sigma));
		//cout<<"dScope="<<dScope<<endl;
		//if (dScope>Fx) cout<<"--------dScope>Fx"<<endl;
		//else cout<<"--------dScope<=Fx"<<endl;
		}while(dScope>Fx);//x越靠近miu，对应的Fx的值越大，dScope<=Fx的概率越大。所以取得x靠近miu的概率大，越远离miu概率越小。
		//cout<<"当dScope<=Fx时满足正太分布得到最终Vx="<<Vx<<endl;
		return Vx;
	}
	//速度为正太分布时，计算出新的位置
	double GetSNormalX(double V,double T, double D,double X)
	{
		//cout<<"速度为正太分布时，计算出新的位置"<<endl;
		double Z;
		Z=V*T;
		//cout<<"Z="<<Z<<endl;
		X=X+Z*cos(D);
		//cout<<"X="<<X<<endl;
		return X;
	}
	//速度为正太分布时，计算出新的位置
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
class PartRandomWalkModel:public RandomWalkModel//部分随机模型
{
private:
	//double Vnmax;//速度是正太分布时的最大值
	//double Vnmin;//速度是正太分布时的最小值
	//double Dmax;//运功方向的角度最大值
	//double Dmin;//运动方向的角度最小值
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
	double GetD_PartRandomWalkModel(double Dmax,double Dmin)//在[0,2π]间产生随机角度
	{
		double Dx;
		do{
		//D=rand()/RAND_MAX*2*pi;
		
		Dx=rand()%360;
		//cout<<"角度D="<<Dx<<endl;
		Dx=Dx/360.0*2.0*pi;
		//cout<<"换算后D="<<Dx<<endl;
		}while(Dx<Dmin || Dx>Dmax);
		//cout<<"最终随机角度为D="<<Dx<<endl;
		return Dx;
	}
	double GetNormalVx_PartRandomWalkModel(double Vnmin, double Vnmax,double Miu,double Sigma)//正太分布生成随机速度
	{
		double dScope;
		double Vx;
		double Fx;
		//srand((unsigned)time(NULL));
		do{
		Vx=AverageRandom(Miu-4*Sigma, Miu+4*Sigma);
		//cout<<"随机出的速度Vx="<<Vx<<endl;
		Fx=LogNormal( Vx, Miu, Sigma);
		//cout<<"概率密度Fx="<<Fx<<endl;
		dScope=AverageRandom(0,LogNormal( Miu, Miu, Sigma));
		}while((dScope>Fx) ||(Vx<Vnmin)||(Vx>Vnmax));
		//cout<<"当dScope<=Fx时且速度在Vnmin与Vnmax之间时，满足正太分布得到最终Vx="<<Vx<<endl;
		return Vx;
	}
	////部分随机模型:速度为正太分布时，计算出新的位置
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
	////部分随机模型:速度为正太分布时，计算出新的位置
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