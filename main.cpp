#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
// Reset lại màu về mặc định
#define RESET	"\033[0m"
#define BOLD	"\033[1m"	// In chữ đậm (bold)
#define RED		"\033[31m"   // Màu đỏ
#define GREEN	"\033[32m"   // Màu xanh lá
#define YELLOW	"\033[33m"   // Màu vàng
#define BLUE	"\033[34m"   // Màu xanh dương
#define MAGENTA	"\033[35m"   // Màu tím hồng
#define CYAN	"\033[36m"   // Màu xanh cyan (xanh ngọc)
#define WHITE	"\033[37m"   // Màu trắng

// mau sang
#define B_RED		"\033[91m" // Đỏ sáng
#define B_GREEN		"\033[92m" // Xanh lá sáng
#define B_YELLOW	"\033[93m" // Vàng sáng
#define B_BLUE		"\033[94m" // Xanh dương sáng
#define B_MAGENTA	"\033[95m" // Tím sáng
#define B_CYAN		"\033[96m" // Cyan sáng
#define B_WHITE		"\033[97m" // Trắng sáng

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

class NhanVat;
// CLASS VUKHI 
class VuKhi {
private:
	string	tenVuKhi;
	int		satThuongCoBan;
	float	tocDoRaDon;
public:
	//constructor / destructor 
	VuKhi(string ten = "Chua co", int st = 0, float td = 0)
	: tenVuKhi(ten), satThuongCoBan(st), tocDoRaDon(td) {}
	VuKhi(const VuKhi& vk)
	: tenVuKhi(vk.tenVuKhi), satThuongCoBan(vk.satThuongCoBan), tocDoRaDon(vk.tocDoRaDon) {}
	virtual ~VuKhi() {}
	
	string	getTenVuKhi()		{ return tenVuKhi;			}
	int		getSatThuongCoBan()	{ return satThuongCoBan;	}
	float	getTocDoRaDon()		{ return tocDoRaDon;		}
	
	void setTenVuKhi(string ten)	{ tenVuKhi			= ten;	}
	void setSatThuongCoBan(int st)	{ satThuongCoBan	= st;	}
	void setTocDoRaDon(float td)	{ tocDoRaDon		= td;	}
	
	virtual void TanCong()			= 0;
	virtual int  SatThuong(int t)	= 0;
	virtual void inThongTin()		= 0;
};

// CLASS SUNG
class Sung : public VuKhi {
private:
	int		soLuongDan;
	float 	tocDoThayBang;
public:
	Sung() : VuKhi(), soLuongDan(30), tocDoThayBang(2) {}
	Sung(string ten, int st, float td, int sld, float tdb)
	: VuKhi(ten, st, td), soLuongDan(sld), tocDoThayBang(tdb) {}
//	Sung(const Sung& sg){
//		
//	}
	~Sung(){}
	
	void TanCong() override {
		cout << YELLOW << BOLD << "[ SUNG ]" << RESET
		<< CYAN << " [SUNG " << getTenVuKhi() << RESET << "] "
		<< "Tan cong tam xa bang nhung vien dan chay bong"
		<< " - " << B_RED << getSatThuongCoBan() << " dmg/vien" << RESET
		<< ", " << getTocDoRaDon() << " dan/giay." << endl;
	}
	
