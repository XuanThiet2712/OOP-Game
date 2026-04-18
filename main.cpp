#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// ============================================================
//  ANSI COLOR CODES
// ============================================================
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define B_RED     "\033[91m"
#define B_GREEN   "\033[92m"
#define B_YELLOW  "\033[93m"
#define B_BLUE    "\033[94m"
#define B_MAGENTA "\033[95m"
#define B_CYAN    "\033[96m"
#define B_WHITE   "\033[97m"

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// ============================================================
// FORWARD DECLARATION
// ============================================================
class NhanVat;

// ============================================================
// CLASS VUKHI (abstract base)
// ============================================================
class VuKhi {
private:
	string  tenVuKhi;
	int     satThuongCoBan;
	float   tocDoRaDon;
public:
	VuKhi(string ten = "Chua co", int st = 0, float td = 0)
	: tenVuKhi(ten), satThuongCoBan(st), tocDoRaDon(td) {}
	
	VuKhi(const VuKhi& vk)
	: tenVuKhi(vk.tenVuKhi), satThuongCoBan(vk.satThuongCoBan), tocDoRaDon(vk.tocDoRaDon) {}
	
	virtual ~VuKhi() {}
	
	string getTenVuKhi()        const { return tenVuKhi;        }
	int    getSatThuongCoBan()  const { return satThuongCoBan;  }
	float  getTocDoRaDon()      const { return tocDoRaDon;      }
	
	void setTenVuKhi(string ten)    { tenVuKhi          = ten; }
	void setSatThuongCoBan(int st)  { satThuongCoBan    = st;  }
	void setTocDoRaDon(float td)    { tocDoRaDon        = td;  }
	
	virtual void TanCong()          = 0;
	virtual int  SatThuong(int t)   = 0;
	virtual void inThongTin()       = 0;
};

// ============================================================
// CLASS SUNG
// ============================================================
class Sung : public VuKhi {
private:
	int   soLuongDan;
	float tocDoThayBang;
public:
	Sung() : VuKhi(), soLuongDan(30), tocDoThayBang(2) {}
	Sung(string ten, int st, float td, int sld, float tdb)
	: VuKhi(ten, st, td), soLuongDan(sld), tocDoThayBang(tdb) {}
	~Sung() {}
	
	void TanCong() override {
		cout << YELLOW << BOLD << "[ SUNG ]" << RESET
		<< " [SUNG " << CYAN << getTenVuKhi() << RESET << "] "
		<< "Tan cong tam xa bang nhung vien dan chay bong"
		<< " - " << B_RED << getSatThuongCoBan() << " dmg/vien" << RESET
		<< ", " << getTocDoRaDon() << " dan/giay." << endl;
		cout << "    >> Dan hien tai: " << B_YELLOW << soLuongDan << " vien" << RESET << endl;
	}
	
	int SatThuong(int t) override {
		float   thoiGianConLai   = (float)t;
		int     tongDamage       = 0;
		int     soLanThayBang    = 0;
		int     dungLuongBang    = soLuongDan;
		float   thoiGianBanHetDan = soLuongDan / getTocDoRaDon();
		
		cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
		cout << "    Dan luc dau: " << B_YELLOW << soLuongDan << " vien" << RESET << endl;
		
		while (thoiGianConLai > 0) {
			if (soLuongDan == 0) {
				if (thoiGianConLai <= tocDoThayBang) {
					cout << RED << "    >> Het dan! Can " << tocDoThayBang
					<< "s thay bang nhung chi con " << thoiGianConLai << "s -> Dung ban." << RESET << endl;
					break;
				}
				cout << YELLOW << "    >> Het dan! Tu dong thay bang... (-" << tocDoThayBang << "s)" << RESET << endl;
				thoiGianConLai -= tocDoThayBang;
				soLuongDan      = dungLuongBang;
				soLanThayBang++;
				cout << "    Bang moi nap xong: " << B_YELLOW << soLuongDan << " vien" << RESET
				<< " | Con lai: " << thoiGianConLai << "s" << endl;
				continue;
			}
			if (thoiGianConLai >= thoiGianBanHetDan) {
				int damage   = soLuongDan * getSatThuongCoBan();
				tongDamage  += damage;
				thoiGianConLai -= thoiGianBanHetDan;
				cout << "    Ban het " << soLuongDan << " vien (mat " << thoiGianBanHetDan << "s)"
				<< " | Damage: " << B_RED << "+" << damage << RESET
				<< " | Con lai: " << thoiGianConLai << "s" << endl;
				soLuongDan = 0;
			} else {
				int danBan = (int)(getTocDoRaDon() * thoiGianConLai);
				if (danBan == 0) break;
				int damage   = danBan * getSatThuongCoBan();
				tongDamage  += damage;
				soLuongDan  -= danBan;
				cout << "    Ban them " << danBan << " vien | Damage: " << B_RED << "+" << damage << RESET
				<< " | Dan con lai trong bang: " << soLuongDan << " vien" << endl;
				thoiGianConLai = 0;
			}
		}
		
		cout << endl;
		cout << left << setw(28) << "    Tong so lan thay bang:" << soLanThayBang << endl;
		cout << left << setw(28) << "    Dan con lai:"           << soLuongDan    << " vien" << endl;
		cout << BOLD << B_RED << left << setw(28) << "    Tong damage:"  << tongDamage << RESET << endl;
		return tongDamage;
	}
	
