#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
// FORWARD DECLARATION
class NhanVat;

// CLASS VUKHI
class VuKhi {
private:
	string	tenVuKhi;
	int		satThuongCoBan;
	float	tocDoRaDon;
public:
	// ham khoi tao tham so 
	VuKhi(string ten = "Chua co", int st = 0, float td = 0) {
		tenVuKhi		= ten;
		satThuongCoBan	= st;
		tocDoRaDon		= td;
	}
	// ham khoi tao sao chep
	VuKhi(const VuKhi& vk){
		tenVuKhi = vk.tenVuKhi ;
		satThuongCoBan = vk.satThuongCoBan ;
		tocDoRaDon = vk.tocDoRaDon ; 
	}
	~VuKhi() {}
	
	string	getTenVuKhi()		{ return tenVuKhi;			}
	int		getSatThuongCoBan()	{ return satThuongCoBan;	}
	float	getTocDoRaDon()		{ return tocDoRaDon;		}
	
	void setTenVuKhi(string ten)	{ tenVuKhi			= ten; }
	void setSatThuongCoBan(int st)	{ satThuongCoBan	= st;  }
	void setTocDoRaDon(float td)	{ tocDoRaDon		= td;  }
	
	virtual void TanCong()			= 0;
	virtual int  SatThuong(int t)	= 0;
	virtual void inThongTin()		= 0;
};

// CLASS SUNG
class Sung : public VuKhi {
private:
	int   soLuongDan;
	float tocDoThayBang;
public:
	Sung() : VuKhi(), soLuongDan(30), tocDoThayBang(2) {}
	Sung(string ten, int st, float td, int sld, float tdb)
	: VuKhi(ten, st, td), soLuongDan(sld), tocDoThayBang(tdb) {}
	~Sung() {}
	
	void TanCong() {
		cout << "[ SUNG ] [SUNG " << getTenVuKhi() << "] Tan cong tam xa bang nhung vien dan chay bong"
		<< " - " << getSatThuongCoBan() << " dmg/vien, "
		<< getTocDoRaDon() << " dan/giay. ";
		cout << endl << "	>> Dan hien tai: " << soLuongDan << " vien." << endl;
	}
	
	int SatThuong(int t) {
		float 	thoiGianConLai	= (float)t;
		int		tongDamage		= 0;
		int		soLanThayBang	= 0;
		int		dungLuongBang	= soLuongDan;
		float thoiGianBanHetDan = soLuongDan / getTocDoRaDon();
		
		cout << endl << "[Dien bien chien dau - " << t << " giay]" << endl;
		cout << "	Dan luc dau:" << soLuongDan << " vien" << endl;
		
		while (thoiGianConLai > 0) {
			if (soLuongDan == 0) {
				if (thoiGianConLai <= tocDoThayBang) {
					cout << "	>> Het dan! Can " << tocDoThayBang
					<< "s thay bang nhung chi con " << thoiGianConLai << "s -> Dung ban." << endl;
					break;
				}
				cout << "	>> Het dan! Tu dong thay bang... (-" << tocDoThayBang << "s)" << endl;
				thoiGianConLai -= tocDoThayBang;
				soLuongDan      = dungLuongBang;
				soLanThayBang++;
				cout << "	Bang moi nap xong:" << soLuongDan << " vien | Con lai: " << thoiGianConLai << "s" << endl;
				continue;
			}
			if (thoiGianConLai >= thoiGianBanHetDan) {
				int damage  = soLuongDan * getSatThuongCoBan();
				tongDamage += damage;
				thoiGianConLai -= thoiGianBanHetDan;
				cout << "	Ban het " << soLuongDan << " vien" << " (mat " << thoiGianBanHetDan << "s)"
				<< " | Damage: +" << damage << " | Con lai: " << thoiGianConLai << "s" << endl;
				soLuongDan = 0;
			} else {
				int danBan = (int)(getTocDoRaDon() * thoiGianConLai);
				if (danBan == 0) break;
				int damage  = danBan * getSatThuongCoBan();
				tongDamage += damage;
				soLuongDan -= danBan;
				cout << "	Ban them " << danBan << " vien | Damage: +" << damage
				<< " | Dan con lai trong bang: " << soLuongDan << " vien" << endl;
				thoiGianConLai = 0;
			}
		}
		cout << endl;
		cout << left << setw(28) << "	Tong so lan thay bang:" << soLanThayBang << endl;
		cout << left << setw(28) << "	Dan con lai:"			<< soLuongDan    << " vien" << endl;
		cout << left << setw(28) << "	Tong damage :"			<< tongDamage    << endl;
		return tongDamage;
	}
	
