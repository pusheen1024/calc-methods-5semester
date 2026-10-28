#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
#define pb push_back

pair<ld, int> f(ld x, ld eps) {
	ld nom = x;
	ld denom = 1;
	int i = 1;
	int sign = 1;
	ld ans = 0;
	int n = 0;
	while (true) {
		ld cur = sign * nom / denom;
		ans += cur;
		n++;
		if (abs(cur) < eps) break;
		nom *= x * x;
		denom *= (i + 1) * (i + 2);
		sign *= (-1);
		i += 2;
	}
	return {ans, n};
}

int main() {
	vector<ld> values;
	ld step = 15;
	int cnt = 9;
	for (ld x = -step * (cnt / 2); x <= step * (cnt / 2 + 1); x += step)
		values.pb(x);
	vector<ld> sums;
	vector<int> number;
	ld eps = 0.0001;
	for (int i = 0; i < cnt; i++) {
		auto [s, c] = f(values[i], eps);
		sums.pb(s);
		number.pb(c);
	}
	cout << "x ";
	for (int i = 0; i < cnt; i++) {
		cout << values[i] << ' ';
	}
	cout << '\n';
	cout << "S ";
	for (int i = 0; i < cnt; i++) {
		cout << sums[i] << ' ';
	}
	cout << '\n';
	/*cout << "sin ";
	for (int i = 0; i < cnt; i++) {
		cout << sin(values[i]) << ' ';
	}
	cout << '\n';*/
	cout << "n ";
	for (int i = 0; i < cnt; i++) {
		cout << number[i] << ' ';
	}
	cout << '\n';

}
