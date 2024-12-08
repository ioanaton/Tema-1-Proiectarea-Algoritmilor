/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

long long SolveTask1(vector<long long>& a, vector<long long>& b, int n) {
    // sortam vectorul a crescator si vectorul b descrescator
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(),
        [](long long x, long long y) -> bool {return x > y;});

    long long sum = 0;
    // comparam elementul din a cu cel din b de pe acceeasi pozitie
    // si il adunam la suma pe cel mai mare
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            sum += a[i];
        } else {
            sum += b[i];
        }
    }
    return sum;
}

long long make_sum(vector<long long>& a, int n) {
    // facem suma tuturor elementelor din vector
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

int64_t SolveTask2(vector<long long>& a, vector<long long>& b,
                     int moves, int n) {
    // comparam perechea de numere de pe aceeasi pozitie din
    // fiecare vector, daca elementul din b este mai mare
    // facem swap astfel incat maximele sa ramana in a
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i])
            swap(a[i], b[i]);
    }
    // sortam ambii vector descrescator
    sort(b.begin(), b.end(),
        [](long long first, long long second)-> bool {return first > second;});
    sort(a.begin(), a.end(),
        [](long long first, long long second)-> bool {return first > second;});

    // facem suma tuturor elementelor din a, vectorul de maxime
    long long sum = make_sum(a, n);

    // parcurgem vectorul a pana cand gasim un element mai mic decat primul
    // element din b dupa care, de moves ori, scadem din suma elementul
    // din a si il adunam pe cel din b, pentru a ajunge la suma maxima
    for (int i = 0; i < moves; i++) {
        if (b[i] > a[n - 1 - i])
            sum = sum + b[i] - a[n - 1 - i];
    }
    return sum;
}

vector<long long> ReadVector(istream& is, int size) {
    vector<long long> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b, n) : SolveTask2(a, b, moves, n);
    fout << res << "\n";

    return 0;
}
