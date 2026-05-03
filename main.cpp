#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;
//color
#define RESET	"\033[0m"  // Reset lại màu về mặc định
#define BOLD	"\033[1m"	// In chữ đậm (bold)
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"   //  tím hồng
#define CYAN	"\033[36m"   //  xanh cyan (xanh ngọc)
#define WHITE	"\033[37m"   // trắng

// mau sang
#define B_RED		"\033[91m" // Đỏ sáng
#define B_GREEN		"\033[92m" // Xanh lá sáng
#define B_YELLOW	"\033[93m" // Vàng sáng
#define B_BLUE		"\033[94m" // Xanh dương sáng
#define B_MAGENTA	"\033[95m" // Tím sáng
#define B_CYAN		"\033[96m" // Cyan sáng
#define B_WHITE		"\033[97m" // Trắng sáng
// clear Screen
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
	string	getTenVuKhi()		{
		return tenVuKhi;
	}
	int		getSatThuongCoBan()	{
		return satThuongCoBan;
	}
	float	getTocDoRaDon()		{
		return tocDoRaDon;
	}
	// set
	void setTenVuKhi(string ten)	{
		tenVuKhi			= ten;
	}
	void setSatThuongCoBan(int st)	{
		satThuongCoBan	= st;
	}
	void setTocDoRaDon(float td)	{
		tocDoRaDon		= td;
	}
	// virtual method
	virtual void TanCong()			= 0;
	virtual int  SatThuong(int t)	= 0;
	virtual void InThongTin()		= 0;
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
	Sung(const Sung& sg): VuKhi(sg) {
		soLuongDan = sg.soLuongDan ;
		tocDoThayBang = sg.tocDoThayBang ;
	}
	~Sung() {}

	//METHOD
	//Mo ta cach tan cong cua Sung
	void TanCong() override {
		cout << YELLOW << BOLD << "[ SUNG ]" << RESET
		     << CYAN << " [ SUNG " << getTenVuKhi()  << "] " << RESET
		     << "Tan cong tam xa bang nhung vien dan chay bong" << endl;
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

		if (tDu >= thoiGianBanHetDan) {
			danDu = dungLuongBang;
			if (tDu == thoiGianBanHetDan)
				vuaHetBang   = true;   // vừa đúng hết băng, không còn TG
			else
				hetDanKoThay = true;   // hết đạn, thừa TG nhưng không đủ thay
		} else {
			danDu = (int)(getTocDoRaDon() * tDu);
		}

		int tongDan    = n * dungLuongBang + danDu;
		int tongDamage = tongDan * getSatThuongCoBan(); 	// tinh toan sat thuong

		soLuongDan = dungLuongBang - danDu;
		cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
		cout << left << setw(28) << "	Tong so lan thay bang:" << n << endl;
		cout << left << setw(28) << "	Dan con lai:" 			<< soLuongDan << " vien" << endl;

		if (hetDanKoThay)
			cout << RED 	<< "		>> Het dan! Khong du thoi gian thay bang." << RESET << endl;
		else if (vuaHetBang)
			cout << YELLOW 	<< "		>> Vua het bang dan dung luc ket thuc!" << RESET << endl;

		cout << BOLD << B_RED << left << setw(28) << "	Tong damage:" << tongDamage << RESET << endl;
		cout << string(70, '=') << endl;
		soLuongDan = dungLuongBang ;
		cout << ">> Tran chien ket thuc , Bang dan da duoc nap day lai nhu cu" << endl;

		return tongDamage;
	}

	// In thong tin - trang thai vu khi hien tai
	void InThongTin() override {
		cout << left << setw(22) << "Player dang su dung " << CYAN  << BOLD << "SUNG " << getTenVuKhi() 	<< RESET << endl;
		cout << left << setw(22) << "Sat thuong/vien:"	<< B_RED	<< getSatThuongCoBan()				<< RESET << endl;
		cout << left << setw(22) << "Toc do ban:"		<< B_YELLOW << getTocDoRaDon() 	<< " dan/giay" 	<< RESET << endl;
		cout << left << setw(22) << "So luong dan:"		<< B_YELLOW << soLuongDan		<< " vien"		<< RESET << endl;
		cout << left << setw(22) << "Toc do thay bang:"	<< tocDoThayBang << " giay" << endl;
	}

	// cin - cout
	friend istream& operator>>(istream& is, Sung& sg);
	friend ostream& operator<<(ostream& os, Sung sg) {
		sg.InThongTin();
		return os;
	}
};

