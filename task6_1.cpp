#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef long double ld;
#define pb push_back

vector<vector<ld>> gauss_forward(vector<vector<ld>> a) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		ld st = a[i][i];
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
	return a;
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

ofstream out("res2.txt");

int main() {
	out << setprecision(2) << fixed;
	int n = 1000;
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
	vector<ld> b = mul(a, v);
	for (int i = 0; i < n; i++) a[i].pb(b[i]);
	out << "Р. М. К.:" << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			out << a[i][j] << ' ';
		}
		out << " | " << a[i][n] << '\n';
	}
	out << '\n';
	out << "Прямой ход:" << '\n';
	auto res = gauss_forward(a);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			out << res[i][j] << ' ';
		}
		out << " | " << res[i][n] << '\n';
	}
	auto ans = gauss_backward(res);
	out << '\n';
	out << "Ответ:" << '\n';
	for (int i = 0; i < n; i++) {
		out << "x" << i + 1 << " = " << ans[i] << '\n';
	}
	out << '\n';
	vector<ld> b1 = mul(a, ans);
	out << "Проверка:" << '\n';
	for (int i = 0; i < n; i++) {
		out << b[i] << ' ' << b1[i] << '\n';
	}
}
