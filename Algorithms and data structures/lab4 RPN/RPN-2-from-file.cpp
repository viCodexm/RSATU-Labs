
#include <bits/stdc++.h>

using namespace std;


class Calculator {
public:
	
	vector<string> rpn;

	void run() {
		cout << "Чтение из файла ouput.txt\n";
		fstream file("output.txt", ios_base::in);
		if (!file.is_open())
			{ cout << "Файл не открывается!\n"; return; }

		string s;
		while (getline(file, s))
			if (!s.empty())
				rpn.push_back(s);
		
		if (!rpn.empty()) {
			cout << "Ответ: "; solve();
		}
		else cout << "Ошибка, файл пуст!\n";
		file.close();
	}

	void solve() {
		stack<float> md;

		for (string& s : rpn) {
			if (s == "+" || s == "-" || s == "*" || s == "/") {
				if (md.size() < 2) { error(); return; }
				float y = md.top(); md.pop();
				float x = md.top(); md.pop();
				
				switch (s[0]) {
				case '+':
					md.push(x + y);
					break;
				case '-':
					md.push(x - y);
					break;
				case '*':
					md.push(x * y);
					break;
				case '/':
					md.push(x / y);
					break;
				}
				continue;
			}
			else md.push(stoi(s));
		}
		if (md.size() > 1) {
			cout << "Ошибка!";
			return;
		}
		cout << md.top();
		md.pop();
	}

	void error() {
		cout << "Ошибка! Неверный ввод!\n";
		exit(0);
	}
	
};



int main() {

	Calculator calc;
	calc.run();
	
	return 0;
}