	void inThongTin() {
		cout << "Player dang su dung VU KHI: ";
		cout << "Sung "	<< getTenVuKhi() 												<< endl;
		cout << left << setw(22) << "Sat thuong/vien:" << getSatThuongCoBan()			<< endl;
		cout << left << setw(22) << "Toc do ban:"      << getTocDoRaDon()<< " dan/giay" << endl;
		cout << left << setw(22) << "Dan con lai:"     << soLuongDan		<< " vien" 	<< endl;
		cout << left << setw(22) << "Toc do thay bang:"<< tocDoThayBang		<< " giay"	<< endl;
	}
	
	friend istream& operator>>(istream& is, Sung& sg);
	friend ostream& operator<<(ostream& os, Sung sg) { sg.inThongTin(); return os; }
};

istream& operator>>(istream& is, Sung& sg) {
	string name; int damage; float td;
	is.ignore();
	cout << "===== VU KHI: SUNG =====" << endl;
	cout << "Moi ban nhap ten Sung : ";                                getline(is, name);
	cout << "Moi ban nhap sat thuong / vien dan : ";                   is >> damage;
	cout << "Moi ban nhap toc do ban / 1s (so dan ban duoc trong 1s): "; is >> td;
	sg.setTenVuKhi(name); sg.setSatThuongCoBan(damage); sg.setTocDoRaDon(td);
	cout << "Moi ban nhap so luong dan (so luong bang dan) : ";        is >> sg.soLuongDan;
	cout << "Moi ban nhap toc do thay bang (giay) : ";                 is >> sg.tocDoThayBang;
	return is;
}

// CLASS KIEM
class Kiem : public VuKhi {
private:
	int doBen;
	int doBenMax;
public:
	Kiem() : VuKhi(), doBen(100), doBenMax(100) {}
	Kiem(string ten, int st, float td, float db) : VuKhi(ten, st, td), doBen(db), doBenMax(db) {}
	~Kiem() {}
	
	int  getDoBen()    { return doBen;    }
	int  getDoBenMax() { return doBenMax; }
	void setDoBen(int db)    { doBen    = (db < 0) ? 0 : db; }
	void setDoBenMax(int db) { doBenMax = (db < 0) ? 0 : db; }
	
	void TanCong() {
		cout << "[ KIEM ] [KIEM " << getTenVuKhi() << "] Tan cong tam gan bang nhung nhat chem sac ben"
		<< " - " << getSatThuongCoBan() << " dmg/chem, "
		<< getTocDoRaDon() << " chem/giay.";
		cout << endl << "	>> Do ben hien tai : " << doBen << "/" << doBenMax << endl;
	}
	
	int SatThuong(int t) {
		if (doBen <= 0) { cout << ">> Kiem da gay! Khong the tan cong!\n"; return 0; }
		
		int tongDon    = (int)(getTocDoRaDon() * t);
		int tongDamage = 0;
		cout << ">> Tan cong trong " << t << " giay (" << tongDon << " don)\n";
		
		for (int i = 0; i < tongDon; i++) {
			if (doBen <= 0) break;
			float heSoDoBen   = doBen / (float)doBenMax;
			int   damageMoiDon = (int)(getSatThuongCoBan() * heSoDoBen);
			tongDamage += damageMoiDon;
			doBen--;
		}
		cout << ">> Tong sat thuong: " << tongDamage << endl;
		cout << ">> Do ben con lai: "  << doBen << "/" << doBenMax << "\n";
		if (doBen <= 0)   cout << ">> Kiem da gay!\n";
		else if (doBen < 30) cout << ">> Canh bao: Do ben thap!\n";
		return tongDamage;
	}
	