istream& operator>>(istream& is, Sung& sg) {
	string name;
	int damage;
	float td;
	is.ignore();
	cout << YELLOW << BOLD << "===== VU KHI: SUNG =====" << RESET << endl;
	cout << "Moi ban nhap ten Sung : ";
	getline(is, name);
	cout << "Moi ban nhap sat thuong / vien dan : ";
	is >> damage;
	cout << "Moi ban nhap toc do ban (dan ban duoc trong 1s): ";
	is >> td;
	sg.setTenVuKhi(name);
	sg.setSatThuongCoBan(damage);
	sg.setTocDoRaDon(td);
	cout << "Moi ban nhap so luong dan : ";
	is >> sg.soLuongDan;
	cout << "Moi ban nhap toc do thay bang (giay) : ";
	is >> sg.tocDoThayBang;
	return is;
}

// CLASS KIEM
class Kiem : public VuKhi {
private:
	int doBen;
public:
	//constructor
	Kiem() : VuKhi() {
		doBen = 100 ;
	}
	Kiem(string ten, int st, float td, int db) : VuKhi(ten, st, td) {
		doBen = db ;
	}
	Kiem(const Kiem& other)
		: VuKhi(other), doBen(other.doBen) {}
	//destructor
	~Kiem() {}

	int  getDoBen()			{
		return doBen;
	}
	void setDoBen(int db)	{
		doBen		= (db < 0) ? 0 : db;
	}


	//method

	void TanCong() override {
		cout << YELLOW << BOLD << "[ KIEM ]" << RESET
		     <<  CYAN << " [ KIEM " << getTenVuKhi() << "] "  << RESET
		     << "Tan cong tam gan bang nhung nhat chem sac ben";
		cout << endl;
	}

	int SatThuong(int t) override {
		double doBenMax = doBen ;
		if (doBen <= 0) {
			cout << RED 	<< ">> Kiem da gay! Khong the tan cong!" << RESET << endl;
			cout << GREEN 	<< ">> Vui long che tao lai Kiem " 		<< RESET << endl ;
			return 0;
		}

		int n   = min((int)(getTocDoRaDon() * t), doBen);  // tong don

		cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
		cout << left << setw(28) << "	>> Tan cong trong " << t << " giay (" << n << " don)\n";

		int tongDamage = getSatThuongCoBan() / (float)(2 * doBen) * n * (2 * doBen - n + 1 ) ; // tinh dame ;

		cout << left << setw(28) << "	>> Tong sat thuong: " << B_RED	<< tongDamage << RESET << endl;
		doBen -= n ;
		cout << left << setw(28) << "	>> Do ben con lai:  ";
		if (doBen <= 0) 	cout << RED    << doBen << "/" << doBenMax << " [GAY!]"	<< RESET;
		else if (doBen / doBenMax < 0.3f  )cout << YELLOW << doBen << "/" << doBenMax << " [THAP!]" << RESET;
		else				cout << GREEN  << doBen << "/" << doBenMax 				<< RESET;
		cout << endl;
		if (doBen > 0) {
			doBen = doBenMax ;
			cout << string(70, '=') << endl;
			cout << ">> Sau khi chien dau xong,thanh kiem da duoc mai lai ve 100% do ben nhu cu" << endl;
		} else {
			cout << RED<<">> Kiem da gay, hay che tao lai !" << endl;
		}

		return tongDamage;
	}

	void InThongTin() override {
		cout << left << setw(22) << "Player dang su dung "	<< CYAN		<< "Kiem " << getTenVuKhi() << RESET << endl;
		cout << left << setw(22) << "Sat thuong/don:"		<< B_RED	<< getSatThuongCoBan()			<< RESET << endl;
		cout << left << setw(22) << "Toc do:"				<< B_YELLOW << getTocDoRaDon() << " don/s"	<< RESET << endl;
		cout << left << setw(22) << "Do ben:" 				<< B_YELLOW << doBen << RESET << endl;
		cout << endl;
	}

	//cin - cout

