
#include <bits/stdc++.h>

using namespace std;


class Calculator {
public:
	
	stack<char> operatorStack;
	vector<char> rpn;
	
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
			cout << "Ответ: "; for (char& s : rpn) { cout << s << " "; file << s << "\n"; }
		}
		else cout << "Ошибка!\n";
		file.close();
	}

	void error(string message) {
		cout << message;
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
		error("Ошибка #1! Неверный ввод!");
        return 0;
	}
	
	bool higher_precedence(char& a, char& b) {
		return getPriority(a) >= getPriority(b);
	}

	bool findError(string str) {
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		const int size = str.size();

		int open_brace = 0, operands = 0, operations = 0;

		// операций внутри скобок на одну меньше чем операндов
		for (int i = 0; i < size; ++i) {
			if (open_brace < 0)
				return true;
			if (str[i] == '(') {
				open_brace++;
			}
			else if (str[i] == ')') {
				open_brace--;
			}
			else if (isoperat(str[i])) {
				if (i - 1 >= 0 && (isoperat(str[i - 1]) || str[i - 1] == '('))
					return true;
				operations++;
			}
			else if (isalpha(str[i])) {
				if (i - 1 >= 0 && (isalpha(str[i - 1]) || str[i - 1] == ')'))
					return true;
				operands++;
			}
			else return true;
		}

		if (!operations && !operands && !open_brace)
			return false;
		return operands - 1 != operations;
	}
	bool read() {
		string infix; getline(cin, infix);
		if (findError(infix))
			error("Ошибка #2! Неверный ввод!");
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
					if (operatorStack.top() == '(')
						error("Ошибка #3! Неверный ввод!");
					rpn.push_back( operatorStack.top() );
					operatorStack.pop();
					if (operatorStack.top() == '(') found = true;
				}
				if (!found) error("Ошибка #4! Неверный ввод!");
				else operatorStack.pop();
				continue;
			}

			// if it's operator
			if (isoperat(infix[i])) {
				while (!operatorStack.empty() && higher_precedence(operatorStack.top(), infix[i]))
				{
					rpn.push_back( operatorStack.top() );
					operatorStack.pop();
				}
				operatorStack.push(infix[i]);
				continue;
			}

			// if it's char
			rpn.push_back(infix[i]);
		}
		while (!operatorStack.empty()) {
			rpn.push_back( operatorStack.top() );
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