	int SatThuong(int t) override {
		int dungLuongBang	= soLuongDan;
		float thoiGianBanHetDan	= dungLuongBang / getTocDoRaDon();
		float tChuKy = thoiGianBanHetDan + tocDoThayBang;
		
		int   n   = (int)(t / tChuKy);
		float tDu = t - n * tChuKy;
		
		int  danDu        = 0;
		bool hetDanKoThay = false;   // hết đạn, không đủ TG thay
		bool vuaHetBang   = false;   // vừa đúng hết băng
		
		if (tDu >= thoiGianBanHetDan + tocDoThayBang) {
			danDu = dungLuongBang;
		} 
		else if (tDu >= thoiGianBanHetDan) {
			danDu = dungLuongBang;
			if (tDu == thoiGianBanHetDan)
				vuaHetBang   = true;   // vừa đúng hết băng, không còn TG
			else
				hetDanKoThay = true;   // hết đạn, thừa TG nhưng không đủ thay
		} 
		else {
			danDu = (int)(getTocDoRaDon() * tDu);
		}
		
		int tongDan    = n * dungLuongBang + danDu;
		int tongDamage = tongDan * getSatThuongCoBan();
		
		soLuongDan = dungLuongBang - danDu;
		
		cout << left << setw(28) << "	Tong so lan thay bang:"<< n << endl;
		cout << left << setw(28) << "	Dan con lai:" 			<< soLuongDan << " vien" << endl;
		
		if (hetDanKoThay)
			cout << RED 	<< "		>> Het dan! Khong du thoi gian thay bang." << RESET << endl;
		else if (vuaHetBang)
			cout << YELLOW 	<< "		>> Vua het bang dan dung luc ket thuc!"<< RESET << endl;
		
		cout << BOLD << B_RED << left << setw(28) << "	Tong damage:"<< tongDamage << RESET << endl;
		soLuongDan = dungLuongBang ; 
		return tongDamage;
	}
	
	void inThongTin() override {
		cout << "Player dang su dung " << CYAN  << BOLD<< "SUNG " << getTenVuKhi() 	<< RESET << endl;
		cout << left << setw(22) << "Sat thuong/vien:"	<< B_RED	<< getSatThuongCoBan()				<< RESET << endl;
		cout << left << setw(22) << "Toc do ban:"		<< B_YELLOW << getTocDoRaDon() 	<< " dan/giay" 	<< RESET << endl;
		cout << left << setw(22) << "Dan con lai:"		<< B_YELLOW << soLuongDan		<< " vien"		<< RESET << endl;
		cout << left << setw(22) << "Toc do thay bang:"	<< tocDoThayBang << " giay" << endl;
	}
	
	friend istream& operator>>(istream& is, Sung& sg);
	friend ostream& operator<<(ostream& os, Sung sg) { 
		sg.inThongTin(); 
		return os; 
	}
};

istream& operator>>(istream& is, Sung& sg) {
	string name; int damage; float td;
	is.ignore();
	cout << YELLOW << BOLD << "===== VU KHI: SUNG =====" << RESET << endl;
	cout << "Moi ban nhap ten Sung : "; 								getline(is, name);
	cout << "Moi ban nhap sat thuong / vien dan : ";					is >> damage;
	cout << "Moi ban nhap toc do ban / 1s (dan ban duoc trong 1s): ";	is >> td;
	sg.setTenVuKhi(name); 
	sg.setSatThuongCoBan(damage); 
	sg.setTocDoRaDon(td);
	cout << "Moi ban nhap so luong dan (so luong bang dan) : ";			is >> sg.soLuongDan;
	cout << "Moi ban nhap toc do thay bang (giay) : ";					is >> sg.tocDoThayBang;
	return is;
}

// CLASS KIEM
class Kiem : public VuKhi {
private:
	int doBen;
	int doBenMax;
public:
	Kiem() : VuKhi(), doBen(100), doBenMax(100) {}
	Kiem(string ten, int st, float td, int db) : VuKhi(ten, st, td), doBen(db), doBenMax(db) {}
	~Kiem() {}
	
	int  getDoBen()			{ return doBen;    }
	int  getDoBenMax()		{ return doBenMax; }
	void setDoBen(int db)	{ doBen		= (db < 0) ? 0 : db; }
	void setDoBenMax(int db){ doBenMax 	= (db < 0) ? 0 : db; }
	
	void TanCong() override {
		cout << YELLOW << BOLD << "[ KIEM ]" << RESET
		<< CYAN << " [KIEM " << getTenVuKhi() << RESET << "] "
		<< "Tan cong tam gan bang nhung nhat chem sac ben"
		<< " - " << B_RED << getSatThuongCoBan() << " dmg/chem" << RESET
		<< ", " << getTocDoRaDon() << " chem/giay." << endl;
		cout << endl;
	}
	
