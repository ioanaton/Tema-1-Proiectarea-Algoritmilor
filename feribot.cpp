#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

long long sum(int n, const vector< long long>& c) {
    // adunam toate valorile vectorului si returnam suma
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += c[i];
    }
    return sum;
}
int solution(int n, int k, const vector <long long>& c, long long max) {
    // greutarea feribotului curent
    long long crt_cost = 0;
    // nr de feriboturi
    long long f_number = 0;

    for (int i = 0; i < n; i++) {
        // daca masina curenta mai incape pe feribot o adunam la
        // greutatea feribotului
        if (c[i] + crt_cost <= max) {
            crt_cost += c[i];
        // daca o masina este din start mai mare decat valoarea
        // maxima este clar ca aranjarea masinilor nu poate fi realizata
        } else if (c[i] > max) {
            return 0;
        // daca masina curenta nu mai incape pe feribot o punem pe urmatorul
        // feribot si crestem nr de feriboturi
        } else if (crt_cost + c[i] > max) {
            crt_cost = c[i];
            f_number++;
        }
        // daca greutatea curenta este cea maxima, trecem la urmatorul feribot
        if (crt_cost == max) {
            crt_cost = 0;
            f_number++;
        }
        // la final verificam daca nr de feriboturi necesare este egal cu cel
        // dat in enuntul problemei si returnam 1 in caz de egalitate si
        // 0 in caz contrar
        if (f_number >= k)
        return 0;
    }
    return 1;
}

int64_t Solve(int n, int k, const vector<long long> &c) {
    long long max = sum(n, c);
    long long start = 0, end = max - 1, mid;
    // facem cautare binara pentru a gasi cea mai mica greutate
    // pentru care impartirea in feriboturi este corecta
    while (start <= end) {
        mid = start + (end - start) /2;

        // testam daca pentru valoarea curenta se respecta nr de feriboturi
        if (solution(n, k, c, mid) == 1) {
            end = mid - 1;
            // daca pentru mid-1 nu se verifica numarul de feriboturi
            // inseamna ca valoarea curenta este cea mai mica si o returnam
            if (solution(n, k, c, mid-1) == 0)
                return mid;
        } else {
            start = mid + 1;
        }
    }
    return start;
}

vector<long long> ReadVector(istream& is, int size) {
    vector<long long> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    // citim n,k si vectorul
    int n, k;
    fin >> n >> k;
    auto c = ReadVector(fin, n);
    // calculam solutia
    auto res = Solve(n, k, c);
    fout << res << "\n";

    return 0;
}
