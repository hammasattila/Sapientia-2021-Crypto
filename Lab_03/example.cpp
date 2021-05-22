
#include <NTL/matrix.h>
#include <NTL/mat_ZZ.h>
#include <time.h>
#include <iomanip>

using namespace std;
using namespace NTL;

void my_writeM(Mat<ZZ>key) {
	for (int i = 0; i < key.NumRows(); ++i) {
		for (int j = 0; j < key.NumCols(); ++j)
			cout << setw(6) << key[i][j];
		cout << endl;
	}
}

void keyGen(Mat<ZZ> &key, Mat<ZZ> &invKey, int mod) {
	ZZ d;
	Mat<ZZ>adjKey;
	int i, j, n = key.NumRows();
	adjKey.SetDims(n, n);

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			key[i][j] = rand() % mod;

	while (1) {
		inv(d, adjKey, key, 0);
		d = d % mod;
		if (d < 0) d += mod;
		if ( GCD(d, to_ZZ(mod)) != to_ZZ(1) ) {
			i = rand() % n;
			j = rand() % n;
			key[i][j] = rand() % mod;
		}
		else break;
	}
	
	ZZ idet = InvMod(d, to_ZZ(mod));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			invKey[i][j] = (adjKey[i][j] * idet) % mod;

}


int main()
{
	Mat<ZZ> key, invKey;
	int n, mod = 256;
	cout << "n: ";
	cin >> n;

	key.SetDims(n, n);
	invKey.SetDims(n, n);
	keyGen(key, invKey, mod);

	cout << "key mat: " << endl;
	my_writeM(key);

	cout << "inv mat: " << endl;
	my_writeM(invKey);

	Mat<ZZ> x;
	x.SetDims(n, n);
	mul(x, key, invKey);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			x[i][j] = x[i][j] % mod;

	cout << "check mat: " << endl;
	my_writeM(x);

	return 0;
}