	friend istream& operator>>(istream& is, Kiem& km) {
		string ten;
		int st;
		float td;
		is.ignore();
		cout << B_CYAN << BOLD << "===== VU KHI: KIEM =====" << RESET << endl;
		cout << left << setw(22) << "Nhap ten kiem : ";
		getline(is, ten);
		cout << left << setw(22) << "Nhap sat thuong moi don : ";
		is >> st;
		cout << left << setw(22) << "Nhap toc do ra don /1s : ";
		is >> td;
		km.setTenVuKhi(ten);
		km.setSatThuongCoBan(st);
		km.setTocDoRaDon(td);
		cout << left << setw(22) << "Nhap do ben : ";
		is >> km.doBen;
		if (km.doBen < 0) km.doBen = 0;
		return is;
	}
	friend ostream& operator<<(ostream& os, Kiem km)  {
		km.InThongTin();
		return os;
	}
};

// PHEP THUAT

class PhepThuat : public VuKhi {
private:
	string   loaiPhep;
	int      manaTieuThu;
	NhanVat* nguoiDungPhep;

public:
	PhepThuat() : VuKhi(), loaiPhep("Hoa"), manaTieuThu(10), nguoiDungPhep(nullptr) {}
	PhepThuat(string ten, int st, float td, string lp = "Hoa", int mtb = 10)
		: VuKhi(ten, st, td), loaiPhep(lp), manaTieuThu(mtb), nguoiDungPhep(nullptr) {}
	PhepThuat(const PhepThuat& pt): VuKhi(pt) {
		loaiPhep = pt.loaiPhep ;
		manaTieuThu = pt.manaTieuThu ;
		nguoiDungPhep = pt.nguoiDungPhep ;
	}
	~PhepThuat() {}

	string   getLoaiPhep() {
		return loaiPhep;
	}
	int      getManaTieuThu() {
		return manaTieuThu;
	}
	NhanVat* getNguoiDungPhep() {
		return nguoiDungPhep;
	}

	void setLoaiPhep(string lp)        {
		loaiPhep      = lp;
	}
	void setManaTieuThu(int mtb)       {
		manaTieuThu   = mtb;
	}
	void setNguoiDungPhep(NhanVat* nv) {
		nguoiDungPhep = nv;
	}

	void TanCong()        override;
	int  SatThuong(int t) override;
	void InThongTin()     override;

	friend ostream& operator<<(ostream& out, PhepThuat p) {
		p.InThongTin();
		return out;
	}
	friend istream& operator>>(istream& is,  PhepThuat& p) {
		string ten, lp;
		int st, mtb;
		float td;
		is.ignore();
		cout << B_MAGENTA << BOLD << "===== VU KHI: PHEP THUAT =====" << RESET << endl;
		cout << "Nhap ten phep          : ";
		getline(is >> ws, ten);
		cout << "Nhap sat thuong/don    : ";
		is >> st;
		cout << "Nhap toc do ra don     : ";
		is >> td;
		cout << "Nhap mana tieu thu/don : ";
		is >> mtb;
		cout << "\nChon loai phep:" << endl;
		cout << "  " << RED    << "1. Hoa   (moi don gay them 10% sat thuong goc, chay am i)"         << RESET << endl;
		cout << "  " << YELLOW << "2. Loi   (moi 5 don binh thuong, don thu 6 CRIT x2 sat thuong)"    << RESET << endl;
		cout << "  " << B_CYAN << "3. Phong (sat thuong +1%/don, reset chuoi khi can hoi mana)"       << RESET << endl;
		cout << "Lua chon (1-3): ";
		int chon;
		is >> chon;
		switch (chon) {
			case 1:
				lp = "Hoa";
				break;
			case 2:
				lp = "Loi";
				break;
			case 3:
				lp = "Phong";
				break;
			default:
				lp = "Hoa";
				cout << "Khong hop le, mac dinh Hoa." << endl;
		}
		p.setTenVuKhi(ten);
		p.setSatThuongCoBan(st);
		p.setTocDoRaDon(td);
		p.loaiPhep    = lp;
		p.manaTieuThu = mtb;
		return is;
	}
};

