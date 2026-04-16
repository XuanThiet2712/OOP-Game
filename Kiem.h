#include "VuKhi.h"
class Kiem : public VuKhi {
    private: 
        int doBen; // độ bền (0 - 100)
		int doBenMax;
    public:
        //Constructor
        Kiem() : VuKhi() {
            doBen = 100;
			doBenMax = 100 ; 
        }
        Kiem (string ten, int st, float td, float db) : VuKhi(ten,st, td) {
            doBen = db;
			doBenMax = doBen ; 
        }
        //Hàm hủy
        ~Kiem() {}
        //Getter / Setter
        int getDoBen() { return doBen; }
        void setDoBen(int db) {
            if (db < 0) doBen = 0;
            else doBen = db;
        }
		int getDoBenMax() { return doBen; }
		void setDoBenMax(int db) {
			if (db < 0) doBen = 0;
			else doBen = db;
		}

        // Mô tả tấn công
        void TanCong(){
            cout << " [KIEM] " << getTenVuKhi()
                 << " | ST: " << getSatThuongCoBan()
                 << " | TD: " << getTocDoRaDon() << "don/s"
                 << " | Do Ben:  " << doBen << "/100";
            if (doBen <= 0) cout << "[GAY!]";
            else if (doBen < 30) cout << "[THAP]";
            cout << endl;
        }
        //Tính sát thương
        int SatThuong(int t){
            if (doBen <= 0) {
                cout << ">> Kiem da gay! Khong the tan cong!\n";
                return 0;
            }

            int tongDon = (int)(getTocDoRaDon() * t); // tổng số đòn đánh
            int tongDamage = 0;

            cout << ">> Tan cong trong " << t << " giay (" << tongDon << " don)\n";

           for (int i = 0; i < tongDon; i++) {
			   if (doBen <= 0) break;
			   
			   // hệ số theo độ bền (0 → 1)
			   float heSoDoBen = doBen / (float)doBenMax;
			   
			   int damageMoiDon = (int)(getSatThuongCoBan() * heSoDoBen);
			   
			   tongDamage += damageMoiDon;
			   
			   // giảm 1 độ bền mỗi đòn
			   doBen--;
		   }

            cout << ">> Tong sat thuong: " << tongDamage << endl;
            cout << ">> Do ben con lai: " << doBen << "/100\n";

            if (doBen <= 0) cout << ">> Kiem da gay! \n";
            else if (doBen < 30) cout << ">> Canh bao: Do ben thap!\n";

            return tongDamage;
        }
        //Xuất thông tin
        friend ostream& operator<<(ostream& os, Kiem km) {
            os << "Player dang su dung VU KHI: " ;
            os <<"Kiem " << km.getTenVuKhi() << endl;
            os << setw(20) << left << "Sat thuong:" << km.getSatThuongCoBan() << endl;
            os << setw(20) << left << "Toc do:" << km.getTocDoRaDon() << " don/s\n";
            os << setw(20) << left << "Do ben:" << km.doBen <<"/"<<km.doBenMax<<endl;

            if (km.doBen <= 0) os << " [GAY!]";
            else if (km.doBen < 30) os << " [THAP]";

            os << endl;
            return os;
        }
        //Nhập thông tin
        friend istream& operator>>(istream& is, Kiem& km) {
            string ten;
            int st;
            float td;
			is.ignore();
			cout << "===== VU KHI: KIEM =====" << endl;	
            cout << "Nhap ten kiem : ";
            getline(is >> ws, ten);
            cout << "Nhap sat thuong moi don : ";
            is >> st;
            cout << "Nhap toc do ra don /1s : ";
            is >> td;
            km.setTenVuKhi(ten);
            km.setSatThuongCoBan(st);
            km.setTocDoRaDon(td);
            cout << "Nhap do ben : ";
            is >> km.doBen;
			km.doBenMax = km.doBen ;
            if (km.doBen < 0) km.doBen = 0;
            return is;
        }
        
};
