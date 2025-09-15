#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

void resolver(vector<vector<int> > costes , int N){
    vector<vector<int> > m(N, vector<int>(N, 0));
    int i = 0;
    int j = 1;
    while (i < N - 1 && j < N){
        m[i][j] = costes[i][0];
        j++;
        i++;
    }

    i = 0;
    j = 2;

    while (j < N){
        int aux = j + 1;
        while (i < N - 1 && j - i - 1 < N - 1 && j < N){
            int minimo = costes[i][j - i - 1];
            for (int k = i + 1; k < j; ++k){
                minimo = min(minimo, m[i][k] + m[k][j]);
            }
            m[i][j] = minimo;
            i++;
            j++;
        }
        j = aux;
        i = 0;
    }

    for (int p = 0; p < N; ++p){
        for (int q = p + 1; q < N; ++q){
            cout << m[p][q] << ' ';
        }
        cout << '\n';
    }
}



bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;

    vector<vector<int> > costes(N - 1, vector<int>(N - 1, 0));
    for (int i = 0; i < N - 1; ++i){
        for (int j = 0; j < N - 1 - i; ++j){
            cin >> costes[i][j];
        }
    }

    resolver(costes, N);

    return true;
}

int main() {
    while (resuelveCaso()); 
    return 0;
}