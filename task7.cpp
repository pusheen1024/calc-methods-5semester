#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long double ld;
#define pb push_back

const ld EPS = 1e-9;

pair<vector<vector<ld>>, ld> gauss_forward(vector<vector<ld>> a) {
	int n = a.size();
	int swaps = 0;
	ld det = 1;
	for (int i = 0; i < n; i++) {
		if (abs(a[i][i]) < EPS) {
			swaps++;
			int mx = i;
			for (int m = i + 1; m < n; m++) {
				if (abs(a[m][i]) > abs(a[mx][i])) {
					mx = m;
				}
			}
			if (abs(a[mx][i]) < EPS) {
				int mx1 = i;
				for (int m = i + 1; m < n; m++) {
					if (abs(a[i][m]) > abs(a[i][mx1])) {
						mx1 = m;
					}
				}
				for (int j = 0; j < n; j++) swap(a[j][i], a[j][mx1]);
			}
			swap(a[mx], a[i]);
		}
		ld st = a[i][i];
		det *= st;
		for (int j = 0; j <= n; j++) {
			a[i][j] /= st;
		}
		for (int j = i + 1; j < n; j++) {
			ld st = a[j][i];
			for (int k = 0; k <= n; k++) {
				a[j][k] -= a[i][k] * st;
			}
		}
	}
	if (swaps % 2) det *= (-1);
	cout << "ПВГЭ выполнена " << swaps << " раз." << '\n';
	return {a, det};
}

vector<ld> gauss_backward(vector<vector<ld>> a) {
	int n = a.size();
	vector<ld> x(n);
	for (int i = n - 1; i >= 0; i--) {
		ld sum = 0;
		for (int j = i + 1; j < n; j++) {
			sum += x[j] * a[i][j];
		}
		x[i] = a[i][n] - sum;
	}
	return x;
}

vector<ld> mul(vector<vector<ld>> a, vector<ld> v) {
	int n = a.size();
	vector<ld> res(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i] += a[i][j] * v[j];
		}
	}
	return res;
}

int main() {
	int n = 5;
	vector<vector<ld>> a(n, vector<ld> (n));
	int cur = 11;
	vector<ld> v;
	for (int i = 0; i < n; i++) {
		v.pb(cur);
		for (int j = 0; j < n; j++) {
			if (i == j) a[i][j] = cur;
			else a[i][j] = 0.01 * cur;
		}
		cur += 2;
	}
	a[0][0] = 0;
	vector<ld> b = mul(a, v);
	for (int i = 0; i < n; i++) a[i].pb(b[i]);
	cout << "Р. М. К.:" << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << ' ';
		}
		cout << " | " << a[i][n] << '\n';
	}
	cout << '\n';
	auto [res, det] = gauss_forward(a);
	cout << "Определитель: " << det << '\n';
	cout << '\n';
	cout << "Прямой ход:" << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << res[i][j] << ' ';
		}
		cout << " | " << res[i][n] << '\n';
	}
	auto ans = gauss_backward(res);
	cout << '\n';
	cout << "Ответ:" << '\n';
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << ans[i] << '\n';
	}
	cout << '\n';
	vector<ld> b1 = mul(a, ans);
	cout << "Проверка:" << '\n';
	for (int i = 0; i < n; i++) {
		cout << b[i] << ' ' << b1[i] << '\n';
	}
}
