#pragma once
#include "VuKhi.h"
#include <cstdlib>
#include <ctime>

// ============================================================
//  PHEP THUAT - 3 loai: Hoa | Set | Phong
//
//  Giai doan mana (tinh theo % mana hien tai / manaMax):
//    70-100% -> tier 3: sat thuong x1.5, tieu 10 mana/don
//    30- 70% -> tier 2: sat thuong x1.0, tieu  7 mana/don
//     0- 30% -> tier 1: sat thuong x0.6, tieu  3 mana/don
//  Het mana (< mana can tier 1) -> cho hoi, hoi 5 mana/giay
//
//  Hieu ung rieng:
//    HOA  : moi don de lai 1 stack dot (toi da 5), cuoi giay
//           gay them stackHoa * 8 sat thuong chay.
//    SET  : 20% co hoi chi mang x2, hien thi ro khi no.
//    PHONG: sat thuong tang dan theo thoi gian chien dau
//           dmg = baseDmg * (1 + soGiayDaDanh * 0.1)
//           (cap toi da x3 = 20 giay)
// ============================================================

class PhepThuat : public VuKhi {
private:
	string loaiPhep;
	int    manaHienTai;
	int    manaMax;
	
	// --- Hoa ---
	int stackHoa;        // 0-5
	
	// --- Set ---
	// (khong co bien trang thai, chi la xac suat)
	
	// --- Phong ---
	int soGiayDaDanh;    // dem so giay da thuc su tan cong (co mana)
	
	// -------- helper: tinh giai doan mana --------
	// tra ve: tier 3/2/1, hoac 0 neu het mana
	int getTier() const {
		float pct = (float)manaHienTai / manaMax * 100.0f;
		if (pct >= 70) return 3;
		if (pct >= 30) return 2;
		if (pct >  0 ) return 1;
		return 0;
	}
	int manaCan(int tier) const {
		if (tier == 3) return 10;
		if (tier == 2) return  7;
		return 3; // tier 1
	}
	float heSoTier(int tier) const {
		if (tier == 3) return 1.5f;
		if (tier == 2) return 1.0f;
		return 0.6f;
	}
	
public:
	// ===== Constructor =====
	PhepThuat()
	: VuKhi(), loaiPhep("Hoa"), manaHienTai(100), manaMax(100),
	stackHoa(0), soGiayDaDanh(0) {
		srand((unsigned)time(nullptr));
	}
	
	PhepThuat(string ten, int st, float td, string lp, int manaMax_ = 100)
	: VuKhi(ten, st, td), loaiPhep(lp),
	manaHienTai(manaMax_), manaMax(manaMax_),
	stackHoa(0), soGiayDaDanh(0) {
		srand((unsigned)time(nullptr));
	}
	
	// ===== TanCong: gioi thieu nhanh =====
	void TanCong() override {
		cout << "[ PHEP THUAT ] [" << getTenVuKhi() << "] "
		<< "Loai: " << loaiPhep
		<< " - " << getSatThuongCoBan() << " dmg/don, "
		<< getTocDoRaDon() << " don/giay." << endl;
		cout << "    >> Mana hien tai: " << manaHienTai << "/" << manaMax << endl;
	}
	
