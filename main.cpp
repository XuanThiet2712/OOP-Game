#include <iostream>
#include <iomanip>
using namespace std;
#include "VuKhi.h"
#include "Sung.h"
#include "Kiem.h"
#include "PhepThuat.h"
#include "NhanVat.h"

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
} 
  
void hienThiGiaoDien(NhanVat& nr, NhanVat& p) {
	clearScreen(); 
	 
	cout << "========== MUC TIEU: " << nr.getName() << " ==========\n";
	cout << nr  ; 
	 
	cout << "PLAYER: " << p.getName()<< " | HP: " << p.getHp()<< " | Mana: " << p.getMana()<<"/"<< p.getManaMax()<< "\n";
	cout << "TRANG BI HIEN TAI:\n";
	p.trangBiHienTai();   //
	cout << "\n";
	
	cout << "===== Vu Khi Dang Su Dung =====\n";
	p[p.getViTriDangDung()]->inThongTin();
	cout << "\n";
	
	cout << "==============================\n";
	cout << "  1. Tan cong\n";
	cout << "  2. Doi vu khi\n";
	cout << "  3. Che tao lai vu khi\n";
	cout << "  0. Thoat\n";
	cout << "==============================\n";
	cout << "Lua chon: ";
}

int main() {
	// Khai bao 1 so vu khi mac dinh 
	Sung      sung("AK47",      35, 10.0f, 30, 2.0f);
	Kiem      kiem("Muramasa",  50,  2.0f, 100);
	PhepThuat phep("Amaterasu", 60,  1.0f, "Hoa");
	VuKhi *vk[3] = {&sung , &kiem , &phep};
	// khai bao muc tieu test dame nguoi rom va nguoi choi 
	NhanVat nr    ("Nguoi Rom",     10000, 0 );
	NhanVat player("Shadow Reaper", 10000, 500 , vk , 0);  // name , hp , mana , vu khi , 	
	int lua = -1;	
	while (lua != 0 && nr.ConSong()) {		
		hienThiGiaoDien(nr, player);
		cin >> lua;
		
		if (lua == 1) { 
			//TAN CONG 
			clearScreen();
			cout << "========== MUC TIEU: " << nr.getName() << " ==========\n";
			cout << nr;
//			cout << "========== PLAYER: " << player.getName() << " ==========\n";
//			cout << player ;
			cout << "PLAYER: " << player.getName()
			<< " | HP: " 	<< player.getHp()
			<< " | Mana: " 	<< player.getMana() << "/" << player.getManaMax() << "\n";
			cout << "===== TAN CONG =====\n";
			player[player.getViTriDangDung()]->TanCong();  
			cout << "\nNhap thoi gian tan cong (giay): ";
			int t; cin >> t;
			int damage = player.SatThuong(t);   
			cout << "\nSat thuong gay len " << nr.getName() << ": " << damage << "\n";
			if (damage > 0) {
				cout <<endl;
				nr.BiTanCong(damage);
				if (nr.ConSong())
					cout << "\n>> " << nr.getName() << " van song! HP: " << nr.getHp() << "\n";
				else
					cout << "\n>> " << nr.getName() << " da bi ha guc!\n";
			}
			cout << "\nNhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 2) {
			//DOI VU KHI 
			clearScreen();
			cout << "===== DOI VU KHI =====\n";
			player.trangBiHienTai();
			cout << "Lua chon (1-3): ";
			int chon; cin >> chon;
			player.setViTriDangDung(chon-1);
			cout << "\n>> Da chon:\n";
			player[player.getViTriDangDung()]->TanCong(); 
			cout << "\nNhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 3) {
		//CHE TAO VU KHI
			clearScreen();
			cout << "===== CHE TAO VU KHI =====\n";
			cout << "  1. Sung\n  2. Kiem\n  3. Phep Thuat\n";
			cout << "Lua chon: ";
			int chon; cin >> chon;
			switch (chon) {
				case 1: 
				cin >> sung; 
				player[0] = &sung ; 
				player.setViTriDangDung(0); 
				break;
				case 2: 
				cin >> kiem; 
				player[1] = &kiem ; 
				player.setViTriDangDung(1); 
				break;
				case 3: 
				cin >> phep; 
				player[2] = &phep ; 
				player.setViTriDangDung(2); 
				break;
				default: cout << "Lua chon khong hop le!\n"; break;
			}
			cout << "\n>> Che tao thanh cong!\n";
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 0) {
			clearScreen();
			cout << "Tam biet!\n";
			return 0;
		} 
		else {
			cout << "Lua chon khong hop le.\n";
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
	}
	
	if (!nr.ConSong()) {
		clearScreen();
		cout << "\n=============================\n"
		<< "  " << nr.getName() << " DA BI TIEU DIET!\n"
		<< "=============================\n";
	}
	
	return 0;
}
