#ifndef SchedualEntity_H
#define SchedualEntity_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "UserRequest.h"
#include "SchedualOut.h"
#include <map>
using namespace std;


class SchedualEntity
{
private:
	int vRbNum;                                /*调度的总RB数目*/
	int vRbLeft;                               /*剩余RB数目*/
	//SchedualOut vSchedualResult;		       /*返回用户的输入结果*/
	int vBbuId;		 	                       /*基站的Id*/
	int vTti;		                           /*表示当前的TTI标志*/

public:
	SchedualEntity()
	{
		vRbNum = 100;
		vRbLeft = 100;
	};
	void ScheualEntity(int RbNum,int BbuId,int Tti)
	{
		vRbNum = RbNum;
		vBbuId = BbuId;
		vTti = Tti;

	};                                               /*构造函数*/
	int getvRbNum();
	int getvRbLeft();
	//SchedualOut getvSchedualResult();
	int getvBbuId();
	int getvTti();
	/*设置Bbu各项基本信息*/
	bool setvRbNum(int RbNum);
	bool setvRbLeft(int RbLeft);
	bool setvBbuId(int BbuId);
	bool setvTti(int Tti);

};



int  SchedualEntity::getvRbNum()
{
	return vRbNum;
}
int  SchedualEntity::getvRbLeft()
{
	return vRbLeft;
}
/*SchedualOut  SchedualEntity::getvSchedualResult()
{
	return vSchedualResult;
}*/
int  SchedualEntity::getvBbuId()
{
	return vBbuId;
}
int  SchedualEntity::getvTti()
{
	return vTti;
}



bool  SchedualEntity::setvRbNum(int RbNum)
{
	vRbNum = RbNum;
	return 1;
}
bool  SchedualEntity::setvRbLeft(int RbLeft)
{
	vRbLeft = RbLeft;
	return 1;
}
bool  SchedualEntity::setvBbuId(int BbuId)
{
	vBbuId = BbuId;
	return 1;
}
bool  SchedualEntity::setvTti(int Tti)
{
	vTti = Tti;
	return 1;
}



#endif