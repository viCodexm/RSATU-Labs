
#include <bits/stdc++.h>

using namespace std;


class Calculator {
public:
	
	stack<char> operatorStack;
	vector<string> rpn;
	
	bool isoperat(char& c) {
		return c == '+' || c == '-' || c == '*' || c == '/';
	}

	void run() {
		cout << "Запись в файл ouput.o\n";
		fstream file("output.o", ios_base::out);
		if (!file.is_open())
			{ cout << "Файл не открывается!\n"; return; }

		cout << "Введите выражение:\n";
		if (read())	{
			cout << "Ответ: "; for (string& s : rpn) { cout << s << " "; file << s << "\n"; }
		}
		else cout << "Ошибка!\n";
		file.close();
	}

	void error() {
		cout << "Ошибка! Неверный ввод!\n";
		exit(0);
	}

	int getPriority(char& c) {
		switch (c) {
		case '+': return 0;
		case '-': return 0;
		case '*': return 1;
		case '/': return 1;
		case '(': return -1;
		case ')': return 2;
		}
		error();
        return 0;
	}
	// a >= b ? true : false
	bool higher_precedence(char& a, char& b) {
		return getPriority(a) >= getPriority(b);
	}

	bool read() {
		string infix; getline(cin, infix);
		int n = infix.size();
		// 'i' changes if we found an integer
		for (int i = 0; i < n; ++i) {
			if (infix[i] == ' ') continue;

			if (infix[i] == '(') {
				operatorStack.push('(');
				continue;
			}
			if (infix[i] == ')') {
				bool found = false;
				while (!operatorStack.empty() && !found) {
					rpn.push_back({ operatorStack.top() });
					operatorStack.pop();
					if (operatorStack.top() == '(') found = true;
				}
				if (!found) error();
				else operatorStack.pop();
				continue;
			}

			// if it's operator
			if (isoperat(infix[i]) && i + 1 < n && infix[i + 1] == ' ') { // if not negative number
				if (!operatorStack.empty() && higher_precedence(operatorStack.top(), infix[i]))
				{
					rpn.push_back({ operatorStack.top() });
					operatorStack.pop();
				}
				operatorStack.push(infix[i]);
				continue;
			}

			bool negative = (infix[i] == '-');

			// if it's integer
			string integer; negative ? integer = "-" : integer = "";

			// we are changing iteraror `i`
			i = negative ? i + 1 : i;
			while (i < infix.size() && isdigit(infix[i]))
			{
				integer += infix[i];
				++i;
			}
			--i;

			if (!integer.empty())
				rpn.push_back(integer);
			else {
				error();
				return false;
			}

		}
		while (!operatorStack.empty()) {
			rpn.push_back({ operatorStack.top() });
			operatorStack.pop();
		}
		return true;
	}
	
};



int main() {

	Calculator calc;
	calc.run();
	
	return 0;
}