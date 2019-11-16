#ifndef NetworkManager_H
#define NetworkManager_H

#include "odbcoperate.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "BbuPool.h"
#include "Bbu.h"
#include "Rru.h"
#include "Ue.h"
#include "LinkPath.h"
#include "Link.h"
#include "AccessPoint.h"
#include "UserRequest.h"

using namespace std;

string getstring(const int n) { std::stringstream newstr; newstr << n; return newstr.str(); }
string getstring(const double n) { std::stringstream newstr; newstr << n; return newstr.str(); }
class NetworkManager
{
private:
	int BbuPoolSize, UeSize, RruSize, BbuSize;

	CODBCDatabase pdb;


public:
	vector<LinkPath> vLinkBbuPool2BbuPoolList;
	vector<LinkPath> vLinkBbu2BbuList;
	vector<LinkPath> vLinkBbu2RruList;
	vector<LinkPath> vLinkAccess2RruList;
	vector<Link> vLinkList;
	vector<AccessPoint> vAccessPointList;
	vector<BbuPool> vBbuPoolList;
	vector<Bbu> vBbuList;
	vector<Rru> vRruList;
	vector<Ue> vUeList;
	vector<UserRequest> vRequestList;
	int BusinessType,ResSchedualType, WirlessLinkModelType, vTTI;	//模型变量
	//用户移动模型参数
	bool vMoveKind;
	bool vVType;
	double vVa;
	double vVb;
	double vM;
	double vS;
	double vVaMax;
	double vVbMin;
	double vDa;
	double vDb;
	double vBorderX;
	double vBorderY;

	bool ConnectInit();       //初始化连接
	bool UeDataSave();			//批量写入Ue到数据库
	bool RruDataSave();			//批量写入Rru到数据库
	bool BbuDataSave();			//批量写入Bbu到数据库
	bool BbuPoolDataSave();		//批量写入BbuPool到数据库
	bool LinkDataSave();	//批量写入LinkCircle到数据库
	bool LinkPathDataSave(vector<LinkPath> vLinkPathList, string name);//批量写入LinkPath到数据库
	//bool AccessPointDataSave();		//

	void SNRCount(vector<Ue> &vUeList, int TTI);
	void PrintUe();			//打印Ue信息
	void PrintRru();			//打印Rru信息
	void PrintBbu();			//打印Bbu信息
	void PrintBbuPool();		//打印BbuPool信息
	void PrintLink();	//打印LinkCircle信息
	void PrintLinkPath(vector<LinkPath> vLinkPathList);		//打印LinkPath信息
	void Last5PercentRate(vector<Ue> &vUeList, int TTI);
	void UeMoveModelInit();		//用户移动模型初始化
	bool UeDataInit();			//批量导入Ue数据
	bool RruDataInit();			//批量导入Rru数据
	bool EstRruDataInit(int TTI);			//批量导入含有既定业务量的Rru数据
	bool BbuDataInit();			//批量导入Bbu数据
	bool BbuPoolDataInit();		//批量导入Bbu池数据
	bool LinkPathDataInit(vector<LinkPath> vLinkPathList, string name);		//批量导入链路数据
	bool LinkDataInit();			//环的导入
	bool AccessPointDataInit();			//接入点初始化
	bool ConnectClose();				//关闭连接
	void Efficiency(vector<Ue> &vUeList, vector<Bbu> &vBbuList, int TTI, int Time);
	void ConsumeSum(vector<Bbu>&vBbuList, vector<Rru>&vRruList, int TTI);//计算总能耗
	//void Schedule();              //初始化rru与ue，bbu与rru的关系，供测试使用
	void GetWorkType();			//获取工作类型
	void GetWorkType2();			//获取工作类型
	void GetBusinessType();			//获取工作类型

	void GetTTI();					//获取当前TTI
	bool AddTTI(int tti);			//添加TTI
	int ReConnectUe2Rru(int UeId, int NewRruId);                    /*用户重新与新的RRU关联。*/
	int ReConnectRru2Bbu(int RruId, int NewBbuId);                  /*Rru重新与新的BBU关联*/
	int ReConnectBbu2BbuPool(int BbuId, int NewBbuPoolId);          /*BBU重新与新的BBUPool关联*/
	bool Delete(string Str);
};

bool NetworkManager::ConnectInit()
{
	char * pszUName = "sa";       //用户名
	char * pszUPassword = "zhangtao";  //密码
	char * pszDSN = "C-RAN";         //数据源名
	pdb.SetConnectionTimeout(15);
	pdb.Open(pszDSN, pszUName, pszUPassword);
	return 1;
}