//CLASS NHAN VAT
class NhanVat {
private:
	string name;
	int    hp;
	int    mana; // mana hien tai
	int    manaMax;
	int    hoiMana;   // mana hoi lai moi giay (mac dinh 5)
	VuKhi* vk[3];			// sung - kiem - phep
	int    viTriDangDung;   // vi tri dung vu khi

public:
	NhanVat(string _name = "Khong ro", int _hp = 1000, int _mana = 1000, int _manaMax = 1000, int hm = 5, VuKhi** _vk = nullptr, int vt = 0)
		: name(_name), hp(_hp), mana(_mana), manaMax(_manaMax), hoiMana(hm), viTriDangDung(vt) {
		for (int i = 0; i < 3; i++)
			vk[i] = (_vk ? _vk[i] : nullptr);
	}
	NhanVat(const NhanVat& x) {
		name = x.name ;
		hp = x.hp ;
		mana = x.mana ;
		manaMax = x.manaMax ;
		hoiMana = x.hoiMana ;
		for (int i = 0; i < 3; i++) {
			vk[i] = x.vk[i];
		}

		viTriDangDung = x.viTriDangDung ;

	}
	~NhanVat() {}

	string 	getName() 			{
		return name;
	}
	int		getHp()				{
		return hp;
	}
	int		getMana()			{
		return mana;
	}
	int		getManaMax() {
		return manaMax;
	}
	int		getHoiMana() {
		return hoiMana;
	}
	int		getViTriDangDung() {
		return viTriDangDung;
	}

	void setName(string _name){
		name = _name;
	}
	void setHp(int _hp){
		hp    = (_hp   < 0) ? 0 : _hp;
	}
	void setMana(int _mana)	{
		mana  = (_mana < 0) ;
	}
	void setManaMax(int _manaMax){
		manaMax = _manaMax ; 
	}
	void setHoiMana(int hm)	{
		hoiMana = (hm < 0) ? 0 : hm;
	}
	void setViTriDangDung(int vt)	{
		viTriDangDung = vt;
	}

	// Hoi mana trong t giay
	int HoiMana(int t) {
		int tongHoi = hoiMana * t;
		int truoc	= mana;
		setMana(mana + tongHoi);
		return mana - truoc;   // tra ve so mana thuc su hoi duoc
	}
	// trang bi vu khi dang su dung hien tai , bao gom sung kiem phep thuat
	void TrangBiHienTai() {
		for (int i = 0; i < 3; i++) {
			cout << B_WHITE << "[" << i + 1 << "]" << RESET ;
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
			cout << RED << ">> [" << name << "] Chua co vu khi!" << RESET << endl;
			return 0;
		}
		return v->SatThuong(t);
	}
	// nhan vat bi tan cong
	void BiTanCong(int st) {
		int hpTruoc = hp;
		hp -= st;
		if (hp < 0) hp = 0;
		cout << RED << ">> " << name << " bi tan cong" << RESET << endl;
		cout << "	HP: " << B_GREEN << hpTruoc << RESET << " -> " << B_RED << hp << RESET << endl;
	}
	// kiem tra trang thai con song hay da chet cua nhan vat
	bool ConSong() {
		return hp > 0;
	}

	friend istream& operator>>(istream& in, NhanVat& nv) {
		cout << "Nhap ten nhan vat: ";
		in.ignore();
		getline(in, nv.name);
		cout << "Nhap HP: ";
		in >> nv.hp;
		cout << "Nhap Mana: ";
		in >> nv.mana;
		nv.manaMax = nv.mana;
		cout << "Nhap hoi mana / s :" ;
		in >> nv.hoiMana ;
		return in;
	}
	friend ostream& operator<<(ostream& out, NhanVat nv) {
		out << left << setw(22) << "Ten:"  << B_WHITE  << nv.name	<< RESET << endl;
		out << left << setw(22) << "HP:"   << B_RED  << nv.hp 		<< RESET << endl;
		out << left << setw(22) << "Mana:" << BLUE   << nv.mana << B_BLUE << "/" << nv.manaMax << RESET << endl;
		out << left << setw(22) << "Hoi mana/giay:" << B_BLUE << nv.hoiMana << RESET << endl;
		out << CYAN << string(70, '=') << RESET << endl;
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
	     << CYAN << "[ "  << getTenVuKhi()  << " ] " << RESET
	     << " Su dung 1 nang luc tam linh ky la tan cong vao ke dich " << endl ;

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
		cout << RED << ">> [" << getTenVuKhi() << "] Chua gan nguoi dung phep!\n" << RESET;
		return 0;
	}