	void inThongTin() override {
		cout << "Player dang su dung " << YELLOW << BOLD << "VU KHI: Sung " << CYAN << getTenVuKhi() << RESET << endl;
		cout << left << setw(22) << "Sat thuong/vien:"   << B_RED    << getSatThuongCoBan()           << RESET << endl;
		cout << left << setw(22) << "Toc do ban:"        << B_YELLOW << getTocDoRaDon() << " dan/giay" << RESET << endl;
		cout << left << setw(22) << "Dan con lai:"       << B_YELLOW << soLuongDan     << " vien"      << RESET << endl;
		cout << left << setw(22) << "Toc do thay bang:"  << tocDoThayBang << " giay" << endl;
	}
	
	friend istream& operator>>(istream& is, Sung& sg);
	friend ostream& operator<<(ostream& os, Sung sg) { sg.inThongTin(); return os; }
};

istream& operator>>(istream& is, Sung& sg) {
	string name; int damage; float td;
	is.ignore();
	cout << YELLOW << BOLD << "===== VU KHI: SUNG =====" << RESET << endl;
	cout << "Moi ban nhap ten Sung : ";                              getline(is, name);
	cout << "Moi ban nhap sat thuong / vien dan : ";                 is >> damage;
	cout << "Moi ban nhap toc do ban / 1s (dan ban duoc trong 1s): "; is >> td;
	sg.setTenVuKhi(name); sg.setSatThuongCoBan(damage); sg.setTocDoRaDon(td);
	cout << "Moi ban nhap so luong dan (so luong bang dan) : ";      is >> sg.soLuongDan;
	cout << "Moi ban nhap toc do thay bang (giay) : ";               is >> sg.tocDoThayBang;
	return is;
}

// ============================================================
// CLASS KIEM
// ============================================================
class Kiem : public VuKhi {
private:
	int doBen;
	int doBenMax;
public:
	Kiem() : VuKhi(), doBen(100), doBenMax(100) {}
	Kiem(string ten, int st, float td, int db) : VuKhi(ten, st, td), doBen(db), doBenMax(db) {}
	~Kiem() {}
	
	int  getDoBen()    const { return doBen;    }
	int  getDoBenMax() const { return doBenMax; }
	void setDoBen(int db)    { doBen    = (db < 0) ? 0 : db; }
	void setDoBenMax(int db) { doBenMax = (db < 0) ? 0 : db; }
	
