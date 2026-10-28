#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
#define pb push_back

vector<ld> gauss(vector<vector<ld>> a) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		int mx = i;
		for (int j = i + 1; j < n; j++) {
			if (abs(a[j][i]) > abs(a[mx][i])) mx = j;
		}
		swap(a[mx], a[i]);
		for (int j = n; j >= i; j--) {
			a[i][j] /= a[i][i];
		}
		for (int j = 0; j < n; j++) {
			if (j != i) {
				for (int k = n; k >= i; k--) {
					a[j][k] -= a[i][k] * a[j][i];
				}
			}
		}
	}
	vector<ld> ans(n);
	for (int i = 0; i < n; i++) ans[i] = a[i][n];
	return ans;
}

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
	vector<vector<ld>> a(n + 1, vector<ld> (n + 2));
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			int pw = n - j;
			a[i][j] = 1;
			for (int k = 0; k < pw; k++) a[i][j] *= x[i];
		}
		a[i][n + 1] = f[i];
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n + 1; j++) {
			cout << a[i][j] << ' ';
			if (j == n) cout << " | ";
		}
		cout << '\n';
	}
	cout << '\n';
	vector<ld> ans = gauss(a);
	for (int i = 0; i <= n; i++) cout << "a" << n - i << ": " << ans[i] << '\n';
	cout << '\n';
	vector<ld> x1;
	for (int i = 0; i <= n; i++) {
		x1.pb(x[i]);
		if (i + 1 <= n) x1.pb((ld) (x[i] + x[i + 1]) / 2);
	}
	cout << "x ";
	for (int i = 0; i < x1.size(); i++) cout << x1[i] << ' ';
	cout << '\n';
	cout << "P ";
	for (int i = 0; i < x1.size(); i++) {
		ld val = 0;
		for (int j = 0; j <= n; j++) {
			val += ans[j] * pow(x1[i], n - j);
		}
		cout << val << ' ';
	}
	cout << '\n';
}
