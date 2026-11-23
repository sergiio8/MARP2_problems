#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;


void resolver(vector<vector<int> > v, int N){
    vector<vector<int> > sol(N, vector<int>(N));
    for (int j = 0; j < N; ++j) sol[0][j] = v[0][j];

    for (int i = 1; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (j == 0){
                sol[i][j] = v[i][j] + max(sol[i - 1][j], sol[i - 1][j + 1]);
            }
            else if (j == N - 1){
                sol[i][j] = v[i][j] + max(sol[i - 1][j], sol[i - 1][j - 1]);
            }
            else {
                sol[i][j] = v[i][j] + max(sol[i - 1][j - 1], max(sol[i - 1][j], sol[i - 1][j + 1]));
            }
        }
    }

    int max = sol[N - 1][0];
    int ind = 0;
    for (int j = 1; j < N; ++j){
        if (sol[N - 1][j] > max) {
            max = sol[N - 1][j];
            ind = j;
        }
    }

    cout << max << ' ' << ind + 1 << '\n';
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (!cin) return false;

    vector<vector<int> > v(N, vector<int>(N));

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cin >> v[i][j];
        }
    }
    

    resolver(v, N);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}