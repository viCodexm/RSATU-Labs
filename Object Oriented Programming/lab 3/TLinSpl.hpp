
#include <bits/stdc++.h>
#include "TDat.hpp"

using namespace std;

class TLinSpl : public TDat {
public:
    double linear_interpolation(double x1, double y1, double x2, double y2, double x) {
        return y1 + ((y2 - y1) / (x2 - x1)) * (x - x1);
    }
    double get_y(double x) override {
        if (coords.find(x) == coords.end()) {
            auto left = coords.begin();
            while (left != coords.end() && left->first < x)
                left++;
            
            left--;
            if (left == coords.end())
                return 1;
            
            auto right = left++;
            coords[x] = linear_interpolation(right->first, right->second, left->first, left->second, x);
        }

        return coords[x];
    }
};