bool NetworkManager::ConnectClose()
{
	pdb.Close();
	return 1;
}
bool NetworkManager::Delete(string Str)
{
	string str1 = "Delete from ";
	string str2 = str1 + Str;
	char * s14 = (char *)str2.c_str();
	pdb.Execute(s14);
	return 1;
}
bool NetworkManager::UeDataSave()
{
	string s0 = "delete from Ue";
	char * s00 = (char *)s0.c_str();
	pdb.Execute(s00);
	vector<Ue>::iterator it;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		string s1 = "Insert Into Ue (UeId,UeType,X,Y,Z,ServiceRruId,RbNum,UeTransPower,UeAntennaId,IsActivity,UeGroupId,ModelType,SNR,TotalBit,TTISent,AverageRate,BbuId,TotalRb,Dis,Priority,WorkType) values( ";
		string s01 = getstring(it->GetvUeIdInfo());
		string s21 = ", ";
		string s3 = getstring(it->GetvUeTypeInfo());
		string s31 = ",";
		string s4 = getstring(it->GetvXInfo());
		string s41 = ",";
		string s5 = getstring(it->GetvYInfo());
		string s51 = ",";
		string s6 = getstring(it->GetvZInfo());
		string s61 = ",";
		string s7 = getstring(it->GetvServiceRruIdInfo());
		string s71 = ",";
		string s8 = getstring(it->GetvRbNumInfo());
		string s81 = ",";
		string s9 = getstring(it->GetvUeTransPowerInfo());
		string s91 = ",";
		string s10 = getstring(it->GetvUeAntennaIdInfo());
		string s101 = ",";
		string s11 = getstring(it->GetvIsActivityInfo());
		string s111 = ",";
		string s12 = getstring(it->GetvUeGroupIdInfo());
		string s15 = ",";
		string s155 = getstring(it->GetvModelTypeInfo());
		string s16 = ",";
		string s166 = getstring(it->GetvSNRInfo());
		string s17 = ",";
		string s177 = getstring(it->getvTotalBit());
		string s18 = ",";
		string s188 = getstring(it->getvTTISent());
		string s19 = ",";
		string s199 = getstring(it->getvAverageRate());
		string s20 = ",";
		string s200 = getstring(it->GetvBbuIdInfo());
		string ss20 = ",";
		string ss200 = getstring(it->getvTotalRb());
		string ss21 = ",";
		string ss201 = getstring(it->getvDis());
		string ss22 = ",";
		string ss202 = getstring(it->getvPriority());
		string ss2021 = ",";
		string ss2020 = getstring(it->getvWorkType());
		string s33 = " )";

		string s13 = s1 + s01 + s21 + s3 + s31 + s4 + s41 + s5 + s51 + s6 + s61 + s7 + s71 + s8 + s81 + s9 + s91 + s10 + s101 + s11 + s111 + s12 + s15 + s155 + s16 + s166 + s17 + s177 + s18 + s188 + s19 + s199 + s20 + s200 + ss20 + ss200 + ss21 + ss201 + ss22 + ss202 + ss2021 + ss2020 + s33;
		char * s14 = (char *)s13.c_str();
		pdb.Execute(s14);
		//cout<<pdb.GetRowsAffected()<<endl;

	}
	while (!vUeList.empty())
	{
		vUeList.pop_back();
	}
	return 1;
}

bool NetworkManager::RruDataSave()
{
	vector<Rru>::iterator it;
	for (it = vRruList.begin(); it != vRruList.end(); it++)
	{
		string s1 = "Update Rru Set ";
		string s21 = "ServiceBbuId = ";
		string s3 = getstring(it->GetvServiceBbuIdInfo());
		string s31 = ",Radius = ";
		string s4 = getstring(it->GetvRadiusInfo());
		string s41 = ",X = ";
		string s5 = getstring(it->GetvXInfo());
		string s51 = ",Y = ";
		string s6 = getstring(it->GetvYInfo());
		string s61 = ",Z = ";
		string s7 = getstring(it->GetvZInfo());
		string s71 = ",RruTransPower = ";
		string s8 = getstring(it->GetvRruTransPowerInfo());
		string s81 = ",RruBandwidth = ";
		string s9 = getstring(it->GetvRruBandwidthInfo());
		string s91 = ",UeNum = ";
		string s10 = getstring(it->GetvUeNumInfo());
		string s101 = ",IsActivity = ";
		string s11 = getstring(it->GetvIsActivityInfo());
		string s111 = ",CarrierFrequent = ";
		string s12 = getstring(it->GetvCarrierFrequentInfo());
		string s121 = ",RruAntennaId = ";
		string s13 = getstring(it->GetvRruAntennaIdInfo());
		string s131 = ",EquipPower = ";
		string s14 = getstring(it->GetvEquipPowerInfo());
		string s15 = ",Rate = ";
		string s151 = getstring(it->GetvAverageRateInfo());
		string s33 = " where RruId = ";
		string s2 = getstring(it->GetvRruIdInfo());
		string s16 = s1 + s21 + s3 + s31 + s4 + s41 + s5 + s51 + s6 + s61 + s7 + s71 + s8 + s81 + s9 + s91 + s10 + s101 + s11 + s111 + s12 + s121 + s13 + s131 + s14 + s15 + s151 + s33 + s2;
		//cout<<s15<<endl;
		char * s17 = (char *)s16.c_str();
		pdb.Execute(s17);
		//cout<<pdb.GetRowsAffected()<<endl;
	}
	while (!vRruList.empty())
	{
		vRruList.pop_back();
	}
	return 1;
}


