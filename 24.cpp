#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;


int resolver(vector<int> trozos, int N){
    vector<vector<int> > m(N, vector<int>(N));

    int i = 0;
    int j = 1;
    while (j < N){
        if (trozos[i] == trozos[j] && trozos[i] != 0) m[i][j] = 1;
        else m[i][j] = 0;
        i++;
        j++;
    }

    i = 0;
    j = 2;
    while (j < N){
        int aux = j;
        while (j < N){
            if (trozos[i] == trozos[j] && trozos[i] != 0){
                if (trozos[i] == trozos[i + 1] && trozos[i] != 0){
                    if (trozos[j] == trozos[j - 1] && trozos[j] != 0){
                        m[i][j] = 1 + max(m[i + 1][j - 1], max(m[i + 2][j], m[i][j - 2]));
                    }
                    else{
                        m[i][j] = max(1 + m[i + 1][j - 1], max(1 + m[i + 2][j], m[i][j - 2]));
                    }
                }
                else{
                    if (trozos[j] == trozos[j - 1] && trozos[j] != 0){
                        m[i][j] = max(1 + m[i + 1][j - 1], max(m[i + 2][j], 1 + m[i][j - 2]));
                    }
                    else{
                        m[i][j] = max(1 + m[i + 1][j - 1], max(m[i + 2][j], m[i][j - 2]));
                    }
                }
            }
            else{
                if (trozos[i] == trozos[i + 1] && trozos[i] != 0){
                    if (trozos[j] == trozos[j - 1] && trozos[j] != 0){
                        m[i][j] = max(m[i + 1][j - 1], 1 + max(m[i + 2][j],m[i][j - 2]));
                    }
                    else{
                        m[i][j] = max(m[i + 1][j - 1], max(1 + m[i + 2][j], m[i][j - 2]));
                    }
                }
                else{
                    if (trozos[j] == trozos[j - 1] && trozos[j] != 0){
                        m[i][j] = max(m[i + 1][j - 1], max(m[i + 2][j], 1 + m[i][j - 2]));
                    }
                    else{
                        m[i][j] = max(m[i + 1][j - 1], max(m[i + 2][j], m[i][j - 2]));
                    }
                }

            }
            i++;
            j++; 
        }
        i = 0;
        j = aux + 1;
    }
    return m[0][N - 1];
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;
    vector<int> trozos(N);
    for (int i = 0; i < N; ++i) cin >> trozos[i];

    cout << resolver(trozos, N) << '\n';

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}