	void inThongTin() {
		cout << "Player dang su dung VU KHI: ";
		cout << "Kiem " << getTenVuKhi() << endl;
		cout << setw(20) << left << "Sat thuong:" << getSatThuongCoBan() << endl;
		cout << setw(20) << left << "Toc do:"     << getTocDoRaDon()     << " don/s\n";
		cout << setw(20) << left << "Do ben:"     << doBen << "/" << doBenMax << endl;
		if (doBen <= 0)      cout << " [GAY!]";
		else if (doBen < 30) cout << " [THAP]";
		cout << endl;
	}
	
	friend ostream& operator<<(ostream& os, Kiem km) { km.inThongTin(); return os; }
	friend istream& operator>>(istream& is, Kiem& km) {
		string ten; int st; float td;
		is.ignore();
		cout << "===== VU KHI: KIEM =====" << endl;
		cout << "Nhap ten kiem : ";          getline(is >> ws, ten);
		cout << "Nhap sat thuong moi don : "; is >> st;
		cout << "Nhap toc do ra don /1s : ";  is >> td;
		km.setTenVuKhi(ten); km.setSatThuongCoBan(st); km.setTocDoRaDon(td);
		cout << "Nhap do ben : "; is >> km.doBen;
		km.doBenMax = km.doBen;
		if (km.doBen < 0) km.doBen = 0;
		return is;
	}
};

// CLASS PHEPTHUAT
class PhepThuat : public VuKhi {
private:
	string   loaiPhep;
	int      manaTieuThu;
	NhanVat* nguoiDungPhep;  // tro toi nguoiDungPhep, truy cap mana nho friend
	
public:
	PhepThuat() : VuKhi(), loaiPhep("Hoa"), manaTieuThu(10), nguoiDungPhep(nullptr) {}
	PhepThuat(string ten, int st, float td, string lp = "Hoa", int mtb = 10)
	: VuKhi(ten, st, td), loaiPhep(lp), manaTieuThu(mtb), nguoiDungPhep(nullptr) {}
	~PhepThuat() {}
	
	string   getLoaiPhep()                 { return loaiPhep;      }
	int      getManaTieuThu()              { return manaTieuThu;   }
	NhanVat* getNguoiDungPhep()            { return nguoiDungPhep; }
	void     setLoaiPhep(string lp)        { loaiPhep      = lp;   }
	void     setManaTieuThu(int mtb)       { manaTieuThu   = mtb;  }
	void     setNguoiDungPhep(NhanVat* nv) { nguoiDungPhep = nv;   }
	
	// Khai bao SAU class NhanVat 
	void TanCong()        override;
	int  SatThuong(int t) override;
	void inThongTin()     override;
	
	friend ostream& operator<<(ostream& out, PhepThuat x) { 
		x.inThongTin(); return out; 
	}
	friend istream& operator>>(istream& is,  PhepThuat& p) {
		string ten, lp; int st, mtb; float td;
		is.ignore();
		cout << "===== VU KHI: PHEP THUAT =====" << endl;
		cout << "Nhap ten phep          : "; getline(is >> ws, ten);
		cout << "Nhap sat thuong/don    : "; is >> st;
		cout << "Nhap toc do ra don     : "; is >> td;
		cout << "Nhap mana tieu thu/don : "; is >> mtb;
		cout << "\nChon loai phep:" << endl;
		cout << "  1. Hoa   (dot damage tang theo stack, max 5)"	<< endl;
		cout << "  2. Phong (damage tang dan theo don, max x3)"		<< endl;
		cout << "  3. Thuy  (moi 3 don burst x1.5)"					<< endl;
		cout << "  4. Set   (25% chi mang x2 | 10% siet chet x3)"	<< endl;
		cout << "Lua chon (1-4): ";
		int chon; is >> chon;
		switch (chon) {
			case 1: lp = "Hoa";   break;
			case 2: lp = "Phong"; break;
			case 3: lp = "Thuy";  break;
			case 4: lp = "Set";   break;
			default: lp = "Hoa";  cout << "Khong hop le, mac dinh Hoa." << endl;
		}
		p.setTenVuKhi(ten); p.setSatThuongCoBan(st); p.setTocDoRaDon(td);
		p.loaiPhep    = lp;
		p.manaTieuThu = mtb;
		// nguoiDungPhep giu nguyen, khong reset
		return is;
	}
};

