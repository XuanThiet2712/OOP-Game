#include "VuKhi.h"
class Sung : public VuKhi{
	private:
	int soLuongDan;
	float tocDoThayBang;  // giay
	
public:
	// ===== Constructors =====
	Sung() : VuKhi(), soLuongDan(30), tocDoThayBang(2) {}
	
	Sung(string ten, int st, float td, int sld, float tdb)
	: VuKhi(ten, st, td), soLuongDan(sld), tocDoThayBang(tdb) {}
	void TanCong() override {
		
	}
	
	
	int SatThuong(int t) override {
		
	}
		friend ostream& operator << (ostream& out , Sung x){
			
		}
};