	void TanCong() override {
		cout << B_CYAN << BOLD << "[ KIEM ]" << RESET
		<< " [KIEM " << CYAN << getTenVuKhi() << RESET << "] "
		<< "Tan cong tam gan bang nhung nhat chem sac ben"
		<< " - " << B_RED << getSatThuongCoBan() << " dmg/chem" << RESET
		<< ", " << getTocDoRaDon() << " chem/giay." << endl;
		cout << "    >> Do ben hien tai: ";
		if (doBen <= 0)       cout << RED   << doBen << "/" << doBenMax << " [GAY!]"    << RESET;
		else if (doBen < 30)  cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]"  << RESET;
		else                  cout << GREEN  << doBen << "/" << doBenMax               << RESET;
		cout << endl;
	}
	
	int SatThuong(int t) override {
		if (doBen <= 0) {
			cout << RED << ">> Kiem da gay! Khong the tan cong!" << RESET << endl;
			return 0;
		}
		
		int tongDon    = (int)(getTocDoRaDon() * t);
		int tongDamage = 0;
		
		cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
		cout << ">> Tan cong trong " << t << " giay (" << tongDon << " don)\n";
		
		for (int i = 0; i < tongDon; i++) {
			if (doBen <= 0) break;
			float heSoDoBen    = doBen / (float)doBenMax;
			int   damageMoiDon = (int)(getSatThuongCoBan() * heSoDoBen);
			tongDamage += damageMoiDon;
			doBen--;
		}
		
		cout << ">> Tong sat thuong: " << B_RED   << tongDamage                  << RESET << endl;
		cout << ">> Do ben con lai:  ";
		if (doBen <= 0)      cout << RED    << doBen << "/" << doBenMax << " [GAY!]"   << RESET;
		else if (doBen < 30) cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]"  << RESET;
		else                 cout << GREEN  << doBen << "/" << doBenMax                << RESET;
		cout << endl;
		
		return tongDamage;
	}
	
	void inThongTin() override {
		cout << "Player dang su dung " << B_CYAN << BOLD << "VU KHI: Kiem " << CYAN << getTenVuKhi() << RESET << endl;
		cout << left << setw(22) << "Sat thuong/don:" << B_RED    << getSatThuongCoBan()           << RESET << endl;
		cout << left << setw(22) << "Toc do:"         << B_YELLOW << getTocDoRaDon() << " don/s"   << RESET << endl;
		cout << left << setw(22) << "Do ben:";
		if (doBen <= 0)      cout << RED    << doBen << "/" << doBenMax << " [GAY!]"   << RESET;
		else if (doBen < 30) cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]"  << RESET;
		else                 cout << GREEN  << doBen << "/" << doBenMax                << RESET;
		cout << endl;
	}
	
	friend ostream& operator<<(ostream& os, Kiem km) { km.inThongTin(); return os; }
	friend istream& operator>>(istream& is, Kiem& km) {
		string ten; int st; float td;
		is.ignore();
		cout << B_CYAN << BOLD << "===== VU KHI: KIEM =====" << RESET << endl;
		cout << "Nhap ten kiem : ";           getline(is >> ws, ten);
		cout << "Nhap sat thuong moi don : "; is >> st;
		cout << "Nhap toc do ra don /1s : ";  is >> td;
		km.setTenVuKhi(ten); km.setSatThuongCoBan(st); km.setTocDoRaDon(td);
		cout << "Nhap do ben : "; is >> km.doBen;
		km.doBenMax = km.doBen;
		if (km.doBen < 0) km.doBen = 0;
		return is;
	}
};

// ============================================================
// CLASS PHEPTHUAT  (dinh nghia day du truoc NhanVat)
// ============================================================
class PhepThuat : public VuKhi {
private:
	string   loaiPhep;
	int      manaTieuThu;
	NhanVat* nguoiDungPhep;
	
public:
	PhepThuat() : VuKhi(), loaiPhep("Hoa"), manaTieuThu(10), nguoiDungPhep(nullptr) {}
	PhepThuat(string ten, int st, float td, string lp = "Hoa", int mtb = 10)
	: VuKhi(ten, st, td), loaiPhep(lp), manaTieuThu(mtb), nguoiDungPhep(nullptr) {}
	~PhepThuat() {}
	
	string   getLoaiPhep()      const { return loaiPhep;       }
	int      getManaTieuThu()   const { return manaTieuThu;    }
	NhanVat* getNguoiDungPhep() const { return nguoiDungPhep;  }
	
	void setLoaiPhep(string lp)        { loaiPhep      = lp;  }
	void setManaTieuThu(int mtb)       { manaTieuThu   = mtb; }
	void setNguoiDungPhep(NhanVat* nv) { nguoiDungPhep = nv;  }
	
	void TanCong()        override;
	int  SatThuong(int t) override;
	void inThongTin()     override;
	
