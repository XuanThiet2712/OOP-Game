#include <iostream>
using namespace std;
#include "VuKhi.h"
#include "Sung.h"
#include "Kiem.h"
#include "PhepThuat.h"
#include "NguoiRom.h"

int main() {
	NguoiRom nr(10000 , 0.2f);
	cout << nr;
	
	// Khai bao 3 vu khi 
	Sung		sung("AK47",35, 10, 30, 2);
	Kiem		kiem("Kiem Rong",50, 2, 100);
	PhepThuat	phep("Phep Thuat", 60,1,"Hoa", 10);
	
	VuKhi* vk[3] = { &sung, &kiem, &phep };
	
	// Gioi thieu vu khi
	cout <<endl<<"===== Gioi Thieu Vu Khi =====" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "[" << i+1 << "] "; vk[i]->TanCong();
		cout <<endl ; 
	}
	
	int lua = -1, idx = 0;
	
	while (lua != 0 && nr.ConSong()) {
		cout << endl;
		
//		cout << *vk[idx];
		switch (idx) {
		case 0:
			cout<<sung<<endl;
			break;
		case 1:
			cout<<kiem<<endl;
			break;
		case 2:
			cout<<phep<<endl;
			break;
		default:
			//TODO
			break;
		}
		vk[idx]->TanCong();
		cout<<endl;
		cout << "1.Tan cong"<<endl;
		cout << "2.Doi vu khi"<<endl;
		cout << "3.Che tao vu khi"<<endl;
		cout << "0.Thoat"<<endl;
		cout <<"Lua chon: ";
		cin >> lua;
		int t = 0 ; 
		if (lua == 1) {
			cout << "Nhap thoi gian tan cong (giay): "; cin >> t ; 
			int damage = vk[idx]->SatThuong(t);	
			cout << "Sat thuong gay len nguoi rom : " <<damage <<endl ; 
			if (damage > 0) {
				cout<<endl;
				nr.NhanSatThuong(damage);
				if (nr.ConSong())
					cout << ">> Nguoi rom van song! HP: " << nr.getHp() << endl;
				else
					cout << ">> Nguoi rom da bi ha guc!" << endl;
			}		
		} 
		else if (lua == 2) {
			cout << "Chon vu khi"<<endl ; 
			cout << "1.Sung --- 2.Kiem  --- 3.Phep Thuat"<<endl;
			cout << "Lua chon : ";
			int chon; cin >> chon;
			if (chon >= 1 && chon <= 3) idx = chon - 1;
			cout << ">> Da chon: "; vk[idx]->TanCong();
		}
		else if (lua == 3) {
			cout << "Chon vu khi ban muon che tao "<<endl ; 
			cout << "1.Sung \n2.Kiem  \n3.Phep Thuat"<<endl;
			int chon; cin >> chon;
			switch (chon) {
			case 1:
				cin >> sung ;
				break;
//			case 2:
//				cin >> kiem ; 
//				break;
//			case 3:
//				cin >> phep ; 
//				break;
			default:
//				cout << "Lua chon khong hop le !" <<endl;
				break;
			}
		}
		else if (lua == 0) {
			cout<<"Tam biet ban !";
			return 0 ;
		}
		else cout <<"Lua chon khong hop le , yeu cau nhap lai "<<endl;
	}
	
	if (!nr.ConSong()) {
		cout <<endl << "=============================" << endl;
		cout 		<< "  NGUOI ROM DA BI TIEU DIET! " << endl;
		cout 		<< "=============================" << endl;
	}
	return 0;
}
