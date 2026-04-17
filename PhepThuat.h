#include "VuKhi.h"
#include <cstdlib>   
#include <ctime>     

class PhepThuat : public VuKhi {
private:
	string loaiPhep;          
	int manaTieuThuMoiDon;   
	int manaHienTai;          
	
	// Trang thai doi voi hieu ung Bang
	bool mucTieuDangDongBang;
	int giayConDongBang;
	
	// So stack Hoa dang gay len muc tieu (toi da 10 stack)
	int stackHoa;
	
public:
	// ===== Constructors =====
	PhepThuat()
	: VuKhi(), loaiPhep("Hoa"), manaTieuThuMoiDon(4),
	manaHienTai(100),
	mucTieuDangDongBang(false), giayConDongBang(0), stackHoa(0) {
		srand((unsigned)time(nullptr));
	}
	
	PhepThuat(string ten, int st, float td, string lp, int mana)
	: VuKhi(ten, st, td), loaiPhep(lp),
	manaHienTai(100),
	mucTieuDangDongBang(false), giayConDongBang(0), stackHoa(0) {
		srand((unsigned)time(nullptr));
		
		if      (loaiPhep == "Hoa")  manaTieuThuMoiDon = 4;
		else if (loaiPhep == "Loi")  manaTieuThuMoiDon = 3;
		else if (loaiPhep == "Bang") manaTieuThuMoiDon = 3;
		else                         manaTieuThuMoiDon = mana;
	}
	
	// ===== TanCong: gioi thieu vu khi =====
	void TanCong() override {
		cout << "[PHEP THUAT " << getTenVuKhi() << "]"
		<< " Loai: " << loaiPhep
		<< " - " << getSatThuongCoBan() << " dmg/don, "
		<< getTocDoRaDon() << " don/giay." << endl;
		cout << "	>> Mana hien tai: " << manaHienTai << "/100" << endl;
	}
	
	// ===== SatThuong: xu ly toan bo logic trong t giay =====
	// Moi giay = 1 don danh (tocDoRaDon = 1 don/giay)
	int SatThuong(int t) override {
		//lua chon 1 2 3 phep hoa bang gio 
		int tongSatThuong = 0;
		bool dangHoiMana  = false; // trang thai hoi mana
		
		cout << "===== [" << getTenVuKhi() << " - Phep " << loaiPhep << "] =====" << endl;
		cout << "Mana ban dau: " << manaHienTai << "/100" << endl << endl;
		
		for (int giay = 1; giay <= t; giay++) {
			cout << "-- Giay " << giay << " --" << endl;
			
			// --- Cap nhat trang thai dong bang (dem nguoc) ---
			if (mucTieuDangDongBang) {
				giayConDongBang--;
				if (giayConDongBang <= 0) {
					mucTieuDangDongBang = false;
					giayConDongBang     = 0;
					cout << "  [Bang] Muc tieu da het dong bang!" << endl;
				} else {
					cout << "  [Bang] Muc tieu dang dong bang, con " << giayConDongBang << " giay." << endl;
				}
			}
			
			// --- Che do hoi mana ---
			if (dangHoiMana) {
				// Hoi 10 mana moi giay
				int hoiDuoc = 10;
				manaHienTai += hoiDuoc;
				if (manaHienTai > 100) manaHienTai = 100;
				cout << "  [Hoi Mana] +" << hoiDuoc << " => " << manaHienTai << "/100" << endl;
				
				// Tan cong co ban (khong tieu mana) trong luc cho hoi
				int dmgCoBan = getSatThuongCoBan();
				cout << "  [Tan cong co ban]: " << dmgCoBan << " sat thuong." << endl;
				tongSatThuong += dmgCoBan;
				
				// Khi dat >= 50 mana thi kich hoat lai cuong hoa
				if (manaHienTai >= 50) {
					dangHoiMana = false;
					cout << "  [Mana] Da du 50 mana! Kich hoat lai phep cuong hoa!" << endl;
				}
				cout << endl;
				continue;
			}
			
			// --- Kiem tra du mana de tan cong cuong hoa ---
			if (manaHienTai >= manaTieuThuMoiDon) {
				// Tieu mana
				manaHienTai -= manaTieuThuMoiDon;
				
				int dmg = getSatThuongCoBan();
				
				// --- HOA ---
				if (loaiPhep == "Hoa") {
					if (stackHoa < 10) stackHoa++;
					int dotDmg = stackHoa * 10;
					cout << "  [Hoa] Don danh: " << dmg
					<< " | Stack dot: " << stackHoa
					<< " | Hieu ung dot: +" << dotDmg << " HP/s" << endl;
					dmg += dotDmg;
					cout << "  [Hoa] Tong sat thuong giay nay: " << dmg << endl;
				}
				// --- SET (LOI) ---
				else if (loaiPhep == "Loi") {
					int dmgGoc = dmg;
					dmg = (int)(dmg * 1.5f);
					cout << "  [Set] Don danh: " << dmgGoc
					<< " x1.5 = " << dmg << " sat thuong." << endl;
				}
				// --- BANG ---
				else if (loaiPhep == "Bang") {
					if (mucTieuDangDongBang) {
						int dmgGoc = dmg;
						dmg *= 2;
						cout << "  [Bang] Muc tieu dang dong bang! Sat thuong gap doi: "
						<< dmgGoc << " x2 = " << dmg << endl;
					} else {
						cout << "  [Bang] Don danh: " << dmg << " sat thuong." << endl;
					}
					
					// 10% co hoi dong bang (chi tac dong khi muc tieu chua bi dong bang)
					if (!mucTieuDangDongBang) {
						int roll = rand() % 100;
						if (roll < 10) {
							mucTieuDangDongBang = true;
							giayConDongBang     = 3;
							cout << "  [Bang] DONG BANG! Muc tieu bi dong bang trong 3 giay!" << endl;
						}
					}
				}
				
				tongSatThuong += dmg;
				cout << "  [Mana] Con lai: " << manaHienTai << "/100" << endl;
				
				// Khi het mana (khong du cho don tiep theo) -> vao che do hoi mana
				if (manaHienTai < manaTieuThuMoiDon) {
					dangHoiMana = true;
					cout << "  [Mana] Het mana! Chuyen sang che do hoi mana..." << endl;
				}
			}
			// --- Truong hop khong du mana (du phong, thong thuong khong xay ra) ---
			else {
				dangHoiMana = true;
				int dmgCoBan = getSatThuongCoBan();
				cout << "  [Co ban] Khong du mana, tan cong co ban: " << dmgCoBan << " sat thuong." << endl;
				tongSatThuong += dmgCoBan;
			}
			
			cout << endl;
		}
		
		cout << "===== Ket thuc tan cong =====" << endl;
		cout << "Tong sat thuong: " << tongSatThuong << endl;
		return tongSatThuong;
	}
	