	const int   base      = getSatThuongCoBan();
	const float tocDo     = getTocDoRaDon();
	const int   hoiMana1s = nguoiDungPhep->getHoiMana();
	const int   manaMax   = nguoiDungPhep->getManaMax();
	const int   manaHT    = nguoiDungPhep->getMana();

	int tongDamage = 0;
	int n          = 0;

	if (loaiPhep == "Hoa" || loaiPhep == "Loi") {
		// Tong mana co the dung = mana hien tai + toan bo mana hoi trong t giay
		// (khong gioi han manaMax vi hoi xong la dung lien)
		int tongMana = manaHT + hoiMana1s * t;
		int n_mana   = tongMana / manaTieuThu;
		int n_time   = (int)(tocDo * t);
		n			 = min(n_mana, n_time);

		if (n == 0) {
			cout << RED << ">> Khong du mana va thoi gian de ra bat ky don nao!\n" << RESET;
			return 0;
		}

		if (loaiPhep == "Hoa") {
			tongDamage = (int)(base * 1.1f * n);
		} else { // Loi
			int nChuKy = n / 6;
			int nDu    = n % 6;
			tongDamage = nChuKy * 7 * base + nDu * base;
		}

		// mana cuoi = mana dau + mana hoi - mana tieu thu , gioi han [0, manaMax]
		int manaConLai = manaHT + hoiMana1s * t - n * manaTieuThu;
		nguoiDungPhep->setMana(min(max(0, manaConLai), manaMax));

	} else { // Phong - 2 giai doan

		// --- Giai doan 1: dung mana hien tai, dame cong don lien tuc ---
		int n1_mana = manaHT / manaTieuThu;
		int n1_time = (int)(tocDo * t);
		int n1      = min(n1_mana, n1_time);

		// Tong dame G1: base * sum(1 + i*0.01) voi i = 0..n1-1
		// = base * (n1 + 0.01 * n1*(n1-1)/2)
		float D1 = (float)base * (n1 + 0.01f * n1 * (n1 - 1) / 2.0f);

		// --- Giai doan 2: het mana, hoi lai roi danh x1.00 (reset chuoi) ---
		float tCon      = t - (float)n1 / tocDo;
		int   manaHoiG2 = (tCon > 0) ? (int)(hoiMana1s * tCon) : 0;
		int   n2_mana   = (tCon > 0) ? manaHoiG2 / manaTieuThu : 0;
		int   n2_time   = (tCon > 0) ? (int)(tocDo * tCon)      : 0;
		int   n2		= min(n2_mana, n2_time);
		int   D2		= base * n2;

		n 		   = n1 + n2;
		tongDamage = (int)(D1 + D2);

		if (n == 0) {
			cout << RED << ">> Khong du mana va thoi gian de ra bat ky don nao!\n" << RESET;
			return 0;
		}

		// mana cuoi = mana sau G1 + mana hoi G2 - mana tieu thu G2
		int manaConLai = (manaHT - n1 * manaTieuThu) + manaHoiG2 - n2 * manaTieuThu;
		nguoiDungPhep->setMana(min(max(0, manaConLai), manaMax));
	}

	// --- In ket qua ---
	const char* mau = mauPhep(loaiPhep);

	cout << endl << CYAN << BOLD << "[Dien bien chien dau - " << t << " giay]" << RESET << endl;
	cout << left << setw(28) << "	Tong so don da ra:"   << n << " don"                                   << endl;
	cout << left << setw(28) << "	Mana tieu thu:"       << B_BLUE << n * manaTieuThu << " mana"  << RESET << endl;

	if (loaiPhep == "Loi") {
		cout << left << setw(28) << "	So lan CRIT (don 6):" << YELLOW << BOLD << n / 6 << " lan"  << RESET << endl;
	} else if (loaiPhep == "Phong") {
		int   n1      = min(manaHT / manaTieuThu, (int)(tocDo * t));
		float nhanCuoi = min(1.0f + (n1 - 1) * 0.01f, 3.0f);
		cout << left << setw(28) << "	Nhan cuoi dat duoc:"  << B_CYAN << "x" << fixed << setprecision(2) << nhanCuoi << RESET << endl;
	} else if (loaiPhep == "Hoa") {
		cout << left << setw(28) << "	Hieu ung thieu dot:"  << RED << "+10%/don"                  << RESET << endl;
	}

