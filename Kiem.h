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
    
        
    
}


