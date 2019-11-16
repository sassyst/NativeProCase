#ifndef BbuPoolResSchedule_H
#define BbuPoolResSchedule_H
#include "Bbu.h"
#include "BbuPool.h"
#include "Rru.h"
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <deque>
#include <list>
#include <map>
#include <vector>
#include <cstdlib>
#include <set>
#include <cctype>
#define ll long long
#define lson l,m,rt << 1
#define rson m+1,r,rt << 1 | 1
#define pi acos(-1)
#define INF 0x7f7f7f7f
#define Clear(name,init) memset(name,init,sizeof(name))
#define eps 1e-8
using namespace std;

const int M = 100;
int BBUResourceNum;
int RequitNum;
int L;
struct Basket {

	int ResourceNum;
	//int id[M];
	bool vis[M];
	int BBU_num;
	int cnt;
	int BBU[M];
	vector<int> vt[M];
	double Ratio;
	friend bool operator < (const Basket& a, const Basket& b) {
		return a.Ratio > b.Ratio;
	}
};

struct Requitment {

	int ResourceNum;
	int id;
	double UseRatio;

	friend bool operator < (const Requitment& a, const Requitment& b) {

		return a.UseRatio > b.UseRatio;

	}
}RequitResource[M];

double CalculateUseRatio(int x) {

	int temp = BBUResourceNum;
	while (temp < x) {
		temp += BBUResourceNum;
	}

	return (double)x / (double)temp;

}

bool cmp(Basket a, Basket b) {

	return a.BBU_num < b.BBU_num;
}

