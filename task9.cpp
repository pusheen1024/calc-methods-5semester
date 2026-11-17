#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef long double ld;
#define pb push_back

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

vector<ld> add(vector<ld> a, vector<ld> b) {
    int n = a.size();
    vector<ld> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = a[i] + b[i];
    }
    return res;
}

int main() {
	cout << setprecision(9) << fixed;
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
    vector<vector<ld>> alpha(n, vector<ld> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) alpha[i][j] = 0;
            else alpha[i][j] = -a[i][j] / a[i][i];
        }
    }
    vector<ld> beta(n);
    for (int i = 0; i < n; i++) {
        beta[i] = b[i] / a[i][i];
    }
    cout << "alpha:" << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << alpha[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "beta:" << '\n';
    for (int i = 0; i < n; i++) cout << beta[i] << ' ';
    cout << '\n' << '\n';
    for (auto eps : {1e-3, 1e-6, 1e-9}) {
        cout << "eps = " << eps << '\n';
        vector<ld> x(n);
        cout << "x0: ";
        for (int i = 0; i < n; i++) cout << x[i] << ' ';
        cout << '\n';
        int idx = 1;
        while (true) {
            vector<ld> next_x = add(mul(alpha, x), beta);
            cout << "x" << (idx++) << ": ";
            for (int i = 0; i < n; i++) cout << next_x[i] << ' ';
            cout << '\n';
            ld mx = 0;
            for (int i = 0; i < n; i++) {
                mx = max(mx, abs(next_x[i] - x[i]));
            }
            if (mx < eps) break;
            x = next_x;
        }
        cout << "Число векторов приближений: " << idx << '\n';
        cout << '\n';
    }
}
