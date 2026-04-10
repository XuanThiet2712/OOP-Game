#pragma once
#include<iostream>
#include<iomanip>
#include<string>
#include "VuKhi.h"

using namespace std;
class Kiem : public VuKhi {
    private: 
        float doBen; // độ bền (0 - 100)
    public:
        //Constructor
        Kiem() : VuKhi() {
            doBen == 100.0;
        }
        Kiem (string ten, int st, float td, float db) : VuKhi(ten,st, td) {
            doBen = db;
        }
        //Hàm hủy
        ~Kiem() {}
        //Getter / Setter
        float getDoBen() { return doBen; }
        void setDoBen(float db) {
            if (db >= 0 && db <= 100)
                doBen = db;
        }
        //Mài kiếm
        void MaiKiem() {
            doBen = 100;
            cout << ">> Da mai kiem! Do ben = 100\n";
        }
        // Mô tả tấn công
        void TanCong() override {
            cout << " [KIEM] " << tenVuKhi
                 << " | ST: " << satThuongCoBan
                 << " | TD: " << tocDoRaDon << "don/s"
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

            int tongDon = (int)(tocDoRaDon * t); // tổng số đòn đánh
            int tongDamage = 0;

            cout << ">> Tan cong trong " << t << " giay (" << tongDon << " don)\n";

            for (int i = 0; i < tongDon; i++) {
                if (doBen <= 0) break;
                // hệ số độ bền (0.5 -> 1.0)
                float heSoDoBen = 0.5f + (doBen / 100.0f) * 0.5f;

                int damageMoiDon = (int)(satThuongCoBan * heSoDoBen);

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
        
    
};


