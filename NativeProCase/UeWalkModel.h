/*----------------------------------------------------------------------------------------------------------------------
包含math.h和WalkModel.h
Ue移动过程设计
功能：接收参数，调用移动性静态模型的相关公式
*/
#ifndef UeMove_H
#define UeMove_H
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "RandomWalkModel.h"
#include "Ue.h"
using namespace std;
void UeMove(vector<Ue> &vUeList,bool vMoveKind, bool vVType, double vVa,double vVb,double vM,double vS,double vTt,double vVaMax,double vVbMin
	,double vDa,double vDb,double vBorderX,double vBorderY)
{
	//static bool vMoveKind;//定义静态变量MoveKind，由用户输入，表示选择移动模型的种类。0为全随机模型，1为部分随机模型。不可为空
	//static bool vVType;//定义静态变量VType，由用户输入，表示选择速度分布的类型。0为均匀分布，1为正态分布。不可为空
	//static double vVa;//定义静态变量Va，由用户输入，表示速度为均匀分布时接收到的最大速度。在VType=1时为空
	//static double vVb;//定义静态变量Vb，由用户输入，表示速度为均匀分布时接收到的最小速度。在VType=1时为空
	//static double vM;//定义静态变量M，由用户输入，表示速度为正态分布时接收到的速度均值。在VType=0时为空
	//static double vS;//定义静态变量S，由用户输入，表示速度为正态分布时接收到的速度方差。在VType=0时为空
	//static double vTt;//定义静态变量Tt，由用户输入，表示单次运动的时间。不可为空
	////以下四个静态变量只有当MoveKind=1时才可能使用
	//static double vVaMax;//定义静态变量VaMin，由用户输入，表示部分随机模型下速度分布为正态分布时的最大速度。可以为空
	//static double vVbMin;//定义静态变量VbMax，由用户输入，表示部分随机模型下速度分布为正态分布时的最小速度。可以为空
	//static double vDa;//定义静态变量Da，由用户输入，表示部分随机模型下运动角度的最大值。可以为空
	//static double vDb;//定义静态变量Db，由用户输入，表示部分随机模型下运动角度的最小值。可以为空
	////其他参数	UE坐标信息读出
	double vV;//计算得到的运动速度
	double X;
	double Y;
	srand((unsigned)time(NULL));
	vector<Ue>::iterator it;
	for(it = vUeList.begin(); it != vUeList.end(); it++)
	{
		if(vMoveKind==0)//用户选择全随机模型
		{
			if(vVType==0)//用户选择速度均匀分布
			{
				
				RandomWalkModel m1;//生成全随机模型对象m1
				vV = m1.AverageRandom(vVb, vVa);//计算运动速度
				do{
					double d1=m1.GetD();//计算并返回随机运动角度d1
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m1.GetSRandomX(vV,vTt,d1,X);//计算并返回UE运动后的X坐标
					Y=m1.GetSNormalY(vV,vTt,d1,Y);//计算并返回UE运动后的Y坐标

				} while (X>vBorderX || Y> vBorderY || X < 0 || Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			else if(vVType==1)//用户选择速度正态分布
			{
				
				RandomWalkModel m2;//生成全随机模型对象m2
				vV = m2.GetNormalVx_RandomWalkModel(vM, vS);//计算运动速度
				do{
					double d2=m2.GetD();//计算并返回随机运动角度d2
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m2.GetSNormalX(vV,vTt,d2,X);//计算并返回UE运动后的X坐标
					Y=m2.GetSNormalY(vV,vTt,d2,Y);//计算并返回UE运动后的Y坐标
					}while(X>vBorderX || Y> vBorderY || X < 0|| Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			else
			{
				cout<<"速度分布的类型vVType错误"<<endl;
			}
		}
		else if(vMoveKind==1)//用户选择部分随机模型
		{
			
			if(vVType==0)//用户选择速度均匀分布
			{
				
				PartRandomWalkModel m3;//生成部分随机模型对象m3
				vV = m3.AverageRandom(vVb, vVa);//计算运动速度
				do{
					double d3=m3.GetD_PartRandomWalkModel(vDa,vDb);//计算并返回随机运动角度d3
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m3.GetSRandomX(vV,vTt,d3,X);//计算并返回UE运动后的X坐标
					Y=m3.GetSRandomY(vV,vTt,d3,Y);//计算并返回UE运动后的Y坐标
				} while (X>vBorderX || Y> vBorderY || X < 0 || Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			else if(vVType==1)//用户选择速度正态分布
			{
				
				PartRandomWalkModel m4;//生成部分随机模型对象m4
				vV = m4.GetNormalVx_PartRandomWalkModel(vVbMin, vVaMax, vM, vS);//计算运动速度
				do{
					double d4=m4.GetD_PartRandomWalkModel(vDa,vDb);//计算并返回随机运动角度d3
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m4.GetSNormalX(vV,vTt,d4,X);//计算并返回UE运动后的X坐标
					Y=m4.GetSNormalY(vV,vTt,d4,Y);//计算并返回UE运动后的Y坐标
				} while (X>vBorderX || Y> vBorderY || X < 0 || Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			
		}
		
	}
	
}
#endif