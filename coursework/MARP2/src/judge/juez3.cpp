#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;


void resolver(vector<vector<char> > v, int N, int M){
    vector<vector<int> > sol(N, vector<int>(M));
    sol[N - 1][M - 1] = 1;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            if (!(i == N - 1 && j == M - 1)) sol[i][j] = 0;
        }
    }

    for (int i = N - 1; i >= 0; --i){
        for (int j = M - 1; j >= 0; --j){
            if (v[i][j] == '.'){
                if (i + 1 < N && j + 1 < M){
                    if (v[i + 1][j] != 'X' && v[i][j + 1] != 'X') sol[i][j] += sol[i + 1][j] + sol[i][j + 1];
                    else if (v[i + 1][j] != 'X' && v[i][j + 1] == 'X') sol[i][j] += sol[i + 1][j];
                    else if (v[i + 1][j] == 'X' && v[i][j + 1] != 'X') sol[i][j] += sol[i][j + 1];
                }
                else if (i + 1 < N && j + 1 >= M){
                    if (v[i + 1][j] != 'X') sol[i][j] += sol[i + 1][j];
                }
                else if (i + 1 >= N && j + 1 < M) {
                    if (v[i][j + 1] != 'X') sol[i][j] += sol[i][j + 1];
                }
            }
        }
    }

    /*for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            cout << sol[i][j] << ' ';
        }
        cout << endl;
    }*/


    cout << sol[0][0] << '\n';
}

bool resuelveCaso() {
    int N, M;
    cin >> N >> M;

    if (!cin) return false;

    vector<vector<char> > v(N, vector<char>(M));

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