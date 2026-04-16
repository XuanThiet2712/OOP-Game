#include <iostream>
using namespace std;
#include "VuKhi.h"
#include "Sung.h"
#include "Kiem.h"
#include "PhepThuat.h"
#include "NguoiRom.h"

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void hienThiGiaoDien(NguoiRom& nr, VuKhi* vk[], int x, Sung& sung, Kiem& kiem, PhepThuat& phep) {
	clearScreen();
	
	// Header - Muc tieu nguoi rom
	cout << nr;
	cout << endl;
	
	// Gioi thieu vu khi
	cout << "PLAYER : SHADOW REAPER "<<endl;
	cout << "KHO VU KHI PLAYER :" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "[" << i+1 << "] "; vk[i]->TanCong();
	}
	cout << endl;
	
	// Vu khi dang su dung
	cout << "===== Vu Khi Dang Su Dung =====" << endl;
	switch (x) {
		case 0: cout << sung << endl; break;
		case 1: cout << kiem << endl; break;
		case 2: cout << phep << endl; break;
	}
	
	// Menu lua chon
	cout << "==============================" << endl;
	cout << "  1. Tan cong"   << endl;
	cout << "  2. Doi vu khi" << endl;
	cout << "  3. Che tao vu khi" << endl;
	cout << "  0. Thoat"      << endl;
	cout << "==============================" << endl;
	cout << "Lua chon: ";
}

int main() {
	NguoiRom nr(1000, 0.2f);
	
	// Khai bao 3 vu khi 
	Sung      sung("AK47", 35, 10, 30, 2);
	Kiem      kiem("Muramasa", 50, 2, 100);
	PhepThuat phep("Phep Thuat", 60, 1, "Hoa", 10);
	
	VuKhi* vk[3] = { &sung, &kiem, &phep };
	
	int lua = -1, x = 0;
	
	while (lua != 0 && nr.ConSong()) {
		
		hienThiGiaoDien(nr, vk, x, sung, kiem, phep);
		cin >> lua;
		
		if (lua == 1) {
			//TAN CONG
			clearScreen();
			cout<<nr;
			cout << "===== TAN CONG =====" << endl;
			vk[x]->TanCong();
			cout << endl;
			cout << "Nhap thoi gian tan cong (giay): ";
			int t; cin >> t;
			cout << endl;
			int damage = vk[x]->SatThuong(t);
			cout << endl;
			cout << "Sat thuong gay len nguoi rom: " << damage << endl;
			if (damage > 0) {
				cout << endl;
				nr.NhanSatThuong(damage);
				if (nr.ConSong())
					cout << endl << ">> Nguoi rom van song! HP: " << nr.getHp() << endl;
				else
					cout << endl << ">> Nguoi rom da bi ha guc!" << endl;
			}
			cout << endl << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 2) {
			//DOI VU KHI
			clearScreen();
			cout << "===== DOI VU KHI =====" << endl;
			cout << "	1. Sung" << endl;
			cout << "	2. Kiem" << endl;
			cout << "	3. Phep Thuat" << endl;
			cout << "Lua chon: ";
			int chon; cin >> chon;
			if (chon >= 1 && chon <= 3) x = chon - 1;
			cout << endl << ">> Da chon: "; vk[x]->TanCong();
			cout << endl << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 3) {
			//CHE TAO VU KHI
			clearScreen();
			cout << "===== CHE TAO VU KHI =====" << endl;
			cout << "	1. Sung" << endl;
			cout << "	2. Kiem" << endl;
			cout << "	3. Phep Thuat" << endl;
			cout << "Lua chon: ";
			int chon; cin >> chon;
			switch (chon) {
			case 1:
				cin >> sung;
				x = 0;
				break;
			case 2:
				cin >> kiem;
				x = 1;
				break;
			case 3:
				cin >> phep;
				x = 2;
				break;
			default:
				break;
			}
			cout << endl << ">> Che tao thanh cong!" << endl;
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 0) {
			clearScreen();
			cout << "Tam biet ban!" << endl;
			return 0;
		}
		else {
			cout << "Lua chon khong hop le, yeu cau nhap lai." << endl;
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
	}
	
	if (!nr.ConSong()) {
		clearScreen();
		cout << endl;
		cout << "=============================" << endl;
		cout << "  NGUOI ROM DA BI TIEU DIET! " << endl;
		cout << "=============================" << endl;
	}
	return 0;
}
