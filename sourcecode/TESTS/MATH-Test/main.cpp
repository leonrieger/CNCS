#include "MATH/src/MATH.hpp"
using namespace unit_conversions;
#include <iostream>
using namespace std;

int main() {
	int i = 10;
	double test = 115.202;
	cout << "test1" << endl;
	cout << inch_to_mm(i) << endl;
	cout << inch_to_mm(test) << endl;

	char x[10];
	cin >> x;
}
