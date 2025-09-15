#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;


void resolver(vector<vector<int> > tablero, int N){
    vector<vector<int> > sol(N, vector<int>(N));

    sol[N - 1][N - 1] = tablero[N - 1][N - 1];

    for (int i = 3; i >= 0; --i){
        for (int j = N - 1; j >= 0; --j){
            if (j + 2 < N){
                sol[i][j] = max(tablero[i][j] + sol[i][j + 2], tablero)
            }
        }
    }

    


}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (!cin) return false;

    vector<vector<int> > tablero(4, vector<int>(N));

    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < N; ++j){
            cin >> tablero[i][j];
        }
    }

    

    resolver(tablero, N);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}