void BbuPoolResSchedule(vector<BbuPool> &poollist, vector<Bbu> &bbu, vector<Rru> &rru) {
	vector<Bbu> bbulist;//存储当前要使用BBU信息的容器
	vector<Rru> rrulist;//存储当前要使用RRU信息的容器
	Basket basket[M], used[M];
	BBUResourceNum = 91;      //公式计算出的每个BBU所含的最大资源
	//cout <<"good"<< endl;
	cout << poollist.size() << "poolsize" << endl;
	for (vector<Bbu>::iterator iter14 = bbu.begin(); iter14 != bbu.end(); iter14++)
	{
		iter14->SetvIsActivityInfo(0);
	}
	for (vector<BbuPool>::iterator iter1 = poollist.begin(); iter1 != poollist.end(); iter1++)
	{
		int poolnum;
		poolnum = iter1->GetvBbuPoolIdInfo();
		for (vector<Bbu>::iterator iter2 = bbu.begin(); iter2 != bbu.end(); iter2++)
		{
			
			if (poolnum == iter2->GetvBbuPoolIdInfo())
			{
				bbulist.push_back(*iter2);       //不知道语法是否有错
				//cout << iter2->GetvBbuIdInfo()<<endl;
			}
		}
		for (vector<Rru>::iterator iter3 = rru.begin(); iter3 != rru.end(); iter3++)
		{
			for (vector<Bbu>::iterator iter4 = bbulist.begin(); iter4 != bbulist.end(); iter4++)
			{
				//cout << iter4->GetvBbuIdInfo() << endl;
				if (iter3->GetvServiceBbuIdInfo() == iter4->GetvBbuIdInfo())
					rrulist.push_back(*iter3);
			}
		}
		for (vector<Rru>::iterator iter10 = rrulist.begin(); iter10 != rrulist.end(); iter10++)
		{
			if (iter10->GetvAverageRateInfo() > BBUResourceNum)
				iter10->SetvAverageRateInfo(BBUResourceNum);
		}
		cout << bbulist.size() << "BBUsize" << endl;
		cout << rrulist.size() << "RRUsize" << endl;
		
		//system("pause");
		
		RequitNum = rrulist.size();  //得到一共有多少个RRU请求
		/*cout << "requitnumsize:" << rrulist.size() << endl << endl;
		for (vector<Rru>::iterator iter11 = rrulist.begin(); iter11 != rrulist.end(); iter11++)
		{
		cout << "rate:" << iter11->GetvAverageRateInfo() << endl;                     ////////////////////////////////////////////
		}*/

		/*
		printf("请输入每个BBU所含资源量和RRU的个数:\n");
		scanf("%d%d", &BBUResourceNum, &RequitNum);
		printf("请输入每个RRU的请求资源量，以空格隔开:\n");
		*/
		vector<Rru>::iterator iter = rrulist.begin();                // iter为rru迭代器
		for (int i = 1; i <= RequitNum; i++) {

			int tot;
			tot = iter->GetvAverageRateInfo();
			iter++;
			//scanf("%d", &tot);
			RequitResource[i].ResourceNum = tot;
			RequitResource[i].id = i;
			RequitResource[i].UseRatio = CalculateUseRatio(tot);
		}
		for (int i = 1; i <= RequitNum; i++) {
			if (RequitResource[i].ResourceNum > BBUResourceNum)
				RequitResource[i].ResourceNum = BBUResourceNum;
		}
		//printf("请输入算法的篮子数：\n");
		sort(RequitResource + 1, RequitResource + RequitNum + 1);
		L = 2;                              //预先设定篮子数
		//scanf("%d", &L);
		for (int i = 1; i <= L; i++) {

			basket[i].BBU_num = basket[i].cnt = 0;
			memset(basket[i].vis, false, sizeof(basket[i]).vis);
		}
		for (int i = 1; i <= L; i++) {
			basket[i].ResourceNum = RequitResource[i].ResourceNum;
			basket[i].vis[RequitResource[i].id] = true;
			basket[i].BBU_num++;
			basket[i].BBU[basket[i].cnt++] = RequitResource[i].id;
			basket[i].Ratio = RequitResource[i].UseRatio;
			basket[i].vt[basket[i].BBU_num].push_back(RequitResource[i].id);
		}
		/*for(int i = 1;i <= L; i++){
		for(int j = 0;j < basket[i].cnt; j++)
		printf("%d ", basket[i].BBU[j]);
		puts("");
		}*/
		int judge = 1;
		
		while (judge < RequitNum) {
			// puts("debug");
			int cas = 0;
			for (int i = 1; i <= L; i++) {

				int now_Resource = basket[i].ResourceNum;
				for (int j = 1; j <= RequitNum; j++) {
					if (basket[i].vis[RequitResource[j].id]) continue;
					int temp = now_Resource + RequitResource[j].ResourceNum;
					Basket now = basket[i];
					if (cas < L) {

						while (BBUResourceNum * now.BBU_num < temp) {
							now.BBU_num++;
						}
						now.vt[now.BBU_num].push_back(RequitResource[j].id);
						now.ResourceNum = temp;
						now.vis[RequitResource[j].id] = true;
						now.BBU[now.cnt++] = RequitResource[j].id;
						now.Ratio = CalculateUseRatio(temp);

						used[cas++] = now;
					}
					else {
						sort(used, used + L);
						while (BBUResourceNum * now.BBU_num < temp) {
							now.BBU_num++;
						}
						now.vt[now.BBU_num].push_back(RequitResource[j].id);
						now.ResourceNum = temp;
						now.vis[RequitResource[j].id] = true;
						now.BBU[now.cnt++] = RequitResource[j].id;
						now.Ratio = CalculateUseRatio(temp);

						if (now.Ratio > used[L - 1].Ratio) {
							used[L - 1] = now;
						}
					}
				}
			}
			sort(used, used + L);
			for (int i = 1; i <= L; i++) {
				basket[i] = used[i - 1];
			}
			judge++;
		}
		sort(basket + 1, basket + 1 + L, cmp);
		/* for(int i = 1;i <= L; i++){
		for(int j = 0;j < RequitNum; j++)
		printf("%d ", basket[i].BBU[j]);
		puts("");
		}*/
		//printf("The Least Number of BBU : %d\n", basket[1].BBU_num);
		//cout << "bbunum" << basket[1].BBU_num << endl;
		int k = 1;
		//system("pause");
		
		for (vector<Bbu>::iterator iter5 = bbulist.begin(); iter5 != bbulist.end(); iter5++)
		{
			if (iter5 < (bbulist.begin() + basket[1].BBU_num))
			{
				//cout << "it5" << endl;
				for (int j = 0; j < basket[1].vt[k].size(); j++)
				{
					vector<Rru>::iterator iter6 = rrulist.begin() + basket[1].vt[k][j] - 1;
					for (vector<Rru>::iterator iter7 = rru.begin(); iter7 != rru.end(); iter7++)
					{
						if (iter6->GetvRruIdInfo() == iter7->GetvRruIdInfo())
							iter7->SetvServiceBbuIdInfo(iter5->GetvBbuIdInfo());
						//cout << iter5->GetvBbuIdInfo() << "BBURRU" << iter7->GetvRruIdInfo() << endl;
					}
				}
				//cout << "it12" << endl;
				
				for (vector<Bbu>::iterator iter12 = bbu.begin(); iter12 != bbu.end(); iter12++)
				{
					if (iter5->GetvBbuIdInfo() == iter12->GetvBbuIdInfo())
						iter12->SetvIsActivityInfo(1);
				}
			}

			else
			{
				for (vector<Bbu>::iterator iter13 = bbu.begin(); iter13 != bbu.end(); iter13++)
				{
					if (iter5->GetvBbuIdInfo() == iter13->GetvBbuIdInfo())
						iter13->SetvIsActivityInfo(0);
				}
			}
			k++;
		}

		/*for (int i = 1; i <= basket[1].BBU_num; i++){
		printf("No.%d BBU :", i);
		for (int j = 0; j < basket[1].vt[i].size(); j++) {
		printf("%d ", basket[1].vt[i][j]);
		}
		puts("");
		}    */
		bbulist.clear();
		rrulist.clear();

	}
	for (vector<Rru>::iterator iter9 = rru.begin(); iter9 != rru.end(); iter9++)
	{
		cout << "rruid:" << iter9->GetvRruIdInfo() << endl;
		cout << "service bbuid:" << iter9->GetvServiceBbuIdInfo() << endl;
		cout << "rru rate:" << iter9->GetvAverageRateInfo() << endl << endl;
	}
	//system("pause");
}

#endif