	int SatThuong(int t) override {
		if (doBen <= 0) {
			cout << RED 	<< ">> Kiem da gay! Khong the tan cong!"<< RESET << endl;
			cout << GREEN 	<<">> Vui long che tao lai Kiem " 		<< RESET << endl ;
			return 0;
		}
		
		int tongDon    = (int)(getTocDoRaDon() * t);
		int tongDamage = 0;
		
		cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
		cout << ">> Tan cong trong " << t << " giay (" << tongDon << " don)\n";
		
		for (int i = 0; i < tongDon; i++) {
			if (doBen <= 0) break;
			float 	heSoDoBen		= doBen / (float)doBenMax;
			int		damageMoiDon 	= (int)(getSatThuongCoBan() * heSoDoBen);
			tongDamage += damageMoiDon;
			doBen--;
		}
		
		cout << ">> Tong sat thuong: " << B_RED	<< tongDamage << RESET << endl;
		cout << ">> Do ben con lai:  ";
		if (doBen <= 0) 	cout << RED    << doBen << "/" << doBenMax << " [GAY!]"	<< RESET;
		else if (doBen < 30)cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]"<< RESET;
		else				cout << GREEN  << doBen << "/" << doBenMax 				<< RESET;
		cout << endl;
		
		return tongDamage;
	}
	
	void inThongTin() override {
		cout << "Player dang su dung "<< CYAN<<"  Kiem " << getTenVuKhi()<< RESET << endl;
		cout << left << setw(22) << "Sat thuong/don:"	<< B_RED	<< getSatThuongCoBan()			<< RESET << endl;
		cout << left << setw(22) << "Toc do:"			<< B_YELLOW << getTocDoRaDon() << " don/s"	<< RESET << endl;
		cout << left << setw(22) << "Do ben:";
		if (doBen <= 0)		cout << RED		<< doBen << "/" << doBenMax << " [GAY!]"	<< RESET;
		else if (doBen < 30)cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]"	<< RESET;
		else				cout << GREEN  << doBen << "/" << doBenMax					<< RESET;
		cout << endl;
	}
	
	friend ostream& operator<<(ostream& os, Kiem km) { km.inThongTin(); return os; }
	friend istream& operator>>(istream& is, Kiem& km) {
		string ten; int st; float td;
		is.ignore();
		cout << B_CYAN << BOLD << "===== VU KHI: KIEM =====" << RESET << endl;
		cout << "Nhap ten kiem : ";
		getline(is, ten);
		cout << "Nhap sat thuong moi don : "; 
		is >> st;
		cout << "Nhap toc do ra don /1s : ";  
		is >> td;
		km.setTenVuKhi(ten); 
		km.setSatThuongCoBan(st); 
		km.setTocDoRaDon(td);
		cout << "Nhap do ben : "; 
		is >> km.doBen;
		km.doBenMax = km.doBen;
		if (km.doBen < 0) km.doBen = 0;
		return is;
	}
};


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

//CLASS NHAN VAT
class NhanVat {
private:
	string nameNV;
	int    hp;
	int    mana;
	int    manaMax;
	int    hoiManaPerSec;   // mana hoi lai moi giay (mac dinh 5)
	VuKhi* vk[3];			// sung - kiem - phep 
	int    viTriDangDung;
	
public:
	NhanVat(string _name = "Khong ro", int _hp = 1000, int _mana = 1000, VuKhi* _vk[] = nullptr, int vt = 0, int hm = 5)
	: nameNV(_name), hp(_hp), mana(_mana), manaMax(_mana),hoiManaPerSec(hm), viTriDangDung(vt)
	{
		for (int i = 0; i < 3; i++)
			vk[i] = (_vk ? _vk[i] : nullptr);
	}
	~NhanVat() {}
	
