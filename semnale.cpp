#include <iostream>

using namespace std;

const int mod = 1000000007;
// calculam inversul
unsigned long long inverse(unsigned long long n) {
	int a = mod - 2;
	unsigned long long result = 1;
    // cat timp a este mai mare ca 0
    while (a > 0) {
        // daca a e impar  inmultim rezultatul cu n
        if (a % 2 == 1)
            result = (result * n % mod) % mod;
        // a este actualizat cu jumatatea lui iar n cu
        // patratul lui
        a = a / 2;
        n = (n * n) % mod;
    }
    return result;
}
unsigned long long combinations(unsigned long long x,
                                 int y) {
    // adresam cazurile speciale
	if (x < y) {
		return 0;
    }
    if (x == 0) {
        return 1;
    }

    // vector pentru a calcula factorialul
    unsigned long long fac[x + 1];
    fac[0] = 1;
    // calculam factorialul
    for (int i = 1; i <= x; i++)
        fac[i] = (fac[i - 1] * i) % mod;

    // formula combinarilor: x!/ y!(x-y)!, dar folosim inversul
    // conform micii teoreme a lui Fermat pentru ca nu putem
    // imparti cu numere foarte mari
    return (fac[x] * inverse(fac[y]) % mod * inverse(fac[x - y]) % mod) % mod;
}
long long type1(int x, int y) {
    // combinari de nr de 0-uri plus 1 luate cate nr de 1-uri
	return combinations(x+1, y);
}

int type2(int x, int y) {
    long long sum = 0;
    // incepand de la (y+1)/2 d 1-uri fixate pe care le crestem treptat
	for (int i = (y + 1) / 2; i <= y; i++) {
        // adunam la suma combinari de nr de 0+1 luate cate 1-uri fixate
        // inmultit cu combinari de 1 -uri fixate luate cate nr de 1-uri
        // nefixate
    	sum =(sum + (combinations(x+1, i) * combinations(i, y-i)) % mod) % mod;
	}
    return sum;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}
    return 0;
}
