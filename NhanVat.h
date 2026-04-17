#pragma once
#include <iostream>
#include <iomanip>
#include "VuKhi.h"
using namespace std;

class NhanVat {
private:
	string nameNV;
	int    hp;
	int    mana;
	int    manaMax;
	VuKhi *vk[3] ; // quan ly vu khi 
	int viTriDangDung ; // vi tri vu khi dang su dung 

public:
	NhanVat(string _name = "Khong ro", int _hp = 1000, int _mana = 1000 ,VuKhi* _vk[] = nullptr, int vt = 0){
		nameNV = _name;
		hp = _hp;
		mana = _mana;
		manaMax = _mana;
		for(int i = 0; i < 3; i++){
			vk[i] = (_vk ? _vk[i] : nullptr);
		}	
		viTriDangDung = vt;
	}
//	NhanVat(const NhanVat& x) {
//		nameNV = x.nameNV;
//		hp = x.hp;
//		mana = x.mana;
//		manaMax = x.manaMax;
//		viTriDangDung = x.viTriDangDung;
//		
//		for(int i = 0; i < 3; i++){
//			if(x.vk[i] != nullptr)
//				vk[i] = new VuKhi(*x.vk[i]);
//			else
//				vk[i] = nullptr;
//		}
//	}
	
	~NhanVat() {}
	
	//getset
	string	getName()		{ return nameNV; }
	int		getHp()			{ return hp; }
	int		getMana()		{ return mana; }
	int		getManaMax()	{ return manaMax; }
	int		getViTriDangDung() {return viTriDangDung;}
	
	void	setName(string _name)	{ nameNV = _name; }
	void	setHp(int _hp)			{ hp = (_hp < 0) ? 0 : _hp; }
	void 	setMana(int _mana)		{ mana = (_mana < 0) ? 0 : (_mana > manaMax ? manaMax : _mana); }
	void 	setViTriDangDung(int vitri) {
		viTriDangDung = vitri ; 
	}

	//hien thi menu trang bi
	void trangBiHienTai(){
		for (int i = 0; i < 3; i++) {
			cout << "[" << i+1 << "] "; vk[i]->TanCong();
		} 
	}
	
	// Doi vu khi dang dung

	
	// qua tai lay vu khi []
	VuKhi*& operator[](int index) {
//		if (index >= 0 && index < 3)
			return vk[index];
	}
	
	//fight
	// Tan cong bang vu khi dang dung
	int SatThuong(int t) {
		VuKhi* v = vk[viTriDangDung];
		if (v == nullptr) {
			cout << ">> [" << nameNV << "] Chua co vu khi!" << endl;
			return 0;
		}
		return v->SatThuong(t);
	}
	
	// Nhan sat thuong
	void BiTanCong(int st) {
		int hpTruoc = hp;
		hp -= st;
		if (hp < 0) hp = 0;
		cout << ">> " << nameNV << " bi tan cong\n";
		cout << "	HP: " << hpTruoc << " -> " << hp << endl;
	}
	
	// Phuc hoi mana
//	void PhucHoiMana(int luong = -1) {
//		if (luong == -1) mana = manaMax; // phuc hoi toan bo
//		else mana = min(manaMax, mana + luong);
//		cout << ">> [" << nameNV << "] Mana phuc hoi: " << mana << "/" << manaMax << endl;
//	}
	
	bool ConSong() { return hp > 0; }
	
	
	friend ostream& operator<<(ostream& out, NhanVat nv) {
		out << left << setw(20) << "Ten:"  << nv.nameNV << endl;
		out << left << setw(20) << "HP:"   << nv.hp     << endl;
		out << left << setw(20) << "Mana:" << nv.mana << "/" << nv.manaMax << endl;
		out << "========================================" << endl;
		return out;
	}
	
	friend istream& operator>>(istream& in, NhanVat& nv) {
		cout << "Nhap ten nhan vat: ";
		in.ignore();
		getline(in, nv.nameNV);
		cout << "Nhap HP: ";
		in >> nv.hp;
		cout << "Nhap Mana: ";
		in >> nv.mana;
		nv.manaMax = nv.mana;
		return in;
	}
};
