#include "VuKhi.h"
class PhepThuat : public VuKhi {
private:
	string loaiPhep;       // "Hoa", "Loi", "Tho"
	int manaTieuThuGiay;
	int manaHienTai;
	
public:
	// ===== Constructors =====
	PhepThuat() : VuKhi(), loaiPhep("Hoa"), manaTieuThuGiay(10), manaHienTai(100) {}
	
	PhepThuat(string ten, int st, float td, string lp, int mana)
	: VuKhi(ten, st, td), loaiPhep(lp), manaTieuThuGiay(mana), manaHienTai(100) {}
	void TanCong() override {
		
	}
	
	
	int SatThuong(int t) override {
		
	}
	friend ostream& operator << (ostream& out , PhepThuat x){
		
	}
};
