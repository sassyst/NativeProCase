//#include "Cost231Hata.h"
#include "Cost231HataM.h"
#include "FreeSpaceModel.h"
#include "LeeModel.h"
#include <iostream>

using namespace std;
int main()
{
	int i;
	double j;
	cout << "��������Ҫ���Ե�ģ�͵ı�ţ�" << endl << "       1�����ɿռ�ģ�ͣ�2��Leeģ�ͣ�3��Hata231ģ�ͣ�4��Hata231����ģ�ͣ�" << endl << "     0:�˳����������ɿռ�ģ�ͣ������룺1��" << endl;
	cin >> i;
	while (i != 0){
		switch (i){
		case 1:
			FreeSpaceModel F1;
			cout << "FreeSpace Model" << endl;
			cout << "���������D(Km)" << endl;
			cin >> j;
			F1.SetvFreeSpaceModelD(j);
			cout << "set D = " << F1.GetvFreeSpaceModelD() << endl;
			cout << "������Ƶ��F(MHz)" << endl;
			cin >> j;
			F1.SetvFreeSpaceModelF(j);
			cout << "set F = " << F1.GetvFreeSpaceModelF() << endl;
			cout << "Pl = " << F1.GetFreeSpaceModelPl() << endl << endl;
			break;
		case 2:
			LeeModel L1;
			cout << "LeeModel" << endl;
			cout << "���������D(Km)" << endl;
			cin >> j;
			L1.SetvLeeModelD(j);
			cout << "set D = " << L1.GetvLeeModelD() << endl;
			cout << "������߶�H(Km)" << endl;
			cin >> j;
			L1.SetvLeeModelH(j);
			cout << "set H = " << L1.GetvLeeModelH() << endl;
			cout << "Pl = " << L1.GetLeeModelPl() << endl << endl;
			break;

		case 3:
			Cost231Hata C1;
			cout << "Cost231HataModel" << endl;
			cout << "���������D(Km)" << endl;
			cin >> j;
			C1.SetvCost231HataD(j);
			cout << "set D =" << C1.GetvCost231HataD() << "�����룩" << endl;
			cout << "������������Ч�߶�Hb(Km)" << endl;
			cin >> j;
			C1.SetvCost231HataHb(j);
			cout << "set Hb = " << C1.GetvCost231HataHb() << "����Ч���߸߶ȣ�" << endl;
			cout << "����������ʵ�ʸ߶�Hm(Km)" << endl;
			cin >> j;
			C1.SetvCost231HataHm(j);
			cout << "set Hm = " << C1.GetvCost231HataHm() << "��ʵ�����߸߶ȣ�" << endl;
			cout << "������Ƶ��f��Hz��ע����f>400MHzΪ����У�f<200MHzΪС���У�f������֮��Ϊ��С���У�" << endl;
			cin >> j;
			C1.SetvCost231HataF(j);
				cout << "set F =" << C1.GetvCost231HataF() << endl;
				cout << "Pl = " << C1.GetCost231HataPl1() << endl << endl;
			break;

		case 4:
			Cost231HataM C2;
			cout << "Cost231Hata����Model" << endl;
			cout << "���������D��m��" << endl;
			cin >> j;
			C2.SetvCost231HataD(j);
			cout << "set D =" << C2.GetvCost231HataD() << "�����룩" << endl;
			cout << "������������Ч�߶�Hb��m��" << endl;
			cin >> j;
			C2.SetvCost231HataHb(j);
			cout << "set Hb = " << C2.GetvCost231HataHb() << "����Ч���߸߶ȣ�" << endl;
			cout << "����������ʵ�ʸ߶�Hm��m��" << endl;
			cin >> j;
			C2.SetvCost231HataHm(j);
			cout << "set Hm = " << C2.GetvCost231HataHm() << "��ʵ�����߸߶ȣ�" << endl;
			//cout << "��С����Pl = " << C2.GetCost231HataPl1() << endl << endl;
			cout << "������Ƶ��f(MHz)" << endl;
			cin >> j;
			C2.SetvCost231HataF(j);
			//cout << "set F =" << C2.GetvCost231HataF() << endl;
			cout << "����Pl = " << C2.GetCost231HataPl1() << endl << endl;
			//cout << "set F =" << C2.GetvCost231HataF() << endl;
			cout << "����ũ��Pl = " << C2.GetCost231HataPl2() << endl << endl;
			break;

		}
		system("pause");
		cout << "������������Ҫ���Ե�ģ�͵ı�ţ�"<<endl<<"       1�����ɿռ�ģ�ͣ�2��Leeģ�ͣ�3��Hata231ģ�ͣ�4��Hata231����ģ�ͣ�"<<endl<<"     0:�˳����������ɿռ�ģ�ͣ������룺1��" << endl;
		cin >> i;
	}
	return 0;
}