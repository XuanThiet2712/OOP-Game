#include "VuKhi.h"
class Sung : public VuKhi{
private:
	int soLuongDan;		
	float tocDoThayBang;  // giay
	
public:
	//constructor6
	Sung() : VuKhi(), soLuongDan(30), tocDoThayBang(2) {}
	Sung(string ten, int st, float td, int sld, float tdb)
	: VuKhi(ten, st, td), soLuongDan(sld), tocDoThayBang(tdb) {}
	~Sung(){};
	
//	void ThayBang() { 
//		soLuongDan  = 30; 
//		cout << ">> Thay bang! Dan: " << soLuongDan << endl; 
//	}
	
	void TanCong() {
		cout << "[SUNG "<<getTenVuKhi()<<"] Tan cong tam xa bang nhung vien dan chay bong"
		<< " - " << getSatThuongCoBan() << " dmg/vien, "
		<< getTocDoRaDon() << " dan/giay. ";
		cout<<endl<<"	>> Dan hien tai: " << soLuongDan << " vien." << endl;
	}
	
	int SatThuong(int t) {
		float thoiGianConLai = (float)t;	// thoi gian ban con lai (giay)
		int tongDamage = 0;					// tong sat thuong tich luy
		int	soLanThayBang = 0;          	// dem so lan thay bang
		int	dungLuongBang = soLuongDan; 	// luu dung luong bang 
		float thoiGianBanHetDan = soLuongDan / getTocDoRaDon(); // thoi gian ban het 1 bang dan 
		
		cout <<endl<< "[Dien bien chien dau - " << t << " giay]" << endl;
		cout << "	Dan luc dau:" << soLuongDan << " vien" << endl;
		
		//VONG LAP BAN
		while (thoiGianConLai > 0) { // moi lan lap deu trong trang thai full bang dan chi khac moi thoi gian 
			
			// -------- TRUONG HOP 1: Het dan
			if (soLuongDan == 0) {
				
				// Khong du thoi gian de thay bang -> dung lai
				if (thoiGianConLai <= tocDoThayBang) {
					cout <<"	>> Het dan! Can " << tocDoThayBang 
					<< "s thay bang nhung chi con " << thoiGianConLai << "s -> Dung ban." << endl;
					break;
				}
				
				// Du thoi gian -> thay bang, tru thoi gian thay, nap dan moi
				cout << "	>> Het dan! Tu dong thay bang... (-" << tocDoThayBang << "s)" << endl;
				thoiGianConLai -= tocDoThayBang; // tru thoi gian thay bang
				soLuongDan = dungLuongBang; // nap bang moi day dan
				soLanThayBang++;
				
				cout << "	Bang moi nap xong:"<<soLuongDan<< " vien | Con lai: " << thoiGianConLai << "s" << endl;
				continue; // quay lai dau vong lap
			}
			
			// Tinh thoi gian can de ban het so dan hien tai
			// t_bang = soLuongDan / tocDoRaDon

			
			// -------- TRUONG HOP 2: Du thoi gian ban het ca bang
			if (thoiGianConLai >= thoiGianBanHetDan) {
				
				int damage  = soLuongDan * getSatThuongCoBan();
				tongDamage += damage;
				thoiGianConLai -= thoiGianBanHetDan; // tru thoi gian ban
				
				cout << "	Ban het " << soLuongDan << " vien" << " (mat " << thoiGianBanHetDan << "s)"
				<< " | Damage: +" << damage << " | Con lai: " << thoiGianConLai << "s" << endl;
				
				soLuongDan = 0;
				
			
			} 
			else { 	// -------- TRUONG HOP 3: Khong du thoi gian ban het bang
				
				int danBan = (int)(getTocDoRaDon() * thoiGianConLai);	
				// Neu bang 0 thi khong du thoi gian ban vien nao -> dung lai
				if (danBan == 0) break;
				
				// Damage = so dan ban duoc them  * sat thuong moi vien
				int damage  = danBan * getSatThuongCoBan();
				tongDamage += damage;
				soLuongDan -= danBan; // tru dan da ban
				
				cout <<"	Ban them " << danBan << " vien | Damage: +" << damage			
				<< " | Dan con lai trong bang: " << soLuongDan << " vien" << endl;
				
				thoiGianConLai = 0; // het time , thoat 
			}
		}
		
		//// KET QUA 
		cout<<endl;
		cout << left << setw(28) << "	Tong so lan thay bang:"	<< soLanThayBang	<< endl;
		cout << left << setw(28) << "	Dan con lai:"			<< soLuongDan		<< " vien" << endl;
		cout << left << setw(28) << "	Tong damage :"			<< tongDamage		<< endl;
		
		return tongDamage;
	}
	friend istream& operator >> (istream& is, Sung &sg);
	friend ostream& operator << (ostream& os, Sung sg) {
		os << "Player dang su dung VU KHI: " ;
		os << "Sung "				<< sg.getTenVuKhi()			<< endl;
		os << left << setw(22) << "Sat thuong/vien:"	<< sg.getSatThuongCoBan()	<< endl;
		os << left << setw(22) << "Toc do ban:"			<< sg.getTocDoRaDon()		<< " dan/giay" << endl;
		os << left << setw(22) << "Dan con lai:"		<< sg.soLuongDan			<< " vien" << endl;
		os << left << setw(22) << "Toc do thay bang:"	<< sg.tocDoThayBang			<< " giay" << endl;
		return os;
	}
};

istream& operator >> (istream& is, Sung &sg){
	string name ;
	is.ignore();
	int damage ; 
	float td ;
	cout << "===== VU KHI: SUNG =====" << endl;	
	cout << "Moi ban nhap ten Sung : " ; getline(is,name) ;
	cout << "Moi ban nhap sat thuong / vien dan : " ; is >> damage ;
	cout << "Moi ban nhap toc do ban / 1s (so dan ban duoc trong 1s) : " ; is >> td ;
	sg.setTenVuKhi(name);
	sg.setSatThuongCoBan(damage);
	sg.setTocDoRaDon(td);
	cout << "Moi ban nhap so luong dan (so luong bang dan) : " ; is >> sg.soLuongDan ; 
	cout << "Moi ban nhap toc do thay bang (giay) : " ; is >> sg.tocDoThayBang ; 
	return is ; 
	
}
