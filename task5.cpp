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
	int m = n * 4;
	vector<vector<int>> a(m, vector<int> (m + 1));
	int cur = 0;
	int h = 1;
	for (int i = 0; i < n; i++) {
		a[i + cur][i * 4] = 1;
		a[i + cur][m] = f[i];
	}
	cur += n;
	for (int i = 0; i < n; i++) {
		int pw = 1;
		for (int j = 0; j < 4; j++) {
			a[i + cur][i * 4 + j] = pw;
			pw *= h;
		}
		a[i + cur][m] = f[i + 1];
	}
	cur += n;
	for (int i = 0; i + 1 < n; i++) {
		int pw = 1;
		int coeff = 1;
		for (int j = 1; j < 4; j++) {
			a[i + cur][i * 4 + j] = coeff * pw;
			pw *= h;
			coeff++;
		}
		a[i + cur][(i + 1) * 4 + 1] = -1;
	}
	cur += (n - 1);
	for (int i = 0; i + 1 < n; i++) {
		a[i + cur][i * 4 + 2] = 2;
		a[i + cur][i * 4 + 3] = 6 * h;
		a[i + cur][(i + 1) * 4 + 2] = -2;
	}
	cur += (n - 1);
	a[cur][2] = 2;
	cur++;
	a[cur][n * 4 - 2] = 2;
	a[cur][n * 4 - 1] = 6 * h;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j <= m; j++) {
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
}