// CLASS NHANVAT
// friend class PhepThuat -> PhepThuat truy cap mana/manaMax
class NhanVat {
	friend class PhepThuat;  // cho phep PhepThuat truy cap mana, manaMax
private:
	string nameNV;
	int    hp;
	int    mana;
	int    manaMax;
	VuKhi* vk[3];
	int    viTriDangDung;
	
public:
	NhanVat(string _name = "Khong ro", int _hp = 1000, int _mana = 1000,
			VuKhi* _vk[] = nullptr, int vt = 0) {
		nameNV = _name;
		hp     = _hp;
		mana   = _mana;
		manaMax= _mana;
		for (int i = 0; i < 3; i++)
			vk[i] = (_vk ? _vk[i] : nullptr);
		viTriDangDung = vt;
	}
	~NhanVat() {}
	
	string getName()			{ return nameNV;		}
	int    getHp()				{ return hp;			}
	int    getMana()			{ return mana;			}
	int    getManaMax()			{ return manaMax;		}
	int    getViTriDangDung() 	{ return viTriDangDung;	}
	
	void setName(string _name)   { nameNV = _name; }
	void setHp(int _hp)          { hp   = (_hp < 0) ? 0 : _hp; }
	void setMana(int _mana)      { mana = (_mana < 0) ? 0 : (_mana > manaMax ? manaMax : _mana); }
	void setViTriDangDung(int vt){ viTriDangDung = vt; }
	
	void trangBiHienTai() {
		for (int i = 0; i < 3; i++) { cout << "[" << i+1 << "] "; vk[i]->TanCong(); }
	}
	
	VuKhi*& operator[](int index) { return vk[index]; }
	
	int SatThuong(int t) {
		VuKhi* v = vk[viTriDangDung];
		if (v == nullptr) { cout << ">> [" << nameNV << "] Chua co vu khi!" << endl; return 0; }
		return v->SatThuong(t);
	}
	
	void BiTanCong(int st) {
		int hpTruoc = hp;
		hp -= st;
		if (hp < 0) hp = 0;
		cout << ">> " << nameNV << " bi tan cong\n";
		cout << "	HP: " << hpTruoc << " -> " << hp << endl;
	}
	
	bool ConSong() { return hp > 0; }
	
	friend ostream& operator<<(ostream& out, NhanVat nv) {
		out << left << setw(20) << "Ten:"  << nv.nameNV << endl;
		out << left << setw(20) << "HP:"   << nv.hp     << endl;
		out << left << setw(20) << "Mana:" << nv.mana << "/" << nv.manaMax << endl;
		out << "========================================" << endl;
		return out;
	}
	friend istream& operator>>(istream& in, NhanVat& nv) {
		cout << "Nhap ten nhan vat: "; in.ignore(); getline(in, nv.nameNV);
		cout << "Nhap HP: ";   in >> nv.hp;
		cout << "Nhap Mana: "; in >> nv.mana;
		nv.manaMax = nv.mana;
		return in;
	}
};

void PhepThuat::TanCong() {
	cout << "[ PHEP THUAT ] [" << getTenVuKhi() << "] "
	<< "Loai: "           << loaiPhep
	<< " - "              << getSatThuongCoBan() << " dmg/don, "
	<< getTocDoRaDon()    << " don/giay." << endl;
	cout << "    >> Mana tieu thu/don: " << manaTieuThu;
	if (nguoiDungPhep)
		cout << " | Mana hien tai: " << nguoiDungPhep->mana << "/" << nguoiDungPhep->manaMax;
	cout << endl;
}