bool NetworkManager::BbuDataSave()
{
	vector<Bbu>::iterator it;
	for (it = vBbuList.begin(); it != vBbuList.end(); it++)
	{
		string s1 = "Update Bbu Set ";
		string s2 = "BbuPoolId = ";
		string s3 = getstring(it->GetvBbuPoolIdInfo());
		string s4 = ",X = ";
		string s5 = getstring(it->GetvXInfo());
		string s6 = ",Y = ";
		string s7 = getstring(it->GetvYInfo());
		string s8 = ",Z = ";
		string s9 = getstring(it->GetvZInfo());
		string s10 = ",RruNum = ";
		string s11 = getstring(it->GetvRruNumInfo());
		string s12 = ",SchedualRruMode = ";
		string s13 = getstring(it->GetvSchedualRruModeInfo());
		string s14 = ",TransPower = ";
		string s15 = getstring(it->GetvTransPowerInfo());
		string s16 = ",EquipPower = ";
		string s17 = getstring(it->GetvEquipPowerInfo());
		string s18 = ",IsActivity = ";
		string s19 = getstring(it->GetvIsActivityInfo());
		string s20 = ",Res = ";
		string s21 = getstring(it->GetvResInfo());
		string s22 = ",LinkId = ";
		string s23 = getstring(it->GetvLinkIdInfo());
		string s24 = ",Efficiency = ";
		string s25 = getstring(it->GetvEfficiencyInfo());
		string s26 = ",ResUtilizationRate = ";
		string s27 = getstring(it->GetvResUtilizationRateInfo());
		string s28 = ",Consume = ";
		string s29 = getstring(it->GetvConsumeInfo());
		string s30 = " where BbuId = ";
		string s31 = getstring(it->GetvBbuIdInfo());
		string s32 = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10 + s11 + s12 + s13 + s14 + s15 + s16 + s17 + s18 + s19 + s20 + s21 + s22 + s23 + s24 + s25 + s26 + s27 + s28 + s29 + s30 + s31;
		//cout<<s32<<endl;
		char * s33 = (char *)s32.c_str();
		pdb.Execute(s33);
		//system("pause");
		//cout<<pdb.GetRowsAffected()<<endl;
	}
	while (!vBbuList.empty())
	{
		vBbuList.pop_back();
	}
	return 1;
}

bool NetworkManager::BbuPoolDataSave()
{
	vector<BbuPool>::iterator it;
	for (it = vBbuPoolList.begin(); it != vBbuPoolList.end(); it++)
	{
		string s1 = "Update BbuPool Set ";
		string s21 = "X = ";
		string s3 = getstring(it->GetvXInfo());
		string s31 = ",Y = ";
		string s4 = getstring(it->GetvYInfo());
		string s41 = ",Z = ";
		string s5 = getstring(it->GetvZInfo());
		string s51 = ",AllRes = ";
		string s6 = getstring(it->GetvAllResInfo());
		string s61 = ",ResLeft = ";
		string s7 = getstring(it->GetvResLeftInfo());
		string s71 = ",DynamicEnengy = ";
		string s8 = getstring(it->GetvDynamicEnengyInfo());
		string s81 = ",StaticEnengy = ";
		string s9 = getstring(it->GetvStaticEnengyInfo());
		string s10 = " where BbuPoolId = ";
		string s2 = getstring(it->GetvBbuPoolIdInfo());
		string s13 = s1 + s21 + s3 + s31 + s4 + s41 + s5 + s51 + s6 + s61 + s7 + s71 + s8 + s81 + s9 + s10 + s2;
		//cout<<s13<<endl;
		char * s14 = (char *)s13.c_str();
		pdb.Execute(s14);
		//cout<<pdb.GetRowsAffected()<<endl;
	}
	while (!vBbuPoolList.empty())
	{
		vBbuPoolList.pop_back();
	}
	return 1;
}

