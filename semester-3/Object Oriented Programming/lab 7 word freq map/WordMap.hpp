#pragma once
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct WordMap : map<string, int> {
    fstream input, output;

    WordMap() {
        input.open("input.o");
        output.open("output.o");
        if (!input.is_open() || !output.is_open())
            exit(-1);
    }
    bool isWord(string str) {
        for (char& c : str)
            if (!isalpha(c))
                return false;
        return true;
    }
    void read() {
        string buffer;
        while (!input.eof()) {
            input >> buffer;
            while (!buffer.empty() && !isalpha(buffer[buffer.size() - 1]) && !isalnum(buffer[buffer.size() - 1]))
                buffer.pop_back();
            if (isWord(buffer))
                (*this)[buffer]++;
        }
    }
    bool findWord(string wordToFind) {
        return this->find(wordToFind) != (*this).end();
    }
    vector<pair<string, int>> sortByFrequency() {
        vector<pair<string, int>> word_vector((*this).begin(), (*this).end());
        sort(word_vector.begin(), word_vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        return word_vector;
    }
    template<typename _T>
    void print(_T& ans) {
        cout << "\033[1m";
        cout << "\nСодержимое словаря:\n\033[35m";
        for (auto& [key, val] : ans)
            cout << setw(16) << key << setw(4) << val << "\n";
        cout << "\n\033[0m";
    }
    void print() {
        print(*this);
    }
    void printSortedFreq() {
        vector<pair<string, int>> ans = this->sortByFrequency();
        print(ans);
    }
    void printSameLetter(char letter) {
        cout << "\033[1m";
        cout << "\nСлова, начинающиеся на '" << letter << "':\n\033[31m";
        for (auto& [key, val] : (*this))
            if (key[0] == tolower(letter) || key[0] == toupper(letter))
                cout << key << ": " << val << "\n";
        cout << "\n\033[0m";
    }

    ~WordMap() {
        for (auto& [key, val] : (*this))
            output << key << " " << val << "\n";
        input.close(); output.close();
    }
};