	string 	getName() 			{ return nameNV;		}
	int		getHp()				{ return hp;            }
	int		getMana()			{ return mana;			}
	int		getManaMax(){ return manaMax;				}
	int		getHoiManaPerSec(){ return hoiManaPerSec; }
	int		getViTriDangDung(){ return viTriDangDung; }
	
	void setName(string _name)		{ nameNV = _name; }
	void setHp(int _hp)				{ hp    = (_hp   < 0) ? 0 : _hp; }
	void setMana(int _mana)			{ mana  = (_mana < 0) ? 0 : (_mana > manaMax ? manaMax : _mana); }
	void setHoiManaPerSec(int hm)	{ hoiManaPerSec = (hm < 0) ? 0 : hm; }
	void setViTriDangDung(int vt)	{ viTriDangDung = vt; }
	
	// Hoi mana trong t giay 
	int HoiMana(int t) {
		int tongHoi = hoiManaPerSec * t;
		int truoc	= mana;
		setMana(mana + tongHoi);
		return mana - truoc;   // tra ve so mana thuc su hoi duoc
	}
	
	void trangBiHienTai() {
		for (int i = 0; i < 3; i++) {
			cout << B_WHITE << "[" << i+1 << "] " << RESET;
			vk[i]->TanCong();
		}
	}
	
	VuKhi*& operator[](int index) { 
		return vk[index]; 
	}
	
	int SatThuong(int t) {
		VuKhi* v = vk[viTriDangDung];
		if (!v) { 
			cout << RED << ">> [" << nameNV << "] Chua co vu khi!" << RESET << endl; return 0; 
		}
		return v->SatThuong(t);
	}
	
	void BiTanCong(int st) {
		int hpTruoc = hp;
		hp -= st;
		if (hp < 0) hp = 0;
		cout << RED << ">> " << nameNV << " bi tan cong" << RESET << endl;
		cout << "	HP: " << B_GREEN << hpTruoc << RESET << " -> " << B_RED << hp << RESET << endl;
	}
	
	bool ConSong() const { 
		return hp > 0; 
	}
	