bool NetworkManager::LinkPathDataSave(vector<LinkPath> vLinkPathList, string name)
{
	vector<LinkPath>::iterator it;
	for (it = vLinkPathList.begin(); it != vLinkPathList.end(); it++)
	{
		string s1 = "Insert into " + name + " values( ";
		string s2 = getstring(it->GetvLinkPathIdInfo());
		string s21 = ",  ";
		string s3 = getstring(it->GetvLinkEnd1Info());
		string s31 = ", ";
		string s4 = getstring(it->GetvLinkEnd2Info());
		string s41 = ", ";
		string s5 = getstring(it->GetvRealLengthInfo());
		string s51 = ",";
		string s6 = getstring(it->GetvLinkTypeInfo());
		string s61 = ",";
		string s7 = getstring(it->GetvMaxTransRateInfo());
		string s71 = ", ";
		string s8 = getstring(it->GetvAttenuationInfo());
		string s81 = ",";
		string s9 = getstring(it->GetvDelayInfo());
		string s91 = ", ";
		string s10 = getstring(it->GetvErrorRateInfo());
		string s101 = ",";
		string s11 = getstring(it->GetvCostInfo());
		string s111 = ", ";
		string s12 = getstring(it->GetvLinkCircleIdInfo());
		string s121 = ",";
		string s122 = getstring(it->GetvFibersNumInfo());
		string ss121 = ",";
		string ss122 = getstring(it->GetvNsInfo());
		string sss121 = ",";
		string sss122 = getstring(it->GetvLossInfo());
		string s33 = ")";
		string s13 = s1 + s2 + s21 + s3 + s31 + s4 + s41 + s5 + s51 + s6 + s61 + s7 + s71 + s8 + s81 + s9 + s91 + s10 + s101 + s11 + s111 + s12 + s121 + s122 + ss121 + ss122 + sss121 + sss122 + s33;
		//cout<<s13<<endl;
		char * s14 = (char *)s13.c_str();
		pdb.Execute(s14);
		//cout<<pdb.GetRowsAffected()<<endl;
	}
	while (!vLinkPathList.empty())
	{
		vLinkPathList.pop_back();
	}
	return 1;
}
bool NetworkManager::AddTTI(int tti)
{
	string s = "Update ControlParameter set TTI = " + getstring(tti + 1);
	char * s1 = (char *)s.c_str();
	pdb.Execute(s1);
	return 0;

}
bool NetworkManager::LinkDataSave()
{
	vector<Link>::iterator it;
	for (it = vLinkList.begin(); it != vLinkList.end(); it++)
	{
		string s1 = "Update Link Set ";
		string s81 = "Cost = ";
		string s9 = getstring(it->GetvCostInfo());
		string s10 = " where LinkId = ";
		string s2 = getstring(it->GetvLinkIdInfo());

		string s13 = s1 + s81 + s9 + s10 + s2;
		//cout<<s13<<endl;
		char * s14 = (char *)s13.c_str();
		pdb.Execute(s14);
		//cout<<pdb.GetRowsAffected()<<endl;

	}
	while (!vLinkList.empty())
	{
		vLinkList.pop_back();
	}
	return 1;
}
void  NetworkManager::GetWorkType()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s0 = "Select ModelType From WirelessLinkModel";
	char * s00 = (char *)s0.c_str();
	prs.Open(s00);
	long lData;
	lData = 0;
	prs.GetFieldValue(0, &lData);
	WirlessLinkModelType = lData;
	prs.Close();
}
void  NetworkManager::GetWorkType2()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s0 = "Select ModelType From ResSchedualModel";
	char * s00 = (char *)s0.c_str();
	prs.Open(s00);
	long lData1;
	lData1 = 0;
	prs.GetFieldValue(0, &lData1);
	ResSchedualType = lData1;
	prs.Close();
}
void NetworkManager::GetTTI()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s0 = "Select TTI From ControlParameter";
	char * s00 = (char *)s0.c_str();
	prs.Open(s00);
	long lData;
	lData = 0;
	prs.GetFieldValue(0, &lData);
	vTTI = lData;
	prs.Close();
}
void NetworkManager::UeMoveModelInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s0 = "Select * From UEModifyModel";
	char * s00 = (char *)s0.c_str();
	prs.Open(s00);
	while (!prs.IsEof())
	{
		long lData;
		double dblData;
		int len = 0;
		lData = 0;
		prs.GetFieldValue(2, &lData);
		vMoveKind = lData;

		lData = 0;
		prs.GetFieldValue(3, &lData);
		vVType = lData;

		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vVa = dblData;

		dblData = 0;
		prs.GetFieldValue(5, &dblData);
		vVb = dblData;

		dblData = 0;
		prs.GetFieldValue(6, &dblData);
		vM = dblData;

		dblData = 0;
		prs.GetFieldValue(7, &dblData);
		vS = lData;

		dblData = 0;
		prs.GetFieldValue(8, &dblData);
		vVaMax = lData;

		dblData = 0;
		prs.GetFieldValue(9, &dblData);
		vVbMin = dblData;

		dblData = 0;
		prs.GetFieldValue(10, &dblData);
		vDa = dblData;

		dblData = 0;
		prs.GetFieldValue(11, &dblData);
		vDb = dblData;

		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vBorderX = dblData;

		dblData = 0;
		prs.GetFieldValue(14, &dblData);
		vBorderY = dblData;
		prs.MoveNext();

	}
	prs.Close();
}

bool NetworkManager::UeDataInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s0 = "Select * From Ue";
	char * s00 = (char *)s0.c_str();
	prs.Open(s00);
	while (!prs.IsEof())
	{
		Ue *vUe = new Ue();
		long lData;
		double dblData;
		int len = 0;
		lData = 0;
		prs.GetFieldValue(0, &lData);
		vUe->SetvUeIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vUe->SetvUeTypeInfo(lData);

		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vUe->SetvXInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vUe->SetvYInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vUe->SetvZInfo(dblData);


		lData = 0;
		prs.GetFieldValue(5, &lData);
		vUe->SetvServiceRruIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(6, &lData);
		vUe->SetvRbNumInfo(lData);
		lData = 0;
		prs.GetFieldValue(7, &lData);
		vUe->SetvUeTransPowerInfo(lData);
		lData = 0;
		prs.GetFieldValue(8, &lData);
		vUe->SetvUeAntennaIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(9, &lData);
		vUe->SetvIsActivityInfo(lData);
		lData = 0;
		prs.GetFieldValue(10, &lData);
		vUe->SetvUeGroupIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(11, &lData);
		vUe->SetvModelTypeInfo(lData);
		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vUe->SetvSNRInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(13, &dblData);
		vUe->setvTotalBit(dblData);
		lData = 0;
		prs.GetFieldValue(14, &lData);
		vUe->setvTTISent(lData);
		dblData = 0;
		prs.GetFieldValue(15, &dblData);
		vUe->setvAverageRate(dblData);
		lData = 0;
		prs.GetFieldValue(16, &lData);
		vUe->SetvBbuIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(17, &lData);
		vUe->setvTotalRb(lData);

		dblData = 0;
		prs.GetFieldValue(18, &dblData);
		vUe->setvDis(dblData);
		lData = 0;
		prs.GetFieldValue(19, &lData);
		vUe->setvPriority(lData);

		lData = 0;
		prs.GetFieldValue(20, &lData);
		vUe->setvWorkType(lData);


		vUeList.push_back(*vUe);

		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}

