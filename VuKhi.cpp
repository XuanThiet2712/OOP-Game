//#pragma once 
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std ; 
class VuKhi{
private:
	string tenVuKhi ; 
	int satThuongCoBan ; 
	float tocDoRaDon ; 
public : 
	//constructor 
	VuKhi(string ten = "Khong ro" , int st = 10 , float td = 1 ){
		tenVuKhi = ten ; 
		satThuongCoBan = st ; 
		tocDoRaDon = td  ; 
	}
	~VuKhi(){} 
	//getset
	string getTenVuKhi() { return tenVuKhi; }
	int getSatThuongCoBan() { return satThuongCoBan; }
	float getTocDoRaDon() { return tocDoRaDon; }
	
	void setTenVuKhi(string ten) {
		tenVuKhi = ten; 
	}
	void setSatThuongCoBan(int st) {
		satThuongCoBan = st; 
	}
	void setTocDoRaDon(float td) {
		tocDoRaDon = td ; 
	}
	
	//method
	virtual void TanCong() = 0 ;
	virtual int SatThuong(int t) = 0 ;
};


int main(){
	
}