	friend ostream& operator<<(ostream& out, PhepThuat x) { x.inThongTin(); return out; }
	friend istream& operator>>(istream& is,  PhepThuat& p) {
		string ten, lp; int st, mtb; float td;
		is.ignore();
		cout << B_MAGENTA << BOLD << "===== VU KHI: PHEP THUAT =====" << RESET << endl;
		cout << "Nhap ten phep          : "; getline(is >> ws, ten);
		cout << "Nhap sat thuong/don    : "; is >> st;
		cout << "Nhap toc do ra don     : "; is >> td;
		cout << "Nhap mana tieu thu/don : "; is >> mtb;
		cout << "\nChon loai phep:" << endl;
		cout << "  " << RED     << "1. Hoa   (dot damage tang theo stack, max 5)"    << RESET << endl;
		cout << "  " << B_CYAN  << "2. Phong (damage tang dan theo don, max x3)"     << RESET << endl;
		cout << "  " << BLUE    << "3. Thuy  (moi 3 don burst x1.5)"                << RESET << endl;
		cout << "  " << MAGENTA << "4. Set   (25% chi mang x2 | 10% siet chet x3)"  << RESET << endl;
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
		return is;
	}
};

// ============================================================
// CLASS NHANVAT
// ============================================================
class NhanVat {
private:
	string nameNV;
	int    hp;
	int    mana;
	int    manaMax;
	VuKhi* vk[3];
	int    viTriDangDung;
	
public:
	NhanVat(string _name = "Khong ro", int _hp = 1000, int _mana = 1000,
			VuKhi* _vk[] = nullptr, int vt = 0)
	: nameNV(_name), hp(_hp), mana(_mana), manaMax(_mana), viTriDangDung(vt)
	{
		for (int i = 0; i < 3; i++)
			vk[i] = (_vk ? _vk[i] : nullptr);
	}
	~NhanVat() {}
	
	string getName()          const { return nameNV;        }
	int    getHp()            const { return hp;            }
	int    getMana()          const { return mana;          }
	int    getManaMax()       const { return manaMax;       }
	int    getViTriDangDung() const { return viTriDangDung; }
	
	void setName(string _name)    { nameNV = _name; }
	void setHp(int _hp)           { hp    = (_hp   < 0) ? 0 : _hp; }
	void setMana(int _mana)       { mana  = (_mana < 0) ? 0 : (_mana > manaMax ? manaMax : _mana); }
	void setViTriDangDung(int vt) { viTriDangDung = vt; }
	
	void trangBiHienTai() {
		for (int i = 0; i < 3; i++) {
			cout << B_WHITE << "[" << i+1 << "] " << RESET;
			vk[i]->TanCong();
		}
	}
	
	VuKhi*& operator[](int index) { return vk[index]; }
	
	int SatThuong(int t) {
		VuKhi* v = vk[viTriDangDung];
		if (!v) { cout << RED << ">> [" << nameNV << "] Chua co vu khi!" << RESET << endl; return 0; }
		return v->SatThuong(t);
	}
	
	void BiTanCong(int st) {
		int hpTruoc = hp;
		hp -= st;
		if (hp < 0) hp = 0;
		cout << RED << ">> " << nameNV << " bi tan cong" << RESET << endl;
		cout << "    HP: " << B_GREEN << hpTruoc << RESET << " -> " << B_RED << hp << RESET << endl;
	}
	
	bool ConSong() const { return hp > 0; }
	
