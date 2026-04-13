#include "VuKhi.h"
class Kiem : public VuKhi {
	int doBen ; 
public :
	Kiem() : VuKhi(), doBen(100) {}
	
	Kiem(string ten, int st, float td, float db)
	: VuKhi(ten, st, td), doBen(db) {}
	void TanCong() override {
		
	}

	
	int SatThuong(int t) override {
		
	}
	friend ostream& operator << (ostream& out , Kiem x){
		
	}
};
