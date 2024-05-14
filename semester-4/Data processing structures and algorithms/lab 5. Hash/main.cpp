
#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

const int EINSTEIN_PRIME = 2237561;
template<typename Tkey>
struct HashTable {
	vector<vector<Tkey>> table;

	HashTable(int size) {
		table.resize(size);
	}

	int hash(string key) {
	    // return ((int)key[0] + key.back() * (int)key.size()) % table.size();
        
        int res = 0;
        for (int i = 0; i < key.size(); ++i)
            res += key[i] * (i + 1);
        return res % table.size();
	}

	bool insert(string key) {
		int hv = hash(key);
		table[hv].push_back(key);
		return table[hv].size() == 1;
	}

	bool search(string key) {
        cout << key << " ";
		int hv = hash(key);
		for (auto& e : table[hv])
			if (e == key)
				return true;
		return false;
	}

    int collisions() {
        int collisions = 0;
        for (vector<string>& v : table)
            collisions += max(0, (int)v.size() - 1);
        return collisions;
    }
};

#define time_mark(val) val = chrono::high_resolution_clock::now()
#define time_duration(text) cout << text << duration_cast<chrono::milliseconds>(stop - start).count() << " milliseconds\n"

int main() {
    srand(time(NULL));
	chrono::steady_clock::time_point start, stop;
    freopen("input.txt", "r", stdin);
    
    // cout << "Введите количество городов и размер таблицы: ";
    // int cities_count, table_size; cin >> cities_count >> table_size;


    vector<string> cities;
    for (string city; getline(cin, city);)
        cities.push_back(city);

    HashTable<string> table(500);
    
    int insertions = 1000;
    for (int i = 0; i < insertions; ++i)
        table.insert(cities[rand() % cities.size()]);


    table.insert("aaaaaaaaaa");
    if (table.search("aaaaaaaaaa")) cout << "+\n"; else cout << "-\n";
    cout << "aaaaaaaaaa hash: " << table.hash("aaaaaaaaaa") << "\n";

    table.insert("yk");
    if (table.search("yk")) cout << "+\n"; else cout << "-\n";
    cout << "yk hash: " << table.hash("yk") << "\n\n";



    cout << "Поиск элементов:\n";
    vector<string> queries = {"Vadlamuru", "Moscow", "Rybinsk", "Krakozabra"};
    


    for (string &q : queries)
        if (table.search(q)) cout << "+\n"; else cout << "-\n";
    cout << "\n";

    printf("Размер таблицы: %d\n", table.table.size());
    printf("Количество записей: %d\n", cities.size());
	printf("Количество коллизий: %d\n", table.collisions());
	return 0;
}