	// ===== Operator << =====
	friend ostream& operator<<(ostream& out, PhepThuat x) {
		out << "Player dang su dung VU KHI: ";
		out << "Phep Thuat " << x.getTenVuKhi() << endl;
		out << left << setw(25) << "Loai phep:"         << x.loaiPhep               << endl;
		out << left << setw(25) << "Sat thuong co ban:" << x.getSatThuongCoBan()    << endl;
		out << left << setw(25) << "Toc do ra don:"     << x.getTocDoRaDon() << " don/giay" << endl;
		out << left << setw(25) << "Mana hien tai:"     << x.manaHienTai    << "/100" << endl;
		out << left << setw(25) << "Mana tieu thu:"     << x.manaTieuThuMoiDon << "/don" << endl;
		return out;
	}
	
	// ===== Operator >> =====
	friend istream& operator>>(istream& is, PhepThuat& p) {
		string ten;
		int st;
		float td;
		string lp;
		is.ignore();
		cout << "===== VU KHI: PHEP THUAT =====" << endl;
		cout << "Nhap ten phep thuat: ";
		getline(is >> ws, ten);
		cout << "Nhap sat thuong co ban: ";
		is >> st;
		cout << "Nhap toc do ra don (don/giay): ";
		is >> td;
		cout << "Nhap loai phep (Hoa / Lei / Bang): ";
		is >> lp;
		p.setTenVuKhi(ten);
		p.setSatThuongCoBan(st);
		p.setTocDoRaDon(td);
		p.loaiPhep = lp;
		if      (lp == "Hoa")  p.manaTieuThuMoiDon = 4;
		else if (lp == "Loi")  p.manaTieuThuMoiDon = 3;
		else if (lp == "Bang") p.manaTieuThuMoiDon = 3;
		// Reset trang thai
		p.manaHienTai          = 100;
		p.stackHoa             = 0;
		p.mucTieuDangDongBang  = false;
		p.giayConDongBang      = 0;
		return is;
	}
};