	// ===== SatThuong: chinh =====
	int SatThuong(int t) override {
		int tongSatThuong = 0;
		bool dangChoHoiMana = false;
		
		cout << "\n===== [" << getTenVuKhi() << " - Phep " << loaiPhep
		<< "] Chien dau " << t << " giay =====" << endl;
		cout << "Mana ban dau: " << manaHienTai << "/" << manaMax << endl;
		cout << "----------------------------------------------" << endl;
		
		for (int giay = 1; giay <= t; giay++) {
			
			cout << "\n-- Giay " << giay << "/" << t
			<< " | Mana: " << manaHienTai << "/" << manaMax;
			if (loaiPhep == "Hoa")
				cout << " | Stack dot: " << stackHoa;
			if (loaiPhep == "Phong")
				cout << " | Bo suc: x" << (1.0f + soGiayDaDanh * 0.1f < 3.0f
										   ? 1.0f + soGiayDaDanh * 0.1f : 3.0f);
			cout << " --" << endl;
			
			// --- HOI MANA ---
			int hoiMoiGiay = 5;
			if (dangChoHoiMana || manaHienTai < manaCan(1)) {
				manaHienTai += hoiMoiGiay;
				if (manaHienTai > manaMax) manaHienTai = manaMax;
				cout << "  [Hoi Mana] +" << hoiMoiGiay
				<< " => " << manaHienTai << "/" << manaMax << endl;
				
				// Kiem tra da du mana chua
				if (manaHienTai >= manaCan(1)) {
					dangChoHoiMana = false;
					cout << "  [Mana] Du mana! Chuan bi tan cong..." << endl;
				} else {
					cout << "  [Cho hoi...]" << endl;
					continue; // bo qua tan cong giay nay
				}
			}
			
			// --- XAC DINH TIER ---
			int tier = getTier();
			if (tier == 0) {
				// van het mana (truong hop du phong)
				dangChoHoiMana = true;
				manaHienTai += hoiMoiGiay;
				if (manaHienTai > manaMax) manaHienTai = manaMax;
				cout << "  [Hoi Mana] Het mana, +" << hoiMoiGiay
				<< " => " << manaHienTai << "/" << manaMax << endl;
				continue;
			}
			
			int    mCan = manaCan(tier);
			float  heSo = heSoTier(tier);
			int    baseDmg = getSatThuongCoBan();
			int    dmg  = 0;
			
			// So don trong 1 giay
			int soDon = (int)getTocDoRaDon();
			if (soDon < 1) soDon = 1;
			
			cout << "  [Tier " << tier << "] heSo x" << heSo
			<< " | tieu " << mCan << " mana/don | " << soDon << " don/giay" << endl;
			
			for (int d = 0; d < soDon; d++) {
				// kiem tra mana truoc moi don
				if (manaHienTai < mCan) {
					// ha xuong tier thap hon
					tier = getTier();
					if (tier == 0) {
						dangChoHoiMana = true;
						cout << "  [Don " << d+1 << "] Het mana! Dung danh, cho hoi." << endl;
						break;
					}
					mCan = manaCan(tier);
					heSo = heSoTier(tier);
					cout << "  [Don " << d+1 << "] Mana giam, xuong Tier " << tier << endl;
				}
				
				manaHienTai -= mCan;
				
				// ---- HOA ----
				if (loaiPhep == "Hoa") {
					int donDmg = (int)(baseDmg * heSo);
					if (stackHoa < 5) stackHoa++;
					int dotDmg = stackHoa * 8;
					dmg += donDmg + dotDmg;
					cout << "  [Don " << d+1 << "][HOA] " << donDmg
					<< " + dot " << dotDmg << " (stack " << stackHoa
					<< ") = " << (donDmg+dotDmg) << " | Mana: " << manaHienTai << endl;
				}
				// ---- SET ----
				else if (loaiPhep == "Set") {
					int donDmg = (int)(baseDmg * heSo);
					int roll   = rand() % 100;
					bool chiMang = (roll < 20); // 20%
					if (chiMang) donDmg *= 2;
					dmg += donDmg;
					cout << "  [Don " << d+1 << "][SET] ";
					if (chiMang) cout << "*** CHI MANG! *** ";
					cout << donDmg << " dmg | Mana: " << manaHienTai << endl;
				}
				// ---- PHONG ----
				else if (loaiPhep == "Phong") {
					float boSuc = 1.0f + soGiayDaDanh * 0.1f;
					if (boSuc > 3.0f) boSuc = 3.0f;
					int donDmg = (int)(baseDmg * heSo * boSuc);
					dmg += donDmg;
					cout << "  [Don " << d+1 << "][PHONG] " << baseDmg
					<< " x" << heSo << " x" << boSuc << "(phong) = "
					<< donDmg << " | Mana: " << manaHienTai << endl;
				}
				else {
					int donDmg = (int)(baseDmg * heSo);
					dmg += donDmg;
					cout << "  [Don " << d+1 << "] " << donDmg
					<< " dmg | Mana: " << manaHienTai << endl;
				}
			}
			
			soGiayDaDanh++;
			tongSatThuong += dmg;
			cout << "  => Sat thuong giay " << giay << ": " << dmg
			<< " | Tich luy: " << tongSatThuong << endl;
			
			if (dangChoHoiMana)
				cout << "  [Mana] Het mana, bat dau hoi..." << endl;
		}
		
		cout << "\n===== Ket thuc chien dau =====" << endl;
		cout << "Tong sat thuong: " << tongSatThuong << endl;
		cout << "Mana con lai   : " << manaHienTai << "/" << manaMax << endl;
		return tongSatThuong;
	}
	
	void inThongTin(){
		cout << "Player dang su dung VU KHI: ";
		cout << "Phep Thuat " << getTenVuKhi() << endl;
		cout << left << setw(25) << "Loai phep:"          << loaiPhep            << endl;
		cout << left << setw(25) << "Sat thuong co ban:"  << getSatThuongCoBan() << endl;
		cout << left << setw(25) << "Toc do ra don:"      << getTocDoRaDon()     << " don/giay" << endl;
		cout << left << setw(25) << "Mana hien tai:"      << manaHienTai         << "/" << manaMax << endl;
	}
	// ===== Operator << =====
	friend ostream& operator<<(ostream& out, PhepThuat x) {
		x.inThongTin();
		return out;
	}
	
	// ===== Operator >> =====
	friend istream& operator>>(istream& is, PhepThuat& p) {
		string ten;
		int st, mMax;
		float td;
		string lp;
		
		is.ignore();
		cout << "===== VU KHI: PHEP THUAT =====" << endl;
		cout << "Nhap ten phep thuat  : "; getline(is >> ws, ten);
		cout << "Nhap sat thuong/don  : "; is >> st;
		cout << "Nhap toc do ra don   : "; is >> td;
		cout << "Nhap mana toi da     : "; is >> mMax;
		
		// Menu chon loai phep
		cout << "\nChon loai phep:" << endl;
		cout << "  1. Hoa  (dot damage, chong theo stack)" << endl;
		cout << "  2. Set  (20% chi mang x2)"              << endl;
		cout << "  3. Phong(damage tang theo thoi gian)"   << endl;
		cout << "Lua chon (1-3): ";
		int chon; is >> chon;
		switch (chon) {
			case 1: lp = "Hoa";   break;
			case 2: lp = "Set";   break;
			case 3: lp = "Phong"; break;
			default: lp = "Hoa"; cout << "Khong hop le, mac dinh Hoa." << endl;
		}
		
		p.setTenVuKhi(ten);
		p.setSatThuongCoBan(st);
		p.setTocDoRaDon(td);
		p.loaiPhep    = lp;
		p.manaMax     = mMax;
		p.manaHienTai = mMax;
		p.stackHoa    = 0;
		p.soGiayDaDanh = 0;
		return is;
	}
};
