/*----------------------------------------------------------------------------------------------------------------------
����math.h��WalkModel.h
Ue�ƶ��������
���ܣ����ղ����������ƶ��Ծ�̬ģ�͵���ع�ʽ
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
	//static bool vMoveKind;//���徲̬����MoveKind�����û����룬��ʾѡ���ƶ�ģ�͵����ࡣ0Ϊȫ���ģ�ͣ�1Ϊ�������ģ�͡�����Ϊ��
	//static bool vVType;//���徲̬����VType�����û����룬��ʾѡ���ٶȷֲ������͡�0Ϊ���ȷֲ���1Ϊ��̬�ֲ�������Ϊ��
	//static double vVa;//���徲̬����Va�����û����룬��ʾ�ٶ�Ϊ���ȷֲ�ʱ���յ�������ٶȡ���VType=1ʱΪ��
	//static double vVb;//���徲̬����Vb�����û����룬��ʾ�ٶ�Ϊ���ȷֲ�ʱ���յ�����С�ٶȡ���VType=1ʱΪ��
	//static double vM;//���徲̬����M�����û����룬��ʾ�ٶ�Ϊ��̬�ֲ�ʱ���յ����ٶȾ�ֵ����VType=0ʱΪ��
	//static double vS;//���徲̬����S�����û����룬��ʾ�ٶ�Ϊ��̬�ֲ�ʱ���յ����ٶȷ����VType=0ʱΪ��
	//static double vTt;//���徲̬����Tt�����û����룬��ʾ�����˶���ʱ�䡣����Ϊ��
	////�����ĸ���̬����ֻ�е�MoveKind=1ʱ�ſ���ʹ��
	//static double vVaMax;//���徲̬����VaMin�����û����룬��ʾ�������ģ�����ٶȷֲ�Ϊ��̬�ֲ�ʱ������ٶȡ�����Ϊ��
	//static double vVbMin;//���徲̬����VbMax�����û����룬��ʾ�������ģ�����ٶȷֲ�Ϊ��̬�ֲ�ʱ����С�ٶȡ�����Ϊ��
	//static double vDa;//���徲̬����Da�����û����룬��ʾ�������ģ�����˶��Ƕȵ����ֵ������Ϊ��
	//static double vDb;//���徲̬����Db�����û����룬��ʾ�������ģ�����˶��Ƕȵ���Сֵ������Ϊ��
	////��������	UE������Ϣ����
	double vV;//����õ����˶��ٶ�
	double X;
	double Y;
	srand((unsigned)time(NULL));
	vector<Ue>::iterator it;
	for(it = vUeList.begin(); it != vUeList.end(); it++)
	{
		if(vMoveKind==0)//�û�ѡ��ȫ���ģ��
		{
			if(vVType==0)//�û�ѡ���ٶȾ��ȷֲ�
			{
				
				RandomWalkModel m1;//����ȫ���ģ�Ͷ���m1
				vV = m1.AverageRandom(vVb, vVa);//�����˶��ٶ�
				do{
					double d1=m1.GetD();//���㲢��������˶��Ƕ�d1
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m1.GetSRandomX(vV,vTt,d1,X);//���㲢����UE�˶����X����
					Y=m1.GetSNormalY(vV,vTt,d1,Y);//���㲢����UE�˶����Y����

				} while (X>vBorderX || Y> vBorderY || X < 0 || Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			else if(vVType==1)//�û�ѡ���ٶ���̬�ֲ�
			{
				
				RandomWalkModel m2;//����ȫ���ģ�Ͷ���m2
				vV = m2.GetNormalVx_RandomWalkModel(vM, vS);//�����˶��ٶ�
				do{
					double d2=m2.GetD();//���㲢��������˶��Ƕ�d2
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m2.GetSNormalX(vV,vTt,d2,X);//���㲢����UE�˶����X����
					Y=m2.GetSNormalY(vV,vTt,d2,Y);//���㲢����UE�˶����Y����
					}while(X>vBorderX || Y> vBorderY || X < 0|| Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			else
			{
				cout<<"�ٶȷֲ�������vVType����"<<endl;
			}
		}
		else if(vMoveKind==1)//�û�ѡ�񲿷����ģ��
		{
			
			if(vVType==0)//�û�ѡ���ٶȾ��ȷֲ�
			{
				
				PartRandomWalkModel m3;//���ɲ������ģ�Ͷ���m3
				vV = m3.AverageRandom(vVb, vVa);//�����˶��ٶ�
				do{
					double d3=m3.GetD_PartRandomWalkModel(vDa,vDb);//���㲢��������˶��Ƕ�d3
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m3.GetSRandomX(vV,vTt,d3,X);//���㲢����UE�˶����X����
					Y=m3.GetSRandomY(vV,vTt,d3,Y);//���㲢����UE�˶����Y����
				} while (X>vBorderX || Y> vBorderY || X < 0 || Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			else if(vVType==1)//�û�ѡ���ٶ���̬�ֲ�
			{
				
				PartRandomWalkModel m4;//���ɲ������ģ�Ͷ���m4
				vV = m4.GetNormalVx_PartRandomWalkModel(vVbMin, vVaMax, vM, vS);//�����˶��ٶ�
				do{
					double d4=m4.GetD_PartRandomWalkModel(vDa,vDb);//���㲢��������˶��Ƕ�d3
					X=it->GetvXInfo();
					Y=it->GetvYInfo();
					X=m4.GetSNormalX(vV,vTt,d4,X);//���㲢����UE�˶����X����
					Y=m4.GetSNormalY(vV,vTt,d4,Y);//���㲢����UE�˶����Y����
				} while (X>vBorderX || Y> vBorderY || X < 0 || Y < 0);
				it->SetvXInfo (X);
				it->SetvYInfo (Y);
			}
			
		}
		
	}
	
}
#endif