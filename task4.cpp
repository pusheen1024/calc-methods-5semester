#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
#define pb push_back

int main() {
	int n = 3;
	vector<int> x;
	for (int i = 1; i <= n + 1; i++) x.pb(i);
	vector<int> f = {2, 9, 28, 65};
	cout << "x ";
	for (int i = 0; i <= n; i++) cout << x[i] << ' ';
	cout << '\n';
	cout << "f ";
	for (int i = 0; i <= n; i++) cout << f[i] << ' ';
	cout << '\n' << '\n';
	
	vector<vector<ld>> diff(n + 1);
	for (int i = 0; i <= n; i++) diff[0].pb(f[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < diff[i - 1].size(); j++) {
			diff[i].pb(((ld) diff[i - 1][j] - diff[i - 1][j - 1]) / (x[j - 1 + i] - x[j - 1]));
		}
	}
	cout << "Таблица разделённых разностей:" << '\n';
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < diff[i].size(); j++) {
			cout << diff[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';

	auto N = [&](ld xs) {
		ld res = 0;
		for (int i = 0; i <= n; i++) {
			ld cur = diff[i][0];
			for (int j = 0; j < i; j++) 
				cur *= (xs - x[j]);
			res += cur;
		}
		return res;
	};

	vector<ld> x1;
	for (int i = 0; i <= n; i++) {
		x1.pb(x[i]);
		if (i + 1 <= n) x1.pb((ld) (x[i] + x[i + 1]) / 2);
	}
	cout << "x    ";
	for (int i = 0; i < x1.size(); i++) cout << x1[i] << ' ';
	cout << '\n';
	cout << "N(x) ";
	for (int i = 0; i < x1.size(); i++) cout << N(x1[i]) << ' ';
	cout << '\n';
}
