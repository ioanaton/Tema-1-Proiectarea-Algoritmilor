#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <fstream>
using namespace std;
const int mod = 1000000007;
// valorile globale pentru calcularea numarului finbonacci
long long fb1 = 0;
long long fb2 = 0;
void fast_fib(long long n) {
    if (n == 0) {
        fb1 = 0;
        fb2 = 1;
        return;
    }
    // apelam recursiv fast fibonacci pentru n/2
    fast_fib(n / 2);
    // 2 auxiliari pentru calcularea numarului fibonacci
    long long a, b;
    a = 2 * fb2 - fb1;
    if (a < 0)
        a += mod;
    a = (fb1 * a) % mod;
    b = (fb1 * fb1 + fb2 * fb2) % mod;
    // daca n este par fb1 primeste a si fb2 b
    // in caz contrar fb1 b si fb2 suma a+b
    if (n % 2 == 0) {
        fb1 = a;
        fb2 = b;
    } else {
        fb1 = b;
        fb2 = a + b;
    }
}

int main() {
    ifstream fin("badgpt.in");
    ofstream fout("badgpt.out");
    char c;
    int ans = 1;
    long long nr;
    // citim fiecare litera
    while (fin >> c) {
        // citim numarul care o precede
        fin >> nr;
        // daca litera este u sau n
        if (c == 'n' || c == 'u') {
            // calculam fast fibonacci pentru nr + 1
            fast_fib(nr+1);
            // inmultim nr de variante obtinut cu cele
            // obtinute pana acum
            ans = ans * fb1 % mod;
        }
    }
    // in ans se afla rezultatul final
	fout << ans << endl;
	return 0;
}
