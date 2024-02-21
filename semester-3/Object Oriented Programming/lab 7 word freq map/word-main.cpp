
#include "WordMap.hpp"

using namespace std;

int main() {
    WordMap dict;
    dict.read();
    string wordToFind = "World";
    cout << "\033[1m";
    dict.findWord(wordToFind) ? 
        cout << "Слово '" << wordToFind << "' присутсвует в словаре\n"
        : cout << "Слово '" << wordToFind << "' отсутствует в словаре\n";
    
    dict.print();
    dict.printSortedFreq();
    dict.printSameLetter('h');
    
    return 0;
}