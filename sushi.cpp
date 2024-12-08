#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
	// calculam pretul maxim total
	int maxprice = x * n;
	// facem suma notelor pentru fiecare fel de sushi
	vector <long long > grade_sum(m, 0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			grade_sum[i] = grade_sum[i] + g[j][i];

	// initializam primul element cu 0
    vector< vector<int> > dp(m + 1, vector<int>(maxprice+ 1, 0));
    for (int j = 0;	j <= maxprice; ++j) {
        dp[0][j] = 0;
    }
	// construim matricea
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= maxprice; ++j) {
			// elementul curent primeste elementul anterior
    	    dp[i][j] = dp[i - 1][j];
			// daca pretul felului curent nu depaseste limita
            if (j - p[i - 1] >= 0) {
				// calculam solutia auxiliara unde adunam la valoarea anterioara
				// suma notelor si pastram maximul dintre elementul curent si
				// si solutia auxiliara
                int sol_aux = dp[i - 1][j - p[i - 1]] + grade_sum[i - 1];
                dp[i][j] = max(dp[i][j], sol_aux);
            }
        }
    }
    return dp[m][maxprice];
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	int maxprice = x * n;
	// se calculeaza suma notelor
	vector <long long > grade_sum(m, 0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			grade_sum[i] = grade_sum[i] + g[j][i];
    vector< vector<int> > dp(m + 1, vector<int>(maxprice+ 1, 0));
    for (int j = 0; j <= maxprice; ++j) {
        dp[0][j] = 0;
    }
	// idem ca la taskul 1
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= maxprice; ++ j) {
    	    dp[i][j] = dp[i-1][j];
			if(j - p[i - 1] >= 0) {
			 	 int sol_aux = dp[i-1][j - p[i-1]] + grade_sum[i-1];
        	     dp[i][j] = max(dp[i][j], sol_aux);
			}
			// daca mai poate fi adaugat acelasi fel de 2 ori
			// se va adauga cu suma notelor dublata
			if (j - 2 * p[i - 1] >= 0) {
                int sol_aux = dp[i-  1][j - 2 * p[i - 1]]
							+ 2 * grade_sum[i - 1];
                dp[i][j] = max(dp[i][j], sol_aux);
            }
        }
    }
    return dp[m][maxprice];
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	int maxprice = x * n;
	vector <long long > grade_sum(m, 0);
	// idem ca la taskurile anterioare
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			grade_sum[i] = grade_sum[i] + g[j][i];
	// mai adaugam o dimensiune matricei pentru a retine numarul
	// de feluri comandate
    vector< vector< vector<int> > > dp(m + 1, vector<vector<int>>(maxprice + 1,
										vector<int>(n + 1, 0)));
    for (int i = 0; i <= maxprice; ++i)
		for(int j = 0; j<= n; j++) {
        	dp[0][i][j] = 0;
		}

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= maxprice; ++ j)
			for(int k = 1; k <= n; ++k) {
				// initializam elementul curent cu elementul anterior
				dp[i][j][k] = dp[i - 1][j][k];
				if(j - p[i - 1] >= 0) {
					// in cazul in care adaugam o singura data un fel, adaugam
					// suma notelor la elementul care are cu un fel comandat
					// mai putin
					int sol_aux = dp[i - 1][j - p[i - 1]][k - 1] + grade_sum[i - 1];
					dp[i][j][k] = max(dp[i][j][k], sol_aux);
				}
				if (j - 2 * p[i - 1] >= 0) {
					if(k > 1) {
						// in cazul in care adaugam de doua ori un fel, adaugam
						// suma notelor la elementul care are cu 2 feluri comandate
						// mai putin
						int sol_aux = dp[i-1][j - 2 * p[i - 1]][k - 2] + 2 * grade_sum[i - 1];
						dp[i][j][k] = max(dp[i][j][k], sol_aux);
					}
				}
        }
    }
    return dp[m][maxprice][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);
	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
