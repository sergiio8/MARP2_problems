#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;


void resolver(vector<vector<long long int> > v, int N, int M){
    vector<vector<long long int> > sol(N, vector<long long int>(M));
    sol[N - 1][M - 1] = 1;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            if (i != N - 1 && j != M - 1) sol[i][j] = 0;
        }
    }

    for (int i = N - 1; i >= 0; --i){
        for (int j = M - 1; j >= 0; --j){
            if (!(i == N - 1 && j == M - 1)){
                if (i + v[i][j] < N && j + v[i][j] < M) sol[i][j] += sol[i + v[i][j]][j] + sol[i][j + v[i][j]];
                else if (i + v[i][j] < N && j + v[i][j] >= M) sol[i][j] += sol[i + v[i][j]][j];
                else if (i + v[i][j] >= N && j + v[i][j] < M) sol[i][j] += sol[i][j + v[i][j]];
            }
        }
    }

    cout << sol[0][0] << '\n';
}

bool resuelveCaso() {
    int N, M;
    cin >> N >> M;

    if (!cin) return false;

    vector<vector<long long int> > v(N, vector<long long int>(M));

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            cin >> v[i][j];
        }
    }
    

    resolver(v, N, M);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}