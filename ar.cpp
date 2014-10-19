#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {

	int testCases;
	long long int a;
	long long int b;
	long long int c;
	string op;

	cin >> testCases;
	while(testCases--) {
		cin >> a;
		cin >> op;
		cin >> b;

		if(op == "+") c = a + b;
		else if(op == "-") c = a - b;
		else if(op == "*") c = a * b;
		else if(op == "/") c = a / b;

		while(1) {
			cin >> op;
			if(op == "=") break;
			cin >> b;

			if(op == "+") c = c + b;
			else if(op == "-") c = c - b;
			else if(op == "*") c = c * b;
			else if(op == "/") c = c / b;
		}

		cout << c << endl;
	}
	return 0;
}