	friend ostream& operator<<(ostream& out, NhanVat nv) {
		out << left << setw(22) << "Ten:"  << B_WHITE  << nv.nameNV	<< RESET << endl;
		out << left << setw(22) << "HP:"   << B_RED  << nv.hp 		<< RESET << endl;
		out << left << setw(22) << "Mana:" << BLUE   << nv.mana <<B_BLUE<< "/" << nv.manaMax << RESET << endl;
		out << left << setw(22) << "Hoi mana/giay:" << B_BLUE << nv.hoiManaPerSec << RESET << endl;
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
	cout << mau << YELLOW << BOLD << "[ PHEP THUAT ]" << RESET
	<< " [" << mau << getTenVuKhi() << RESET << "] "
	<< "Loai: " << mau << BOLD << loaiPhep << RESET
	<< " - " << B_RED << getSatThuongCoBan() << " dmg/don" << RESET
	<< ", " << getTocDoRaDon() << " don/giay." << endl;
//	cout << "    >> Mana tieu thu/don: " << B_BLUE << manaTieuThu << RESET;
//	if (nguoiDungPhep)
//		cout << " | Mana hien tai: " << B_BLUE
//		<< nguoiDungPhep->getMana() << "/" << nguoiDungPhep->getManaMax() << RESET;
//	cout << endl;
}

int PhepThuat::SatThuong(int t) {
	if (!nguoiDungPhep) {
		cout << RED << ">> [" << getTenVuKhi() << "] Chua gan nguoi dung phep!" << RESET << endl;
		return 0;
	}
	
	const char* mau          = mauPhep(loaiPhep);
	const int   base         = getSatThuongCoBan();
	const float thoiGian1Don = 1.0f / getTocDoRaDon();  // giay/don
	const int   hoiMana1s    = nguoiDungPhep->getHoiManaPerSec();
	const int   manaMax      = nguoiDungPhep->getManaMax();
	int         manaHienTai  = nguoiDungPhep->getMana();
	
	// ── Tinh so don co the ra trong t giay ──────────────────────────────
	// Mana net tieu thu moi don (sau khi tru hoi mana trong thoiGian1Don)
	int manaNetMoiDon = manaTieuThu - (int)(hoiMana1s * thoiGian1Don);
	if (manaNetMoiDon < 0) manaNetMoiDon = 0;
	
	// Neu mana ban dau khong du don dau, can doi de hoi
	float tChoHoi = 0.0f;
	if (manaHienTai < manaTieuThu) {
		if (hoiMana1s <= 0) {
			cout << RED << BOLD << "!! CANH BAO: Khong du mana, khong the hoi!" << RESET << endl;
			return 0;
		}
		tChoHoi = (float)(manaTieuThu - manaHienTai) / hoiMana1s;
		if (tChoHoi > t) {
			cout << RED << BOLD << "!! CANH BAO: Khong du mana va khong the hoi kip trong "
			<< t << " giay!" << RESET << endl;
			return 0;
		}
		manaHienTai += (int)(hoiMana1s * tChoHoi);
	}
	
	// So don toi da trong thoi gian con lai
	float tHieuQua  = t - tChoHoi;
	int   soDon     = (int)(tHieuQua / thoiGian1Don);
	
	// Gioi han boi mana: neu manaNetMoiDon > 0, mana se can dan theo so don
	if (manaNetMoiDon > 0) {
		int donToiDaMana = manaHienTai / manaNetMoiDon;
		if (soDon > donToiDaMana) soDon = donToiDaMana;
	}
	if (soDon <= 0) {
		cout << RED << ">> Khong du mana de ra bat ky don nao!" << RESET << endl;
		return 0;
	}
	
	// ── Tinh sat thuong co ban ───────────────────────────────────────────
	int tongDameCoBan = soDon * base;
	
	// ── Tinh hieu ung theo loai phep (cong thuc truc tiep) ──────────────
	int tongDameHieuUng = 0;
	int stackHoa = 0, soChiMangSet = 0, soCritSet = 0;
	
	if (loaiPhep == "Hoa") {
		// Stack tang tu 1->5 roi giu nguyen, moi don cong stackHoa*(base/5)
		// Tong = sum(i=1..min(5,soDon)) * base/5  +  max(0, soDon-5)*5*(base/5)
		int donLenStack = min(soDon, 5);
		int bonusLenStack = donLenStack * (donLenStack + 1) / 2 * (base / 5);
		int donSauStack   = max(0, soDon - 5);
		int bonusSauStack = donSauStack * 5 * (base / 5);
		tongDameHieuUng   = bonusLenStack + bonusSauStack;
		stackHoa          = min(soDon, 5);
	}
	else if (loaiPhep == "Phong") {
		// Don thu i co boSuc = min(1 + (i-1)*0.1, 3.0) -> bonus = base*(boSuc-1)
		// boSuc dat max 3.0 tu don thu 21 tro di
		int donTangDan = min(soDon, 21);
		int donMax     = max(0, soDon - 21);
		int bonusTangDan = 0;
		for (int i = 1; i <= donTangDan; i++)
			bonusTangDan += (int)(base * (i - 1) * 0.1f);
		tongDameHieuUng = bonusTangDan + donMax * 2 * base; // boSuc max = 3 -> bonus = 2*base
	}
	else if (loaiPhep == "Thuy") {
		// Moi 3 don burst them base*0.5
		tongDameHieuUng = (soDon / 3) * (int)(base * 0.5f);
	}
	else if (loaiPhep == "Set") {
		// 10% siet chet (x3 = +2*base), 25% chi mang (x2 = +base)
		// Dung ky vong: E[bonus/don] = 0.10*2*base + 0.25*base = 0.45*base
		// Nhung giu rand() de con cam giac may man
		for (int i = 0; i < soDon; i++) {
			int roll = rand() % 100;
			if      (roll < 10) { tongDameHieuUng += base * 2; soCritSet++;    }
			else if (roll < 35) { tongDameHieuUng += base;     soChiMangSet++; }
		}
	}
	
	// ── Cap nhat mana ────────────────────────────────────────────────────
	int manaThucTieu = soDon * manaNetMoiDon;
	manaHienTai = max(0, min(manaHienTai - manaThucTieu, manaMax));
	nguoiDungPhep->setMana(manaHienTai);
	
	// ── In ket qua ───────────────────────────────────────────────────────
	int tongDamage = tongDameCoBan + tongDameHieuUng;
	
	cout << endl;
	cout << mau << BOLD
	<< "[=== KET QUA: " << getTenVuKhi() << " | " << loaiPhep << " | " << t << " giay ===]"
	<< RESET << endl;
	cout << WHITE << string(50, '-') << RESET << endl;
	
	cout << left << setw(30) << "  Tong don da danh:"
	<< B_WHITE << soDon << " don" << RESET << endl;
	
	if (tChoHoi > 0)
		cout << left << setw(30) << "  Thoi gian cho hoi mana:"
		<< YELLOW << (int)tChoHoi << "s" << RESET << endl;
	
	cout << left << setw(30) << "  Sat thuong co ban:"
	<< B_RED << tongDameCoBan << RESET << endl;
	
	if (loaiPhep == "Hoa" && tongDameHieuUng > 0)
		cout << left << setw(30) << "  Sat thuong thieu dot:"
		<< RED << "+" << tongDameHieuUng << " (stack max " << stackHoa << "/5)" << RESET << endl;
	else if (loaiPhep == "Phong" && tongDameHieuUng > 0)
		cout << left << setw(30) << "  Bonus phong (tang dan):"
		<< B_CYAN << "+" << tongDameHieuUng << RESET << endl;
	else if (loaiPhep == "Thuy" && tongDameHieuUng > 0)
		cout << left << setw(30) << "  Burst thuy (moi 3 don):"
		<< BLUE << "+" << tongDameHieuUng << RESET << endl;
	else if (loaiPhep == "Set" && tongDameHieuUng > 0) {
		cout << left << setw(30) << "  Chi mang (x2):"
		<< MAGENTA << "x" << soChiMangSet << " lan" << RESET << endl;
		cout << left << setw(30) << "  Siet chet (x3):"
		<< B_MAGENTA << BOLD << "x" << soCritSet << " lan" << RESET << endl;
		cout << left << setw(30) << "  Tong bonus Set:"
		<< MAGENTA << "+" << tongDameHieuUng << RESET << endl;
	}
	
	cout << WHITE << string(50, '-') << RESET << endl;
	cout << BOLD << B_RED << left << setw(30) << "  TONG DAMAGE:"
	<< tongDamage << RESET << endl;
	cout << left << setw(30) << "  Mana con lai:"
	<< B_BLUE << nguoiDungPhep->getMana() << "/" << manaMax << RESET << endl;
	cout << WHITE << string(50, '=') << RESET << endl;
	
	return tongDamage;
}

void PhepThuat::inThongTin() {
	const char* mau = mauPhep(loaiPhep);
	cout << "Player dang su dung " << mau << BOLD << "VU KHI: Phep Thuat "
	<< getTenVuKhi() << RESET << endl;
	cout << left << setw(25) << "Loai phep:"         << mau << BOLD << loaiPhep            << RESET << endl;
	cout << left << setw(25) << "Sat thuong co ban:" << B_RED    << getSatThuongCoBan()    << RESET << endl;
	cout << left << setw(25) << "Toc do ra don:"     << B_YELLOW << getTocDoRaDon() << " don/giay" << RESET << endl;
	cout << left << setw(25) << "Mana tieu thu/don:" << B_BLUE   << manaTieuThu             << RESET << endl;
//	if (nguoiDungPhep) {
//		cout << left << setw(25) << "Mana hien tai:"
//		<< B_BLUE << nguoiDungPhep->getMana() << "/" << nguoiDungPhep->getManaMax() << RESET << endl;
//		cout << left << setw(25) << "Hoi mana/giay:"
//		<< B_BLUE << nguoiDungPhep->getHoiManaPerSec() << RESET << endl;
//	}
}

// MENU CHINH
void hienThiGiaoDien(NhanVat& nr, NhanVat& p) {
	clearScreen();
	cout << RED << BOLD << "========== MUC TIEU: " << nr.getName() << " ==========" << RESET << "\n";
	cout << nr;
	cout << "PLAYER: " <<B_WHITE<< p.getName() << RESET
	<< " | HP: " 	<< B_RED << p.getHp() 	<< RESET
	<< " | Mana: " 	<< BLUE << p.getMana() <<B_BLUE<< "/" << p.getManaMax() << RESET << "\n";
	cout  << "TRANG BI HIEN TAI:" << RESET << "\n";
	p.trangBiHienTai();
	cout << "\n";
	cout << YELLOW << BOLD << "===== Vu Khi Dang Su Dung =====" << RESET <<endl;
	p[p.getViTriDangDung()]->inThongTin();
	cout << "\n";
	cout << GREEN << "==============================" << RESET <<endl;
	cout << "  1. Tan cong"		<< RESET <<endl;
	cout << "  2. Doi vu khi"	<< RESET <<endl;
	cout << "  3. Che tao lai vu khi" << RESET <<endl;
	cout << "  0. Thoat"		<< RESET <<endl;
	cout << GREEN	<< "==============================" << RESET <<endl;
	cout << "Lua chon: ";
}

// MAIN

int main() {
	srand((unsigned)time(0));
	
	Sung 		sung("AK47",      35, 10.0f, 30, 2.0f);
	Kiem		kiem("Muramasa",  50,  2.0f, 100);
	PhepThuat	phep("Amaterasu", 60,  1.0f, "Hoa", 15);
	
	VuKhi* vk[3] = { &sung, &kiem, &phep };
	
	NhanVat nr		("BAC NONG DAN ",	 10000, 100);
	NhanVat player	("Shadow Reaper",10000, 500, vk, 0);
	
	phep.setNguoiDungPhep(&player);
	
	int lua = -1;
	while (lua != 0 && nr.ConSong()) {
		hienThiGiaoDien(nr, player);
		cin >> lua;
		
		if (lua == 1) {
			clearScreen();
			cout << RED << BOLD << "========== MUC TIEU: " << nr.getName() << " ==========" << RESET << "\n";
			cout << nr;
			cout << RED<< "PLAYER: " <<B_WHITE<< player.getName() << RESET
			<< " | HP: " << B_RED << player.getHp() << RESET
			<< " | Mana: " << BLUE << player.getMana() <<B_BLUE<< "/" << player.getManaMax() << RESET <<endl;
			cout << string(30,'=')<<endl;
			cout << YELLOW << BOLD << "===== TAN CONG =====" << RESET << "\n";
			player[player.getViTriDangDung()]->TanCong();
			cout << "\nNhap thoi gian tan cong (giay): ";
			int t; cin >> t;
			int damage = player[player.getViTriDangDung()]->SatThuong(t);
			cout << "\n" << B_RED << BOLD << "Sat thuong gay len " << nr.getName() << ": " << damage << RESET <<endl;
			if (player.getViTriDangDung() != 2 ) {
				int x = player.HoiMana(t);
				if (x > 0) cout <<"	>>Da phuc hoi them "<<x<<" Mana\n";
			}
			if (damage > 0) {
				cout << endl;
				nr.BiTanCong(damage);
				if (nr.ConSong())
					cout << YELLOW << "\n>> " << nr.getName() << " van song! HP: " << nr.getHp() << RESET <<endl;
				else
					cout << RED << BOLD << "\n>> " << nr.getName() << " da bi ha guc!" << RESET <<endl;
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
			cout << YELLOW << "  1. Sung"		<< RESET << "\n";
			cout << B_CYAN << "  2. Kiem"		<< RESET << "\n";
			cout << MAGENTA<< "  3. Phep Thuat"	<< RESET << "\n";
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
