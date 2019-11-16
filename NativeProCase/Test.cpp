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
	cout << "请输入需要测试的模型的编号：" << endl << "       1：自由空间模型；2：Lee模型；3：Hata231模型；4：Hata231修正模型；" << endl << "     0:退出；（如自由空间模型，请输入：1）" << endl;
	cin >> i;
	while (i != 0){
		switch (i){
		case 1:
			FreeSpaceModel F1;
			cout << "FreeSpace Model" << endl;
			cout << "请输入距离D(Km)" << endl;
			cin >> j;
			F1.SetvFreeSpaceModelD(j);
			cout << "set D = " << F1.GetvFreeSpaceModelD() << endl;
			cout << "请输入频率F(MHz)" << endl;
			cin >> j;
			F1.SetvFreeSpaceModelF(j);
			cout << "set F = " << F1.GetvFreeSpaceModelF() << endl;
			cout << "Pl = " << F1.GetFreeSpaceModelPl() << endl << endl;
			break;
		case 2:
			LeeModel L1;
			cout << "LeeModel" << endl;
			cout << "请输入距离D(Km)" << endl;
			cin >> j;
			L1.SetvLeeModelD(j);
			cout << "set D = " << L1.GetvLeeModelD() << endl;
			cout << "请输入高度H(Km)" << endl;
			cin >> j;
			L1.SetvLeeModelH(j);
			cout << "set H = " << L1.GetvLeeModelH() << endl;
			cout << "Pl = " << L1.GetLeeModelPl() << endl << endl;
			break;

		case 3:
			Cost231Hata C1;
			cout << "Cost231HataModel" << endl;
			cout << "请输入距离D(Km)" << endl;
			cin >> j;
			C1.SetvCost231HataD(j);
			cout << "set D =" << C1.GetvCost231HataD() << "（距离）" << endl;
			cout << "请输入天线有效高度Hb(Km)" << endl;
			cin >> j;
			C1.SetvCost231HataHb(j);
			cout << "set Hb = " << C1.GetvCost231HataHb() << "（有效天线高度）" << endl;
			cout << "请输入天线实际高度Hm(Km)" << endl;
			cin >> j;
			C1.SetvCost231HataHm(j);
			cout << "set Hm = " << C1.GetvCost231HataHm() << "（实际天线高度）" << endl;
			cout << "请输入频率f（Hz）注：（f>400MHz为大城市，f<200MHz为小城市，f在两者之间为中小城市）" << endl;
			cin >> j;
			C1.SetvCost231HataF(j);
				cout << "set F =" << C1.GetvCost231HataF() << endl;
				cout << "Pl = " << C1.GetCost231HataPl1() << endl << endl;
			break;

		case 4:
			Cost231HataM C2;
			cout << "Cost231Hata修正Model" << endl;
			cout << "请输入距离D（m）" << endl;
			cin >> j;
			C2.SetvCost231HataD(j);
			cout << "set D =" << C2.GetvCost231HataD() << "（距离）" << endl;
			cout << "请输入天线有效高度Hb（m）" << endl;
			cin >> j;
			C2.SetvCost231HataHb(j);
			cout << "set Hb = " << C2.GetvCost231HataHb() << "（有效天线高度）" << endl;
			cout << "请输入天线实际高度Hm（m）" << endl;
			cin >> j;
			C2.SetvCost231HataHm(j);
			cout << "set Hm = " << C2.GetvCost231HataHm() << "（实际天线高度）" << endl;
			//cout << "中小城镇Pl = " << C2.GetCost231HataPl1() << endl << endl;
			cout << "请输入频率f(MHz)" << endl;
			cin >> j;
			C2.SetvCost231HataF(j);
			//cout << "set F =" << C2.GetvCost231HataF() << endl;
			cout << "郊区Pl = " << C2.GetCost231HataPl1() << endl << endl;
			//cout << "set F =" << C2.GetvCost231HataF() << endl;
			cout << "开阔农村Pl = " << C2.GetCost231HataPl2() << endl << endl;
			break;

		}
		system("pause");
		cout << "请重新输入需要测试的模型的编号："<<endl<<"       1：自由空间模型；2：Lee模型；3：Hata231模型；4：Hata231修正模型；"<<endl<<"     0:退出；（如自由空间模型，请输入：1）" << endl;
		cin >> i;
	}
	return 0;
}