int PhepThuat::SatThuong(int t) {
	// Kiem tra nguoi dung
	if (nguoiDungPhep == nullptr) {
		cout << ">> [" << getTenVuKhi() << "] Chua gan nguoi dung phep!" << endl;
		return 0;
	}
	// Kiem tra du mana it nhat 1 don
	if (nguoiDungPhep->mana < manaTieuThu) {
		cout << ">> [" << getTenVuKhi() << "] Khong du mana! ("
		<< nguoiDungPhep->mana << "/" << manaTieuThu << " can)" << endl;
		return 0;
	}
	
	int   tongSatThuong  = 0;
	int   soDonDaDanh    = 0;
	int   stackHoa       = 0;
	float thoiGianConLai = (float)t;
	float thoiGianMoiDon = 1.0f / getTocDoRaDon();
	
	cout << "\n[Dien bien chien dau - " << t << " giay | "
	<< getTenVuKhi() << " - " << loaiPhep << "]" << endl;
	cout << "  Mana luc dau: " << nguoiDungPhep->mana << "/" << nguoiDungPhep->manaMax << endl;
	
	while (thoiGianConLai >= thoiGianMoiDon) {
		// Het mana giua chung
		if (nguoiDungPhep->mana < manaTieuThu) {
			cout << "  >> Het mana! Dung danh." << endl;
			break;
		}
		
		thoiGianConLai           -= thoiGianMoiDon;
		nguoiDungPhep->mana      -= manaTieuThu;  // tru mana truc tiep qua friend
		soDonDaDanh++;
		
		int    base       = getSatThuongCoBan();
		int    dmg        = 0;
		int    dmgHieuUng = 0;
		string ghiChu     = "";
		
		// --- HOA: dot tang theo stack max 5, moi stack +20% base ---
		if (loaiPhep == "Hoa") {
			if (stackHoa < 5) stackHoa++;
			dmgHieuUng = stackHoa * (base / 5);
			dmg        = base + dmgHieuUng;
			ghiChu     = "[dot +" + to_string(dmgHieuUng) + " | stack " + to_string(stackHoa) + "]";
		}
		// --- PHONG: he so tang 0.1/don, max x3 ---
		else if (loaiPhep == "Phong") {
			float boSuc = 1.0f + (soDonDaDanh - 1) * 0.1f;
			if (boSuc > 3.0f) boSuc = 3.0f;
			dmg        = (int)(base * boSuc);
			dmgHieuUng = dmg - base;
			ghiChu     = "[phong x" + to_string(boSuc).substr(0,3) + " | bonus +" + to_string(dmgHieuUng) + "]";
		}
		// --- THUY: moi 3 don burst x1.5 ---
		else if (loaiPhep == "Thuy") {
			bool burst = (soDonDaDanh % 3 == 0);
			dmg        = burst ? (int)(base * 1.5f) : base;
			dmgHieuUng = dmg - base;
			ghiChu     = burst ? "[Thuy burst x1.5 | bonus +" + to_string(dmgHieuUng) + "]" : "";
		}
		// --- SET: 25% chi mang x2, 10% siet chet x3 ---
		else if (loaiPhep == "Set") {
			int roll = rand() % 100;
			if      (roll < 10) { dmg = base*3; dmgHieuUng = base*2; ghiChu = "[*** SIET CHET x3! ***]"; }
			else if (roll < 35) { dmg = base*2; dmgHieuUng = base;   ghiChu = "[** Chi mang x2! **]";    }
			else                { dmg = base; }
		}
		else { dmg = base; }
		
		tongSatThuong += dmg;
		cout << "  Don " << setw(3) << soDonDaDanh
		<< " | base " << setw(4) << base
		<< " | dmg +"  << setw(5) << dmg
		<< " | mana: " << nguoiDungPhep->mana
		<< " " << ghiChu << endl;
	}
	
	cout << endl;
	cout << left << setw(28) << "  Tong don da danh:"  << soDonDaDanh                                  << endl;
	cout << left << setw(28) << "  Mana con lai:"      << nguoiDungPhep->mana << "/" << nguoiDungPhep->manaMax << endl;
	cout << left << setw(28) << "  Tong damage:"       << tongSatThuong                                << endl;
	return tongSatThuong;
}

