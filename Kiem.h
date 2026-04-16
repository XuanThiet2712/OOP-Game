#include "VuKhi.h"
class Kiem : public VuKhi {
    private: 
        float doBen; // độ bền (0 - 100)
    public:
        //Constructor
        Kiem() : VuKhi() {
            doBen = 100.0;
        }
        Kiem (string ten, int st, float td, float db) : VuKhi(ten,st, td) {
            doBen = db;
        }
        //Hàm hủy
        ~Kiem() {}
        //Getter / Setter
        float getDoBen() { return doBen; }
        void setDoBen(float db) {
            if (db < 0) doBen = 0;
            else if (db > 100) doBen = 100;
            else doBen = db;
        }
        //Mài kiếm
        void MaiKiem() {
            doBen = 100;
            cout << ">> Da mai kiem! Do ben = 100\n";
        }
        // Mô tả tấn công
        void TanCong() override {
            cout << " [KIEM] " << getTenVuKhi()
                 << " | ST: " << getSatThuongCoBan()
                 << " | TD: " << getTocDoRaDon() << "don/s"
                 << " | Do Ben:  " << doBen << "/100";
            if (doBen <= 0) cout << "[GAY!]";
            else if (doBen < 30) cout << "[THAP]";
            cout << endl;
        }
        //Tính sát thương
        int SatThuong(int t) override {
            if (doBen <= 0) {
                cout << ">> Kiem da gay! Khong the tan cong!\n";
                return 0;
            }

            int tongDon = (int)(getTocDoRaDon() * t); // tổng số đòn đánh
            int tongDamage = 0;

            cout << ">> Tan cong trong " << t << " giay (" << tongDon << " don)\n";

            for (int i = 0; i < tongDon; i++) {
                if (doBen <= 0) break;
                // hệ số độ bền (0.5 -> 1.0)
                float heSoDoBen = 0.5f + (doBen / 100.0f) * 0.5f;

                int damageMoiDon = (int)(getSatThuongCoBan() * heSoDoBen);

                tongDamage += damageMoiDon;

                // giảm độ bền mỗi đòn
                doBen = max(0.0f, doBen - 0.7f);
            }

            cout << ">> Tong sat thuong: " << tongDamage << endl;
            cout << ">> Do ben con lai: " << doBen << "/100\n";

            if (doBen <= 0) cout << ">> Kiem da gay! Can mai kiem.\n";
            else if (doBen < 30) cout << ">> Canh bao: Do ben thap!\n";

            return tongDamage;
        }
        //Xuất thông tin
        friend ostream& operator<<(ostream& os, Kiem& km) {
            os << "===== THONG TIN KIEM =====\n";
            os << setw(20) << left << "Ten:" << km.getTenVuKhi() << endl;
            os << setw(20) << left << "Sat thuong:" << km.getSatThuongCoBan() << endl;
            os << setw(20) << left << "Toc do:" << km.getTocDoRaDon() << " don/s\n";
            os << setw(20) << left << "Do ben:" << km.doBen << "/100";

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
            cout << "Nhap ten vu khi: ";
            getline(is >> ws, ten);
            cout << "Nhap sat thuong: ";
            is >> st;
            cout << "Nhap toc do: ";
            is >> td;
            km.setTenVuKhi(ten);
            km.setSatThuongCoBan(st);
            km.setTocDoRaDon(td);
            cout << "Nhap do ben: ";
            is >> km.doBen;
            if (km.doBen < 0) km.doBen = 0;
            if (km.doBen > 0) km.doBen = 100;
            return is;
        }
        
};