bool NetworkManager::RruDataInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s3 = "Select * From Rru";
	prs.Open((char *)s3.c_str());

	while (!prs.IsEof())
	{
		Rru *vRru = new Rru();
		long lData;
		double dblData;
		int len = 0;

		lData = 0;
		prs.GetFieldValue(0, &lData);
		vRru->SetvRruIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vRru->SetvServiceBbuIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vRru->SetvRadiusInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vRru->SetvXInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vRru->SetvYInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(5, &dblData);
		vRru->SetvZInfo(dblData);


		lData = 0;
		prs.GetFieldValue(6, &lData);
		vRru->SetvRruTransPowerInfo(lData);
		lData = 0;
		prs.GetFieldValue(7, &lData);
		vRru->SetvRruBandwidthInfo(lData);
		lData = 0;
		prs.GetFieldValue(8, &lData);
		vRru->SetvUeNumInfo(lData);
		lData = 0;
		prs.GetFieldValue(9, &lData);
		vRru->SetvIsActivityInfo(lData);
		dblData = 0;
		prs.GetFieldValue(10, &dblData);
		vRru->SetvCarrierFrequentInfo(dblData);
		lData = 0;
		prs.GetFieldValue(11, &lData);
		vRru->SetvRruAntennaIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vRru->SetvEquipPowerInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(13, &dblData);
		vRru->SetvOptimeInfo(dblData);

		vRruList.push_back(*vRru);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}
bool NetworkManager::EstRruDataInit(int TTI)
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s1 = "select * from Rru left join (select * from EstBusiness where TTI = ";
	string s2 = s1 + getstring(TTI);
	string s3 = s2 + " )t on Rru.RruId = t.RruId ";
	char * s4 = (char *)s3.c_str();
	prs.Open(s4);

	while (!prs.IsEof())
	{
		Rru *vRru = new Rru();
		long lData;
		double dblData;
		int len = 0;

		lData = 0;
		prs.GetFieldValue(0, &lData);
		vRru->SetvRruIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vRru->SetvServiceBbuIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vRru->SetvRadiusInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vRru->SetvXInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vRru->SetvYInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(5, &dblData);
		vRru->SetvZInfo(dblData);


		lData = 0;
		prs.GetFieldValue(6, &lData);
		vRru->SetvRruTransPowerInfo(lData);
		lData = 0;
		prs.GetFieldValue(7, &lData);
		vRru->SetvRruBandwidthInfo(lData);
		lData = 0;
		prs.GetFieldValue(8, &lData);
		vRru->SetvUeNumInfo(lData);
		lData = 0;
		prs.GetFieldValue(9, &lData);
		vRru->SetvIsActivityInfo(lData);
		dblData = 0;
		prs.GetFieldValue(10, &dblData);
		vRru->SetvCarrierFrequentInfo(dblData);
		lData = 0;
		prs.GetFieldValue(11, &lData);
		vRru->SetvRruAntennaIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vRru->SetvEquipPowerInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(13, &dblData);
		vRru->SetvOptimeInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(17, &dblData);
		vRru->SetvBusinessInfo(dblData);

		vRruList.push_back(*vRru);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}

bool NetworkManager::BbuDataInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s3 = "Select * From Bbu";
	prs.Open((char *)s3.c_str());

	while (!prs.IsEof())
	{
		Bbu *vBbu = new Bbu();
		long lData;
		double dblData;
		int len = 0;

		lData = 0;
		prs.GetFieldValue(0, &lData);
		vBbu->SetvBbuIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vBbu->SetvBbuPoolIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vBbu->SetvXInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vBbu->SetvYInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vBbu->SetvZInfo(dblData);

		lData = 0;
		prs.GetFieldValue(5, &lData);
		vBbu->SetvRruNumInfo(lData);
		lData = 0;
		prs.GetFieldValue(6, &lData);
		vBbu->SetvSchedualRruModeInfo(lData);
		dblData = 0;
		prs.GetFieldValue(7, &dblData);
		vBbu->SetvTransPowerInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(8, &dblData);
		vBbu->SetvEquipPowerInfo(dblData);
		lData = 0;
		prs.GetFieldValue(9, &lData);
		vBbu->SetvIsActivityInfo(lData);
		dblData = 0;
		prs.GetFieldValue(10, &dblData);
		vBbu->SetvResInfo(dblData);

		lData = 0;
		prs.GetFieldValue(11, &lData);
		vBbu->SetvLinkIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vBbu->SetvOptimeInfo(dblData);

		vBbuList.push_back(*vBbu);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}

bool NetworkManager::BbuPoolDataInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s3 = "Select * From BbuPool";
	prs.Open((char *)s3.c_str());

	while (!prs.IsEof())
	{
		BbuPool *vBbuPool = new BbuPool();
		long lData;
		double dblData;
		int len = 0;

		lData = 0;
		prs.GetFieldValue(0, &lData);
		vBbuPool->SetvBbuPoolIdInfo(lData);
		dblData = 0;
		prs.GetFieldValue(1, &dblData);
		vBbuPool->SetvXInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vBbuPool->SetvYInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vBbuPool->SetvZInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vBbuPool->SetvAllResInfo(dblData);

		dblData = 0;
		prs.GetFieldValue(5, &dblData);
		vBbuPool->SetvResLeftInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(6, &dblData);
		vBbuPool->SetvDynamicEnengyInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(7, &dblData);
		vBbuPool->SetvStaticEnengyInfo(dblData);

		vBbuPoolList.push_back(*vBbuPool);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}