	cout << BOLD << B_RED << left << setw(28) << "	Tong damage:" << tongDamage                    << RESET << endl;
	cout << string(70, '=') << endl;
	cout << ">> Tran chien ket thuc, Mana con lai: " << B_BLUE << nguoiDungPhep->getMana() << "/" << manaMax << RESET << endl;

	return tongDamage;
}

void PhepThuat::InThongTin() {
	const char* mau = mauPhep(loaiPhep);
	cout << left << setw(22) << "Player dang su dung " << B_WHITE << BOLD << "Phep Thuat " << BLUE << getTenVuKhi() << RESET << endl;
	cout << left << setw(22) << "Loai phep:"         << mau << BOLD << loaiPhep            << RESET << endl;
	cout << left << setw(22) << "Sat thuong co ban:" << B_RED    << getSatThuongCoBan()    << RESET << endl;
	cout << left << setw(22) << "Toc do ra don:"     << B_YELLOW << getTocDoRaDon() << " don/giay" << RESET << endl;
	cout << left << setw(22) << "Mana tieu thu/don:" << B_BLUE   << manaTieuThu             << RESET << endl;

	// Mo ta hieu ung
	if (loaiPhep == "Hoa")
		cout << RED    << "  >> Hieu ung: Moi don thieu dot them " << (int)(getSatThuongCoBan() * 0.1f)
		     << " dmg (+10% moi don)" << RESET << endl;
	else if (loaiPhep == "Loi")
		cout << YELLOW << "  >> Hieu ung: Don thu 6 trong chu ky 6 don no CRIT x2 ("
		     << getSatThuongCoBan() * 2 << " dmg)." << RESET << endl;
	else if (loaiPhep == "Phong")
		cout << B_CYAN << "  >> Hieu ung: +1%/don (chuoi don 1 = x1.00, chuoi don 100 = x2.00). Het mana: hoi mana, reset chuoi ve x1!" << RESET << endl;
}

// MENU CHINH
void hienThiGiaoDien(NhanVat& nr, NhanVat& p) {
	clearScreen();
	cout << RED << BOLD << "============= MUC TIEU ==============" << RESET << "\n";
	cout << nr;
	cout << "PLAYER: " << B_WHITE << p.getName() << RESET
	     << " | HP: " 	<< B_RED << p.getHp() 	<< RESET
	     << " | Mana: " 	<< BLUE << p.getMana() << B_BLUE << "/" << p.getManaMax() << RESET
	     << " - "		<< p.getHoiMana() << " mana/s" << endl ;
	cout << CYAN << string(70, '=') << RESET << endl;
	cout  << "TRANG BI HIEN TAI:" << RESET << "\n";
	p.TrangBiHienTai();
	cout << "\n";
	cout << YELLOW << BOLD << "===== Vu Khi Dang Su Dung =====" << RESET << endl;
	p[p.getViTriDangDung()]->InThongTin();
	cout << "\n";
	cout << GREEN << "==============================" << RESET << endl;
	cout << "  1. Tan cong"		<< RESET << endl;
	cout << "  2. Doi vu khi"	<< RESET << endl;
	cout << "  3. Che tao lai vu khi" << RESET << endl;
	cout << "  0. Thoat"		<< RESET << endl;
	cout << GREEN	<< "==============================" << RESET << endl;
	cout << "Lua chon: ";
}

// MAIN CHISNH

