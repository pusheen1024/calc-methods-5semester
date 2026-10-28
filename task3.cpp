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

	auto l = [&] (ld xs) {
		ld ans = 0;
		for (int k = 0; k <= n; k++) {
			ld coeff = 1;
			for (int i = 0; i <= n; i++) {
				if (i == k) continue;
				coeff *= (xs - x[i]);
				coeff /= (x[k] - x[i]);
			}
			ans += f[k] * coeff;
		}
		return ans;
	};

	vector<ld> x1;
	for (int i = 0; i <= n; i++) {
		x1.pb(x[i]);
		if (i + 1 <= n) x1.pb((ld) (x[i] + x[i + 1]) / 2);
	}
	cout << "x    ";
	for (int i = 0; i < x1.size(); i++) cout << x1[i] << ' ';
	cout << '\n';
	cout << "L(x) ";
	for (int i = 0; i < x1.size(); i++) {
		cout << l(x1[i]) << ' ';
	}
	cout << '\n';
}
