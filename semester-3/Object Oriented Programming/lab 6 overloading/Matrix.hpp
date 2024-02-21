#pragma once
#include <bits/stdc++.h>

class Matrix {
private:
    std::vector<std::vector<double>> mat;
    int rows, cols;

public:

    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        mat.resize(rows, std::vector<double>(cols, 0.0));
    }

    Matrix& operator=(double value) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mat[i][j] = value;
        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Error: Matrices must have the same dimensions to be added.");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[i][j] = mat[i][j] + other.mat[i][j];
        return result;
    }

    Matrix operator+(double value) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[i][j] = mat[i][j] + value;
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Error: First matirx must have same amount of columns with second matrix amount of rows to be multiplied.");
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.cols; j++)
                for (int k = 0; k < cols; k++)
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
        return result;
    }

    Matrix operator*(double value) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[i][j] = mat[i][j] * value;
        return result;
    }

    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            return false;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (mat[i][j] != other.mat[i][j])
                    return false;
        return true;
    }

    Matrix operator++() {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.mat[j][i] = mat[i][j];
        return result;
    }

    double getValue(int i, int j) const { return mat[i][j]; }
    void setValue(int i, int j, double value) { mat[i][j] = value; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    void print(std::string message) {
        std::cout << "\n" << message << "\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                std::cout << std::setw(3) <<  mat[i][j];
            std::cout << "\n";
        }
    }
};