	friend ostream& operator<<(ostream& out, NhanVat nv) {
		out << left << setw(20) << "Ten:"  << B_WHITE  << nv.nameNV               << RESET << endl;
		out << left << setw(20) << "HP:"   << B_GREEN  << nv.hp                   << RESET << endl;
		out << left << setw(20) << "Mana:" << B_BLUE   << nv.mana << "/" << nv.manaMax << RESET << endl;
		out << CYAN << "========================================" << RESET << endl;
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

// ============================================================
// PHEPTHUAT – dinh nghia cac ham sau khi NhanVat da khai bao
// ============================================================

// Helper: tra ve mau tuong ung voi loai phep
static const char* mauPhep(const string& lp) {
	if (lp == "Hoa")   return RED;
	if (lp == "Phong") return B_CYAN;
	if (lp == "Thuy")  return BLUE;
	if (lp == "Set")   return MAGENTA;
	return WHITE;
}

void PhepThuat::TanCong() {
	const char* mau = mauPhep(loaiPhep);
	cout << mau << BOLD << "[ PHEP THUAT ]" << RESET
	<< " [" << mau << getTenVuKhi() << RESET << "] "
	<< "Loai: " << mau << BOLD << loaiPhep << RESET
	<< " - " << B_RED << getSatThuongCoBan() << " dmg/don" << RESET
	<< ", " << getTocDoRaDon() << " don/giay." << endl;
	cout << "    >> Mana tieu thu/don: " << B_BLUE << manaTieuThu << RESET;
	if (nguoiDungPhep)
		cout << " | Mana hien tai: " << B_BLUE
		<< nguoiDungPhep->getMana() << "/" << nguoiDungPhep->getManaMax() << RESET;
	cout << endl;
}

int PhepThuat::SatThuong(int t) {
	if (!nguoiDungPhep) {
		cout << RED << ">> [" << getTenVuKhi() << "] Chua gan nguoi dung phep!" << RESET << endl;
		return 0;
	}
	if (nguoiDungPhep->getMana() < manaTieuThu) {
		cout << RED << ">> [" << getTenVuKhi() << "] Khong du mana! ("
		<< nguoiDungPhep->getMana() << "/" << manaTieuThu << " can)" << RESET << endl;
		return 0;
	}
	
	const char* mau   = mauPhep(loaiPhep);
	int   tongSatThuong = 0;
	int   soDonDaDanh   = 0;
	int   stackHoa      = 0;
	
	// ------- tinh so don co the danh dua tren mana -------
	int maxDon = (int)(getTocDoRaDon() * t);
	int donMana = nguoiDungPhep->getMana() / manaTieuThu;
	int tongDon = (maxDon < donMana) ? maxDon : donMana;
	
	cout << endl << mau << BOLD
	<< "[=== Phep Thuat: " << getTenVuKhi()
	<< " | " << loaiPhep << " ===]" << RESET << endl;
	cout << "    Mana luc dau : " << B_BLUE
	<< nguoiDungPhep->getMana() << "/" << nguoiDungPhep->getManaMax() << RESET << endl;
	cout << "    So don du kien: " << B_WHITE << tongDon << RESET << endl;
	cout << endl;
	
	// ---- header bang ----
	cout << BOLD << WHITE
	<< left  << setw(8)  << "  Don"
	<< left  << setw(10) << "Dame"
	<< left  << setw(20) << "Hieu ung"
	<< left  << setw(14) << "Tong dame"
	<< left  << setw(14) << "Mana con lai"
	<< RESET << endl;
	cout << WHITE << string(66, '-') << RESET << endl;
	
	for (int i = 0; i < tongDon; i++) {
		if (nguoiDungPhep->getMana() < manaTieuThu) break;
		
		nguoiDungPhep->setMana(nguoiDungPhep->getMana() - manaTieuThu);
		soDonDaDanh++;
		
		int    base      = getSatThuongCoBan();
		int    dmg       = base;
		int    dmgHieuUng = 0;
		string ghiChu    = "-";
		
		// --- HOA: dot tang theo stack max 5, moi stack +20% base ---
		if (loaiPhep == "Hoa") {
			if (stackHoa < 5) stackHoa++;
			dmgHieuUng = stackHoa * (base / 5);
			dmg        = base + dmgHieuUng;
			ghiChu     = RED + string("dot +") + to_string(dmgHieuUng)
			+ " [stack " + to_string(stackHoa) + "/5]" + RESET;
		}
		// --- PHONG: he so tang 0.1/don, max x3 ---
		else if (loaiPhep == "Phong") {
			float boSuc = 1.0f + (soDonDaDanh - 1) * 0.1f;
			if (boSuc > 3.0f) boSuc = 3.0f;
			dmg        = (int)(base * boSuc);
			dmgHieuUng = dmg - base;
			ghiChu     = B_CYAN + string("x") + to_string(boSuc).substr(0,3)
			+ " bonus +" + to_string(dmgHieuUng) + RESET;
		}
		// --- THUY: moi 3 don burst x1.5 ---
		else if (loaiPhep == "Thuy") {
			bool burst = (soDonDaDanh % 3 == 0);
			dmg        = burst ? (int)(base * 1.5f) : base;
			dmgHieuUng = dmg - base;
			ghiChu     = burst
			? (BLUE + string("BURST x1.5! +") + to_string(dmgHieuUng) + RESET)
			: (string(BLUE) + "-" + RESET);
		}
		// --- SET: 25% chi mang x2, 10% siet chet x3 ---
		else if (loaiPhep == "Set") {
			int roll = rand() % 100;
			if      (roll < 10) { dmg = base*3; dmgHieuUng = base*2; ghiChu = string(B_MAGENTA) + BOLD + "*** SIET CHET x3!" + RESET; }
			else if (roll < 35) { dmg = base*2; dmgHieuUng = base;   ghiChu = string(MAGENTA)           + "** Chi mang x2!"   + RESET; }
			else                { ghiChu = string(MAGENTA) + "-" + RESET; }
		}
		
		tongSatThuong += dmg;
		
		// --- in tung dong ---
		cout << mau
		<< left  << setw(8)  << ("  " + to_string(soDonDaDanh))
		<< RESET;
		cout << B_RED   << left << setw(10) << dmg        << RESET;
		// ghiChu da co ma mau ben trong, pad bang space thu cong
		cout << ghiChu;
		// tinh do rong thuc (bo escape codes)
		int lenGhi = 0;
		bool inEsc = false;
		for (char c : ghiChu) {
			if (c == '\033') { inEsc = true; continue; }
			if (inEsc) { if (c == 'm') inEsc = false; continue; }
			lenGhi++;
		}
		for (int s = lenGhi; s < 20; s++) cout << ' ';
		cout << B_RED   << left << setw(14) << tongSatThuong << RESET;
		cout << B_BLUE  << left << setw(14) << nguoiDungPhep->getMana() << RESET;
		cout << endl;
	}
	
	cout << WHITE << string(66, '-') << RESET << endl << endl;
	
	// ------- Tom tat -------
	cout << left << setw(30) << "  Tong don da danh:"
	<< B_WHITE << soDonDaDanh << RESET << endl;
	cout << left << setw(30) << "  Mana con lai:"
	<< B_BLUE << nguoiDungPhep->getMana() << "/" << nguoiDungPhep->getManaMax() << RESET << endl;
	cout << BOLD << B_RED << left << setw(30) << "  Tong damage:"
	<< tongSatThuong << RESET << endl;
	
	return tongSatThuong;
}

void PhepThuat::inThongTin() {
	const char* mau = mauPhep(loaiPhep);
	cout << "Player dang su dung " << mau << BOLD << "VU KHI: Phep Thuat "
	<< getTenVuKhi() << RESET << endl;
	cout << left << setw(25) << "Loai phep:"         << mau << BOLD << loaiPhep            << RESET << endl;
	cout << left << setw(25) << "Sat thuong co ban:" << B_RED    << getSatThuongCoBan()    << RESET << endl;
	cout << left << setw(25) << "Toc do ra don:"     << B_YELLOW << getTocDoRaDon() << " don/giay" << RESET << endl;
	cout << left << setw(25) << "Mana tieu thu/don:" << B_BLUE   << manaTieuThu             << RESET << endl;
	if (nguoiDungPhep)
		cout << left << setw(25) << "Mana hien tai:"
		<< B_BLUE << nguoiDungPhep->getMana() << "/" << nguoiDungPhep->getManaMax() << RESET << endl;
}

// ============================================================
// GIAO DIEN CHINH
// ============================================================
void hienThiGiaoDien(NhanVat& nr, NhanVat& p) {
	clearScreen();
	cout << RED << BOLD << "========== MUC TIEU: " << nr.getName() << " ==========" << RESET << "\n";
	cout << nr;
	cout << GREEN << "PLAYER: " << p.getName() << RESET
	<< " | HP: " << B_GREEN << p.getHp() << RESET
	<< " | Mana: " << B_BLUE << p.getMana() << "/" << p.getManaMax() << RESET << "\n";
	cout << CYAN << "TRANG BI HIEN TAI:" << RESET << "\n";
	p.trangBiHienTai();
	cout << "\n";
	cout << YELLOW << BOLD << "===== Vu Khi Dang Su Dung =====" << RESET << "\n";
	p[p.getViTriDangDung()]->inThongTin();
	cout << "\n";
	cout << WHITE << "==============================" << RESET << "\n";
	cout << B_RED    << "  1. Tan cong"     << RESET << "\n";
	cout << B_YELLOW << "  2. Doi vu khi"   << RESET << "\n";
	cout << B_CYAN   << "  3. Che tao lai vu khi" << RESET << "\n";
	cout << WHITE    << "  0. Thoat"        << RESET << "\n";
	cout << WHITE << "==============================" << RESET << "\n";
	cout << "Lua chon: ";
}

// ============================================================
// MAIN
// ============================================================
int main() {
	srand((unsigned)time(0));
	
	Sung      sung("AK47",      35, 10.0f, 30, 2.0f);
	Kiem      kiem("Muramasa",  50,  2.0f, 100);
	PhepThuat phep("Amaterasu", 60,  1.0f, "Hoa", 15);
	
	VuKhi* vk[3] = { &sung, &kiem, &phep };
	
	NhanVat nr    ("Nguoi Rom",      10000, 0);
	NhanVat player("Shadow Reaper", 10000, 500, vk, 0);
	
	phep.setNguoiDungPhep(&player);
	
	int lua = -1;
	while (lua != 0 && nr.ConSong()) {
		hienThiGiaoDien(nr, player);
		cin >> lua;
		
		if (lua == 1) {
			clearScreen();
			cout << RED << BOLD << "========== MUC TIEU: " << nr.getName() << " ==========" << RESET << "\n";
			cout << nr;
			cout << GREEN << "PLAYER: " << player.getName() << RESET
			<< " | HP: " << B_GREEN << player.getHp() << RESET
			<< " | Mana: " << B_BLUE << player.getMana() << "/" << player.getManaMax() << RESET << "\n";
			cout << YELLOW << BOLD << "===== TAN CONG =====" << RESET << "\n";
			player[player.getViTriDangDung()]->TanCong();
			cout << "\nNhap so luot tan cong: ";
			int t; cin >> t;
			int damage = player.SatThuong(t);
			cout << "\n" << B_RED << BOLD << "Sat thuong gay len " << nr.getName() << ": " << damage << RESET << "\n";
			if (damage > 0) {
				cout << endl;
				nr.BiTanCong(damage);
				if (nr.ConSong())
					cout << YELLOW << "\n>> " << nr.getName() << " van song! HP: " << nr.getHp() << RESET << "\n";
				else
					cout << RED << BOLD << "\n>> " << nr.getName() << " da bi ha guc!" << RESET << "\n";
			}
			cout << "\nNhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 2) {
			clearScreen();
			cout << YELLOW << BOLD << "===== DOI VU KHI =====" << RESET << "\n";
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
			cout << CYAN << BOLD << "===== CHE TAO VU KHI =====" << RESET << "\n";
			cout << YELLOW << "  1. Sung"        << RESET << "\n";
			cout << B_CYAN << "  2. Kiem"        << RESET << "\n";
			cout << MAGENTA<< "  3. Phep Thuat"  << RESET << "\n";
			cout << "Lua chon: ";
			int chon; cin >> chon;
			switch (chon) {
				case 1: cin >> sung; player[0] = &sung; player.setViTriDangDung(0); break;
				case 2: cin >> kiem; player[1] = &kiem; player.setViTriDangDung(1); break;
			case 3:
				cin >> phep;
				phep.setNguoiDungPhep(&player);
				player[2] = &phep;
				player.setViTriDangDung(2);
				break;
			default:
				cout << RED << "Lua chon khong hop le!\n" << RESET; break;
			}
			cout << B_GREEN << "\n>> Che tao thanh cong!" << RESET << "\n";
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
		else if (lua == 0) {
			clearScreen();
			cout << B_WHITE << "Tam biet!\n" << RESET;
			return 0;
		}
		else {
			cout << RED << "Lua chon khong hop le.\n" << RESET;
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore(); cin.get();
		}
	}
	
	if (!nr.ConSong()) {
		clearScreen();
		cout << "\n" << RED << BOLD;
		cout << "=============================\n";
		cout << "  " << nr.getName() << " DA BI TIEU DIET!\n";
		cout << "=============================" << RESET << "\n";
	}
	return 0;
}
