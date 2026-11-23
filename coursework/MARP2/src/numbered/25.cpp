#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

struct tFestival {
    int precio;
    int artistas;
};

int resolver(vector<tFestival> festivales , int N, int P){
    vector<vector<int> > m(N, vector<int>(P + 1));
    int i = 0;
    for (int j = festivales[0].precio; j <= P;++j) m[i][j] = festivales[0].artistas;

    for (int i = 1; i < N; ++i){
        for (int j = 0; j <= P; ++j){
            if (j >= festivales[i].precio){
                m[i][j] = max(m[i - 1][j], m[i - 1][j - festivales[i].precio] + festivales[i].artistas);
            }
            else m[i][j] = m[i - 1][j];
        }
    }

    return m[N - 1][P];
}



bool resuelveCaso() {
    int P, N;
    cin >> P >> N;
    if (!cin) return false;
    vector<tFestival> festivales(N);
    for (int i = 0; i < N; ++i) {
        cin >> festivales[i].artistas >> festivales[i].precio;
    }

    cout << resolver(festivales, N, P) << '\n';

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}