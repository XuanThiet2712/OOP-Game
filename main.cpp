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
	// get 
	string	getTenVuKhi()		{ return tenVuKhi;			}
	int		getSatThuongCoBan()	{ return satThuongCoBan;	}
	float	getTocDoRaDon()		{ return tocDoRaDon;		}
	// set
	void setTenVuKhi(string ten)	{ tenVuKhi			= ten;	}
	void setSatThuongCoBan(int st)	{ satThuongCoBan	= st;	}
	void setTocDoRaDon(float td)	{ tocDoRaDon		= td;	}
	// 
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
	//constructor / destructor 
	Sung() : VuKhi(), soLuongDan(30), tocDoThayBang(2) {}
	Sung(string ten, int st, float td, int sld, float tdb)
	: VuKhi(ten, st, td), soLuongDan(sld), tocDoThayBang(tdb) {}
	Sung(const Sung& sg):VuKhi(sg){
		soLuongDan = sg.soLuongDan ;
		tocDoThayBang = sg.tocDoThayBang ; 
	}
	~Sung(){}
	//Mo ta cach tan cong cua Sung
	void TanCong() override {
		cout << YELLOW << BOLD << "[ SUNG ]" << RESET
		<<left <<setw(10) << CYAN << " [ SUNG " << getTenVuKhi()  << "] " << RESET
		<< "Tan cong tam xa bang nhung vien dan chay bong"<<endl;
//		<< " - " << B_RED << getSatThuongCoBan() << " dmg/vien" << RESET
//		<< ", " << getTocDoRaDon() << " dan/giay." << endl;
	}
	//Tinh dame tan cong sau t giay 
	int SatThuong(int t) override {
		int dungLuongBang = soLuongDan;
		
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
		cout <<string(22,'=')<<endl;
		soLuongDan = dungLuongBang ; 
		cout <<">> Tran chien ket thuc , Bang dan da duoc nap day lai nhu cu"<<endl;
		
		return tongDamage;
	}
	// In thong tin trang thai vu khi hien tai 
	void inThongTin() override {
		cout << left << setw(22)<< "Player dang su dung " << CYAN  << BOLD<< "SUNG " << getTenVuKhi() 	<< RESET << endl;
		cout << left << setw(22) << "Sat thuong/vien:"	<< B_RED	<< getSatThuongCoBan()				<< RESET << endl;
		cout << left << setw(22) << "Toc do ban:"		<< B_YELLOW << getTocDoRaDon() 	<< " dan/giay" 	<< RESET << endl;
		cout << left << setw(22) << "So luong dan:"		<< B_YELLOW << soLuongDan		<< " vien"		<< RESET << endl;
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
public:
	//constructor 
	Kiem() : VuKhi(){
		doBen = 100 ; 
	}
	Kiem(string ten, int st, float td, int db) : VuKhi(ten, st, td){
		doBen = db ; 
	}
	Kiem(const Kiem& other) 
	: VuKhi(other), doBen(other.doBen) {}
	//destructor 
	~Kiem() {}
	
	int  getDoBen()			{ return doBen;    }
	void setDoBen(int db)	{ doBen		= (db < 0) ? 0 : db; }
	
	void TanCong() override {
		cout << YELLOW << BOLD << "[ KIEM ]" << RESET
		<<left << setw(10) <<  CYAN << " [ KIEM " << getTenVuKhi() << "] "  << RESET
		<< "Tan cong tam gan bang nhung nhat chem sac ben";
//		<< " - " << B_RED << getSatThuongCoBan() << " dmg/chem" << RESET
//		<< ", " << getTocDoRaDon() << " chem/giay." << endl;
		cout << endl;
	}
	
	int SatThuong(int t) override {
		double doBenMax = doBen ; 
		if (doBen <= 0) {
			cout << RED 	<< ">> Kiem da gay! Khong the tan cong!"<< RESET << endl;
			cout << GREEN 	<<">> Vui long che tao lai Kiem " 		<< RESET << endl ;
			return 0;
		}
		
		int n   = min((int)(getTocDoRaDon() * t) , doBen); // tong don 
		
		cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
		cout << ">> Tan cong trong " << t << " giay (" << n << " don)\n";
		
		int tongDamage = getSatThuongCoBan()/(float)(2*doBen) * n * (2*doBen - n + 1 ) ; // tinh dame ; 
		
		cout << ">> Tong sat thuong: " << B_RED	<< tongDamage << RESET << endl;
		
		cout << ">> Do ben con lai:  ";
		if (doBen <= 0) 	cout << RED    << doBen << "/" << doBenMax << " [GAY!]"	<< RESET;
		else if (doBen/doBenMax < 0.3f  )cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]"<< RESET;
		else				cout << GREEN  << doBen << "/" << doBenMax 				<< RESET;
		cout << endl;
		if (doBen > 0) {
			doBen = doBenMax ;
			cout <<">> Sau khi chien dau xong,thanh kiem da duoc mai lai ve 100% do ben nhu cu"<<endl;
		}
		else {
			cout <<">> Kiem da gay, hay che tao lai !"<<endl;
		}
		
		return tongDamage;
	}
	
	void inThongTin() override {
		cout << "Player dang su dung "<< CYAN<<"  Kiem " << getTenVuKhi()<< RESET << endl;
		cout << left << setw(22) << "Sat thuong/don:"	<< B_RED	<< getSatThuongCoBan()			<< RESET << endl;
		cout << left << setw(22) << "Toc do:"			<< B_YELLOW << getTocDoRaDon() << " don/s"	<< RESET << endl;
		cout << left << setw(22) << "Do ben:";
		if (doBen <= 0)		cout << RED		<< doBen << " [GAY!]"	<< RESET;
		else if (doBen < 30)cout << YELLOW << doBen << " [THAP!]"	<< RESET;
		else				cout << GREEN  << doBen 					<< RESET;
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
	PhepThuat(const PhepThuat& pt):VuKhi(pt){
		loaiPhep = pt.loaiPhep ; 
		manaTieuThu = pt.manaTieuThu ;
		nguoiDungPhep = pt.nguoiDungPhep ; 
	}
	~PhepThuat() {}
	
	string   getLoaiPhep(){ return loaiPhep;       }
	int      getManaTieuThu() { return manaTieuThu;    }
	NhanVat* getNguoiDungPhep(){ return nguoiDungPhep;  }
	
	void setLoaiPhep(string lp)        { loaiPhep      = lp;  }
	void setManaTieuThu(int mtb)       { manaTieuThu   = mtb; }
	void setNguoiDungPhep(NhanVat* nv) { nguoiDungPhep = nv;  }
	
	void TanCong()        override;
	int  SatThuong(int t) override;
	void inThongTin()     override;
	
	friend ostream& operator<<(ostream& out, PhepThuat p) { 
		p.inThongTin(); 
		return out; 
	}
	friend istream& operator>>(istream& is,  PhepThuat& p) {
		string ten, lp; int st, mtb; float td;
		is.ignore();
		cout << B_MAGENTA << BOLD << "===== VU KHI: PHEP THUAT =====" << RESET << endl;
		cout << "Nhap ten phep          : "; getline(is >> ws, ten);
		cout << "Nhap sat thuong/don    : "; is >> st;
		cout << "Nhap toc do ra don     : "; is >> td;
		cout << "Nhap mana tieu thu/don : "; is >> mtb;
		cout << "\nChon loai phep:" << endl;
		cout << "  " << RED    << "1. Hoa   (moi don gay them 10% sat thuong goc, chay am i)"         << RESET << endl;
		cout << "  " << YELLOW << "2. Loi   (moi 5 don binh thuong, don thu 6 CRIT x2 sat thuong)"    << RESET << endl;
		cout << "  " << B_CYAN << "3. Phong (sat thuong +1%/don, reset chuoi khi can hoi mana)"       << RESET << endl;
		cout << "Lua chon (1-3): ";
		int chon; is >> chon;
		switch (chon) {
			case 1: lp = "Hoa";   break;
			case 2: lp = "Loi";   break;
			case 3: lp = "Phong"; break;
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
	int    mana; // mana hien tai 
	int    manaMax;
	int    hoiMana;   // mana hoi lai moi giay (mac dinh 5)
	VuKhi* vk[3];			// sung - kiem - phep 
	int    viTriDangDung;   // vi tri dung vu khi 
	
public:
	NhanVat(string _name = "Khong ro", int _hp = 1000, int _mana = 1000,int _manaMax = 1000 , int hm = 5 ,  VuKhi* _vk[] = nullptr, int vt = 0)
	: nameNV(_name), hp(_hp), mana(_mana), manaMax(_manaMax),hoiMana(hm), viTriDangDung(vt)
	{
		for (int i = 0; i < 3; i++)
			vk[i] = (_vk ? _vk[i] : nullptr);
	}
	NhanVat(const NhanVat& x){
		nameNV = x.nameNV ; 
		hp = x.hp ; 
		mana = x.mana ; 
		manaMax = x.manaMax ; 
		for (int i = 0; i < 3; i++){
			vk[i] = x.vk[i];
		}

		viTriDangDung = x.viTriDangDung ; 
		hoiMana = x.hoiMana ; 
	}
	~NhanVat() {}
	
	string 	getName() 			{ return nameNV;		}
	int		getHp()				{ return hp;            }
	int		getMana()			{ return mana;			}
	int		getManaMax(){ return manaMax;				}
	int		getHoiMana(){ return hoiMana; }
	int		getViTriDangDung(){ return viTriDangDung; }
	
	void setName(string _name)		{ nameNV = _name; }
	void setHp(int _hp)				{ hp    = (_hp   < 0) ? 0 : _hp; }
	void setMana(int _mana)			{ mana  = (_mana < 0) ? 0 : (_mana > manaMax ? manaMax : _mana); }
	void setHoiMana(int hm)	{ hoiMana = (hm < 0) ? 0 : hm; }
	void setViTriDangDung(int vt)	{ viTriDangDung = vt; }
	
	// Hoi mana trong t giay 
	int HoiMana(int t) {
		int tongHoi = hoiMana * t;
		int truoc	= mana;
		setMana(mana + tongHoi);
		return mana - truoc;   // tra ve so mana thuc su hoi duoc
	}
	// trang bi vu khi dang su dung hien tai , bao gom sung kiem phep thuat
	void trangBiHienTai() {
		for (int i = 0; i < 3; i++) {
			cout << B_WHITE << "[" << i+1 << "]" << RESET;
			vk[i]->TanCong();
		}
	}
	// vu khi dang su dung
	VuKhi*& operator[](int index) { 
		return vk[index]; 
	}
	//sat thuong vu khi hien tai gay ra trong t giay 
	int SatThuong(int t) {
		VuKhi* v = vk[viTriDangDung];
		if (!v) { 
			cout << RED << ">> [" << nameNV << "] Chua co vu khi!" << RESET << endl; return 0; 
		}
		return v->SatThuong(t);
	}
	// nhan vat bi tan cong 
	void BiTanCong(int st) {
		int hpTruoc = hp;
		hp -= st;
		if (hp < 0) hp = 0;
		cout << RED << ">> " << nameNV << " bi tan cong" << RESET << endl;
		cout << "	HP: " << B_GREEN << hpTruoc << RESET << " -> " << B_RED << hp << RESET << endl;
	}
	// kiem tra trang thai con song hay da chet cua nhan vat 
	bool ConSong(){ 
		return hp > 0; 
	}
	
	friend istream& operator>>(istream& in, NhanVat& nv) {
		cout << "Nhap ten nhan vat: "; in.ignore(); getline(in, nv.nameNV);
		cout << "Nhap HP: ";   in >> nv.hp;
		cout << "Nhap Mana: "; in >> nv.mana;
		nv.manaMax = nv.mana;
		return in;
	}
	friend ostream& operator<<(ostream& out, NhanVat nv) {
		out << left << setw(22) << "Ten:"  << B_WHITE  << nv.nameNV	<< RESET << endl;
		out << left << setw(22) << "HP:"   << B_RED  << nv.hp 		<< RESET << endl;
		out << left << setw(22) << "Mana:" << BLUE   << nv.mana <<B_BLUE<< "/" << nv.manaMax << RESET << endl;
		out << left << setw(22) << "Hoi mana/giay:" << B_BLUE << nv.hoiMana << RESET << endl;
		out << CYAN <<string(70,'=') << RESET << endl;
		return out;
	}
};

//// PHEP THUAT
static const char* mauPhep(const string& lp) {
	if (lp == "Hoa")   return RED;
	if (lp == "Loi")  return YELLOW;
	if (lp == "Phong") return B_CYAN;
	return WHITE;
}		// mau loai phep 

void PhepThuat::TanCong() {
	const char* mau = mauPhep(loaiPhep);
	cout << mau << YELLOW << BOLD << "[ PHEP THUAT ]" << RESET
	<<left<<setw(1) <<CYAN<< "[ "  << getTenVuKhi()  << " ] " << RESET
	<< " Su dung 1 nang luc tam linh ky la tan cong vao ke dich " <<endl ; 
	
	// Mo ta hieu ung rieng tung loai phep
	if (loaiPhep == "Hoa") {
		cout << RED << "    >> [HOA PHAP] "		<< RESET 
		<< "Moi don gay them " << (int)(getSatThuongCoBan() * 0.1f)
		<< " dmg thieu dot (10% sat thuong goc). Lua thieu ngay cang hung han!" << RESET << endl;
	} else if (loaiPhep == "Loi") {
		cout << YELLOW << "    >> [LOI PHAP] "  << RESET 
		<< "Danh 5 don binh thuong, don thu 6 no CRIT x2 ("
		<< getSatThuongCoBan() * 2 << " dmg). Chu ky cu tiep tuc!" << RESET << endl;
	} else if (loaiPhep == "Phong") {
		cout << B_CYAN << "    >> [PHONG PHAP] " << RESET 
		<< "Sat thuong cong don cang danh cang manh, moi don danh ke tiep khong ngung nghi se duoc + them 1% damage" << RESET << endl;
	}
}

int PhepThuat::SatThuong(int t) {
	if (!nguoiDungPhep) {
		cout << RED << ">> [" << getTenVuKhi() << "] Chua biet nguoi dung phep!" << RESET << endl;
		return 0;
	}
	
	const char* mau         = mauPhep(loaiPhep);
	const int   base        = getSatThuongCoBan();
	const int   hoiMana1s   = nguoiDungPhep->getHoiMana();
	const int   manaMax     = nguoiDungPhep->getManaMax();
	const float thoiGian1Don = 1.0f / getTocDoRaDon(); // giay / 1 don
	
	// ── Kiem tra ban dau 
	int manaHienTai = nguoiDungPhep->getMana();
	if (manaHienTai < manaTieuThu) {
		// Tinh thoi gian hoi du mana cho don dau
		if (hoiMana1s <= 0) {
			cout << RED << BOLD << "!! Khong du mana va khong the hoi!" << RESET << endl;
			return 0;
		}
		float tHoi = (float)(manaTieuThu - manaHienTai) / hoiMana1s;
		if (tHoi > t) {
			cout << RED << BOLD << "!! Khong the hoi du mana trong " << t << " giay!" << RESET << endl;
			return 0;
		}
	}
	
	// ── Mo phong theo chu ky: danh het mana -> hoi -> danh tiep ────────
	// Trong luc danh: KHONG hoi mana
	// Het mana: dung lai, hoi mana (tính thoi gian cho), roi danh tiep
	int   tongDamage  = 0;
	int   soDon       = 0;
	int   soCrit      = 0;   // Loi: dem so lan crit
	int   donPhong    = 0;   // Phong: vi tri don trong chuoi (reset khi het mana)
	float tHienTai    = 0.0f;
	int   manaHT      = manaHienTai;
	
	while (tHienTai < (float)t) {
		// Neu khong du mana: hoi mana, tinh thoi gian cho
		if (manaHT < manaTieuThu) {
			if (hoiMana1s <= 0) break; // khong the hoi, dung
			int canHoi      = manaTieuThu - manaHT;
			float tChoHoi   = (float)canHoi / hoiMana1s;
			tHienTai       += tChoHoi;
			if (tHienTai >= (float)t) break; // het gio trong luc hoi
			manaHT         += canHoi; // du mana cho 1 don
			donPhong        = 0;      // Phong: het mana -> reset chuoi ve x1
		}
		
		// Kiem tra con du gio danh 1 don khong
		if (tHienTai + thoiGian1Don > (float)t) break;
		
		// Danh don (khong hoi mana trong luc danh)
		manaHT     -= manaTieuThu;
		tHienTai   += thoiGian1Don;
		soDon++;
		
		if (loaiPhep == "Hoa") {
			tongDamage += (int)(base * 1.1f);
			
		} else if (loaiPhep == "Loi") {
			if (soDon % 6 == 0) {
				tongDamage += base * 2;
				soCrit++;
			} else {
				tongDamage += base;
			}
			
		} else if (loaiPhep == "Phong") {
			float nhan = min(1.0f + donPhong * 0.01f, 3.0f);
			tongDamage += (int)(base * nhan);
			donPhong++;
		}
	}
	
	nguoiDungPhep->setMana(manaHT > manaMax ? manaMax : (manaHT < 0 ? 0 : manaHT));
	
	if (soDon <= 0) {
		cout << RED << ">> Khong du mana va thoi gian de ra bat ky don nao!" << RESET << endl;
		return 0;
	}
	
	// ── In ket qua ───────────────────────────────────────────────────────
	cout << endl;
	cout << mau << BOLD
	<< "[=== KET QUA: " << getTenVuKhi() << " | " << loaiPhep << " | " << t << " giay ===]"
	<< RESET << endl;
	cout << WHITE << string(50, '-') << RESET << endl;
	
	cout << left << setw(30) << "  Tong don da danh:"
	<< B_WHITE << soDon << " don" << RESET << endl;
	
	if (loaiPhep == "Hoa") {
		cout << left << setw(30) << "  Cong thuc:"
		<< RED << soDon << " don x " << base << " x 1.1 (thieu dot +10%/don)" << RESET << endl;
		
	} else if (loaiPhep == "Loi") {
		int donThuong = soDon - soCrit;
		cout << left << setw(30) << "  So lan CRIT (don thu 6):"
		<< YELLOW << BOLD << soCrit << " lan crit!" << RESET << endl;
		cout << left << setw(30) << "  Cong thuc:"
		<< YELLOW << donThuong << " don x " << base
		<< " + " << soCrit << " crit x " << base*2 << " (x2)" << RESET << endl;
		
	} else if (loaiPhep == "Phong") {
		float nhanCuoi = min(1.0f + (donPhong - 1) * 0.01f, 3.0f);
		cout << left << setw(30) << "  Nhan cuoi cung dat duoc:"
		<< B_CYAN << "x" << fixed << setprecision(2) << nhanCuoi
		<< " (+" << (donPhong-1) << "% sau " << donPhong << " don)" << RESET << endl;
		cout << left << setw(30) << "  Cong thuc:"
		<< B_CYAN << "sum(base * (1 + i*1%)), i=0.." << (soDon-1)
		<< " | reset khi can hoi mana" << RESET << endl;
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
	
	// Mo ta hieu ung
	if (loaiPhep == "Hoa")
		cout << RED    << "  >> Hieu ung: Moi don thieu dot them " << (int)(getSatThuongCoBan()*0.1f)
		<< " dmg (+10% moi don)" << RESET << endl;
	else if (loaiPhep == "Loi")
		cout << YELLOW << "  >> Hieu ung: Don thu 6 trong chu ky 6 don no CRIT x2 ("
		<< getSatThuongCoBan()*2 << " dmg). Het mana se hoi va danh tiep!" << RESET << endl;
	else if (loaiPhep == "Phong")
		cout << B_CYAN << "  >> Hieu ung: +1%/don (don 1=x1.00, don 100=x2.00, max x3.00). Het mana: hoi mana, reset chuoi ve x1!" << RESET << endl;
}

// MENU CHINH
void hienThiGiaoDien(NhanVat& nr, NhanVat& p) {
	clearScreen();
	cout << RED << BOLD << "========== MUC TIEU: " << nr.getName() << " ==========" << RESET << "\n";
	cout << nr;
	cout << "PLAYER: " <<B_WHITE<< p.getName() << RESET
	<< " | HP: " 	<< B_RED << p.getHp() 	<< RESET
	<< " | Mana: " 	<< BLUE << p.getMana() <<B_BLUE<< "/" << p.getManaMax() << RESET 
	<< " - "		<< p.getHoiMana() << " mana/s" << endl ; 
	cout << CYAN <<string(70,'=') << RESET << endl;
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
	
	NhanVat nr		("BAC NONG DAN ",	 10000, 100 , 100 );
	NhanVat player	("Shadow Reaper",10000, 500 , 500 ,5 ,  vk, 0);
	
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