int main() {
	Sung 		sung("AK47",      35, 10.0f, 30, 2.0f);
	Kiem		kiem("Muramasa",  50,  2.0f, 100);
	PhepThuat	phep("Amaterasu", 60,  1.0f, "Hoa", 15);

	VuKhi* vk[3] = { &sung, &kiem, &phep };

	NhanVat nr		("BAC NONG DAN ",	 10000, 100, 100 );
	NhanVat player	("Shadow Reaper", 10000, 500, 500, 5,  vk, 0);

	phep.setNguoiDungPhep(&player);

	int lua = -1;
	while (lua != 0 && nr.ConSong()) {
		hienThiGiaoDien(nr, player);
		cin >> lua;

		if (lua == 1) {
			clearScreen();
			cout << RED << BOLD << "============= MUC TIEU ==============" << RESET << "\n";
			cout << nr;
			cout << RED << "PLAYER: " << B_WHITE << player.getName() << RESET
			     << " | HP: " << B_RED << player.getHp() << RESET
			     << " | Mana: " << BLUE << player.getMana() << B_BLUE << "/" << player.getManaMax() << RESET
			     << " - "		<< player.getHoiMana() << " mana/s" << endl ;
			cout << CYAN << string(70, '=') << endl;
			cout << YELLOW << BOLD << "============= VU KHI TAN CONG =============" << RESET << "\n";
			player[player.getViTriDangDung()]->TanCong();
			cout << "\nNhap thoi gian tan cong (giay): ";
			int t;
			cin >> t;
			int damage = player[player.getViTriDangDung()]->SatThuong(t);
			cout << "\n" << B_RED << BOLD << "Sat thuong gay len " << nr.getName() << ": " << RESET << damage  << endl;
			if (player.getViTriDangDung() != 2 ) {
				int x = player.HoiMana(t);
				if (x > 0) cout << "	>>Da phuc hoi them " << x << " Mana\n";
			}
			if (damage > 0) {
				cout << endl;
				nr.BiTanCong(damage);
				if (nr.ConSong())
					cout << YELLOW << "\n>> " << nr.getName() << " van song! HP: " << nr.getHp() << RESET << endl;
				else
					cout << RED << BOLD << "\n>> " << nr.getName() << " da bi ha guc!" << RESET << endl;
			}
			cout << "\nNhan Enter de tiep tuc...";
			cin.ignore();
			cin.get();
		} else if (lua == 2) {
			clearScreen();
			cout << RED << BOLD << "PLAYER" << RESET << "\n";
			cout << player;
			cout << YELLOW << BOLD << "================== DOI VU KHI ==============" << RESET << "\n";
			player.TrangBiHienTai();
			cout << "Lua chon (1-3): ";
			int chon;
			cin >> chon;
			player.setViTriDangDung(chon - 1);
			cout << "\n>> Da chon:\n";
			player[player.getViTriDangDung()]->TanCong();
			cout << "\nNhan Enter de tiep tuc...";
			cin.ignore();
			cin.get();
		} else if (lua == 3) {
			clearScreen();
			cout << RED << BOLD << "PLAYER" << RESET << "\n";
			cout << player;
			cout << CYAN << BOLD << "===== CHE TAO VU KHI =====" << RESET << "\n";
			cout << YELLOW << "  1. Sung"		<< RESET << "\n";
			cout << B_CYAN << "  2. Kiem"		<< RESET << "\n";
			cout << MAGENTA << "  3. Phep Thuat"	<< RESET << "\n";
			cout << "Lua chon: ";
			int chon;
			cin >> chon;
			switch (chon) {
				case 1:
					cin >> sung;
					player[0] = &sung;
					player.setViTriDangDung(0);
					break;
				case 2:
					cin >> kiem;
					player[1] = &kiem;
					player.setViTriDangDung(1);
					break;
				case 3:
					cin >> phep;
					phep.setNguoiDungPhep(&player);
					player[2] = &phep;
					player.setViTriDangDung(2);
					break;
				default:
					cout << RED << "Lua chon khong hop le!\n" << RESET;
					break;
			}
			cout << B_GREEN << "\n>> Che tao thanh cong!" << RESET << "\n";
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore();
			cin.get();
		} else if (lua == 0) {
			clearScreen();
			cout << B_WHITE << "Tam biet!\n" << RESET;
			return 0;
		} else {
			cout << RED << "Lua chon khong hop le.\n" << RESET;
			cout << "Nhan Enter de tiep tuc...";
			cin.ignore();
			cin.get();
		}
	}

	if (!nr.ConSong()) {
		clearScreen();
		cout << "\n" << RED << BOLD;
		cout << "=======================================\n";
		cout << "  " << nr.getName() << " DA BI TIEU DIET!\n";
		cout << "=======================================" << RESET ;
	}
	return 0;
}
