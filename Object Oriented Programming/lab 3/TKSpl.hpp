
#include <bits/stdc++.h>
#include "TDat.hpp"

using namespace std;

class TKSpl : public TDat {
public:
    double get_y(double x) override {
        if (coords.find(x) == coords.end()) {
            auto left = coords.begin();
            while (left != coords.end() && left->first < x)
                left++;
            if (left == coords.end() || left == coords.begin())
                return 1;
            auto b = prev(left, 1), a = prev(b, 1), d = next(left, 1);
            if (d == coords.end() || b == coords.begin())
                return 1;
            
            coords[x] = quad_interpolation(x, a->first, b->first, left->first, d->first, a->second, b->second, left->second, d->second);
        }

        return coords[x];
    }
    double det(int n, float mat[4][4]) {
        double d = 0;
        int c, subi, i, j, subj;
        float submat[4][4];
        if (n == 2)
            return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
        
        for (c = 0; c < n; c++) {
            subi = 0;
            for (i = 1; i < n; i++) {
                subj = 0;
                for (j = 0; j < n; j++)
                    if (j != c) {
                        submat[subi][subj] = mat[i][j];
                        subj++;
                    }
                subi++;
            }
            if (c % 2) d = d + (-mat[0][c] * det(n - 1, submat));
            else d = d + (mat[0][c] * det(n - 1, submat));
        }
        return d;
    }
    float quad_interpolation(float x, float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4) {
        float deterMain;
        float temp[4], detArray[4], answer[4], freeVar[4], aMain[4][4];
        aMain[0][0] = 1;
        aMain[0][1] = x1;
        aMain[0][2] = x1 * x1;
        aMain[0][3] = x1 * x1 * x1;
        aMain[1][0] = 1;
        aMain[1][1] = x2;
        aMain[1][2] = x2 * x2;
        aMain[1][3] = x2 * x2 * x2;
        aMain[2][0] = 1;
        aMain[2][1] = x3;
        aMain[2][2] = x3 * x3;
        aMain[2][3] = x3 * x3 * x3;
        aMain[3][0] = 1;
        aMain[3][1] = x4;
        aMain[3][2] = x4 * x4;
        aMain[3][3] = x4 * x4 * x4;
        freeVar[0] = y1;
        freeVar[1] = y2;
        freeVar[2] = y3;
        freeVar[3] = y4;
        deterMain = det(4, aMain);
        if (deterMain == 0)
            return 1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[j] = aMain[j][i];
                aMain[j][i] = freeVar[j];
            }
            detArray[i] = det(4, aMain);
            for (int j = 0; j < 4; j++)
                aMain[j][i] = temp[j];
        }
        for (int i = 0; i < 4; i++)
            answer[i] = detArray[i] / deterMain;
        return answer[0] + answer[1] * x + answer[2] * x * x + answer[3] * x * x * x;
    }
};