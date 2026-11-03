#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef long double ld;
#define pb push_back

const ld EPS = 1e-9;

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

ofstream out("res.txt");

int main() {
	out << setprecision(2) << fixed;
	int n = 5000;
	vector<vector<ld>> a(n, vector<ld> (n));
	int cur = 11;
	vector<ld> v;
	for (int i = 0; i < n; i++) {
		v.pb(cur);
		for (int j = 0; j < n; j++) {
			if (i == j) a[i][j] = cur;
			else if (abs(i - j) == 1) a[i][j] = 0.01 * cur;
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
	
	vector<ld> ax(n);
	vector<ld> bx(n);
	vector<ld> cx(n);
	vector<ld> dx(n);
	for (int i = 0; i < n; i++) {
		if (i > 0) ax[i] = a[i][i - 1];
		bx[i] = -a[i][i];
		if (i + 1 < n) cx[i] = a[i][i + 1];
		dx[i] = a[i][n];
	}
	out << "ai     bi     ci     di" << '\n';
	for (int i = 0; i < n; i++) {
		out << ax[i] << ' ' << bx[i] << ' ' << cx[i] << ' ' << dx[i] << '\n';
	}
	out << '\n';
	vector<ld> p(n + 1);
	vector<ld> q(n + 1);
	p[1] = cx[0] / bx[0];
	q[1] = -dx[0] / bx[0];
	for (int i = 1; i < n; i++) {
		p[i + 1] = cx[i] / (bx[i] - ax[i] * p[i]);
		q[i + 1] = (ax[i] * q[i] - dx[i]) / (bx[i] - ax[i] * p[i]);
	}
	out << "P и Q:" << '\n';
	for (int i = 1; i <= n; i++) {
		out << "p" << i + 1 << " = " << p[i] << "; q" << i + 1 << " = " << q[i] << '\n';
	}
	out << '\n';
	vector<ld> x(n);
	x[n - 1] = q[n];
	for (int i = n - 2; i >= 0; i--) {
		x[i] = p[i + 1] * x[i + 1] + q[i + 1]; 
	}
	out << "Ответ:" << '\n';
	for (int i = 0; i < n; i++) {
		out << "x" << i + 1 << " = " << x[i] << '\n';
	}
	out << '\n';
	/*vector<ld> b1 = mul(a, x);
	cout << "Проверка:" << '\n';
	for (int i = 0; i < n; i++) {
		cout << b[i] << ' ' << b1[i] << '\n';
	}*/
}
