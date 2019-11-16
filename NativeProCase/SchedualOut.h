#ifndef schedualOut_H
#define schedualOut_H
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "UserRequest.h"
#include "Ue.h"
using namespace std;


void schedualOut(vector<UserRequest> &temp, vector<Ue> &vUeList)
{
	vector<UserRequest>::iterator it;
	for (it = temp.begin(); it != temp.end(); it++)
	{
		vector<Ue>::iterator it2;
		for (it2 = vUeList.begin(); it2 != vUeList.end(); it2++)
		{
			if (it2->GetvUeIdInfo() == it->getvUserId())
			{
				it2->setvAverageRate(it->getvAverageRate());
				it2->setvTotalBit(it->getvTotalBit());
				it2->setvTotalRb(it->getvTotalRb());
				it2->setvPriority(it->getPriority());
				it2->setvRate(it->getvSpeed());
			}
		}
	}
};
#endif