bool NetworkManager::LinkPathDataInit(vector<LinkPath> vLinkPathList, string name)
{
	CODBCRecordset prs = CODBCRecordset(&pdb);

	string s1 = "Select * From ";
	string s3 = s1 + name;
	char * s4 = (char *)s3.c_str();
	prs.Open(s4);

	while (!prs.IsEof())
	{
		LinkPath *vLinkPath = new LinkPath();

		long lData;
		double dblData;
		int len = 0;

		lData = 0;
		prs.GetFieldValue(0, &lData);
		vLinkPath->SetvLinkPathIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vLinkPath->SetvLinkEnd1Info(lData);
		lData = 0;
		prs.GetFieldValue(2, &lData);
		vLinkPath->SetvLinkEnd2Info(lData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vLinkPath->SetvRealLengthInfo(dblData);
		lData = 0;
		prs.GetFieldValue(4, &lData);
		vLinkPath->SetvLinkTypeInfo(lData);

		dblData = 0;
		prs.GetFieldValue(5, &dblData);
		vLinkPath->SetvMaxTransRateInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(6, &dblData);
		vLinkPath->SetvAttenuationInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(7, &dblData);
		vLinkPath->SetvDelayInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(8, &dblData);
		vLinkPath->SetvErrorRateInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(9, &dblData);
		vLinkPath->SetvCostInfo(dblData);
		lData = 0;
		prs.GetFieldValue(10, &lData);
		vLinkPath->SetvLinkCircleIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(10, &lData);
		vLinkPath->SetvFibersNumInfo(lData);
		dblData = 0;
		prs.GetFieldValue(11, &dblData);
		vLinkPath->SetvNsInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vLinkPath->SetvLossInfo(dblData);

		vLinkPathList.push_back(*vLinkPath);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}

bool NetworkManager::LinkDataInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s1 = "Select * From Link";
	char * s4 = (char *)s1.c_str();
	prs.Open(s4);
	while (!prs.IsEof())
	{
		Link *vLink = new Link();
		long lData;
		double dblData;
		int len = 0;

		lData = 0;
		prs.GetFieldValue(0, &lData);
		vLink->SetvLinkIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vLink->SetvLinkTypeInfo(lData);

		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vLink->SetvX1Info(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vLink->SetvY1Info(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vLink->SetvZ1Info(dblData);
		prs.GetFieldValue(5, &dblData);
		vLink->SetvX2Info(dblData);
		dblData = 0;
		prs.GetFieldValue(6, &dblData);
		vLink->SetvY2Info(dblData);
		dblData = 0;
		prs.GetFieldValue(7, &dblData);
		vLink->SetvZ2Info(dblData);
		dblData = 0;
		prs.GetFieldValue(8, &dblData);
		vLink->SetvLongRadiusInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(9, &dblData);
		vLink->SetvShortRadiusInfo(dblData);
		lData = 0;
		prs.GetFieldValue(10, &lData);
		vLink->SetvAccessPointNumInfo(lData);
		dblData = 0;
		prs.GetFieldValue(11, &dblData);
		vLink->SetvCostInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(12, &dblData);
		vLink->SetvRemainResInfo(dblData);

		vLinkList.push_back(*vLink);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}


void NetworkManager::PrintUe()
{
	vector<Ue>::iterator it;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		std::cout << it->GetvUeIdInfo() << " ";
		std::cout << it->GetvUeTypeInfo() << " ";
		std::cout << it->GetvXInfo() << " ";
		std::cout << it->GetvYInfo() << " ";
		std::cout << it->GetvZInfo() << " ";
		std::cout << it->GetvServiceRruIdInfo() << " ";
		std::cout << it->GetvRbNumInfo() << " ";
		std::cout << it->GetvUeTransPowerInfo() << " ";
		std::cout << it->GetvUeAntennaIdInfo() << " ";
		std::cout << it->GetvIsActivityInfo() << " ";
		std::cout << it->GetvUeGroupIdInfo() << " ";
		std::cout << it->GetvSNRInfo() << " ";
		std::cout << it->getvAverageRate() << " ";
		std::cout << it->getvTotalBit() << " ";
		std::cout << it->getvTTISent() << " ";
		std::cout << it->GetvBbuIdInfo() << " ";
		std::cout << it->getvTotalRb() << " ";
		std::cout << it->getvRate() << " ";
		std::cout << std::endl;
	}
}
void NetworkManager::PrintRru()
{
	vector<Rru>::iterator it;
	for (it = vRruList.begin(); it != vRruList.end(); it++)
	{
		std::cout << it->GetvRruIdInfo() << " ";
		std::cout << it->GetvServiceBbuIdInfo() << " ";
		std::cout << it->GetvRadiusInfo() << " ";
		std::cout << it->GetvXInfo() << " ";
		std::cout << it->GetvYInfo() << " ";
		std::cout << it->GetvZInfo() << " ";
		std::cout << it->GetvRruTransPowerInfo() << " ";
		std::cout << it->GetvRruBandwidthInfo() << " ";
		std::cout << it->GetvUeNumInfo() << " ";
		std::cout << it->GetvIsActivityInfo() << " ";
		std::cout << it->GetvCarrierFrequentInfo() << " ";
		std::cout << it->GetvRruAntennaIdInfo() << " ";
		std::cout << it->GetvEquipPowerInfo() << " ";
		std::cout << it->GetvAverageRateInfo() << " ";
		std::cout << std::endl;
	}
}
void NetworkManager::PrintBbu()
{
	vector<Bbu>::iterator it;
	for (it = vBbuList.begin(); it != vBbuList.end(); it++)
	{
		std::cout << it->GetvBbuIdInfo() << " ";
		std::cout << it->GetvBbuPoolIdInfo() << " ";
		std::cout << it->GetvXInfo() << " ";
		std::cout << it->GetvYInfo() << " ";
		std::cout << it->GetvZInfo() << " ";
		std::cout << it->GetvRruNumInfo() << " ";
		std::cout << it->GetvSchedualRruModeInfo() << " ";
		std::cout << it->GetvTransPowerInfo() << " ";
		std::cout << it->GetvEquipPowerInfo() << " ";
		std::cout << it->GetvIsActivityInfo() << " ";
		std::cout << it->GetvResInfo() << " ";
		std::cout << it->GetvEfficiencyInfo() << " ";
		std::cout << std::endl;
	}
}
void NetworkManager::PrintBbuPool()
{
	vector<BbuPool>::iterator it;
	for (it = vBbuPoolList.begin(); it != vBbuPoolList.end(); it++)
	{
		std::cout << it->GetvBbuPoolIdInfo() << " ";
		std::cout << it->GetvXInfo() << " ";
		std::cout << it->GetvYInfo() << " ";
		std::cout << it->GetvZInfo() << " ";
		std::cout << it->GetvAllResInfo() << " ";
		std::cout << it->GetvResLeftInfo() << " ";
		std::cout << it->GetvDynamicEnengyInfo() << " ";
		std::cout << it->GetvStaticEnengyInfo() << " ";
		std::cout << std::endl;
	}
}
void NetworkManager::PrintLink()
{
	vector<Link>::iterator it;
	for (it = vLinkList.begin(); it != vLinkList.end(); it++)
	{
		std::cout << it->GetvLinkIdInfo() << " ";
		std::cout << it->GetvLinkTypeInfo() << " ";
		std::cout << it->GetvX1Info() << " ";
		std::cout << it->GetvY1Info() << " ";
		std::cout << it->GetvZ1Info() << " ";
		std::cout << it->GetvX2Info() << " ";
		std::cout << it->GetvY2Info() << " ";
		std::cout << it->GetvZ2Info() << " ";
		std::cout << it->GetvLongRadiusInfo() << " ";
		std::cout << it->GetvShortRadiusInfo() << " ";
		std::cout << it->GetvAccessPointNumInfo() << " ";
		std::cout << it->GetvCostInfo() << " ";
		std::cout << std::endl;
	}
}
void NetworkManager::PrintLinkPath(vector<LinkPath> vLinkPathList)
{
	vector<LinkPath>::iterator it;
	for (it = vLinkPathList.begin(); it != vLinkPathList.end(); it++)
	{
		std::cout << it->GetvLinkPathIdInfo() << " ";
		std::cout << it->GetvLinkEnd1Info() << " ";
		std::cout << it->GetvLinkEnd2Info() << " ";
		std::cout << it->GetvRealLengthInfo() << " ";
		std::cout << it->GetvLinkTypeInfo() << " ";
		std::cout << it->GetvMaxTransRateInfo() << " ";
		std::cout << it->GetvAttenuationInfo() << " ";
		std::cout << it->GetvDelayInfo() << " ";
		std::cout << it->GetvErrorRateInfo() << " ";
		std::cout << it->GetvCostInfo() << " ";
		std::cout << it->GetvLinkCircleIdInfo() << " ";
		std::cout << it->GetvFibersNumInfo() << " ";
		std::cout << std::endl;
	}
}

int NetworkManager::ReConnectUe2Rru(int UeId, int NewRruId)
{
	vector<Ue>::iterator it;
	int vOldRruId = -1;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		if (it->GetvUeIdInfo() == UeId)
		{
			vOldRruId = it->GetvServiceRruIdInfo();
			it->SetvServiceRruIdInfo(NewRruId);
			break;
		}
	}
	if (it == vUeList.end()) return 1;
	if (vOldRruId != NewRruId)
	{
		vector<Rru>::iterator it2;
		for (it2 = vRruList.begin(); it2 != vRruList.end(); it2++)
		{
			if (it2->GetvRruIdInfo() == NewRruId)
				it2->SetvUeNumInfo(it2->GetvUeNumInfo() + 1);
			else if (it2->GetvRruIdInfo() == vOldRruId)
				it2->SetvUeNumInfo(it2->GetvUeNumInfo() - 1);

		}
	}
	return 0;
}

int NetworkManager::ReConnectRru2Bbu(int RruId, int NewBbuId)
{
	vector<Rru>::iterator it;
	int vOldBbuId = -1;
	for (it = vRruList.begin(); it != vRruList.end(); it++)
	{
		if (it->GetvRruIdInfo() == RruId)
		{
			vOldBbuId = it->GetvServiceBbuIdInfo();
			it->SetvServiceBbuIdInfo(NewBbuId);
			break;
		}
	}
	if (it == vRruList.end()) return 1;
	if (vOldBbuId != NewBbuId)
	{
		vector<Bbu>::iterator it2;
		for (it2 = vBbuList.begin(); it2 != vBbuList.end(); it2++)
		{
			if (it2->GetvBbuIdInfo() == NewBbuId)
				it2->SetvRruNumInfo(it2->GetvRruNumInfo() + 1);
			else if (it2->GetvBbuIdInfo() == vOldBbuId)
				it2->SetvRruNumInfo(it2->GetvRruNumInfo() - 1);

		}
	}
	return 0;
}

int NetworkManager::ReConnectBbu2BbuPool(int BbuId, int NewBbuPoolId)
{
	vector<Bbu>::iterator it;
	for (it = vBbuList.begin(); it != vBbuList.end(); it++)
	{
		if (it->GetvBbuIdInfo() == BbuId)
		{
			it->SetvBbuPoolIdInfo(NewBbuPoolId);
			break;
		}
	}
	if (it == vBbuList.end()) return 1;
	return 0;
}
bool NetworkManager::AccessPointDataInit()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s3 = "Select * From AccessPoint";
	prs.Open((char *)s3.c_str());

	while (!prs.IsEof())
	{
		AccessPoint *vAP = new AccessPoint();
		long lData;
		double dblData;
		int len = 0;
		lData = 0;
		prs.GetFieldValue(0, &lData);
		vAP->SetvAccessPointIdInfo(lData);
		lData = 0;
		prs.GetFieldValue(1, &lData);
		vAP->SetvLinkIdInfo(lData);

		dblData = 0;
		prs.GetFieldValue(2, &dblData);
		vAP->SetvXInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(3, &dblData);
		vAP->SetvYInfo(dblData);
		dblData = 0;
		prs.GetFieldValue(4, &dblData);
		vAP->SetvZInfo(dblData);

		vAccessPointList.push_back(*vAP);
		prs.MoveNext();

	}
	prs.Close();
	//pdb.Close();

	return 0;
}
void NetworkManager::Last5PercentRate(vector<Ue> &vUeList, int TTI)
{
	int length = vUeList.size() / 2;
	cout << length << endl;
	//system("pause");
	int Size = vUeList.size();
	double *a = new double[length];

	for (int i = 0; i < length; i++)
	{
		if (i == 0)
			a[i] = vUeList[i].getvAverageRate();
		else if (vUeList[i].getvAverageRate() > a[i - 1])
		{
			a[i] = vUeList[i].getvAverageRate();

		}
		else
		{
			for (int j = 0; j < i; j++)                  //插入排序
				if (vUeList[i].getvAverageRate() < a[j])
				{
				for (int k = i; k > j; k--)
					a[k] = a[k - 1];
				a[j] = vUeList[i].getvAverageRate();
				break;
				}

		}
		//system("pause");
	}
	for (int i = length; i < Size; i++)
	{
		for (int j = 0; j < length; j++)                  //插入排序
			if (vUeList[i].getvAverageRate() < a[j])
			{
			for (int k = length - 1; k > j; k--)
				a[k] = a[k - 1];
			a[j] = vUeList[i].getvAverageRate();
			break;
			}
	}
	double all = 0;

	for (int m = 0; m < length; m++)
	{
		cout << a[m] << endl;
		all = all + a[m];
	}
	string s13 = "insert into Last5PercentRate values(" + getstring(TTI) + " , " + getstring(all / length) + ")";
	char * s14 = (char *)s13.c_str();
	pdb.Execute(s14);
}
void NetworkManager::SNRCount(vector<Ue> &vUeList, int TTI)
{
	int LN6DB = 0;
	int BN6L3DB = 0;
	int B3L20DB = 0;
	int B20DB = 0;
	vector<Ue>::iterator it;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		if (it->GetvSNRInfo() < -6)
			LN6DB++;
		else if (it->GetvSNRInfo() >= -6 && it->GetvSNRInfo() < 3)
			BN6L3DB++;
		else if (it->GetvSNRInfo() >= 3 && it->GetvSNRInfo() < 20)
			B3L20DB++;
		else if (it->GetvSNRInfo() >= 20)
			B20DB++;
	}
	string s13 = "insert into SNRCount values(" + getstring(TTI) + " , " + getstring(LN6DB) + "," + getstring(BN6L3DB) + "," + getstring(B3L20DB) + "," + getstring(B20DB) + ")";
	char * s14 = (char *)s13.c_str();
	pdb.Execute(s14);
}
void NetworkManager::Efficiency(vector<Ue> &vUeList, vector<Bbu>&vBbuList, int TTI, int Time)//总频谱效率
{
	double AllUeBit = 0;
	double AllBbuRes = 0;
	vector<Bbu>::iterator it2;
	for (it2 = vBbuList.begin(); it2 != vBbuList.end(); it2++)
	{
		AllBbuRes = AllBbuRes + it2->GetvResInfo();
		cout << AllBbuRes << "Bbu" << endl;
	}
	vector<Ue>::iterator it;
	for (it = vUeList.begin(); it != vUeList.end(); it++)
	{
		AllUeBit = AllUeBit + it->getvTotalBit();
	}
	double Efficiency = AllUeBit / (AllBbuRes*Time);
	string s13 = "Insert into Efficiency values(" + getstring(TTI) + "," + getstring(Efficiency) + ")";
	char * s14 = (char *)s13.c_str();
	pdb.Execute(s14);
}

void NetworkManager::ConsumeSum(vector<Bbu>&vBbuList, vector<Rru>&vRruList, int TTI)//计算总能耗
{
	double ConsumeSum = 0;
	vector<Bbu>::iterator it2;
	for (it2 = vBbuList.begin(); it2 != vBbuList.end(); it2++)
	{
		ConsumeSum = ConsumeSum + it2->GetvConsumeInfo() + it2->GetvEquipPowerInfo();
	}
	vector<Rru>::iterator it;
	for (it = vRruList.begin(); it != vRruList.end(); it++)
	{
		ConsumeSum = ConsumeSum + it->GetvEquipPowerInfo();
	}
	string s13 = "Insert into ConsumeSum values(" + getstring(TTI) + "," + getstring(ConsumeSum) + ")";
	char * s14 = (char *)s13.c_str();
	pdb.Execute(s14);
	}
void NetworkManager::GetBusinessType()
{
	CODBCRecordset prs = CODBCRecordset(&pdb);
	string s3 = "Select BusinessType From BusinessModel";
	prs.Open((char *)s3.c_str());
	long lData1;
	lData1 = 0;
	prs.GetFieldValue(0, &lData1);
	BusinessType = lData1;
	prs.Close();
}

#endif