void PhepThuat::inThongTin() {
	cout << "Player dang su dung VU KHI: ";
	cout << "Phep Thuat " << getTenVuKhi() << endl;
	cout << left << setw(25) << "Loai phep:"         << loaiPhep            << endl;
	cout << left << setw(25) << "Sat thuong co ban:" << getSatThuongCoBan() << endl;
	cout << left << setw(25) << "Toc do ra don:"     << getTocDoRaDon()     << " don/giay" << endl;
	cout << left << setw(25) << "Mana tieu thu/don:" << manaTieuThu         << endl;
	if (nguoiDungPhep)
		cout << left << setw(25) << "Mana hien tai:"
		<< nguoiDungPhep->mana << "/" << nguoiDungPhep->manaMax << endl;
}

//ME NU
void hienThiGiaoDien(NhanVat& nr, NhanVat& p) {
	clearScreen();
	cout << "========== MUC TIEU: " << nr.getName() << " ==========\n";
	cout << nr;
	cout << "PLAYER: " << p.getName() << " | HP: " << p.getHp()
	<< " | Mana: " << p.getMana() << "/" << p.getManaMax() << "\n";
	cout << "TRANG BI HIEN TAI:\n";
	p.trangBiHienTai();
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

//MAIN
int main() {
	srand((unsigned)time(0));  // khoi tao random cho Set
	
	Sung		sung("AK47",      35, 10.0f, 30, 2.0f);
	Kiem		kiem("Muramasa",  50,  2.0f, 100);
	PhepThuat	phep("Amaterasu", 60,  1.0f, "Hoa", 15);
	
	VuKhi* vk[3] = {&sung, &kiem, &phep};
	
	NhanVat nr    ("Nguoi Rom",		10000, 0);
	NhanVat player("Shadow Reaper", 10000, 500, vk, 0);
	
	//Gan nguoi dung phep sau khi player da duoc khai bao
	phep.setNguoiDungPhep(&player);
	
	int lua = -1;
	while (lua != 0 && nr.ConSong()) {
		hienThiGiaoDien(nr, player);
		cin >> lua;
		
		if (lua == 1) {
			clearScreen();
			cout << "========== MUC TIEU: " << nr.getName() << " ==========\n";
			cout << nr;
			cout << "PLAYER: " << player.getName()
			<< " | HP: "   << player.getHp()
			<< " | Mana: " << player.getMana() << "/" << player.getManaMax() << "\n";
			cout << "===== TAN CONG =====\n";
			player[player.getViTriDangDung()]->TanCong();
			cout << "\nNhap thoi gian tan cong (giay): ";
			int t; cin >> t;
			int damage = player.SatThuong(t);
			cout << "\nSat thuong gay len " << nr.getName() << ": " << damage << "\n";
			if (damage > 0) {
				cout << endl;
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
			clearScreen();
			cout << "===== DOI VU KHI =====\n";
			player.trangBiHienTai();
			cout << "Lua chon (1-3): ";
			int chon; cin >> chon;
			player.setViTriDangDung(chon - 1);
			cout << "\n>> Da chon:\n";
			player[player.getViTriDangDung()]->TanCong();
			cout << "\nNhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 3) {
			clearScreen();
			cout << "===== CHE TAO VU KHI =====\n";
			cout << "  1. Sung\n  2. Kiem\n  3. Phep Thuat\n";
			cout << "Lua chon: ";
			int chon; cin >> chon;
			switch (chon) {
				case 1: cin >> sung; player[0] = &sung; player.setViTriDangDung(0); break;
				case 2: cin >> kiem; player[1] = &kiem; player.setViTriDangDung(1); break;
			case 3:
				cin >> phep;
				phep.setNguoiDungPhep(&player); // giu ket noi sau khi nhap lai
				player[2] = &phep;
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
