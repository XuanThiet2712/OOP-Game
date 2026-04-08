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
		cout << "[" << i+1 << "] "; b[i]->TanCong();
	}
	
	int lua = -1, idx = 0;
	
	while (lua != 0 && nr.conSong()) {
		cout << endl;
		
		cout << *vk[idx];
		
		cout << "1.Tan cong"<<endl;
		cout << "2.Doi vu khi"<<endl;
		cout << "0.Thoat"<<endl;
		cout <<"Lua chon: ";
		cin >> lua;
		int t = 0 ; 
		if (lua == 1) {
			cout << "Nhap thoi gian tan cong (giay): "; cin >> t ; 
			int damage = vk[idx]->SatThuong(t);			
			if (damage > 0) {
				nr.NhanSatThuong(damage);
				if (nr.conSong())
					cout << ">> Nguoi rom van song! HP: " << nr.getHp() << endl;
				else
					cout << ">> Nguoi rom da bi ha guc!" << endl;
			}		
		} 
		else if (lua == 2) {
			cout << "Chon vu khi (1.Sung  2.Kiem  3.Phep Thuat): ";
			int chon; cin >> chon;
			if (chon >= 1 && chon <= 3) idx = chon - 1;
			cout << ">> Da chon: "; vk[idx]->TanCong();
		}
		else if (lua == 0) {
			cout<<"Tam biet ban !";
			return 0 ;
		}
		else cout <<"Lua chon khong hop le , yeu cau nhap lai "<<endl;
	}
	
	if (!nr.conSong()) {
		cout <<endl << "=============================" << endl;
		cout 		<< "  NGUOI ROM DA BI TIEU DIET! " << endl;
		cout 		<< "=============================" << endl;
	}
	return 0;
}
