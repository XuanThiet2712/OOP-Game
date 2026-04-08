#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std ; 

class NguoiRom{
	int hp ;
	float giap ; 
public :
	//constructor
	NguoiRom(int _hp = 1000 , float _giap = 0.0f){
		hp = _hp ; 
		giap = _giap ; 
	}
	~NguoiRom(){}
	//getset
	int getHp(){
		return hp ; 
	}
	float getGiap(){
		return giap ;
	}
	void setHp(int _hp){
		hp = _hp ; 
	}
	void setGiap(float _giap){
		giap = _giap ; 
	}
	//method 
	void NhanSatThuong(int st , float xg = 0);
	bool ConSong();
	friend istream& operator >> (istream& in , NguoiRom &nr);
	friend ostream& operator << (ostream& out , NguoiRom nr);
};

void NguoiRom::NhanSatThuong(int st, float xg){
	int damageThucTe = st * (giap - xg) ; 
	cout << "[Phong thu muc tieu]" << endl;
	cout << left << setw(30) << "  Giap ban dau: "   << (int)(giap * 100)       << "%" << endl;
	cout << left << setw(30) << "  Giap sau xuyen: " << (int)(giap - xg) << "%" << endl;
	cout << left << setw(30) << "  Giam boi giap: "  << st - damageThucTe   << endl;
	cout << "[Sat thuong thuc te]" << endl;
	cout << left << setw(30) << "  Damage gay len HP: " << damageThucTe << endl;
	int hpTruoc = hp;
	hp -= damageThucTe;
	if (hp < 0) hp = 0;
	cout << "[Nguoi rom]" << endl;
	cout << left << setw(30) << "  HP truoc: " << hpTruoc << endl;
	cout << left << setw(30) << "  HP sau:   " << hp      << endl;
}
bool NguoiRom::ConSong() { return hp > 0; }
istream& operator >> (istream& in , NguoiRom &nr){
	cout << "Nhap HP nguoi rom: ";
	cin >> nr.hp;
	float giapPhanTram;
	cout << "Nhap giap (0-100%%): ";
	cin >> giapPhanTram;
	nr.giap = giapPhanTram / 100.0f;
	return in ;
}
ostream& operator << (ostream& out , NguoiRom nr){
	cout << "========== MUC TIEU NGUOI ROM =========="<< endl;
	cout << left << setw(20) <<"Ten:"<< "Nguoi rom" << endl;
	cout << left << setw(20) <<"HP:"<<nr.hp<< endl;
	cout << left << setw(20) <<"Giap:"<<(int)(nr.giap * 100)<< "%" << endl;
	cout << "========================================" << endl;
	return out ;
}
